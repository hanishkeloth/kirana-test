<?php
/**
 * @file
 * Class for interacting with Amazon SES service.
 */

/**
 * Modify the drupal mail system to use Amazon SES.
 */
class AmazonSesClass {

  /**
   * AWSSDK Configuration.
   */
  private $sesClient;

  /**
   * Initiliaze this class.
   */
  public function __construct() {
    libraries_load('awssdk');
    $awssdk_config = awssdk_config_load();
    $this->sesClient = new AmazonSES($awssdk_config);
  }

  /**
   * Add required parameter & header to the Query according to Query action.
   */
  public function performServiceAction($query_action, $action_parameter = array()) {
    switch ($query_action) {
      case 'DeleteIdentity':
        $result = $this->deleteIdentity($action_parameter);
        break;

      case 'GetIdentityDkimAttributes':
        $result = $this->getIdentityDkimAttributes($action_parameter);
        break;

      case 'GetIdentityVerificationAttributes':
        $result = $this->getIdentityVerificationAttributes($action_parameter);
        break;

      case 'GetSendStatistics':
        $result = $this->getSendStatistics($action_parameter);
        break;

      case 'GetSendQuota':
        $result = $this->getSendQuota($action_parameter);
        break;

      case 'ListIdentities':
        $result = $this->listIdentities($action_parameter);
        break;

      case 'SendEmail':
        $result = $this->sendEmail($action_parameter);
        break;

      case 'VerifyDomainDkim':
        $result = $this->verifyDomainDkim($action_parameter);
        break;

      case 'VerifyDomainIdentity':
        $result = $this->verifyDomainIdentity($action_parameter);
        break;

      case 'VerifyEmailIdentity':
        $result = $this->verifyEmailIdentity($action_parameter);
        break;
    }
    return $result;
  }

