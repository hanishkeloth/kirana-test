<?php

/* Cron to run for personalization hashtags */

/**
 * Calculate Colorbias for the Color hashtags
 * Formula : colorbias = min((Number of Wish IDs of that color)/(Avg number of Wish IDs per color),1)
 */

function calculate_hashtags_colorbias() {
  //Get the count of all wishes/blogs/expression with published status
  $query = db_select('node','n')
  ->condition('n.type',array('pin','blog','expression'),'IN')
  ->condition('n.status',1,'=');
  $alias = $query->addExpression('COUNT(nid)','total_count');
  $total_contents_count = $query->execute()->fetchField();

  //Fetch all the Color terms tid and get the No. of wishes for each color
  $color_vocabulary = taxonomy_vocabulary_machine_name_load('color');
  $color_terms = taxonomy_get_tree($color_vocabulary->vid);
  $total_color_terms = sizeof($color_terms);

  //Calculate Avg number of #IDs per color
  $color_avg = $total_contents_count/$total_color_terms;
  $color = array();
  $color_bias = '';
  foreach($color_terms as $term) {
    //Fetch all the nodes attached to a color
    $all_contents = taxonomy_select_nodes($term->tid,FALSE);
    if(!empty($all_contents)){
      $total_color_contents = sizeof($all_contents);

      //Calculate Colorbias for each color
      $colorbias = round(max(($total_color_contents/$color_avg),1),2);
    } else {
      $colorbias = 0;
    }

    db_merge('color_weight')
     ->key(array('color_id'=>$term->tid))
      ->fields(array(
      'color_id' => $term->tid,
      'color_weight' => $colorbias,
      ))
    ->execute();
  }
}

/**
 * Function to calculate Ageing equation for the hashtags activities
 */

function _calculate_ageing_equation($uid){
  $current_week = strtotime(date("Y-m-d",strtotime("-1 week")));
  $ageing = 0.9775;
  $query = db_select('users_sessions_tracking','ust')
    ->condition('ust.timestamp',$current_week,'>=')
    ->condition('ust.uid',$uid,'=');
  $alias = $query->addExpression('SUM(no_of_times_access)','no_of_times_access');
  $segment = $query->execute()->fetchField();
  if(empty($segment)){
    $ageing = 0.9886;
  } else if($segment > 1 && $segment <= 4){
    $ageing = 0.9775;
  } else if($segment > 4){
    $ageing=0.955;
  }
  return $ageing;
}


/**
 * Function to update the Hashtags weightage daily
 * Daily score of #ID = For all activity for that date Sum of (weightage * number of times activity is done)
 */
function _hashtag_daily_score_save(){
  $today = strtotime(date('Y-m-d'));
  //$today = strtotime(date("Y-m-d",strtotime("-1 day")));
  //Calculate Daily score of #ID
  $query = db_select('hashtags_activities','ht')
    ->fields('ht',array('user_id','hashtag_tid'))
    ->condition('ht.activity_date',$today,'=');
  $alias = $query->addExpression('sum(hashtag_weight*no_of_times)','daily_score');
  $query->groupby('ht.user_id')
  ->groupby('ht.hashtag_tid');
  $daily_score_list = $query->execute()->fetchAll();
  if(!empty($daily_score_list)){
    foreach ($daily_score_list as $daily_score => $value) {
      db_merge('hashtag_activities_daily_score')
        ->key(array('hashtag_tid'=>$value->hashtag_tid,'user_id'=>$value->user_id,'activity_date'=>$today))
        ->fields(array(
        'hashtag_tid' => $value->hashtag_tid,
        'user_id' => $value->user_id,
        'activity_date' => $today,
        'daily_score' => $value->daily_score,
        ))
       ->execute();
    }

    //Calculate cumulative score of hash id based on the daily score
    _calculate_cumulative_score();
    //_calculate_approx_ids();
  }
}

function _calculate_cumulative_score() {
  $today = strtotime(date('Y-m-d'));
  $daily_score_query = db_select("hashtag_activities_daily_score",'ds')
    ->fields('ds',array('hashtag_tid','user_id','activity_date','daily_score'));
  $daily_score_query->groupby('user_id')
  ->groupBy('hashtag_tid')
  ->groupBy('activity_date')
  ->orderBy('activity_date','DESC');
   $daily_score_list = $daily_score_query->execute()->fetchAll();
  if(!empty($daily_score_list)){
    //Caculate Cumulative score for each hashtag and user id

    foreach ($daily_score_list as $daily_score => $daily_score_value) {
      //Get ageing for each user for a week
      $ageing = _calculate_ageing_equation($daily_score_value->user_id);

      //Interval between current day and activity day
      $interval = abs($today-$daily_score_value->activity_date)/60/60/24;
      $cumulative_score = ($daily_score_value->daily_score * pow($ageing,$interval));
      if(isset($final_cumulative_score[$daily_score_value->hashtag_tid][$daily_score_value->user_id])) {
        $final_cumulative_score[$daily_score_value->hashtag_tid][$daily_score_value->user_id] += $cumulative_score;
      } else {
        $final_cumulative_score[$daily_score_value->hashtag_tid][$daily_score_value->user_id] = $cumulative_score;
      }
    }
    foreach ($final_cumulative_score as $hashtag_key => $hashtag_value) {
        foreach ($hashtag_value as $user_key => $value) {
          db_merge('hashtag_activities_cumulative_score')
          ->key(array('hashtag_tid' => $hashtag_key,'user_id' => $user_key))
          ->fields(array(
            'hashtag_tid' => $hashtag_key,
            'user_id' => $user_key,
            'cumulative_score' => $value,
          ))
          ->execute();
        }
    }

    //Calculate approx. no. of Hashtag ids for each user based on the cumulative score
    _calculate_approx_ids();
  }
}

