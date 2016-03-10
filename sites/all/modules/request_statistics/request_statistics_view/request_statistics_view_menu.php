<?php
/**
 * @file
 * Request statistics view data through Views.
 */

/**
 * Responds to hook_menu().
 */
class RequestStatisticsViewMenu {
  /**
   * Responds to hook_menu().
   */
  public function menu() {
    $items = array();
    $rs = request_statistics();
    $path = $rs->menuPathPrefix() . str_replace('_', '-', $rs->machineName());
    $items[$path] = array(
      'title' => $rs->displayName(),
      'description' => $rs->displayName() . ' reports.',
      'page callback' => 'request_statistics_view_reports',
      'access arguments' => array('administer site configuration'),
      'file' => 'request_statistics_view_reports.php',
    );
    return $items;
  }

}
