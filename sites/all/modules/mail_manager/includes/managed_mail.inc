<?php
/**
 * @file
 * MailManager_ManagedMail Class Definition
 * User: cristian.burtan
 */

/**
 * Provides logic form managed mail objects.
 * MailManager_ManagedMail define emails that integrate with mail_edit.
 *
 * @TODO: Implement theme feature for mail body. Replace t function with theme($this->body_theme) in MailManager_ManagedMail::render method
 *
 */
class MailManager_ManagedMail {

  /**
   * Separator to use when building internal id from object properties
   */
  const ID_SEPARATOR            = '-';
  const MODULE_NAME             = 'mail_manager';
  const TOKEN_EMPTY_DESCRIPTION = 'No description';
  const DEFAULT_WRAPPER_THEME   = 'managed_mail_wrapper';
  const DEFAULT_BODY_THEME      = 'managed_mail_body';

  public $module;
  public $key;

  public $to;
  public $params;
  public $from;
  public $subject;
  public $body;
  public $headers;
  public $language;
  public $send;
  public $token_list;
  public $token_values;

  public $description;

  public $wrapper_theme;
  public $body_theme;

  public $subject_rendered;
  public $body_rendered;
  public $result;
  public $message;

  #<editor-fold desc=" --- Constructors --- ">

  /**
   * Main constructor.
   *
   * @param string $key
   * @param string $description
   */
  function __construct($key, $description) {
    $this->key         = $key;
    $this->description = $description;

    $this->setDefaultValues();
  }

  /**
   * Static constructor for chaining purposes.
   *
   * @param string $key
   * @param string $description
   *
   * @return MailManager_ManagedMail
   */
  public static function build($key, $description) {
    return new self($key, $description);
  }

  #</editor-fold>

  #<editor-fold defaultstate="collapsed" desc=" --- Getter / Setter --- ">

