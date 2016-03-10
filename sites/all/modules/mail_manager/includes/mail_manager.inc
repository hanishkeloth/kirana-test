<?php

/**
 * @file
 * MailManager class definition.
 * User: cristian.burtan
 */

/**
 * Common MailManager logic
 */
class MailManager {

  /**
   * Returns a list of general tokens that will be available for any mail.
   *
   * @return array
   */
  public static function defaultTokensList() {
    $tokens = array();

    $tokens['uri_brief'] = ("Website's URL without the leading http://");

    return $tokens;
  }

  /**
   * Returns values for the tokens defined in MailManager::defaultTokensList
   *
   * @see MailManager::defaultTokensList
   *
   * @param MailManager_ManagedMail $mail
   *
   * @return array
   */
  public static function defaultTokensValues(MailManager_ManagedMail $mail) {

    global $base_url;

    $language = isset($mail->language) ? $mail->language : language_default();

    $tokens = array(
      'uri_brief' => drupal_substr($base_url, drupal_strlen('http://')),
    );

    return $tokens;
  }

  /**
   * Procedural wrapper function to send an email through the MailManager module.
   *
   * @param       $module
   * @param       $key
   * @param null  $to
   * @param null  $language
   * @param array $params
   * @param null  $from
   * @param bool  $send
   *
   * @return MailManager_ManagedMail
   */
  public static function send($module, $key, $to = NULL, $language = NULL, $params = array(), $from = NULL, $send = TRUE) {

    $id   = implode(MailManager_ManagedMail::ID_SEPARATOR, array($module, $key));
    $mail = MailManager_Registry::get($id);

    if ($to) {
      $mail->to = $to;
    }

    if ($language) {
      $mail->language = $language;
    }

    if ($params) {
      $mail->params = $params;
    }

    if ($from) {
      $mail->from = $from;
    }

    if ($send) {
      $mail->send = $send;
    }

    return $mail->send();

  }

  /**
   * This is just the default theming function, no theming is actually applied.
   * To apply a theme to you outgoing email you can implement a template in your theme named:
   *
   * managed-mail-wrapper.tpl.php - for general use
   * managed-mail-wrapper--[mail_key].tpl.php - for a specific mail identified by the key
   * managed-mail-wrapper--[mail_key]--[language_code].tpl.php - for a specific mail and language
   *
   * Or you can create your own hook_theme and use the MailManager_ManagedMail::addWrapperTheme method to add your own theming function.
   *
   * @see MailManager_ManagedMail::addWrapperTheme
   *
   * @param $body
   * @param $mail
   *
   * @return mixed
   */
  public static function themeWrapper($variables) {
    // As a default we do not apply any theming to the body, just return it
    return $variables['body'];
  }

  /**
   * This is just the default theming function, no theming is actually applied.
   * The body is only passed through t() so it is translatable.
   * To apply a theme to you outgoing email body you can implement a template in your theme named:
   *
   * managed-mail-body.tpl.php - for general use
   * managed-mail-body--[mail_key].tpl.php - for a specific mail identified by the key
   * managed-mail-body--[mail_key]--[language_code].tpl.php - for a specific mail and language
   *
   * Or you can create your own hook_theme and use the MailManager_ManagedMail::addBodyTheme method to add your own theming function.
   *
   * @see MailManager_ManagedMail::addBodyTheme
   *
   * @param $mail
   *
   * @return mixed
   */
  public static function themeBody($variables) {
    return t($variables['body'], $variables['token_values'], array('langcode' => $variables['mail']->language->language));
  }
}


