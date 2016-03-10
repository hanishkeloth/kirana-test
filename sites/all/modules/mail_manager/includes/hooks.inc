<?php
/**
 * @file
 *
 * MailManager_Hooks class definition
 * User: cristian.burtan
 *
 * TODO: Research the hook_mail_alter workflow. Is it possible that the alterations done here might be overwritten in a hook called later?
 * TODO: Cannot use a higher weight for the module because html body is transformed to plain text. (who does that?)
 * TODO: Is implementing a custom 'drupal_mail_wrapper' a possible solution?
 */

/**
 * Provides hook implementations
 */
class MailManager_Hooks {

  /**
   * Implements hook_mail().
   */
  public static function mail($key, &$message, $params = NULL) {

    if (isset($message['params']['mail']) && $message['params']['mail'] instanceof MailManager_ManagedMail) {
      $mail = $message['params']['mail'];
    }
    else {
      MailManager_Registry::buildFromHooks();
      $mail = MailManager_Registry::get($key);
    }

    if ($mail) {
      $message['result']  = NULL;
      $message['subject'] = $mail->getSubjectRendered();
      $message['body']    = $mail->getBodyRendered();
      $message['mail']    = $mail;

      // I know this looks odd but notice that I am setting the subject and body
      // to references of $message['subject'] and $message['body'] so any changes
      // done by a hook_mail_alter hook to the body or subject will be reflected in the mail object as well.
      $mail->subject_rendered = & $message['subject'];
      $mail->body_rendered    = & $message['body'];

      // Adding the message array as a reference to the mail object
      // so we will have access to the result key when it will be set
      $mail->result  = & $message['result'];
      $mail->message = & $message;

      if (!empty($mail->headers) && is_array($mail->headers)) {
        foreach ($mail->headers as $key => $header) {
          $message['headers'][$key] = $header;
        }
      }
    }
  }

  /**
   * Implements hook_mail_alter().
   */
  public static function mailAlter(&$message) {
    if (isset($message['mail']) && $message['mail'] && $message['mail'] instanceof MailManager_ManagedMail) {
      $mail = $message['mail'];
      if ($mail->getWrapperTheme()) {
        $theme = $mail->getWrapperTheme();
        if ($theme) {
          $message['body'] = theme($theme, array('body' => $message['body'], 'mail' => $message['mail']));
        }
        $mail->body_rendered = & $message['body'];
      }
    }
  }

  /**
   * Implements hook_theme().
   */
  public static function theme($existing, $type, $theme, $path) {
    $templates_path = drupal_get_path('module', 'mail_manager') . '/templates';

    return array(
      'managed_mail_wrapper' => array(
        'variables' => array('body' => '', 'mail' => NULL),
        'path'      => $templates_path,
        'pattern'   => 'managed_mail_wrapper__',
        'template'  => 'managed-mail-wrapper',
        'function'  => 'theme_mail_manager_wrapper',
      ),
      'managed_mail_body' => array(
        'variables' => array('body' => '', 'token_values' => array(), 'mail' => NULL),
        'path'      => $templates_path,
        'pattern'   => 'managed_mail_body__',
        'template'  => 'managed-mail-body',
        'function'  => 'theme_mail_manager_body',
      ),
    );
  }

  /**
   * Implements hook_mailkeys().
   *
   * @return array
   */
  public static function mailKeys() {

    $mail_keys = array();

    $mails = MailManager_Registry::getAll();
    foreach ($mails as $key => $mail) {
      $mail_keys[$key] = $mail->getDescription() ? : t('No description available');
    }

    return $mail_keys;
  }

  /**
   * Implements hook_mail_edit_text().
   */
  public static function mailEditText($mailkey, $langcode) {
    $mail = MailManager_Registry::get($mailkey);

    $return = array();

    $return['subject'] = $mail->getSubject();
    $return['body']    = $mail->getBody();

    return $return;
  }

}