  /**
   * @param string $body
   *
   * @return $this
   */
  public function setBody($body) {
    $this->body = $body;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getBody() {
    return $this->body;
  }

  /**
   * @param $headers
   *
   * @return $this
   */
  public function setHeaders($headers) {
    $this->headers = $headers;

    return $this;
  }

  /**
   * @return array
   */
  public function getHeaders() {
    return $this->headers ? : array();
  }

  /**
   * @param string $description
   *
   * @return $this
   */
  public function setDescription($description) {
    $this->description = $description;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getDescription() {
    return $this->description;
  }

  /**
   * @param string $key
   *
   * @return $this
   */
  public function setKey($key) {
    $this->key = $key;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getKey() {
    return $this->key;
  }

  /**
   * @param string $module
   *
   * @return $this
   */
  public function setModule($module) {
    $this->module = $module;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getModule() {
    return $this->module;
  }

  /**
   * @param string $subject
   *
   * @return $this
   */
  public function setSubject($subject) {
    $this->subject = $subject;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getSubject() {
    return $this->subject;
  }

  /**
   * @param $body_rendered
   *
   * @return $this
   */
  public function setBodyRendered($body_rendered) {
    $this->body_rendered = $body_rendered;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getBodyRendered() {

    if (!$this->body_rendered && $this->body) {
      $this->render();
    }

    return $this->body_rendered;
  }

  /**
   * @param $subject_rendered
   *
   * @return $this
   */
  public function setSubjectRendered($subject_rendered) {
    $this->subject_rendered = $subject_rendered;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getSubjectRendered() {

    if (!$this->subject_rendered && $this->subject) {
      $this->render();
    }

    return $this->subject_rendered;
  }

  /**
   * @param array $token_values
   *
   * @return $this
   */
  public function setTokenValues($token_values) {
    $this->token_values = $token_values;

    return $this;
  }

  /**
   * @return array
   */
  public function getTokenValues() {
    return $this->token_values ? : array();
  }

  /**
   * @param array $tokens
   *
   * @return $this
   */
  public function setTokenList($tokens) {
    $this->token_list = $tokens;

    return $this;
  }

  /**
   * @return array
   */
  public function getTokenList() {
    return $this->token_list ? : array();
  }

  /**
   * Add a token.
   *
   * @param string $token
   * @param string $value
   * @param string $description
   *
   * @return $this
   */
  public function addToken($token, $value, $description = '') {

    $description = $description ? : t(self::TOKEN_EMPTY_DESCRIPTION);

    $this->token_list[$token]   = $description;
    $this->token_values[$token] = $value;

    return $this;
  }

  /**
   * Set tokens from the given array. See the expected format below.
   *
   * @param array $tokens
   *      Expected format for $tokens:
   *      array(
  array('!token_name', 'token_value', 'token_description'),
   *      array([name], [value], [description]),
   *      .......
   *    );
   *
   * @return $this
   */
  public function setTokens(array $tokens) {
    if ($tokens) {
      foreach ($tokens as $token) {
        if (isset($token[0]) && isset($token[1])) {
          call_user_func_array(array($this, 'addToken'), $token);
        }
      }

    }

    return $this;
  }

  /**
   * @param string $from
   *
   * @return $this
   */
  public function setFrom($from) {
    $this->from = $from;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getFrom() {
    return $this->from;
  }

  /**
   * @param object $language
   *
   * @return $this
   */
  public function setLanguage($language) {
    $this->language = $language;

    return $this;
  }

  /**
   * @return object
   */
  public function getLanguage() {
    return $this->language;
  }

  /**
   * @param array $params
   *
   * @return $this
   */
  public function setParams($params) {
    $this->params = $params;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getParams() {
    return $this->params ? : array();
  }

  /**
   * @param boolean $send
   *
   * @return $this
   */
  public function setSend($send) {
    $this->send = $send;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getSend() {
    return $this->send;
  }

  /**
   * @param string $to
   *
   * @return $this
   */
  public function setTo($to) {
    $this->to = $to;

    return $this;
  }

  /**
   * @return mixed
   */
  public function getTo() {
    return $this->to;
  }

  /**
   * @param string $theme
   *
   * @return $this
   */
  public function addWrapperTheme($theme) {
    $this->wrapper_theme = array_merge(array($theme), (array) $this->wrapper_theme);

    return $this;
  }

  /**
   * @param string $theme
   *
   * @return $this
   */
  public function addBodyTheme($theme) {
    $this->body_theme = array_merge(array($theme), (array) $this->body_theme);

    return $this;
  }

  /**
   * @return array
   */
  public function getBodyTheme() {
    return $this->body_theme;
  }

  /**
   * @return array
   */
  public function getWrapperTheme() {
    return $this->wrapper_theme;
  }

  #</editor-fold>

  /**
   * Set default values for $this object
   */
  public function setDefaultValues() {
    $this->language       = user_preferred_language($GLOBALS['user']);
    $this->from           = variable_get('site_mail', ini_get('sendmail_from'));
    $this->send           = TRUE;
    $this->wrapper_theme  = array();
    $this->body_theme     = array();
    $this->params['mail'] = $this;

    $this->addHtmlHeaders();
  }

  /**
   * Appends the default theme sugestions as a fallback.
   */
  public function addDefaultTemplateSuggestions() {
    if ($this->getKey()) {

      if ($this->getLanguage() && isset($this->getLanguage()->language)) {
        $this->wrapper_theme[] = self::DEFAULT_WRAPPER_THEME . '__' . $this->getKey() . '__' . $this->getLanguage()->language;
        $this->body_theme[]    = self::DEFAULT_BODY_THEME . '__' . $this->getKey() . '__' . $this->getLanguage()->language;
      }

      $this->wrapper_theme[] = self::DEFAULT_WRAPPER_THEME . '__' . $this->getKey();
      $this->body_theme[]    = self::DEFAULT_BODY_THEME . '__' . $this->getKey();
    }

    $this->wrapper_theme[] = self::DEFAULT_WRAPPER_THEME;
    $this->body_theme[]    = self::DEFAULT_BODY_THEME;

    return $this;
  }

  /**
   * Render the subject and body.
   */
  public function render() {
    $this->subject_rendered = t($this->getSubject(), $this->getTokenValues(), array('langcode' => $this->language->language));

    $this->body_rendered    = theme('managed_mail_body', array(
      'body'         => $this->getBody(),
      'token_values' => $this->getTokenValues(),
      'mail'         => $this,
    ));

    return $this;
  }

  /**
   * Send the email.
   * Return the MailManager_ManagedMail object with the 'result' property set to indicate the success of the action.
   * Use $mail->result to check if the mail was sent or an error occurred.
   *
   * @return MailManager_ManagedMail
   */
  public function send() {
    // If no module is set we use the default
    if ($this->module === NULL) {
      $this->module = self::MODULE_NAME;
    }

    // Adds the default template callback suggestions
    $this->addDefaultTemplateSuggestions();

    // Check if all required properties have been set
    $this->validateObjectForSending();

    // Actually sends out the email
    $message = drupal_mail(self::MODULE_NAME, self::generateId($this), $this->to, $this->language, $this->params, $this->from, $this->send);

    // Return the mail object
    return isset($message['mail']) ? $message['mail'] : NULL;
  }

  #<editor-fold desc="--- Helpers ---">

  /**
   * @throws MailManager_ManagedMail_Exception
   */
  protected function validateObjectForSending() {
    if (!isset($this->to) || !$this->to) {
      throw new MailManager_ManagedMail_Exception('MailManager_ManagedMail object is missing the required "to" property.');
    }

    if (!isset($this->language) || !$this->language) {
      throw new MailManager_ManagedMail_Exception('MailManager_ManagedMail object is missing the required "language" property.');
    }

    return $this;
  }

  /**
   * Generate an id to be used in as an internal key to store and retrieve the object
   *
   * @param MailManager_ManagedMail $mail
   *
   * @return string
   * @throws MailManager_ManagedMail_Exception
   */
  public static function generateId(MailManager_ManagedMail $mail) {
    if (!isset($mail->module) || !$mail->module || !isset($mail->key) || !$mail->key) {
      throw new MailManager_ManagedMail_Exception('"module" and "key" properties must be set in order to register a managed mail with the registry. Please provide valid values for module and key.');
    }

    return implode(self::ID_SEPARATOR, array($mail->module, $mail->key));
  }

  /**
   * @param $id
   *
   * @return array
   */
  public static function parseId($id) {
    $parts = explode(self::ID_SEPARATOR, $id, 2);

    return array(
      'module' => $parts[0],
      'key'    => $parts[1],
    );
  }

  /**
   * Add necessary headers for sending HTML mail.
   */
  public function addHtmlHeaders() {
    $this->headers = array(
      'MIME-Version'              => '1.0',
      'Content-Type'              => 'text/html; charset=UTF-8; format=flowed',
      'Content-Transfer-Encoding' => '8Bit',
      'X-Mailer'                  => 'Drupal'
    );

    return $this;
  }

  public function generateTokenPlaceholder($token){
    return self::buildTokenPlaceholder(self::generateId($this), $token);
  }

  public static function buildTokenPlaceholder($id, $token){
    return '[' . self::MODULE_NAME . '_' . $id . ':' . $token . ']';
  }

  #</editor-fold>

}

class MailManager_ManagedMail_Exception extends Exception {

}
