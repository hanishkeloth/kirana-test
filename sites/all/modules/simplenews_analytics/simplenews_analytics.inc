<?php

/**
 * @file
 * Helperfunctions for Simplenews Analytics.
 */

/**
 * Simplenews Google Analytics settings
 */
function simplenews_analytics_admin($form, &$form_state) {
  $form['simplenews_analytics_utm_source'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign source'),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('simplenews_analytics_utm_source', 'newsletter'),
  );
  $form['simplenews_analytics_utm_medium'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign medium'),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('simplenews_analytics_utm_medium', 'email'),
  );
  $form['simplenews_analytics_utm_campaign'] = array(
    '#type' => 'textfield',
    '#title' => t('Campaign name'),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 128,
    '#default_value' => variable_get('simplenews_analytics_utm_campaign', '[node:field_simplenews_term]	'),
    '#description' => t('Newsletter name, product, promo code, or slogan. Use <em>[node:field_simplenews_term]	</em> to use the name of the newsletter series.'),
  );
  $form['simplenews_analytics_current_domain'] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit to current domain'),
    '#default_value' => variable_get('simplenews_analytics_current_domain', TRUE),
    '#description' => t('When checked, the Google Analytics tags will only be added to links to the current domain (%domain).', array('%domain' => _simplenews_analytics_current_domain())),
  );

  return system_settings_form($form);
}

/**
 * Recursively parse email message body array.
 *
 * @param $text
 *  Mail message body text (array or string).
 */
function _simplenews_analytics_parse_body(&$text) {
  if (is_array($text)) {
    foreach ($text as $key => $element) {
      _simplenews_analytics_parse_body($text[$key]);
    }
  }
  else {
    if (!empty($text)) {
      $text = preg_replace_callback("`(https?://[a-zA-Z0-9@:%_+*~#?&=.,/;-]*[a-zA-Z0-9@:%_+*~#&?=/;-])`i", '_simplenews_analytics_parse_full_url', $text);
    }
  }
}

/**
 * preg callback: Add Google Analytics query string to url.
 *
 * @param $match
 *  Preg match array.
 *  
 * @return parsed url
 */
function _simplenews_analytics_parse_full_url($match) {
  // Don't add query string if link is outside of current domain.
  if (variable_get('simplenews_analytics_current_domain', TRUE) && strpos($match[1], _simplenews_analytics_current_domain()) === FALSE) {
    return $match[1];
  }

  // Use ? or & prefix depending on existing query string.
  if ($query = _simplenews_analytics_build_query()) {
    $query = strpos($match[1], '?') ? '&' . $query : '?' . $query;
  }

  // Add query string to url.
  return $match[1] . $query;
}

/**
 * Build query from Google Analytics settings
 *
 * @return query string containing Google Analytics query.
 */
function _simplenews_analytics_build_query() {
  global $language;
  $query[] = 'utm_source=' . drupal_encode_path(variable_get('simplenews_analytics_utm_source', 'newsletter'));
  $query[] = 'utm_medium=' . drupal_encode_path(variable_get('simplenews_analytics_utm_medium', 'email'));

  // Build campain data with token replacements.
  $context = _simplenews_analytics_get_context();
  $campaign = token_replace(variable_get('simplenews_analytics_utm_campaign', '[node:title]'), $context);
  $query[] = 'utm_campaign=' . drupal_encode_path($campaign);

  return implode('&', $query);
}

/**
 * Return the base URL without the protocol.
 */
function _simplenews_analytics_current_domain() {
  global $base_url;
  return preg_replace('@https?://(.*)@i', '\1', $base_url);
}

/**
 * Store and reproduce context variables.
 *
 * @param $context
 *  Array of data to store. If NULL returns the data
 */
function _simplenews_analytics_get_context($context = NULL) {
  static $data = array();

  if (isset($context)) {
    $data['node'] = $context['simplenews_source']->getNode();
  }
  return $data;
}