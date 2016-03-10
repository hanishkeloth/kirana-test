<?php
/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances - controls.
 */

/**
 * Implementation of hook_controls_info().
 */
function deeplink_controls_info() {
  return array(
    'deeplink' => array(
      'deeplinkers' => array(
        'byuser' => array(
          'title' => t('Deeplink by user'),
          'description' => t('Select users to be sent a deeplink.'),
          'bypass login' => FALSE,
        ),
        'byemail' => array(
          'title' => t('Deeplink by email'),
          'description' => t('Select emails to be sent a deeplink.'),
          'bypass login' => TRUE,
        ),
      ),
    ),
  );
}

// ============= DEEPLINK BY USER ============= //

function deeplink_deeplinkers_byuser_deeplink_access($control, $args) {
  global $user;
  if ($user->uid == 1) {
    return TRUE;
  }
  if (is_array($args['deeplink']->data)) {
    return in_array($user->uid, $args['deeplink']->data);
  }
  return FALSE;
}

function deeplink_deeplinkers_byuser_node_view_form($deeplink, $args) {
  $users = array();
  $roles = implode(',', array_filter(variable_get(DEEPLINK_USER_ROLES, array(0))));
  // The db_rewrite_sql will ensure the query is filtered to only include
  // people from the same client(s) as the person issuing the deeplink
  $results = db_query(db_rewrite_sql('SELECT u.uid, u.name FROM {users} u
    INNER JOIN {users_roles} ur ON ur.uid=u.uid
    WHERE ur.rid IN (%s) AND u.uid!=%d ORDER BY u.name', 'u', 'uid'), $roles, $user->uid);

  while ($result = db_fetch_object($results)) {
    $users[$result->uid] = check_plain($result->name);
  }

  return array(
    '#type' => 'fieldset',
    '#title' => check_plain(t($deeplink['title'])),
    '#description' => filter_xss($deeplink['description']),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'users' => array(
      '#type' => 'checkboxes',
      '#title' => t('Select users'),
      '#options' => $users,
    ),
  );
}

function deeplink_deeplinkers_byuser_node_view_form_submit($deeplink, $values) {
  return array_filter($values['users']);
}

function deeplink_deeplinkers_byuser_notify_people($deeplink, $args) {
  global $language;
  extract($args);

  foreach ($people as $uid) {
    $params = array(
      'account' => user_load($uid),
      'subject' => $email_subject,
      'body' => $email_body,
      'entity_type' => $deeplink->entity_type,
      'entity' => $deeplink->entity,
      'deeplink' => $deeplink,
    );
    drupal_mail('deeplink', 'notify', $params['account']->mail, $language, $params);
  }
}

function deeplink_deeplinkers_byuser_included($deeplink, $args) {
  extract($args);
  if (is_array($data['users'])) {
    return in_array($account->uid, array_filter($data['users']));
  }
  return FALSE;
}


// ============= DEEPLINK BY EMAIL ============= //

function deeplink_deeplinkers_byemail_deeplink_access($control, $args) {
  // If they have the link they can get in.
  return TRUE;
}

function deeplink_deeplinkers_byemail_node_view_form($deeplink, $args) {

  return array(
    '#type' => 'fieldset',
    '#title' => check_plain(t($deeplink['title'])),
    '#description' => filter_xss($deeplink['description']),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    'emails' => array(
      '#type' => 'textarea',
      '#title' => t('Enter email addresses'),
      '#description' => t('Put each email on a single line, with no other punctuation or separators.'),
    ),
  );
}

function deeplink_deeplinkers_byemail_node_view_form_submit($deeplink, $values) {
  // split into separate emails
  $emails = preg_split("/[\s,]+/", $values['emails']);
  // and remove duplicates
  return array_flip(array_flip(array_filter($emails)));
}

function deeplink_deeplinkers_byemail_notify_people($deeplink, $args) {
  global $language;
  extract($args);

  foreach ($people as $email) {
    $params = array(
      'account' => (object) array('uid' => 999, 'name' => '', 'mail' => $email),
      'subject' => $email_subject,
      'body' => $email_body,
      'entity_type' => $deeplink->entity_type,
      'entity' => $deeplink->entity,
      'deeplink' => $deeplink,
    );
    drupal_mail('deeplink', 'notify', $params['account']->mail, $language, $params);
  }
}

function deeplink_deeplinkers_byemail_included($deeplink, $args) {
  return TRUE;
}
