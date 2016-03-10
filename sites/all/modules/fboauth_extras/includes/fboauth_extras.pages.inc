<?php
/**
 * Render the facebook friends invite form.
 */
function fboauth_extras_page() {
  global $base_url;
  global $user;

  return theme('fboauth_invite_form', array('request_form_attributes' => $request_form_attributes, 'friends_selector_attributes' => $friends_selector_attributes));
}

/**
 * Menu callback; Display the settings form for Facebook OAuth.
 */
function fboauth_extras_settings_form($form, &$form_state) {
  $form['fboauth_picture_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import a given user\'s facebook profile picture upon login via Facebook OAuth.'),
    '#description' => t('By default, the Facebook OAuth module will import a user picture only during new account creation. It will not import a user picture for existing Drupal accounts that are newly connect to facebook. Note: this will not overwrite existing pictures.'),
    '#default_value' => variable_get('fboauth_picture_import', 0),
  );
  $form['fboauth_extras_cron'] = array(
    '#type' => 'checkbox',
    '#disabled' => TRUE,
    '#title' => t("Import all Facebook Oauth connect user's friends when cron runs."),
    '#default_value' => variable_get('fboauth_extras_cron', 1),
    '#description' => t('This is intended to be an alternative to importing friends on login. For this to work well, cron must run frequently - before a Facebook Access Token expires.'),
  );
  $form['fboauth_extras_friends_import'] = array(
    '#type' => 'checkbox',
    '#title' => t("Import a given user's facebook friends upon login via Facebook OAuth."),
    '#default_value' => variable_get('fboauth_extras_friends_import', 1)
  );
  $form['fboauth_extras_friends_import_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Import frequency'),
    '#description' => t("How frequently should each user's list of facebook friends be updated?"),
    '#options' => array(
      //'once' => t('Only once, after first login'),
      'every' => t('Immediately after every login'),
      //'custom' => t('Custom time period'),
    ),
    '#default_value' => variable_get('fboauth_extras_friends_import_frequency', 'every'),
  );
  $form['fboauth_extras_custom_frequency'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom Import Frequency'),
    '#description' => t("Please enter a relative date value. E.g., '-2 days'. See <a href=\"http://php.net/manual/en/datetime.formats.relative.php\">PHP Relative Formats</a> for more information."),
    '#default_value' => variable_get('fboauth_extras_custom_frequency', ''),
    '#states' => array(
       'visible' => array(
        ':input[name="fboauth_extras_friends_import_frequency"]' => array('value' => 'custom'),
       ),
     ),
  );
  $form['fboauth_extras_update'] = array(
    '#type' => 'checkbox',
    '#title' => t("Update a given user's facebook friends upon login via Facebook OAuth."),
    '#description' => t('
    <ol>
      <li>Update friends\' information. E.g., update their Facebook name in the case that it changed.</li>
      <li>Unpublish friends that the user has unfriended.</li>
    </ol>'),
    '#default_value' => variable_get('fboauth_extras_update', 1)
  );
  $form['fboauth_extras_post_wall_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Post to Wall Settings'),
  );
  $form['fboauth_extras_post_wall_settings']['fboauth_extras_post_wall_settings_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link URL'),
    '#default_value' => variable_get('fboauth_extras_post_wall_settings_link', "<front>"),
    '#description' => t('The URL of the page that the facebook wall post will link to.'),
  );
  $form['fboauth_extras_post_wall_settings']['fboauth_extras_post_wall_settings_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => variable_get('fboauth_extras_post_wall_settings_name', t("I'm saving my list of favorite local businesses here, you should too.")),
    '#description' => t('This acts as the title of a post. It is linked back to the link URL and appears in bold.'),
  );
  $form['fboauth_extras_post_wall_settings']['fboauth_extras_post_wall_settings_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#default_value' => variable_get('fboauth_extras_post_wall_settings_description', t('Description goes here.')),
    '#description' => t('This appears below the caption.'),
  );
  
  return system_settings_form($form);
}

/**
 * The FB Javascript SDK will redirect dialog requests
 * to facebook_friends/redirect_uri after completion.
 * This callback will handle that redirect by closing the dialog
 * and flagging the dialog request as successful on our server.
 */
function fboauth_extras_fb_redirect_uri($action, $to) {
  if ($action == 'fboauth_extras_invite') {
    fboauth_extras_create_invite($action ,$to);
  }


  // Close popup window.
  //drupal_add_js('jQuery(document).ready(function () { window.close(); return TRUE; });', 'inline');
  //return '';

  //drupal_add_http_header('Content-Type', 'application/javascript');
  print '<script>window.close();</script>';
  drupal_exit();
}