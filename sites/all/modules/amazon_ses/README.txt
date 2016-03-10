INTRODUCTION
------------
This module create new mail system which sends the mail by using Amazon SES.
By using amazon SES service mail will always goes into recepient's inbox.

REQUIREMENTS
------------
1. Drupal 7 libraries https://www.drupal.org/project/libraries
2. Drupal 7 awssdk https://www.drupal.org/project/awssdk

INSTALLATION
------------
 * Just like other module , donwload it via drush or FTP, and enable it.
 * This module uses external library GUZZLE. Inastall it via composer dependecny
 tool.

CONFIGURATION
-------------
Follow these steps:

* For configuration go to url "admin/config/aws-settings".

* Provide your AWS Security Credentials, it is must, so that this module can
  send api request to your AWS account. For more details about AWS Credentials
  read through
  http://docs.aws.amazon.com/general/latest/gr/aws-security-credentials.html.
  Get your access key here
  https://portal.aws.amazon.com/gp/aws/securityCredentials.

* Amazon SES requires that you verify your email address or domain, to confirm
  that you own it and to prevent others from using it. so you must verify your
  sender id. For this go to "admin/config/aws-settings/aws-verify-ses-sender-id"
  If you don't have Production Access to Amazon SES, you must verify
  reciepient's mail addresses.


Benefits of this module over smtp:
----------------------------------
1. Very less configuration, just need AWS credentials
2. It sends the mail by calling direct Amazon SES API.
3. Provides interface for verifying identities, list identities, DKIM settings
and sending mail statistics.
