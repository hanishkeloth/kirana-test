<?php

/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances - admin.
 */

/*
function deeplink_workflow($deeplink) {
  $build = node_view($deeplink->entity, FALSE, TRUE, FALSE);
  return $build;
}
*/

function deeplink_workflow_node_view_deeplink(&$node) {
  // Check this is a content type for which we are permitting deeplinking
  if (!deeplink_workflow_valid_type($node->type)) {
    return;
  }
  $uri = deeplink_get_base_uri($node);
  $node->content['deeplink_workflow_form'] = (arg(0) == $uri) ? drupal_get_form('deeplink_workflow_node_view_form', $node) : NULL;
}

function deeplink_workflow_node_view_form($form_state, $build, $node) {
  // Scan to see if this user is allowed to issue the deeplinks and
  // that deeplinker is enabled; call the relevant deeplink control.
  $elements = array();
  $args = array('node' => &$node);
  $deeplinkers = array_filter(variable_get(DEEPLINK_ALLOWED_CONTROLS, array()));
  foreach (controls_get('deeplinkers') as $name => $deeplinker) {
    if (isset($deeplinkers[$name]) && deeplink_access_deeplinker($deeplinker)) {
      $elements[$name] = controls_callback('node_view_form', $deeplinker, $args);
    }
  }

  if (empty($elements)) {
    return;
  }
  
  $curr_sid = workflow_node_current_state($node); // get current workflow state
  $states = workflow_field_choices($node); // get restricted workflow states based on current user
  // $states = deeplink_workflow_get_states($node); // get all workflow states
  unset($states[$curr_sid]); // remove current workflow state from the list

  // Add the buttons.
  $form = array();
  $form['actions'] = array(
      '#type' => 'actions',
      '#weight' => '99',
      );
  foreach ($states as $sid => $state) {
    $state_name = variable_get('deeplink_workflow_state_use_alt_name', FALSE) ? end(explode('|', $state)) : $state;
    $form['actions']['deeplink_workflow_' . $sid] = array(
      '#type' => 'submit',
      '#access' => TRUE,
      '#value' => t($state_name),
      '#submit' => array('deeplink_workflow_form_submit'),
    );
  }
  deeplink_additions($node); // display additional message
  return $form;
}

function deeplink_workflow_form_submit($form, &$form_state) {
  $op = $form_state['values']['op'];
  $node = $form_state['build_info']['args'][0];
  $states = deeplink_workflow_get_states($node); // get all workflow states
  $sid_new = NULL;
  foreach ($states as $sid => $value) {
    $state_name = variable_get('deeplink_workflow_state_use_alt_name', FALSE) ? end(explode('|', $value)) : $value;
    if ($op == $state_name) {
      $sid_new = $sid;
      break;
    }
  }
  workflow_execute_transition($node, $sid_new);
}

/*
function _deeplink_workflow_node_view_form_validate($form, &$form_state) {
  foreach ($form_state['values']['deeplinks'] as $name => $values) {
    if ($deeplinker = controls_get('deeplinkers', $name)) {
      controls_callback('node_view_form_validate', $deeplinker, $values);
    }
  }
}

function _deeplink_workflow_node_view_form_submit($form, &$form_state) {
  //
}
*/

/*
 * Replace tokens into correct form in e-mail subject and body
 */
function deeplink_workflow_token_replace($text, $objects) {
  foreach ($objects as $type => $object) {
    $text = token_replace($text, array($type => $object));
  }
  return $text;
}