  /**
   * Call Query API action DeleteIdentity.
   *
   * Deletes the specified identity (email address or domain) from the list of
   * verified identities. This action is throttled at one request per second.
   */
  private function deleteIdentity($action_parameter) {
    $response_xml = $this->sesClient->delete_identity($action_parameter['identity']);

    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action GetIdentityNotificationAttributes.
   *
   * This action is throttled at one request per second.
   */
  private function getIdentityDkimAttributes($action_parameter) {
    $response_xml = $this->sesClient->get_identity_dkim_attributes($action_parameter['Identities']);

    // Parse xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $entry = $response->GetIdentityDkimAttributesResult->DkimAttributes->entry;
      $result['key'] = check_plain($entry->key);
      $result['DkimEnabled'] = check_plain($entry->value->DkimEnabled);
      $result['DkimVerificationStatus'] = check_plain($entry->value->DkimVerificationStatus);
      $dkim_tokens = $entry->value->DkimTokens->member;
      $i = 0;
      if (strpos($result['key'], '@') != FALSE) {
        $temp_arr = explode('@', $result['key']);
        $domain = $temp_arr[1];
      }
      else {
        $domain = $result['key'];
      }
      foreach ($dkim_tokens as $token) {
        $name = (string) $token . '._domainkey.' . $domain;
        $value = (string) $token . '.dkim.amazonses.com';
        $result['member']['row' . $i]['name'] = check_plain($name);
        $result['member']['row' . $i]['value'] = check_plain($value);
        $result['member']['row' . $i]['type'] = 'CNAME';
        $i++;
      }
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action GetIdentityVerificationAttributes.
   *
   * This action is throttled at one request per second.
   */
  private function getIdentityVerificationAttributes($action_parameter) {
    $response_xml = $this->sesClient->get_identity_verification_attributes($action_parameter['Identities']);

    // Parse the xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
      $entries = $response->GetIdentityVerificationAttributesResult->VerificationAttributes->entry;
      $i = 0;
      if (!is_array($entries)) {
        $entries = array($entries);
      }
      foreach ($entries as $entry) {
        $result['token']['row' . $i]['key'] = check_plain($entry->key);
        $value = $entry->value;
        if (isset($value->VerificationStatus)) {
          $result['token']['row' . $i]['VerificationStatus'] = check_plain($value->VerificationStatus);
        }
        // The verification token for a domain identity. Null for email
        // address identities.
        if (isset($value->VerificationToken)) {
          $domain = $result['token']['row' . $i]['key'];
          $domain_record_set = "<div class = ''><strong>Name: </strong> _amazonses.{$domain} <br/>
          <strong>Type:</strong> TXT <br/>
          <strong>Value:</strong> {$value->VerificationToken}";
          $result['token']['row' . $i]['DomainRecordSet'] = filter_xss_admin($domain_record_set);
        }
        $i++;
      }
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action GetSendStatistics.
   *
   * The result is a list of data points, representing the last two weeks of
   * sending activity. Each data point in the list contains statistics for a 15
   * minute interval. This action is throttled at one request per second.
   */
  private function getSendStatistics($action_parameter) {
    $response_xml = $this->sesClient->get_send_statistics($action_parameter);

    // Parse the xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;

      // Number of emails that have been enqueued for sending.
      $result['DeliveryAttempts'] = 0;
      // Number of emails rejected by Amazon SES.
      $result['Rejects'] = 0;
      // Number of emails that have bounced.
      $result['Bounces'] = 0;
      // Number of unwanted emails that were rejected by recipients.
      $result['Complaints'] = 0;
      if (isset($response->GetSendStatisticsResult->SendDataPoints->member)) {
        $member = $response->GetSendStatisticsResult->SendDataPoints->member;
        if (is_array($member)) {
          foreach ($member as $value) {
            $result['DeliveryAttempts'] = check_plain($value->DeliveryAttempts) + $result['DeliveryAttempts'];
            $result['Rejects'] = check_plain($value->Rejects) + $result['Rejects'];
            $result['Bounces'] = check_plain($value->Bounces) + $result['Bounces'];
            $result['Complaints'] = check_plain($value->Complaints) + $result['Complaints'];
          }
        }
        else {
          $result['DeliveryAttempts'] = check_plain($member->DeliveryAttempts);
          $result['Rejects'] = check_plain($member->Rejects);
          $result['Bounces'] = check_plain($member->Bounces);
          $result['Complaints'] = check_plain($member->Complaints);
        }

      }
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action GetSendQuota.
   *
   * This action is throttled at one request per second.
   */
  private function getSendQuota($action_parameter) {
    $response_xml = $this->sesClient->get_send_quota($action_parameter);

    // Parse the xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
      $result['SentLast24Hours'] = check_plain($response->GetSendQuotaResult->SentLast24Hours);
      $result['Max24HourSend'] = check_plain($response->GetSendQuotaResult->Max24HourSend);
      $result['MaxSendRate'] = check_plain($response->GetSendQuotaResult->MaxSendRate);
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action ListIdentities.
   *
   * This action is throttled at one request per second.
   */
  private function listIdentities($action_parameter) {
    $response_xml = $this->sesClient->list_identities($action_parameter);
    // Parse xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
      if (isset($response->ListIdentitiesResult->Identities->member)) {
        $result['member'] = $response->ListIdentitiesResult->Identities->member;
      }
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action SendEmail.
   *
   * Composes an email message based on input data, and then immediately queues
   * the message for sending.
   */
  private function sendEmail($action_parameter) {
    $mail = $action_parameter['mail'];
    $message = $mail['message'];
    $response_xml = $this->sesClient->send_email($mail['from'], $mail['destination'], $message);
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
      // todo: Will be used later.
      if (isset($response->SendEmailResult->MessageId)) {
        $result['message_id'] = check_plain($response->SendEmailResult->MessageId);
      }
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action VerifyDomainDkim.
   *
   * This action is throttled at one request per second. DKIM tokens are
   * character strings that represent your domain's identity. Using these tokens
   * you will need to create DNS CNAME records that point to DKIM public keys
   *  hosted by Amazon SES.
   */
  private function verifyDomainDkim($action_parameter, $request, $action_response = '', $response_code = '0') {
    if ($request) {
      $this->setRequestParameter('Action', 'VerifyDomainDkim');
      if (isset($action_parameter['Domain'])) {
        $this->setRequestParameter('Domain', $action_parameter['Domain']);
      }
    }
    // Parse the http response.
    else {
      $result = array();
      if ($response_code == '200') {
        $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
        $dkim_tokens = $action_response->DkimTokens;
        foreach ($dkim_tokens as $member) {
          $result[]['member'] = (string) $member;
        }
        return $result;
      }
      // Error in response.
      else {
        $result['Type'] = $action_response->Type;
        $result['Code'] = $action_response->Code;
        $result['Message'] = $action_response->Message;
        $result['status'] = AMAZON_SES_REQUEST_FALIURE;
        return $result;
      }
    }
  }

  /**
   * Call Query API action VerifyEmailIdentity.
   *
   * Verifies an email address. This action causes a confirmation email message
   * to be sent to the specified address. This action is throttled at one
   * request per second.
   */
  private function verifyEmailIdentity($action_parameter) {
    $response_xml = $this->sesClient->verify_email_identity($action_parameter['EmailAddress']);

    // Parse xml response.
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

  /**
   * Call Query API action VerifyDomaindentity.
   *
   * Verifies a domain.This action is throttled at one request per second.
   */
  private function verifyDomainIdentity($action_parameter) {
    $response_xml = $this->sesClient->verify_domain_identity($action_parameter['Domain']);

    // Parse xml response.
    $response = $response_xml->body->to_stdClass();
    if ($response_xml->status == '200') {
      $result['status'] = AMAZON_SES_REQUEST_SUCCESS;
      $result['token'] = $response->VerifyDomainIdentityResult->VerificationToken;
    }
    // Error in response.
    else {
      $result['status'] = AMAZON_SES_REQUEST_FALIURE;
    }
    return $result;
  }

}
