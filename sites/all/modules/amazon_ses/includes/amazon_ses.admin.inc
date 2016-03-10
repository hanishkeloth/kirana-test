<?php
/**
 * @file
 * Administration menu callbacks for amazon_mail_service.
 */

/**
 * Form for sending request to verify sender identity.
 */
function amazon_ses_verify_sender_id_form($form, &$form_state) {
  // Verify if User has provided AWS credential, if not then force him to
  // provide that as without aws credential this we can't talk with amazon ses.
  $form['amazon_ses_service'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verify sender identity'),
    '#collapsed' => FALSE,
  );

  $form['ajax_region'] = array(
    '#prefix' => '<div id = "amazon-identity-setting-form-wrapper">',
    '#suffix' => '</div>',
  );
  $form['amazon_ses_service']['identity_type'] = array(
    '#type' => 'radios',
    '#title' => t('Please Select Identityfication Type'),
    '#options' => array(
      'EmailAddress' => t('Email Address'),
      'Domain' => t('Domain Name'),
    ),
    '#attributes' => array('class' => array('container-inline')),
    '#required' => TRUE,
    '#description' => t('To maintain trust between
      <strong>ISPs</strong> and <strong>Amazon SES</strong>, Amazon SES needs to
      ensure that its senders are who they say they are.'
    ),
  );

  $form['amazon_ses_service']['identity_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Fully Qualified Domain Name'),
    '#size' => 60,
    '#description' => t('You must verify each email address that will be used as
      a <strong>From</strong> or <strong>Return-Path</strong> address for your
      messages.') . '<br/>' . t('The entire email address is <strong>
      case-sensitive</strong>.') . '<br/>' . t('Until you are granted production
      access to Amazon SES, you must also verify the email address of every
      recipient except for the recipients provided by the Amazon SES mailbox
      simulator.') . '<br/>' . t('<strong>Important:</strong> In order to
      complete verification, On success full sending this request you will get a
      token or a TXT record that must be placed in the DNS settings for the
      domain.'),
    '#prefix' => '<div class = identity-domain-class>',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="identity_type"]' => array('value' => 'Domain'),
      ),
    ),
  );

  $form['amazon_ses_service']['identity_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#size' => 60,
    '#description' => t('When you verify an entire domain, you are verifying all
      email addresses from that domain, so you dont need to verify email addresses
      from that domain individually.') . '<br/>' . t('Domain names are <strong>
      case-insensitive</strong>.') . '<br/>' . t('<strong>Important:</strong>
      Amazon SES only verifies fully qualified domain names (FQDNs). Even if you
      verify a domain, you have to verify subdomains of that domain. For example
      , if you want to send email from both example.com and newyork.example.com,
      you need to verify each of these FQDNs separately.'),
    '#prefix' => '<div class = identity-email-class>',
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="identity_type"]' => array('value' => 'EmailAddress'),
      ),
    ),
  );

  $form['amazon_ses_service']['send_request'] = array(
    '#type' => 'submit',
    '#value' => t('Send Request'),
  );
  return $form;
}

/**
 * Validate domain name and email address, based on type of identity.
 */
function amazon_ses_verify_sender_id_form_validate($form, &$form_state) {
  if (isset($form_state['values']['identity_type'])) {
    $identity_type = $form_state['values']['identity_type'];
    switch ($identity_type) {
      case 'EmailAddress':
        if ($form_state['values']['identity_email'] == '') {
          form_set_error('identity_email', t("The sender's email address is required."));
          return '';
        }
        if (!valid_email_address($form_state['values']['identity_email'])) {
          form_set_error('identity_email', t("The sender's email address you supplied is not valid."));
        }
        break;

      case 'Domain':
        if ($form_state['values']['identity_domain'] == '') {
          form_set_error('identity_domain', t("The sender's Domain name is required."));
          return '';
        }
        break;
    }
  }
}

/**
 * Submit handler for amazon identity request form.
 */
