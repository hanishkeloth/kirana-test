<?php
/**
 * @file
 * Amazon SES Mail system Used by drupal core system.
 */

require_once 'classes/amazonses.class.php';

/**
 * Create system which will send mail using amazon ses api.
 */
class AmazonSesSystem extends DefaultMailSystem {
  /**
   * Concatenate and wrap the e-mail body for plain-text mails.
   */
  public function format(array $message) {
    // Join the body array into one string.
    $message['body'] = implode("\n\n", $message['body']);
    $message['body'] = drupal_wrap_mail($message['body']);
    return $message;
  }

  /**
   * Send an e-mail message, using Drupal variables and default settings.
   */
  public function mail(array $message) {
    $message['destination'] = array(
      'ToAddresses' => array($message['to']),
    );
    $message['message']['Subject']['Data'] = $message['subject'];
    $message['message']['Body']['Html']['Data'] = $message['body'];
    unset($message['headers']);
    unset($message['body']);
    unset($message['to']);
    unset($message['params']);
    unset($message['subject']);
    unset($message['key']);
    unset($message['module']);
    unset($message['language']);
    unset($message['id']);
    $action_parameters['mail'] = $message;

    $result = amazon_ses_send_request('SendEmail', $action_parameters);
    $result['message'] = $result['status'];
    return $result['message'];
  }

}


/**
 * Send the request to amazon ses, which directly call Amazon SES API.
 *
 * After sending request, it parse the http response returned by Amazon
 * API call.
 */
function amazon_ses_send_request($query_action, $action_parameters) {
  $amazon_mail_service = new AmazonSesClass();
  $result = $amazon_mail_service->performServiceAction($query_action, $action_parameters);
  return $result;
}
