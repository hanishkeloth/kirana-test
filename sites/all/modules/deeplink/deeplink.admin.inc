<?php
/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances - admin.
 */

/**
 * Form API menu callback
 */
function deeplink_settings() {
  $form = array();
  $form[DEEPLINK_DEFAULT_LINK] = array(
    '#type' => 'textfield',
    '#title' => t('Default prefix for deeplink links.'),
    '#description' => t('Select URI prefix used for deeplink links. You can use tokens as well.'),
    '#default_value' => deeplink_get_base_uri(),
  );

  $form[DEEPLINK_CONTENT_TYPES] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Select the content types that can be deeplinked to.'),
    '#options' => _node_types_build()->names,
    '#default_value' => variable_get(DEEPLINK_CONTENT_TYPES, array()),
  );

  $items = array();
  foreach (controls_get('deeplinkers') as $name => $control) {
    $items[$name] = $control['title'];
  }

  $form[DEEPLINK_ALLOWED_CONTROLS] = array(
    '#type' => 'checkboxes',
    '#title' => t('Deeplink types'),
    '#description' => t('Select which deeplink types are permitted, you have to have at least one. If you deselect one that was previously selected any existing deeplinks already sent out will function until they expire.'),
    '#options' => $items,
    '#default_value' => variable_get(DEEPLINK_ALLOWED_CONTROLS, array()),
    '#required' => TRUE,
  );

  $roles = user_roles();

  $form[DEEPLINK_USER_ROLES] = array(
    '#type' => 'checkboxes',
    '#title' => t('Send to roles'),
    '#description' => t('Select which roles can be sent deeplinks.'),
    '#options' => $roles,
    '#default_value' => variable_get(DEEPLINK_USER_ROLES, array()),
    // '#required' => TRUE,
  );

  $form[DEEPLINK_APPROVAL_TIME] = array(
    '#type' => 'textfield',
    '#title' => t('Available hours'),
    '#description' => t('Type the number of hours the deeplink will be available (by default) after which the deeplink will expire (type 0 for one-time login).'),
    '#default_value' => variable_get(DEEPLINK_APPROVAL_TIME, DEEPLINK_APPROVAL_TIME_DEFAULT),
  );

  $form[DEEPLINK_DEFAULT_PAGE_TITLE] = array(
    '#type' => 'textfield',
    '#title' => t('Override page title'),
    '#description' => t('This is the default page title when accessing page through the deeplink. Type (default) to use a default node title or leave it empty to remove completely.'),
    '#default_value' => variable_get(DEEPLINK_DEFAULT_PAGE_TITLE, '(default)'),
    '#required' => FALSE,
  );

  $form[DEEPLINK_DEFAULT_EMAIL_SUBJECT] = array(
    '#type' => 'textfield',
    '#title' => t('Notification email subject'),
    '#description' => t('This is the default email subject to use for notifying individuals about the deeplink. You can insert replacement [tokens] which are listed below, specialised tokens include [end_date] which is when the deeplink ceases to be available. Note that "user" tokens will not work if unregistered users are included in the notifications.'),
    '#default_value' => variable_get(DEEPLINK_DEFAULT_EMAIL_SUBJECT, DEEPLINK_DEFAULT_EMAIL_SUBJECT_CONTENT),
    '#required' => TRUE,
  );

  $form[DEEPLINK_DEFAULT_EMAIL_BODY] = array(
    '#type' => 'textarea',
    '#title' => t('Notification email body'),
    '#description' => t('This is the default email body to use for notifying individuals about the deeplink. You can insert replacement [tokens] which are listed below, specialised tokens include [end_date] which is when the deeplink ceases to be available. Note that "user" tokens will not work if unregistered users are included in the notifications.'),
    '#default_value' => variable_get(DEEPLINK_DEFAULT_EMAIL_BODY, DEEPLINK_DEFAULT_EMAIL_BODY_CONTENT),
    '#required' => TRUE,
  );

  $form['token_help'] = array(
    '#type' => 'fieldset',
    '#title' => t('Tokens'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    array('#value' =>  theme('token_help', 'deeplink')),
    array('#value' =>  theme('token_help', 'global')),
    array('#value' =>  theme('token_help', 'node')),
    array('#value' =>  theme('token_help', 'user')),
  );

  $form['deeplink_form'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['deeplink_form']['nid'] = array(
    '#type' => 'textfield',
    '#value' => '',
    '#submit' => array('Type Node ID for which you want to generate deeplink link.'),
  );

  $form['deeplink_form']['generate_deeplink'] = array(
    '#type' => 'submit',
    '#value' => t('Generate deeplink link'),
    '#submit' => array('deeplink_form_generate'),
  );

  $form['#submit'][] = 'deeplink_settings_submit';
  return system_settings_form($form);
}

/**
 * Implementation of custom submission handler (http://drupal.org/node/222158)
 */
function deeplink_settings_submit($form, &$form_state) {
  $v = $form_state['values'];
  $form_link = $v['deeplink_default_link'];
  $default_link = deeplink_get_base_uri();
  if ($form_link <> $default_link) {
    // when menu to deeplink has been change, rebuild the menu
    menu_rebuild();
  }
}

function deeplink_view(&$account) {
  global $user;
  $user = drupal_clone($user);

  $results = db_query('SELECT dlid FROM {deeplinks} WHERE expires > %d ORDER BY expires ASC', time());
  $deeplinks = array();
  while ($result = db_fetch_object($results)) {
    $deeplink = deeplink_load($result->dlid);
    $control = controls_get('deeplinkers', $deeplink->control);
    if (controls_callback('included', $control, array('data' => $deeplink->data, 'account' => $user))) {
      $deeplinks[$deeplink->dlid] = theme('deeplink', $deeplink);
    }
  }

  $account->content['deeplink'] = array(
    '#title' => t('Available deeplinks'),
    '#description' => t('These are the deeplinks to which you currently have access.'),
    '#type' => 'user_profile_category',
    'deeplink' => array(
      '#value' => empty($deeplinks) ? t('None') : theme('item_list', $deeplinks),
    ),
  );
}

/**
 * Form API submit callback
 * Generate deeplink link for specified node
 */
function deeplink_form_generate($form, &$form_state) {
  $v = $form_state['input'];
  $nid = $v['nid'];
  if ($node = node_load($nid)) {
    $uri = deeplink_generate_node_deeplink($node);
    drupal_set_message(t("Generated deeplink: <a href='!root!uri'>!uri</a> for node id: !nid", array('!root' => check_plain(base_path()), '!uri' => $uri, '!nid' => $nid)));
  }
  else {
    drupal_set_message(t("Cannot load the node id: '!nid'", array('!nid' => check_plain($nid))), 'error');
  }
}

