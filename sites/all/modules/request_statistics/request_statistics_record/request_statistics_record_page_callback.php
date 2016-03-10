<?php
/**
 * @file
 * Request statistics record data for visitor and page.
 */

/**
 * Callback for the Ajax request.
 *
 * This records the data from the Javascript Ajax call.
 * Check the data fits the database row.
 */
class RequestStatisticsRecordPageCallback {
  protected $rsr;
  protected $validFields = array(
    'year' => array('type' => 'int', 'size' => 'small'),
    'month' => array('type' => 'int', 'size' => 'tiny'),
    'day' => array('type' => 'int', 'size' => 'tiny'),
    'hour' => array('type' => 'int', 'size' => 'tiny'),
    'request_id' => array('type' => 'varchar', 'length' => 30),
    'visitor_id' => array('type' => 'int'),
    'referrer_uri' => array('type' => 'varchar', 'length' => 200),
    'user_agent' => array('type' => 'varchar', 'length' => 300),
    'request_scheme' => array('type' => 'varchar', 'length' => 10),
    'request_path' => array('type' => 'varchar', 'length' => 200),
    'request_query' => array('type' => 'varchar', 'length' => 200),
    'request_fragment' => array('type' => 'varchar', 'length' => 100),
    'inner_height' => array('type' => 'int'),
    'inner_width' => array('type' => 'int'),
    'outer_height' => array('type' => 'int'),
    'outer_width' => array('type' => 'int'),
    'screen_height' => array('type' => 'int'),
    'screen_width' => array('type' => 'int'),
  );
  /**
   * Request statistics record is the common code.
   *
   * @param object $request_statistics_record
   *   Object containing common code and settings.
   */
  public function __construct($request_statistics_record) {
    $this->rsr = $request_statistics_record;
  }
  /**
   * Callback method.
   */
  public function pageCallback() {
    if (!isset($_POST['query'])) {
      $this->error('No query in POST: @string', array('@string' => serialize($_POST)));
      return;
    }
    if ($_POST['query'] != 'insert' and $_POST['query'] != 'update') {
      $this->error('Query not insert or update: @string', array('@string' => serialize($_POST['query'])));
      return;
    }
    $rs = $this->rsr->rs();
    $primary_keys = $rs->requestPrimaryKeys();
    $table_name = $rs->requestTableName();
    foreach ($primary_keys as $name) {
      if (!isset($_POST[$name])) {
        $this->error('No @name in POST: @string', array('@name' => $name, '@string' => serialize($_POST)));
        return;
      }
    }
    $fields = array();
    // Split request_uri into scheme, path, query, and fragment.
    if (isset($_POST['request_uri'])) {
      $request_uri_parts = parse_url($_POST['request_uri']);
      unset($_POST['request_uri']);
      $parts = array('scheme', 'path', 'query', 'fragment');
      foreach ($parts as $name) {
        if (isset($request_uri_parts[$name])) {
          $field_name = 'request_' . $name;
          $field_maximum_length = $this->validFields[$field_name]['length'];
          $fields[$field_name] = substr($request_uri_parts[$name], 0, $field_maximum_length);
        }
      }
    }
    $other_string_fields = array('referrer_uri', 'request_id', 'user_agent');
    foreach ($other_string_fields as $field_name) {
      if (isset($_POST[$field_name])) {
        $field_maximum_length = $this->validFields[$field_name]['length'];
        $fields[$field_name] = substr($_POST[$field_name], 0, $field_maximum_length);
      }
    }
    $other_integer_fields = array(
      'inner_width', 'inner_height',
      'outer_height', 'outer_width',
      'screen_height', 'screen_width',
      'visitor_id',
    );
    foreach ($other_integer_fields as $field_name) {
      if (isset($_POST[$field_name])) {
        $fields[$field_name] = (integer) $_POST[$field_name];
      }
    }
    if ($_POST['query'] == 'insert') {
      // Insert new request.
      foreach ($primary_keys as $name) {
        $fields[$name] = $_POST[$name];
      }
      db_insert($table_name)
        ->fields($fields)
        ->execute();
    }
    elseif ($_POST['query'] == 'update') {
      // Update existing request.
      $query = db_update($table_name)->fields($fields);
      foreach ($primary_keys as $name) {
        $query->condition($name, $_POST[$name], '=');
      }
      // The following query execution could be checked and errors logged.
      $query->execute();
    }
  }
  /**
   * Log messages.
   *
   * Developers and installers should check for messages on first use.
   */
  protected function error($message, $variables = array()) {
    watchdog($this->rsr->moduleName(), $message, $variables, WATCHDOG_ERROR);
  }

}
