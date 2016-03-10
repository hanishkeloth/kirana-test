<?php
/**
 * @file
 * Rules integration for the persistent dismissable messages module.
 */

/**
 * Implements hook_rules_action_info().
 */
function pdm_rules_action_info() {
  return array(
    'pdm_message' => array(
      'label' => t('Show a persistent message on the site'),
      'group' => t('System'),
      'parameter' => array(
        'message' => array(
          'type' => 'text',
          'label' => t('Message'),
          'sanitize' => TRUE,
          'translatable' => TRUE,
        ),
        'type' => array(
          'type' => 'token',
          'label' => t('Message type'),
          'options list' => 'rules_action_drupal_message_types',
          'default value' => 'status',
          'optional' => TRUE,
        ),
        'pdm_type' => array(
          'type' => 'text',
          'label' => t('Persistent Message type'),
          'description' => t('This is a custom setting where you can enter any string you wish. It\'s function is identical to the first parameter of the watchdog() function.'),
          'optional' => TRUE,
        ),
        'repeat' => array(
          'type' => 'boolean',
          'label' => t('Repeat message'),
          'description' => t("If disabled and the message has been already shown, then the message won't be repeated."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
        'persist' => array(
          'type' => 'boolean',
          'label' => t('Persist message'),
          'description' => t("If enabled, the message is saved to the database and will show until dismissed, or it expires."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
        'persist_count' => array(
          'type' => 'integer',
          'label' => t('Persist count'),
          'description' => t("If set to a value greater than 0 the message will display only for the number of times set and then expire."),
          'default value' => 0,
          'optional' => TRUE,
        ),
        'persist_time' => array(
          'type' => 'integer',
          'label' => t('Persist time'),
          'description' => t("If set to a value greater than 0 the message will display for that many seconds from when it was created."),
          'default value' => 0,
          'optional' => TRUE,
        ),
        'dismissable' => array(
          'type' => 'boolean',
          'label' => t('Dismissable'),
          'description' => t("If enabled, the message can be dismissed otherwise the message will display until it expires by some other means (time or count)."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
        'dismiss_time' => array(
          'type' => 'integer',
          'label' => t('Dismiss time'),
          'description' => t("If enabled, the message will only be suppressed for the number of seconds specified if it is dismissed by a user. After that it will reappear."),
          'default value' => 0,
          'optional' => TRUE,
        ),
        'dismiss_type' => array(
          'type' => 'boolean',
          'label' => t('Dismiss Type'),
          'description' => t("This setting determines whether or not the message can be permanently dismissed. If disabled, it will cause the message to not reappear even if another persitable message is created with the same message again."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
        'paths' => array(
          'type' => 'text',
          'label' => t('Paths'),
          'description' => t('A standard list of paths (just like the blocks page display settings) where you can list a series of paths separated by a new line and with * as a wildcard. Setting this parameter will cause the persistent to only show on the paths specified.'),
          'optional' => TRUE,
        ),
        'disable_ajax' => array(
          'type' => 'boolean',
          'label' => t('Disable Ajax'),
          'description' => t("Restrict this pdm from being displayed inside of a modal, or content powered by an AJAX callback."),
          'default value' => TRUE,
          'optional' => TRUE,
          'restriction' => 'input',
        ),
        'user' => array(
          'type' => 'user',
          'label' => t('User'),
          'description' => t('The user that this message should be shown to, defaults to the logged in user.'),
          'optional' => TRUE,
        ),

      ),
      'base' => 'pdm_action_pdm_message',
      'access callback' => 'rules_system_integration_access',
    ),
  );
}

/**
 * Action: Show a PDM message.
 */
function pdm_action_pdm_message($message, $type, $pdm_type, $repeat, $persist, $persist_count, $persist_time, $dismissable, $dismiss_time, $dismiss_type, $paths, $disable_ajax, $user) {

  if (!empty($user)) {
    $uid = $user->uid;
  } else {
    $uid = NULL;
  }

  $options = array(
    'type' => $type,
    'pdm_type' => $pdm_type,
    'repeat' => $repeat,
    'persist' => $persist,
    'persist_count' => $persist_count,
    'persist_time' => $persist_time,
    'dismissable' => $dismissable,
    'dissmiss_time' => $dismiss_time,
    'dissmiss_type' => $dismiss_type,
    'paths' => $paths,
    'disable_ajax' => $disable_ajax,
    'uid' => $uid,
  );
  pdm_create_message(filter_xss_admin($message), $options);
}