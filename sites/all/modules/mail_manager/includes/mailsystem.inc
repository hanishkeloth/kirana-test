<?php
/**
 * @file
 * Custom MailSystemInterface implementation enabling MailManger to send html mail.
 * User: cristian.burtan
 */
/**
 * Modify the drupal mail system to send HTML emails.
 */
class MailManager_MailSystem extends DefaultMailSystem implements MailSystemInterface {

  /**
   * Concatenate and wrap the e-mail body for plain-text mails.
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   *
   * @return
   *   The formatted $message.
   */
  public function format(array $message) {
    $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);
    // Join the body array into one string.
    if (is_array($message['body'])) {
      $message['body'] = implode("$line_endings$line_endings", $message['body']);
    }

    return $message;
  }

}
