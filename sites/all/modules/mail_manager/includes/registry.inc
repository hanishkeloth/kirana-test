<?php
/**
 * @file
 * MailManager_Registry Class Definition
 * User: cristian.burtan
 */

/**
 * Provides a registry for registering instances of MailManager_ManagedMail
 */
class MailManager_Registry {

  /**
   * Name of the hook to be used by client modules
   */
  const MAIL_MANAGER_REGISTRY_HOOK = 'managed_mail';

  /**
   * Container holding the registered mail objects
   *
   * @var
   */
  static $container;

  protected static $hooks_invoked = FALSE;

  /**
   * Add $mail object to the registry
   *
   * @param MailManager_ManagedMail $mail
   */
  public static function set(MailManager_ManagedMail $mail) {
    if (!isset($mail->module)) {
      $mail->module = MailManager_ManagedMail::MODULE_NAME;
    }
    $id                   = MailManager_ManagedMail::generateId($mail);
    self::$container[$id] = $mail;
  }

  /**
   * Get registered object with $id
   *
   * @param $id
   *
   * @return MailManager_ManagedMail
   */
  public static function get($id) {
    if (!isset(self::$container[$id])) {
      $parts  = MailManager_ManagedMail::parseId($id);
      $module = $parts['module'];
      $mail   = module_invoke($module, self::MAIL_MANAGER_REGISTRY_HOOK);

      $mail->module = $module;

      if ($mail && $mail instanceof MailManager_ManagedMail) {
        self::$container[$id] = $mail;
      }

    }

    return self::$container[$id];
  }

  /**
   * Return all registered mail instances.
   *
   * @return MailManager_ManagedMail[]
   */
  public static function getAll() {
    self::buildFromHooks();
    return self::$container ?: array();
  }

  /**
   * Invoke all hooks implemented by client modules, collect all defined mail objects and register them with the registry
   *
   * @param bool $force Force invoking hooks again even if they were already invoked before.
   */
  public static function buildFromHooks($force = FALSE) {

    if (!self::$hooks_invoked || $force) {

      // We do not use module_invoke_all because we need to know the module that defines each MailManager_ManagedMail instance
      foreach (module_implements(self::MAIL_MANAGER_REGISTRY_HOOK) as $module) {
        $mail = module_invoke($module, self::MAIL_MANAGER_REGISTRY_HOOK);
        if ($mail instanceof MailManager_ManagedMail) {
          if (!isset($mail->module)) {
            $mail->module = $module;
          }
          $mail->addDefaultTemplateSuggestions();

          self::set($mail);
        }
      }

      self::$hooks_invoked = TRUE;
    }

  }

}