function amazon_ses_verify_sender_id_form_submit($form, &$form_state) {
  // Send Request to amzon SES API.
  module_load_include('inc', 'amazon_ses', 'includes/amazon_ses.mail');
  if (isset($form_state['values']['identity_type'])) {
    $identity_type = $form_state['values']['identity_type'];
    $_SESSION['amazon_selected_identity'] = $identity_type;
    switch ($identity_type) {
      case 'EmailAddress':
        $action_parameter['EmailAddress'] = $form_state['values']['identity_email'];
        $result = amazon_ses_send_request('VerifyEmailIdentity', $action_parameter);
        break;

      case 'Domain':
        $action_parameter['Domain'] = $form_state['values']['identity_domain'];
        $result = amazon_ses_send_request('VerifyDomainIdentity', $action_parameter);
        break;
    }
  }

  // Display the response of calling of Amazon SES API.
  switch ($result['status']) {
    case AMAZON_SES_REQUEST_SUCCESS:
      if ($identity_type == 'EmailAddress') {
        $message = t('A verification mail with further instruction has been sent to
          @mail By Amazon SES', array(
            '@mail' => $form_state['values']['identity_email'],
          )
        );
        drupal_set_message($message, 'status');
        drupal_goto('admin/config/aws-settings/aws-ses-sender-id-list');
      }
      elseif ($identity_type == 'Domain') {
        $message = t('In order to complete verification of this domain, you must
          create a TXT record in the DNS settings for the domain, with the value
          shown in TXT column.<br/> When Amazon Web Services has confirmed that
          these values are present in the DNS settings for the domain, the Status
          for the domain will change to <strong>verified</strong>. This may take up
          to 72 hours <a href="@learn_more">Learn More</a>', array(
            '@learn_more' => 'http://docs.aws.amazon.com/ses/latest/DeveloperGuide/verify-domains.html',
          )
        );
        drupal_set_message($message, 'status');
        drupal_goto('admin/config/aws-settings/aws-ses-sender-id-list');
      }
      break;

    case AMAZON_SES_REQUEST_FALIURE:
      $message = t('Request to <strong>@action</strong> action of Amazon SES API
       call has failed, please check your network connection or try after some
        time', array(
          '@action' => "Verify{$identity_type}Identity",
        )
      );
      drupal_set_message($message, 'error');
      break;
  }
}

/**
 * Retrieve sender identities and their status.
 */
