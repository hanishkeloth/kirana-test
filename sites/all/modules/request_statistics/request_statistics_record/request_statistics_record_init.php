<?php
/**
 * @file
 * Request statistics record data for visitor and page.
 */

/**
 * Respond to hook_init().
 *
 * Function db_query is faster than db_select.
 */
class RequestStatisticsRecordInit {
  protected $rsr;
  /**
   * Accept common code and settings.
   *
   * @param object $request_statistics_record
   *   Common code and settings for record.
   */
  public function __construct($request_statistics_record) {
    $this->rsr = $request_statistics_record;
  }
  /**
   * Respond to hook_init().
   */
  public function init() {
    global $user;
    $module_name = $this->rsr->moduleName();
    $rs = $this->rsr->rs();
    $visitor_primary_key = $rs->visitorPrimaryKey();
    $visitor_table_name = $rs->visitorTableName();
    if (!isset($_SESSION[$module_name])) {
      $_SESSION[$module_name] = array();
    }
    elseif (isset($_SESSION[$module_name][$visitor_primary_key])
      and !isset($_SESSION[$module_name]['user_id'])) {
      $_SESSION[$module_name] = array();
    }
    elseif (isset($_SESSION[$module_name][$visitor_primary_key])
      and isset($_SESSION[$module_name]['user_id'])
      and $_SESSION[$module_name]['user_id'] != $user->uid) {
      $_SESSION[$module_name] = array();
    }
    if (!isset($_SESSION[$module_name][$visitor_primary_key])) {
      $visitor_id = db_insert($visitor_table_name)
        ->fields(array('user_id' => $user->uid))
        ->execute();
      if ($visitor_id === FALSE) {
        watchdog($module_name, 'Visitor id failed: :v', array(':v' => serialize($visitor_id)));
      }
      else {
        $_SESSION[$module_name][$visitor_primary_key] = $visitor_id;
        $_SESSION[$module_name]['user_id'] = $user->uid;
      }
    }
    if (isset($_SESSION[$module_name][$visitor_primary_key])) {
      drupal_add_js('var ' . $module_name . '_' . $visitor_primary_key . ' = ' . $_SESSION[$module_name][$visitor_primary_key] . ';', 'inline');
    }
  }

}
