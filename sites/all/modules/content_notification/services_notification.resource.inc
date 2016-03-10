<?php
function services_notifications_retrieve($user_id, $offset=0, $limit=10) {
	module_load_include('module', 'push_notification', 'push_notification');
	$query = db_select('content_notification','cn')
        ->fields('cn', array('notify_id','read_status','created','noty_message','entity_id','entity_type','sent_uid'))
        ->condition('received_uid',$user_id)
		->orderBy('created', 'DESC');
    $result = $query->execute()->fetchAll();
    $user_notifications = array();
	$i=0;
    foreach($result as $record){
        $user_notifications[$i] = $record;
		if($record->entity_type == 'follow'){
			$entity_id = $record->sent_uid;
		}else{
			$entity_id = $record->entity_id;
		}
		$user_notifications[$i]->image = _get_profile_content_images($record->entity_type, $entity_id);
    $user_notifications[$i]->notification_type = 'user';
		$i++;
    }
	$push_notifications = _system_notifications_list();
  $system_notifications = array();
  $j=0;
  foreach ($push_notifications as $push_notify) {
    $system_notifications[$j] = $push_notify;
    $path = preg_replace('/\//','',parse_url($push_notify->link,PHP_URL_PATH),1);
    $url = explode("/", $path);
    if(!empty($url)){
      if($url[0] == 'search_results'){
        $search_keyword = str_replace("+"," ",$url[1]);
        $system_notifications[$j]->search = $search_keyword;
      } else {
        $org_path = drupal_lookup_path("source", $path);
        if(!empty($org_path)){
          $node = menu_get_object("node", 1, $org_path);
          if($node->type!='article' && $node->type!='blog'){
            $nid = $node->nid;
            $system_notifications[$j]->entity_id = $nid;
          }
        }
      }
    }
    $system_notifications[$j]->notification_type = 'system';
    $j++;
  }
	$notifications_list = array_merge($system_notifications,$user_notifications);
  $notifications = array_slice($notifications_list, $offset, $limit);
  return $notifications;
}

/**
 * Function to udpdate the notifications status through services
 */
function _update_notifications($notify_id, $notify_type='user', $user_id) {
  if($notify_type=='user'){
    $num_updated = db_update("content_notification")
       ->fields(array('read_status' => '1',))
       ->condition('notify_id', $notify_id, '=')
       ->condition('read_status', '0', '=')
       ->execute();
    if($num_updated>0){
      drupal_json_output($notify_id);
    } else {
      drupal_json_output('Update Failed');
    }
  } else {
    $status_update = db_insert("system_notification_read")
      ->fields(array(
        'notification_id' => $notify_id,
        'uid' => $user_id,
        'read_status' => 1,
      ))
      ->execute();
    if($num_updated>0){
      drupal_json_output($notify_id);
    } else {
      drupal_json_output('Update Failed');
    }
  }
}

/**
 * Retrieve notifications count for user
 */

function _notifications_resource_count_all($uid){
  module_load_include('module', 'push_notification', 'push_notification');
  $query = db_select('content_notification','cn')
        ->fields('cn', array('notify_id'))
        ->condition('received_uid',$uid)
        ->condition('read_status','0','=');
    $user_notifications = $query->execute()->rowCount();
    $push_notifications = _system_notifications_list();
    drupal_json_output($user_notifications + count($push_notifications));
    exit;
}

/**
 * Retrieve the user notification email status
 */
function _notifications_resource_email_status($uid){
  $user = user_load($uid);
  if(isset($user->field_notification_email['und'])){
    drupal_json_output($user->field_notification_email['und'][0]['value']);
  } else {
    drupal_json_output('0');
  }
  exit;
}

/**
 * Update user notification email status
 */
function _update_notifications_email_status($user_id,$status){
  $user = user_load($user_id);
  $edit = array(
    'field_notification_email' => array(
      'und' => array(
        0 => array(
          'value' => ($status),
        ),
      ),
    ),
  );

  user_save($user, $edit);
  return $user->field_notification_email['und'][0]['value'];
}

