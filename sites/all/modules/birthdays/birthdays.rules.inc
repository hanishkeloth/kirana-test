<?php

/**
 * @file
 * Birthdays module - Rules support
 */


/**
 * Implements hook_rules_event_info().
 */
function birthdays_rules_event_info() {
  $info = array();
  $info['birthdays_current'] = array(
    'group' => t('Birthdays'),
    'label' => t('Current birthdays'),
    'help' => t('Current birthdays'),
    'variables' => array(
      'account' => array(
        'type' => 'user',
        'label' => t('User with birthdays'),
        'bundle' => 'user',
      ),
    ),
    'access callback' => 'rules_user_integration_access',
  );
  return $info;
}
