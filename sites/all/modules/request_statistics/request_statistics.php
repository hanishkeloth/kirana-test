<?php
/**
 * @file
 * Request statistics for visitor and page.
 *
 * My apologies for the UglyCase and lowerUglyCase names.
 * Someone at Drupal.org decided we are not allowed to write semantic code.
 */

/**
 * Common data definitions.
 *
 * Drupal requires non semantic UglyCase for class names.
 */
class RequestStatistics {
  protected $machineName = 'request_statistics';
  protected $displayName = 'Request statistics';
  protected $menuPathPrefix = 'admin/reports/';
  protected $requestDescription = 'Request statistics for request. Usually a page.';
  protected $requestPrimaryKeys = array(
    'year',
    'month',
    'day',
    'hour',
    'request_id',
  );
  protected $requestTableDisplayName = 'Request statistics request';
  protected $requestTableName = 'request_statistics_request';
  protected $visitorDescription = 'Request statistics for a visitor.';
  protected $visitorPrimaryKey = 'visitor_id';
  protected $visitorTableDisplayName = 'Request statistics visitor';
  protected $visitorTableName = 'request_statistics_visitor';
  /**
   * Machine name is the module name for use in code.
   */
  public function machineName() {
    return $this->machineName;
  }
  /**
   * Display name is the module name for display to humans.
   */
  public function displayName() {
    return $this->displayName;
  }
  /**
   * Menu path prefix is the common prefix for all admin menu paths.
   */
  public function menuPathPrefix() {
    return $this->menuPathPrefix;
  }
  /**
   * Request table human readable description.
   */
  public function requestDescription() {
    return $this->requestDescription;
  }
  /**
   * Request primary keys is a list of the primary keys for request table.
   */
  public function requestPrimaryKeys() {
    return $this->requestPrimaryKeys;
  }
  /**
   * Request table display name is the human readable name of the request table.
   */
  public function requestTableDisplayName() {
    return $this->requestTableDisplayName;
  }
  /**
   * Request table name is the internal name of the request table.
   */
  public function requestTableName() {
    return $this->requestTableName;
  }
  /**
   * Visitor table human readable description.
   */
  public function visitorDescription() {
    return $this->visitorDescription;
  }
  /**
   * Visitor primary key is the primary key for visitor table.
   */
  public function visitorPrimaryKey() {
    return $this->visitorPrimaryKey;
  }
  /**
   * Visitor table display name is the human readable name of the visitor table.
   */
  public function visitorTableDisplayName() {
    return $this->visitorTableDisplayName;
  }
  /**
   * Visitor table name is the internal name of the visitor table.
   */
  public function visitorTableName() {
    return $this->visitorTableName;
  }

}