function amazon_ses_get_identity_list($identity_type = NULL) {
  $options = array();

  // If identity type is not specified, then fetch both email & domain,for
  // this we will not send parameter 'IdentityType' in http request.
  if ($identity_type != NULL) {
    $action_parameter['IdentityType'] = $identity_type;
  }
  $result = NULL;
  $action_parameter['MaxItems'] = 10;
  module_load_include('inc', 'amazon_ses', 'includes/amazon_ses.mail');
  $result = amazon_ses_send_request('ListIdentities', $action_parameter);

  // Display the response of calling of Amazon SES API.
  if ($result['status'] == AMAZON_SES_REQUEST_FALIURE) {
    $message = t('Request to <strong>ListIdentities</strong> action of Amazon
      SES API call has failed, please check your network connection or try after
      some time.');
    drupal_set_message($message, 'error');
    $form['exception'] = TRUE;
    return $form;
  }
  unset($action_parameter);
  if (isset($result['member'])) {
    $action_parameter['Identities'] = $result['member'];
    $result = amazon_ses_send_request('GetIdentityVerificationAttributes', $action_parameter);
    $options = $result['token'];

    // Display the response of calling of Amazon SES API.
    if ($result['status'] == AMAZON_SES_REQUEST_FALIURE) {
      $message = t('Request to <strong>GetIdentityVerificationAttributes</strong>
       action of Amazon SES API call has failed, please check your network
      connection or try after some time.');
      drupal_set_message($message, 'error');
      $form['exception'] = TRUE;
      return $form;
    }
  }

  // Form filter component.
  $form['amazon_list_identities_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Identites belongs to'),
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['amazon_list_identities_filter']['select_indentity'] = array(
    '#type' => 'select',
    '#title' => '',
    '#options' => array(
      'EmailAddress' => t('Email Address'),
      'Domain' => t('Domain'),
    ),
    '#default_value' => array($identity_type),
  );
  $form['amazon_list_identities_filter']['filter_identity_list'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#submit' => array('amazon_ses_identity_list_filter'),
  );

  // Form component when Identity type is Domain.
  if ($identity_type == 'Domain') {
    $header = array(
      'key' => t('Domain Name'),
      'VerificationStatus' => t('Status'),
      'DomainRecordSet' => t('Domain Verification Record Set'),
    );
    $form['amazon_list_identities_filter']['#description'] = t('To complete
      domain verification, you must add a <strong>TXT</strong> record with the
      displayed <strong>Name</strong> and <strong>Value</strong> to
      your domain\'s DNS settings.') . '<br/>' . t('<strong>Note: </strong>Some
      domain name providers use the term <strong>Host</strong> instead of
      <strong>Name</strong>. If your DNS provider does not allow underscores in
      record names, you can omit the underscore before amazonses in the TXT
      record name.') . '<br/>' . t("When verification is complete, the domain's
      status in the Amazon SES console will change from <strong>Pending</strong>
      to <strong>Verified</strong>, and you will receive an Amazon SES Domain
      Verification SUCCESS confirmation email from Amazon Web Services. (Amazon
      Web Services emails are sent to the email address you used when you signed
      up for Amazon SES.) <a href='@learn_more'>Learn more about verifying
      domain in Amazon SES.</a>", array(
        '@learn_more' => 'http://docs.aws.amazon.com/ses/latest/DeveloperGuide/verify-domains.html',
      )
    ) . '<br/>';
  }

  // Form component when Identity type is Email address.
  else {
    $header = array(
      'key' => t('Email Address'),
      'VerificationStatus' => t('Status'),
    );
    $form['amazon_list_identities_filter']['#description'] = '<li>' . t('In your
      email client, open the message from Amazon SES asking you to confirm that
      you are the owner of this email address.') . '</li><li>' . t('Click the
      link in the message.') . '</li><li>' . t('<strong>Note:</strong> The link in
      the verification message expires 24 hours after your original verification
      request.') . '</li><li>' . t('The status of the email address in the Amazon
      SES console will change from <strong>Pending</strong> to <strong>Success
      </strong>.') . '</li>' . t('<a href="@learn_more">Learn more about
      verifying Emails in Amazon SES.</a>', array(
        '@learn_more' => 'http://docs.aws.amazon.com/ses/latest/DeveloperGuide/verify-email-addresses.html')
      ) . '<br/></br>';
  }

  // Form Update component.
  $form['amazon_list_identities_update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verified Idenities'),
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['amazon_list_identities_update']['list_table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No content available.'),
  );

  return $form;
}

/**
 * Display Verified Sender Identites to Admin.
 *
 * From here admin can also delete Sender Identites.
 */
function amazon_ses_identity_list_form($form, &$form_state) {
  // Set default identity type to Email Address.
  $identity_type = 'EmailAddress';
  // When user has already selected a filter, then on regeneration of form
  // should set same identity.
  if (isset($_SESSION['amazon_selected_identity'])) {
    $identity_type = $_SESSION['amazon_selected_identity'];
  }

  // Reterieve identity list by sending request to amazon SES API.
  $form = amazon_ses_get_identity_list($identity_type);

  $form['amazon_list_identities_update']['select_update'] = array(
    '#type' => 'select',
    '#title' => '',
    '#options' => array('DeleteIdentity' => t('Delete Identity')),
  );
  $form['amazon_list_identities_update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Send Request'),
    '#submit' => array('amazon_ses_identity_list_update'),
  );
  return $form;
}