/**
 * Calculate approx. no. of Hashtag ids for each user
 *
 */
function _calculate_approx_ids() {

  $total_hashid_query = db_select('hashtag_activities_cumulative_score','cs')
    ->fields('cs',array('user_id'))
    ->groupBy('user_id');
  $alias = $total_hashid_query->addExpression('COUNT(hashtag_tid)','total_hashids');
  $total_hashids = $total_hashid_query->execute()->fetchAll();
  foreach ($total_hashids as $key => $value) {
    //echo "<pre>";print_r($value);

    //N = max(50,(total number of #IDs)/3)
    $approx_ids = max(50,($value->total_hashids)/3);
    //echo "N=".$approx_ids."<br>";

    //H = ((total number of #IDs - 10)/4)
    $each_quarter_val = floor(($value->total_hashids - 10)/4);
    ///echo "Quartile H=".floor($each_quarter_val)."<br>";

    if($each_quarter_val>10){
      //T1 =min((N-10)*.5,H)
      $quarter1 = min(($approx_ids - 10) * 0.5,floor($each_quarter_val));

       //T2 =min((N-10) *.25,H)
      $quarter2 = min(($approx_ids - 10) * 0.25,floor($each_quarter_val));

       //T3 =min((N-10) *.15,H)
      $quarter3 = min(($approx_ids - 10) * 0.15,floor($each_quarter_val));

       //T4 =min((N-10) *.1,H)
      $quarter4 = min(($approx_ids - 10) * 0.10,floor($each_quarter_val));
    }
    $top10_ids = db_select('hashtag_activities_cumulative_score','cs')
      ->fields('cs',array('hashtag_tid'))
      ->condition('cs.user_id',$value->user_id,'=')
      ->orderBy('cs.cumulative_score','DESC')
      ->range(0,10)
      ->execute()->fetchAll();
    foreach ($top10_ids as $top10 => $hashtag_id) {
      $hashtags_ids[$value->user_id][] = $hashtag_id->hashtag_tid;
    }


    if($each_quarter_val>10){
       $quartely_query = "(SELECT hashtag_tid FROM (SELECT hashtag_tid FROM hashtag_activities_cumulative_score WHERE user_id=".$value->user_id." ORDER BY cumulative_score DESC LIMIT 11,".floor($each_quarter_val).") Derived ORDER BY RAND() LIMIT ".floor($quarter1).")
          UNION ALL
          (SELECT hashtag_tid FROM (SELECT hashtag_tid FROM hashtag_activities_cumulative_score WHERE user_id=".$value->user_id." ORDER BY cumulative_score DESC LIMIT ".(11 + floor($each_quarter_val)).",".floor($each_quarter_val).") Derived ORDER BY RAND() LIMIT ".floor($quarter2).")
          UNION ALL
          (SELECT hashtag_tid FROM (SELECT hashtag_tid FROM hashtag_activities_cumulative_score WHERE user_id=".$value->user_id." ORDER BY cumulative_score DESC LIMIT ".(11 + (floor($each_quarter_val) * 2)).",".floor($each_quarter_val).") Derived ORDER BY RAND() LIMIT ".floor($quarter3).")
          UNION ALL
          (SELECT hashtag_tid FROM (SELECT hashtag_tid FROM hashtag_activities_cumulative_score WHERE user_id=".$value->user_id." ORDER BY cumulative_score DESC LIMIT ".(11 + (floor($each_quarter_val) * 3)).",".floor($each_quarter_val).") Derived ORDER BY RAND() LIMIT ".floor($quarter4).")";

      //echo $quartely_query;
      $quartely_hashtags = db_query($quartely_query)->fetchAll();
      foreach ($quartely_hashtags as $quarter_hashtag => $quarter_hashtag_value) {
        $hashtags_ids[$value->user_id][] = $quarter_hashtag_value->hashtag_tid;
      }
    }
  }

  if(!empty($hashtags_ids)){
    foreach ($hashtags_ids as $hashtag_user => $final_hashtag_ids) {
      foreach ($final_hashtag_ids as $hashtag_key => $hashtag_tid) {
          db_merge('user_hashtags')
          ->key(array('tid' => $hashtag_tid,'uid' => $hashtag_user))
          ->insertFields(array(
            'tid' => $hashtag_tid,
            'uid' => $hashtag_user,
          ))
          ->execute();
      }
    }
  }

}

