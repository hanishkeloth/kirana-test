<?php
/**
 * @file
 * Request statistics record page request.
 */

/**
 * Request statistics record page request.
 */
class RequestStatisticsRecord {
  protected $moduleName = 'request_statistics_record';
  protected $displayName = 'Request statistics record';
  protected $pageCallbackName = 'request_statistics_record_page_callback';
  protected $rs;
  /**
   * Accept the common code.
   *
   * @param object $request_statistics
   *   Common code and settings.
   */
  public function __construct($request_statistics) {
    $this->rs = $request_statistics;
  }
  /**
   * Module internal name.
   */
  public function moduleName() {
    return $this->moduleName;
  }
  /**
   * Module human readable name for display.
   */
  public function displayName() {
    return $this->displayName;
  }
  /**
   * Initialise the record process.
   */
  public function init() {
    require_once 'request_statistics_record_init.php';
    $init = new RequestStatisticsRecordInit($this);
    return $init->init();
  }
  /**
   * Respond to hook_menu().
   */
  public function menu() {
    require_once 'request_statistics_record_menu.php';
    $menu = new RequestStatisticsRecordMenu($this);
    return $menu->menu();
  }
  /**
   * Callback to record a page visit.
   */
  public function pageCallback() {
    require_once 'request_statistics_record_page_callback.php';
    $page_callback = new RequestStatisticsRecordPageCallback($this);
    return $page_callback->pageCallback();
  }
  /**
   * Name of the callback for use in building code.
   */
  public function pageCallbackName() {
    return $this->pageCallbackName;
  }
  /**
   * Request statistics common code and settings object.
   */
  public function rs() {
    return $this->rs;
  }

}
