<?php

function intel_og_admin_config_form($form, $form_state) {
  $entity_info = entity_get_info();

  $options = array();
  foreach ($entity_info AS $key => $value) {
    $options[$key] = $value['label'];
  }
  $form['intel_og_default_group_type'] = array(
    '#type' => 'select',
    '#title' => t('Default group entity type'),
    '#options' => $options,
    '#default_value' => variable_get('intel_og_default_group_type', 'node'),
    '#description' => t('Enter the default group entity type for intelligence to use for reporting.'),
  );

  return system_settings_form($form);
}

function intel_og_admin_page($group_type, $gid, $options) {
  og_set_breadcrumb($group_type, $gid, array(l(t('Intel'), "$group_type/$gid/intel")));

  $output = array();
  $output[] = array(
    '#markup' => '<h3>' . t('Reports') . '</h3>',
  );
  $items = array();
  $items[] = l(t('Dashboard'), current_path() . '/analytics/dashboard');
  $items[] = l(t('Scorecard'), current_path() . '/analytics/scorecard');
  $output[]  = array(
    '#theme' => 'item_list',
    '#items' => $items,
  );


  $output[] = array(
    '#markup' => '<h3>' . t('People') . '</h3>',
  );
  $items = array();
  $items[] = l(t('Contacts'), current_path() . '/people/contacts');
  $items[] = l(t('Submissions'), current_path() . '/people/submissions');
  $output[]  = array(
    '#theme' => 'item_list',
    '#items' => $items,
  );
  
  return $output;
}

function intel_og_admin_people_contacts($group_type, $gid) {
  include_once drupal_get_path('module', 'intel') . '/admin/intel.admin_visitor.inc';
  // call the standard intel_admin_listing, contacts are filtered by group using
  // hook_query_alter
  return intel_admin_people_contacts();
}

function intel_og_admin_people_submissions($group_type, $gid) {
  include_once drupal_get_path('module', 'intel') . '/admin/intel.admin_submission.inc';
  // call the standard intel_admin_listing, contacts are filtered by group using
  // hook_query_alter
  return intel_admin_people_submissions();
}