<?php
/**
 * @file
 * Token integration for Mail Manager module.
 * User: cristian.burtan
 */

class MailManager_Token {

  /**
   * Implements hook_token_info().
   */
  public static function info() {

    $ns = MailManager_ManagedMail::MODULE_NAME;

    $registered_mails = MailManager_Registry::getAll();

    $types  = array();
    $tokens = array();

    foreach ($registered_mails as $mail) {

      $token_list = $mail->getTokenList();
      $token_list += MailManager::defaultTokensList();

      if (!empty($token_list)) {

        $id       = MailManager_ManagedMail::generateId($mail);
        $type_key = $ns . '_' . $id;

        $types[$type_key] = array(
          'name'        => t('Managed Mail'),
          'description' => t('Tokens related to Managed Mail mailkey: ' . $id),
          'needs-data'  => $type_key,
        );

        foreach ($token_list as $name => $description) {
          $tokens[$type_key][$name] = array(
            'name'        => $name,
            'description' => $description,
          );
        }
      }

    }

    return array(
      'types'  => $types,
      'tokens' => $tokens,
    );
  }

  /**
   * Implements hook_tokens().
   */
  public static function tokens($type, $tokens, array $data = array(), array $options = array()) {

    $replacements = array();

    if (isset($data['mail']) && $data['mail'] && $data['mail'] instanceof MailManager_ManagedMail) {
      $token_values = $data['mail']->getTokenValues();
      $token_values += MailManager::defaultTokensValues($data['mail']);
      if (!empty($token_values)) {
        foreach ($tokens as $name => $original) {
          if (isset($token_values[$name])) {
            $replacements[$original] = $token_values[$name];
          }
        }
      }
    }

    return $replacements;
  }

}