<?php
/**
 * @file
 * Request statistics view data through Views.
 */

/**
 * Implements Views field handler for browser type.
 *
 * The type is derived from user agent.
 */
class RequestStatisticsViewHandlerFieldBrowserType extends views_handler_field {
  /**
   * Provide the SQL for the query.
   *
   * Add field accepts a table alias and will use the normal table name if you
   * leave the table alias empty.
   *
   * We then provide our special SQL as the second parameter, the real field.
   *
   * Our new column name is added as the third parameter, the column alias.
   */
  public function query() {
    // add_field($this->table_alias, $this->real_field, alias, $params);
    $this->field_alias = $this->query->add_field(
      NULL,
      "if (`user_agent` like '%mobile%', 'mobile', if (`user_agent` like '%tablet%', 'tablet', 'desktop'))",
      'browser_type'
    );
  }

}
