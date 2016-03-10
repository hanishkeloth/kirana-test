<?php
/**
 * @file
 * Request statistics record data for visitor and page.
 *
 * We may be recording visits by anonymous users.
 * Make sure anyone can access this entry.
 * The statistics are only switched on for the occasional sample.
 * If you are going to record on a frequent basis, include a token
 * to limit access to legitimate requests.
 */

/**
 * Respond to hook_menu().
 */
class RequestStatisticsRecordMenu {
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
   * Respond to hook_menu().
   */
  public function menu() {
    $items = array();
    $items[$this->rsr->moduleName()] = array(
      'title' => $this->rsr->displayName(),
      'page callback' => $this->rsr->pageCallbackName(),
      'access callback' => TRUE,
      'type' => MENU_CALLBACK,
    );
    return $items;
  }

}
