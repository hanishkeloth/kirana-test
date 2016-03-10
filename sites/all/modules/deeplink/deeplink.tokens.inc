<?php
/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances.
 */

/**
 * Implementation of hook_token_info().
 */
function deeplink_token_info() {
  // All date types can share the same deeplink value type.

  // deeplink related values
  $type = array(
    'name' => t('Deeplink'),
    'description' => t('Tokens related to deeplink values.'),
    // 'needs-data' => 'node',
    'field-value' => TRUE,
  );
  $tokens['user-mail-firstname'] = array(
    'name' => t('User First Name'),
    'description' => t('Tries to breakdown the email address to produce a first name, or just outputs the username.'),
  );
  $tokens['user-mail-lastname'] = array(
    'name' => t('User Lastname'),
    'description' => t('Tries to breakdown the email address to produce a last name, or just outputs the username.'),
  );

  /*
  $tokens['types']['deeplink'] = array(
    'name' => t('Deeplink values'),
    'description' => t('Tokens related to deeplink values.'),
    'needs-data' => 'user',
    'field-value' => TRUE,
  );
  */
  $tokens['url-local'] = array(
    'name' => t('Local URL (URI)'),
    'description' => t('The local URL (no domain) for the supplied deeplink object."'),
  );
  $tokens['url-absolute'] = array(
    'name' => t('Absolute URL'),
    'description' => t('The absolute URL (with domain) for the supplied deeplink object.'),
  );
  $tokens['link-local'] = array(
    'name' => t('Title with local URL'),
    'description' => t('The object title wrapped in the local URL (no domain) link for the supplied deeplink object.'),
  );
  $tokens['link-absolute'] = array(
    'name' => t('Title with absolute URL'),
    'description' => t('The object title wrapped in the absolute URL (with domain) link for the supplied deeplink object.'),
  );
  $tokens['expires-small'] = array(
    'name' => t('Deeplink expire date (small)'),
    'description' => t('The date that the supplied deeplink expires formatted with the small format.'),
  );
  $tokens['expires-medium'] = array(
    'name' => t('Deeplink expire date (medium)'),
    'description' => t('The date that the supplied deeplink expires formatted with the medium format.'),
  );
  $tokens['expires-large'] = array(
    'name' => t('Deeplink expire date (large)'),
    'description' => t('The date that the supplied deeplink expires formatted with the large format.'),
  );
  $tokens['expires-stamp'] = array(
    'name' => t('Deeplink expire date (timestamp)'),
    'description' => t('The date that the supplied deeplink expires as a UNIX timestamp.'),
  );
  $tokens['expires-in'] = array(
    'name' => t('Deeplink expire datetime'),
    'description' => t('The days, minutes and hours to when the deeplink expires.'),
  );
  return array(
    'types' => array('deeplink' => $type),
    'tokens' => array('deeplink' => $tokens),
  );
}

/**
 * Implementation of hook_token_values().
 */
function deeplink_tokens($type, $tokens, $data, $options) {
  $values = array();
  if ($type == 'deeplink') {
    $object = current($data);
    foreach ($tokens as $name => $original) {
      if (!empty($object)) {
        if (!empty($object->mail)) {
          list($firstname, $lastname) = _deeplink_username($object);
          $name == 'user-firstname' ? $values[$original] = $firstname : NULL;
          $name == 'user-lastname'  ? $values[$original] = $lastname : NULL;
        }
        elseif (!empty($object->uid)) {
          list($firstname, $lastname) = _deeplink_username(user_load($object->uid));
          $name == 'user-firstname' ? $values[$original] = $firstname : NULL;
          $name == 'user-lastname'  ? $values[$original] = $lastname : NULL;
        }
      }

      if (!empty($object)) {
        $entity = node_load($object->entity_id);
        $uri = deeplink_get_base_uri($entity);
        $expires = ($object->expires == 0) ? time() : $object->expires;
        $title = 'title';
        $name == 'url-local'      ? $values[$original] = url("$uri/{$object->dlid}") : NULL;
        $name == 'url-absolute'   ? $values[$original] = url("$uri/{$object->dlid}", array('absolute' => TRUE)) : NULL;
        $name == 'link-local'     ? $values[$original] = l(check_plain($entity->$title), "$uri/{$object->dlid}") : NULL;
        $name == 'link-absolute'  ? $values[$original] = l(check_plain($entity->$title), "$uri/{$object->dlid}", array('absolute' => TRUE)) : NULL;
        $name == 'expires-small'  ? $values[$original] = format_date($expires, 'small') : NULL;
        $name == 'expires-medium' ? $values[$original] = format_date($expires, 'medium') : NULL;
        $name == 'expires-large'  ? $values[$original] = format_date($expires, 'large') : NULL;
        $name == 'expires-stamp'  ? $values[$original] = $expires : NULL;
        $name == 'expires-in'     ? $values[$original] = _deeplink_formatdatediff($expires) : NULL;
      } // end: if
    } // end: foreach
  } // end: if
  return $values;
}

function _deeplink_formatdatediff($start, $end = NULL) {
  if (!($start instanceof DateTime)) {
    $start = new DateTime(is_numeric($start) ? date(DateTime::ATOM, $start) : $start);
  }

  if ($end === NULL) {
    $end = new DateTime();
  }
  if (!($end instanceof DateTime)) {
    $end = new DateTime(is_numeric($end) ? date(DateTime::ATOM, $end) : $end);
  }
  if ($start <= $end) {
    return t('expired');
  }
  
  $interval = date_difference($start, $end);  
  if ($interval < 60) {
    return t('less than a minute');
  }
  else {
    return format_interval($interval);
  } 
}

function deeplink_formatinterval($f, $v, $w) {
  return "$f $w" . ($v==1?'':'s');
}

function _deeplink_username($account) {
  list($firstname, $lastname) = array_map('drupal_ucfirst', explode('.', drupal_strtolower($account->name)));
  if (!$firstname || !$lastname) {
    list($firstname, $lastname) = array_map('drupal_ucfirst', explode('.', array_shift(explode('@', drupal_strtolower($account->mail)))));
    if (!$firstname || !$lastname) {
      return array($account->name, $account->name);
    }
  }
  return array($firstname, $lastname);
}

