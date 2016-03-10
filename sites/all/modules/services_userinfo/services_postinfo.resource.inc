
<?php

/**
* Callback function for my room info retrieve
*/
function _services_postinfo_resource($fn,$nid) {
  // Check for mad values
  $nid = intval($nid);
  return
services_postinfo_retreive_items($nid);
}
/**
* Gets My Room Info
*/
function services_postinfo_retreive_items($nid) {
print $nid;exit;
$node = node_load($nid);
		print_r($node);exit;
  		
  // Compose query
  global $user;
  if($user->uid) {
    if ($nid) { 
		$node = node_load($nid);
		print_r($node);exit;
  		$follower_uids = db_select('pinboard_follow','p')
            ->condition('p.aid', $uid);
        $follower_uids->addExpression('distinct(p.uid)');
        $follower_uids = $follower_uids->execute()->fetchCol();
		$result->uid = $uid;
        $result->name = $user->name;
		$result->Followers_items = $follower_uids;
		
		$following_uids = db_select('pinboard_follow','p')
            //->fields('p', array('uid'));
            ->condition('p.uid', $uid);
        $following_uids->addExpression('distinct(p.aid)');
        $following_uids = $following_uids->execute()->fetchCol();
		
		$result->Following_items = $following_uids;
		
		$vids = db_select('votingapi_vote', 'v');
		$vids->addExpression('COUNT(v.vote_id)','Star Count');
		$vids->condition('v.uid', $uid,'=');
		$vids = $vids->execute()->fetchCol();
		
		$result->StarCount = $vids[0];
		
		$qw = db_select('pinboard_boards', 'b');
		$qw->leftJoin('pinboard_accessboard', 'a', 'b.bid = a.bid');
   		$qw->fields('b',array('bid', 'name'));
		$qw->condition('b.uid',$uid); 
		$or = db_or()->condition('a.uid', $user->uid)->condition('a.uid');
		$qw->condition($or);
    	$result_qw1 = $qw->orderBy('name', 'ASC')->execute()->fetchAllKeyed();
		foreach ($result_qw1 as $k => $v) {

        $qw2 = db_select('pinboard_repins', 'r');
        $qw2->leftJoin('node', 'node', 'node.nid = r.nid');
        $qw2->addTag('node_access');
        $qw2->fields('r', array('nid'))->condition('r.bid', $k, '=')->orderBy('r.nid', 'DESC');
        $result2 = $qw2->execute()->fetchCol();
		
		$query = db_select('pinboard_repins', 'v');
		$query->leftJoin('node', 'node', 'node.nid = v.nid');
		$query->addTag('node_access');
		$query->addField('v', 'nid');
		$query->condition('v.bid',$k, '=');
		$query->orderRandom();
		$query->range(0, 6);
		$result_board_pins = $query->execute()->fetchCol();
		//if (count($result2)) {
			$result_qw[$k]=array('Collection_name' => $v,
								// 'Collection_url' => url('user/'.$uid.'/'.PINBOARD_REPLACE_PATH_BOARD.'/'.$k),
			                     'Collection_item_pins' => $result_board_pins);//'">'.$v.'('.count($result2).')';
			
		//}
		}
		$result->Collections = $result_qw;
		$user_pins = db_select('node', 'r')->addTag('node_access')
					->extend('PagerDefault')->fields('r', array('nid'))->condition('type', PINBOARD_REPLACE_PATH_PIN, '=')
						->condition('status', 1, '=')->condition('uid', $uid, '=')
						->orderBy('created', 'DESC')->limit(30)->execute()->fetchCol();
						
		$result->User_pins = $user_pins;
		return $result;
      }
	}
    else {
      // return '0';
	   return services_error(t('Anonymous user yields no result.'), 401);
    }
}
?>