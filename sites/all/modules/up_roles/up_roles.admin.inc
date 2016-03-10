<?php
// $Id$

function up_roles_select_form(){
  // exclude anonymous user
  $up_roles_selectable_roles = user_roles(TRUE);
  // remove authenticated user
  unset($up_roles_selectable_roles[DRUPAL_AUTHENTICATED_RID]);
  ksort($up_roles_selectable_roles);
  $default_electable_roles =array(
  );
  $default_electable_roles =variable_get('up_roles_selectable_roles', array());
  $form['tips'] = array(
    '#type' => 'markup',
    '#value' => t('注意：取消对某个复选框的选中，将会从数据库中删除相关的记录.'),
  );
  $form['up_roles_selectable_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('选择积分相关角色'), 
    //'#default_value' => variable_get('up_roles_selectable_roles', array()),
    '#default_value' => $default_electable_roles,
    '#options' => $up_roles_selectable_roles,
    '#description' => t('请选择与积分相关联对应的用户角色.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('提交'),
  );
	return $form;

}
/*
function up_roles_select_form_validate(){

}
*/

function up_roles_select_form_submit($form, &$form_state){
  $sql = '';
  $result = db_query('SELECT rid FROM {userpoints_roles} ORDER BY rid');
  $current_roles = array_filter($form_state['values']['up_roles_selectable_roles']);
  //$current_roles = 
  $old_roles =array();
  foreach ($result as $role) {
		
    if(in_array($role->rid,$current_roles)){
      $old_roles[] = $role->rid;
    }else{
      db_query('DELETE FROM {userpoints_roles} WHERE rid = :rid', array(':rid' => $role->rid));
    }
  }
	
  foreach($current_roles as $current_role){
    if(in_array($current_role,$old_roles)){
      //数据库中已存在,不需要更新
    }else{
      db_query('INSERT INTO {userpoints_roles} (rid,low,high) VALUES (:rid, :low, :high)', array(':rid'=>$current_role, ':low' => 0, ':high' => -1));
    }
  } 
  variable_set('up_roles_selectable_roles', $current_roles);
  //variable_get('up_roles_selectable_roles', $form_state['values']['up_roles_selectable_roles']);
}

function up_roles_list_page(){
  $output ="";
  $sql = "SELECT ur.*, r.name FROM {userpoints_roles} ur LEFT JOIN {role} r ON ur.rid = r.rid ORDER BY ur.rid";
  $header = array("角色","最低分限制","最高分限制","编辑");
  $ta = array('id' => 'my-table', 'align' => 'center');
  $result = db_query($sql);
  $trows = array();
  while($data = $result->fetchObject()){
    $trows[] = array(
      array('data'=>$data->name,'valign'=>'top'),
      array('data'=>$data->low,'valign'=>'top'),
      array('data'=>$data->high,'valign'=>'top'),
      array('data'=>l(t('编辑'),'admin/config/people/userpointsroles/config/'.$data->rid),'valign'=>'top'),		
    );
  }
  $output .="下面为用户角色与积分对应表，初始化配置为(0,-1),请完成对角色最低积分限制，最高积分限制的配置工作";
  $output .= theme('table', array('header' =>$header, 'rows' => $trows));
  
  return $output;
}
function up_roles_config_page($rid){
  if($rid < 2){
    drupal_set_message('无效的角色ID');
    drupal_goto('admin/config/people/userpointsroles/list');
  }
  $sql = "SELECT ur.*, r.name FROM {userpoints_roles} ur LEFT JOIN {role} r ON ur.rid = r.rid WHERE ur.rid = :rid";
  $result = db_query($sql,array(':rid' => $rid));
  $current_role = $result->fetchObject();
  if(empty($current_role)){
    drupal_set_message('无效的角色ID');
    drupal_goto('admin/config/people/userpointsroles/list');
  }
  $output = "";
  $output .= t('当前角色：').$current_role->name;
  $output .= t("<p><strong>注意</strong>：当前角色的最低积分限制必须大于前一角色的最高积分限制</p>");
  $output .= t("<p><strong>注意</strong>：当前角色的最高积分限制必须大于当前角色的最低积分限制</p>");
  $up_roles_config_form = drupal_get_form('up_roles_config_form',$current_role);
  $output .= drupal_render($up_roles_config_form);
  return $output;
	
}
function up_roles_config_form($form, &$form_state, $role= NULL){

  $form['rid'] = array(
    '#type' => 'value',
    '#value' => $role->rid,
  );
  $form['low'] = array(
    '#type' => 'textfield',
    '#title' => t('积分最低限制'), 
    '#default_value' => $role->low,
  );
  $form['high'] = array(
    '#type' => 'textfield',
    '#title' => t('积分最高限制'), 
    '#default_value' => $role->high,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

function up_roles_config_form_validate($form, &$form_state){
  if($form_state['values']['low'] >= $form_state['values']['high']){
    form_set_error('low',t('积分最低限制不能大于等于积分最高限制').$form_state['values']['low'].":".$form_state['values']['high']);
  }
  $sql = "SELECT * FROM {userpoints_roles} WHERE rid < :rid ORDER BY rid DESC";
  $previous_role = db_query($sql, array(':rid' => $form_state['values']['rid']))->fetchObject();
  if(!empty($previous_role) && $form_state['values']['low'] <= $previous_role->high){
    form_set_error('low',t('本角色积分最低限制必须大于上一角色积分最低限制：@previous_role_high',array('@previous_role_high'=>$previous_role->high)));
  }
}

function up_roles_config_form_submit($form, &$form_state){
  $sql = 'UPDATE {userpoints_roles} SET low = :low, high = :high WHERE rid = :rid';
  $result = db_query($sql,array(':low' => $form_state['values']['low'], ':high' => $form_state['values']['high'], ':rid' => $form_state['values']['rid']));
  drupal_set_message('编辑完成');
  drupal_goto('admin/config/people/userpointsroles/list');
}