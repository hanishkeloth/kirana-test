<?php
/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances.
 */

/**
 * Implementation of hook_menu().
 */
function _deeplink_workflow_menu() {
  return array(
      /*
    'deeplink/%deeplink' => array(
      'title callback' => 'deeplink_workflow_title',
      'title arguments' => array(1),
      'page callback' => 'deeplink',
      'page arguments' => array(1),
      'access callback' => 'deeplink_workflow_access',
      'access arguments' => array(1),
      'file' => 'deeplink.pages.inc',
      'type' => MENU_CALLBACK,
    ),
    */
    'admin/config/deeplink/workflow' => array(
      'title' => 'Workflow',
      'description' => 'Set-up the various configuration settings for the Deeplink Workflow module.',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('deeplink_workflow_settings'),
      'access arguments' => array('administer deeplink workflow configuration'),
      'file' => 'deeplink_workflow.admin.inc',
      'type' => MENU_LOCAL_ACTION,
    ),
  );
}

/**
 * Implementation of hook_theme().
 */
function _deeplink_workflow_theme() {
  return array(
    'deeplink' => array(
      'arguments' => array('deeplink' => NULL, 'style' => 'short'),
      'file' => 'deeplink.themes.inc',
    ),
  );
}

