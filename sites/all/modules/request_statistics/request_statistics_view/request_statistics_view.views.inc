<?php
/**
 * @file
 * Request statistics view data through Views.
 *
 * Some of the complicated code in t() is purely to stop pareview complaining.
 */

/**
 * Implements hook_views_data().
 *
 * You need a table definition per real table plus a column definition per
 * real column. You can also add fake columns for derived and related data.
 */
function request_statistics_view_views_data() {
  $rs = request_statistics();
  $display_name = $rs->displayName();
  $request_table_name = $rs->requestTableName();
  $request_table_display_name = $rs->requestTableDisplayName();
  $visitor_table_name = $rs->visitorTableName();
  $visitor_table_display_name = $rs->visitorTableDisplayName();
  $visitor_primary_key = $rs->visitorPrimaryKey();
  $tables = array();
  $table = array();
  $table['table']['group'] = t('@name', array('@name' => $display_name));
  $table['table']['base'] = array(
    'field' => $visitor_primary_key,
    'title' => t('@name', array('@name' => $visitor_table_display_name)),
    'help' => t('@table contains a row per logged in visitor.', array('@table' => $visitor_table_display_name)),
  );
  // Numeric text field. Is there an integer?
  $table[$visitor_primary_key] = array(
    'title' => t('Visitor id'),
    'help' => t('Primary key.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. Is there an integer?
  $table['user_id'] = array(
    'title' => t('User id'),
    'help' => t('{user}.uid.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Define a relationship to the {user} table, so example_table views can
    // add a relationship to nodes. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
      'base' => 'user',
      'base field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
      'title' => t('User relationship'),
      'help' => t('User data can be added through this relationship.'),
    ),
  );
  // This table references {user}.uid.
  $table['table']['join'] = array(
    'user' => array(
      // Primary key in the referenced table:
      'left_field' => 'uid',
      // Foreign key in this table:
      'field' => 'user_id',
    ),
  );
  $tables[$visitor_table_name] = $table;
  $table = array();
  $table['table']['group'] = t('@name', array('@name' => $display_name));
  $table['table']['base'] = array(
    'field' => 'request_id',
    'title' => t('@name', array('@name' => $request_table_display_name)),
    'help' => t('@name', array('@name contains a row per page request.' => $request_table_display_name)),
  );
  // Numeric text field. Is there an integer?
  $table['year'] = array(
    'title' => t('Year'),
    'help' => t('Year is the first primary key.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. Is there an integer?
  $table['month'] = array(
    'title' => t('Month'),
    'help' => t('Month is part of the primary key. Year then month.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. Is there an integer?
  $table['day'] = array(
    'title' => t('Day'),
    'help' => t('Day is part of the primary key. Year, month then day.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. Is there an integer?
  $table['hour'] = array(
    'title' => t('Hour'),
    'help' => t('Hour is part of primary key. Hour within day.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Request id is a text field.
  $table['request_id'] = array(
    'title' => t('Request id'),
    'help' => t('The request id is unique within year, month, day, and hour.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $table[$visitor_primary_key] = array(
    'title' => t('Visitor id'),
    'help' => t('Primary key.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Define a relationship to the {user} table, so example_table views can
    // add a relationship to nodes. If you want to define a relationship the
    // other direction, use hook_views_data_alter(), or use the 'implicit' join
    // method described above.
    'relationship' => array(
      'base' => $visitor_table_name,
      'base field' => $visitor_primary_key,
      'handler' => 'views_handler_relationship',
      'label' => t('Visitor'),
      'title' => t('Visitor relationship'),
      'help' => t('Visitor data can be added through this relationship.'),
    ),
  );
  // This table references {user}.uid.
  $table['table']['join'] = array(
    $visitor_table_name => array(
      // Primary key in the referenced table:
      'left_field' => $visitor_primary_key,
      // Foreign key in this table:
      'field' => $visitor_primary_key,
    ),
  );
  // User agent string.
  $table['user_agent'] = array(
    'title' => t('User agent'),
    'help' => t('User agent contains whatever the Web browser or robot decides to send. The content may be misleading.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Browser type from User agent string.
  $table['browser_type'] = array(
    'title' => t('Browser type'),
    'help' => t('Browser type derived from the user agent.'),
    'real field' => 'user_agent',
    'field' => array(
      'handler' => 'requestStatisticsViewHandlerFieldBrowserType',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Referrer URI.
  $table['referrer_uri'] = array(
    'title' => t('Referrer URI'),
    'help' => t('Referrer URI may be missing or incomplete.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Request scheme.
  $table['request_scheme'] = array(
    'title' => t('Request scheme'),
    'help' => t('Request scheme is usually http or https.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Request path.
  $table['request_path'] = array(
    'title' => t('Request path'),
    'help' => t('Request path may be empty for visits to the home page.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Request query.
  $table['request_query'] = array(
    'title' => t('Request query'),
    'help' => t('Request query is often empty.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Request fragment.
  $table['request_fragment'] = array(
    'title' => t('Request fragment'),
    'help' => t('Request fragment is mostly empty.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['inner_height'] = array(
    'title' => t('Inner height'),
    'help' => t('Inner height is the height left after scroll bars.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['inner_width'] = array(
    'title' => t('Inner width'),
    'help' => t('Inner width is the width left after scroll bars.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['outer_height'] = array(
    'title' => t('Outer height'),
    'help' => t('Outer height is the height including scroll bars.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['outer_width'] = array(
    'title' => t('Outer width'),
    'help' => t('Outer width is the width including scroll bars.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['screen_height'] = array(
    'title' => t('Screen height'),
    'help' => t('Screen height may be the height of the physical screen.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Numeric text field. This is a full integer field.
  $table['screen_width'] = array(
    'title' => t('Screen width'),
    'help' => t('Screen width may be the width of the physical screen.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  $tables[$request_table_name] = $table;
  return $tables;
}
