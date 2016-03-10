<?php
function _services_collection_resource_myroom($fn, $uid, $bid, $bname) {

  // Check for mad values
  $uid = intval($uid);
  $bid = $bid;
  //$bname = intval($bname);
  return
services_collection_find_myroom_items($uid,$bid,$bname);
}
function services_collection_find_myroom_items($uid, $bid, $bname) {
  global $user;
    if (arg(1)) {
        $acc = user_load(arg(1));
    } else {
        return '';
    }
    

 $bbid = db_select('pinboard_boards')->fields('pinboard_boards', array('uid'))
        ->condition('uid', $user->uid, '=')->condition('bid', $bid, '=')->execute()->fetchCol();
if ($user->uid) {  

if (isset($bid) and $bid ) {
    db_update('pinboard_boards')
      ->condition('bid', $bid)
      ->fields(array(
    	  'uid' => $bbid,
    	  'name' => $bname,
    	  'data' => ''
  	  ))
      ->execute();
    drupal_set_message("hello success");
    //$bid = $form_state['values']['bid'];
    $bp = new stdClass;
    $bp->bid = $bid;
    $bp->uid = $bbid;
    $bp->name = $bname;
    $bp->username = 'admin';
    pinboard_helper_pathauto_update_alias($bp, 'update');

   return "Successfully updated board";
 }
 
}else{
 return "Access Denied";
}

}
function _services_collectiond_resource_myroom($fn, $uid, $bid, $bname) {

  // Check for mad values
  $uid = intval($uid);
  $bid = $bid;
   $bname = $bname;
  return
services_collectiond_find_myroom_items($uid,$bid);
}
function services_collectiond_find_myroom_items($uid, $bid, $bname) {
  global $user;
    if (arg(1)) {
        $acc = user_load(arg(1));
    } else {
        return '';
    }
     $bbid = db_select('pinboard_boards')->fields('pinboard_boards', array('uid'))
        ->condition('uid', $user->uid, '=')->condition('bid', $bid, '=')->execute()->fetchCol();
    
if ($user->uid) {    
$result = db_select('pinboard_repins', 'r')
    ->fields('r', array('nid'))
    ->condition('bid', $bid, '=')
    ->execute()->fetchCol();
  node_delete_multiple($result);
  db_delete('pinboard_boards')->condition('bid', $bid, '=')->execute();
  db_delete('pinboard_userboard')->condition('bid', $bid, '=')->execute();
  db_delete('pinboard_accessboard')->condition('bid', $bid, '=')->execute();
  $bp = new stdClass;
  $bp->bid = $bid;
  $bp->uid =$bbid;
  pinboard_helper_pathauto_delete($bp);
  //drupal_set_message("success");
  //watchdog('taxonomy', 'Deleted board %name.', array('%name' => $form_state['values']['name']), WATCHDOG_NOTICE);

  
 return "Successfully deleted board";

}else
{

 return "Access Denied";

}

}