/**
 * Validate that user must select minimum 1 identity.
 */
function amazon_ses_identity_list_form_validate($form, &$form_state) {
  $selected_identities = array_filter($form_state['values']['list_table']);
  $selected_identities_no = count($selected_identities);
  if ($selected_identities_no == 0 && $form_state['values']['update'] == $form_state['triggering_element']['#value']) {
    form_set_error('list_table', t('Please select atleast one Identity.'));
    return '';
  }
}

/**
 * Send request to amazon ses api to delete sender's identities.
 */
function amazon_ses_identity_list_update($form, &$form_state) {
  $selected_identities = array_filter($form_state['values']['list_table']);
  module_load_include('inc', 'amazon_ses', 'includes/amazon_ses.mail');

  // @todo Amazon SES api throtteled request per second. Here we are sending
  // request in loop which may cause problem. so will add sleep for 1 sec.
  foreach ($selected_identities as $value) {
    $action_parameter['identity'] = $form_state['complete form']['amazon_list_identities_update']['list_table']['#options'][$value]['key'];
    // This request is throttled per second.
    $result = amazon_ses_send_request('DeleteIdentity', $action_parameter);

    // Display the response of calling of Amazon SES API.
    if (isset($result['status'])) {
      switch ($result['status']) {
        case AMAZON_SES_REQUEST_SUCCESS:
          // For reloading identities.
          $message = t('Identity @identity is deleted successfully from Amazon SES.', array(
            '@identity' => $action_parameter['identity'],
            )
          );
          drupal_set_message($message, 'status');
          break;

        case AMAZON_SES_REQUEST_FALIURE:
          $message = t('Request to <strong>DeleteIdentity</strong> action of Amazon
            SES API call has failed, please check your network connection or try
            after some time.');
          drupal_set_message($message, 'error');
          break;
      }
    }
  }
}

/**
 * Rebuild form so that identites can be fetched again from SES API.
 */
function amazon_ses_identity_list_filter($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $_SESSION['amazon_selected_identity'] = $form_state['values']['select_indentity'];
}

/**
 * Display Sending Quota and Statistics data.
 *
 * @todo Sendign Quota and statistics should be displayed to user in better
 * GUI and user of graph.
 */
function amazon_ses_get_mail_statistics_form($form, $form_state) {
  module_load_include('inc', 'amazon_ses', 'includes/amazon_ses.mail');
  $result_quota = amazon_ses_send_request('GetSendQuota', array());
  if ($result_quota['status'] == AMAZON_SES_REQUEST_FALIURE) {
    $message = t('Request to <strong>GetSendQuota</strong> action of Amazon SES
      API call has failed, please check your network connection or try after some time.');
    drupal_set_message($message, 'error');
    return '';
  }

  $form['sending_limits_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Your Amazon SES Sending Limits'),
    '#collapsed' => FALSE,
  );
  $form['sending_limits_fieldset']['sending_limit_data'] = array(
    '#prefix' => t('<strong>Sending Quota:</strong> Send @max_send emails per 24
    hour period.', array('@max_send' => $result_quota['Max24HourSend'])) . '<br/>'
    . t('<strong>Sent Mail:</strong> @sent_last', array('@sent_last' => $result_quota['SentLast24Hours'])) .
    '<br/>' . t('<strong>Max Send Rate:</strong> @send_rate Email/second.', array(
      '@send_rate' => $result_quota['MaxSendRate'],
      )
    ),
  );

  $result_statistics = amazon_ses_send_request('GetSendStatistics', array());
  if ($result_statistics['status'] == AMAZON_SES_REQUEST_FALIURE) {
    $message = t('Request to <strong>GetSendStatistics</strong> action of Amazon
      SES API call has failed, please check your network connection or try after some time.');
    drupal_set_message($message, 'error');
    return '';
  }
  $form['sending_statistics_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Your Amazon SES Metrics'),
    '#collapsed' => FALSE,
  );
  $form['sending_statistics_fieldset']['sending_statistics_data'] = array(
    '#prefix' => t('<strong>Total number of mails sent:</strong> @delivery_attempts
    in last two weeks.', array('@delivery_attempts' => $result_statistics['DeliveryAttempts']))
    . '<br/>' . t('<strong>Total number of Bounces Mail:</strong> @bounces in
    last two weeks.', array('@bounces' => $result_statistics['Bounces'])) .
    '<br/>' . t('<strong>Total number of Complaints mail:</strong> @complaints
    in last two weeks.', array('@complaints' => $result_statistics['Complaints'])) . '<br/>' .
    t('<strong>Total number of Rejected mail:</strong> @rejects in last two
    weeks.', array(
      '@rejects' => $result_statistics['Rejects'],
    )) . '<br/>',
  );
  return $form;
}

/**
 * Form for Enablling DKIM for sender's Identity.
 */
function amazon_ses_domain_dkim_enable_form($form, &$form_state) {
  // Set default identity type to Domain.
  $identity_type = 'Domain';

  if (isset($form_state['values']['select_indentity'])) {
    $identity_type = $form_state['values']['select_indentity'];
  }

  // Reterieve identity list by sending request to amazon SES API.
  $form = amazon_ses_get_identity_list($identity_type);

  if (isset($form['exception'])) {
    return '';
  }
  $form['amazon_list_identities_filter']['select_indentity']['#default_value'] = array($identity_type);

  $form['amazon_list_identities_update']['select_update'] = array(
    '#type' => 'select',
    '#title' => '',
    '#options' => array(
      'DkimAttributes' => t('Get CNAME record'),
    ),
  );
  $form['amazon_list_identities_update']['update'] = array(
    '#type' => 'button',
    '#value' => t('Send Request'),
  );

  $form['amazon_list_identities_update']['#title'] = t('DKIM Settings');
  $form['amazon_list_identities_update']['#description'] = t('DomainKeys
    Identified Mail (DKIM) is a standard that allows senders to sign their email
    messages and ISPs to use those signatures to verify that those messages are
    legitimate and have not been modified by a third party in transit.') .
    '<br/>' . t("To set up DKIM, you must update your domain's DNS settings with
    the CNAME record information. For obtaining CNAME record select Domain or
    Email addrees then click on <strong>Send Request</strong>.") . '<br/>';
  $form['amazon_list_identities_update']['list_table']['#multiple'] = FALSE;
  $form['amazon_list_identities_update']['list_table']['#input'] = FALSE;

  $form['amazon_list_identities_update']['update']['#ajax'] = array(
    'callback' => 'amazon_ses_domain_dkim_enable_callback',
    'wrapper' => 'domain-dkim-wrapper',
    'effect' => 'fade',
    'method' => 'html',
  );

  // Form component showing DKIM records.
  $header = array(
    'name' => t('Name'),
    'type' => t('Type'),
    'value' => t('Value'),
  );
  $form['div'] = array(
    '#prefix' => '<div id = "domain-dkim-wrapper">',
    '#suffix' => '</div>',
  );
  $form['div']['domain_dkim_info'] = array(
    '#prefix' => '',
    '#suffix' => '',
  );
  $form['div']['domain_dkim_token_table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => NULL,
    '#empty' => t('No content available.'),
    '#access' => FALSE,
  );
  return $form;
}

/**
 * Ajax callback for domain_dkim_enable.
 */
function amazon_ses_domain_dkim_enable_callback($form, &$form_state) {
  return $form['div'];
}

/**
 * Validate that user has selected atleast one identity.
 */
function amazon_ses_domain_dkim_enable_form_validate($form, &$form_state) {
  if ($form_state['values']['update'] == $form_state['triggering_element']['#value'] && empty($form_state['values']['list_table'])) {
    form_set_error('list_table', t('You must select one identity for generating DKIM tokens'));
  }
}
