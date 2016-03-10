<?php
/**
 * @file
 * Request statistics view data through Views.
 */

/**
 * Implements hook_views_default_views().
 */
function request_statistics_view_views_default_views() {
  // List of views.
  $views = array();

  $view = new view();
  $view->name = 'request_statistics_browser_type';
  $view->description = 'Browser type is desktop, mobile, or tablet. Listed by year and month.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_request';
  $view->human_name = 'Request statistics browser type';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics browser type';
  $handler->display->display_options['display_comment'] = 'Browser type is desktop, mobile, or tablet.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'year' => 'year',
    'month' => 'month',
    'browser_type' => 'browser_type',
    'request_id' => 'request_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'month' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'browser_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Request statistics: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['separator'] = '';
  /* Field: Request statistics: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  $handler->display->display_options['fields']['month']['separator'] = '';
  /* Field: Request statistics: Browser type */
  $handler->display->display_options['fields']['browser_type']['id'] = 'browser_type';
  $handler->display->display_options['fields']['browser_type']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['browser_type']['field'] = 'browser_type';
  /* Field: COUNT(Request statistics: Request id) */
  $handler->display->display_options['fields']['request_id']['id'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_id']['field'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['group_type'] = 'count';
  $handler->display->display_options['fields']['request_id']['label'] = 'Requests';

  /* Display: Browser type */
  $handler = $view->new_display('page', 'Browser type', 'browser_type');
  $handler->display->display_options['display_comment'] = 'Browser type is desktop, mobile, or tablet. Listed by year, month. Mobile and tablet are in some user agent strings. All other user agents default to desktop.';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/browser-type';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics browser type';
  $handler->display->display_options['menu']['description'] = 'browser type listed by year and month.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'request_statistics_inner_width';
  $view->description = 'Inner width is the best indicator of available screen width on a device. Listed by year and month.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_request';
  $view->human_name = 'Request statistics inner width';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics inner width';
  $handler->display->display_options['display_comment'] = 'Inner width is the critical measurement for most devices. Outer width and screen width might be relevant in some cases.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'year' => 'year',
    'month' => 'month',
    'inner_width' => 'inner_width',
    'request_id' => 'request_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'month' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'inner_width' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Request statistics: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['separator'] = '';
  /* Field: Request statistics: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  $handler->display->display_options['fields']['month']['separator'] = '';
  /* Field: Request statistics: Inner width */
  $handler->display->display_options['fields']['inner_width']['id'] = 'inner_width';
  $handler->display->display_options['fields']['inner_width']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['inner_width']['field'] = 'inner_width';
  $handler->display->display_options['fields']['inner_width']['separator'] = '';
  /* Field: COUNT(Request statistics: Request id) */
  $handler->display->display_options['fields']['request_id']['id'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_id']['field'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['group_type'] = 'count';
  $handler->display->display_options['fields']['request_id']['label'] = 'Requests';

  /* Display: Inner width */
  $handler = $view->new_display('page', 'Inner width', 'inner_width');
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/inner-width';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics inner width';
  $handler->display->display_options['menu']['description'] = 'Inner width listed by year and month.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'request_statistics_path';
  $view->description = 'Path identifies a page. Find the most popular pages. Listed by year and month.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_request';
  $view->human_name = 'Request statistics path';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics path';
  $handler->display->display_options['display_comment'] = 'Path listed by year, month.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'year' => 'year',
    'month' => 'month',
    'request_path' => 'request_path',
    'request_id' => 'request_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'month' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Request statistics: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['separator'] = '';
  /* Field: Request statistics: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  $handler->display->display_options['fields']['month']['separator'] = '';
  /* Field: Request statistics: Request path */
  $handler->display->display_options['fields']['request_path']['id'] = 'request_path';
  $handler->display->display_options['fields']['request_path']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_path']['field'] = 'request_path';
  /* Field: COUNT(Request statistics: Request id) */
  $handler->display->display_options['fields']['request_id']['id'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_id']['field'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['group_type'] = 'count';
  $handler->display->display_options['fields']['request_id']['label'] = 'Requests';
  /* Filter criterion: Request statistics: Year */
  $handler->display->display_options['filters']['year']['id'] = 'year';
  $handler->display->display_options['filters']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['year']['field'] = 'year';
  $handler->display->display_options['filters']['year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['operator_id'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['year']['expose']['operator'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['identifier'] = 'year';
  $handler->display->display_options['filters']['year']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Request statistics: Month */
  $handler->display->display_options['filters']['month']['id'] = 'month';
  $handler->display->display_options['filters']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['month']['field'] = 'month';
  $handler->display->display_options['filters']['month']['exposed'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['operator_id'] = 'month_op';
  $handler->display->display_options['filters']['month']['expose']['label'] = 'Month';
  $handler->display->display_options['filters']['month']['expose']['operator'] = 'month_op';
  $handler->display->display_options['filters']['month']['expose']['identifier'] = 'month';
  $handler->display->display_options['filters']['month']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Path */
  $handler = $view->new_display('page', 'Path', 'path');
  $handler->display->display_options['display_comment'] = 'Path listed by year, month.';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/path';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics path';
  $handler->display->display_options['menu']['description'] = 'Path listed by year and month.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'request_statistics_request';
  $view->description = 'List every column and row by the primary keys of year, month, day, hour, and request id.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_request';
  $view->human_name = 'Request statistics request';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics request';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'year' => 'year',
    'month' => 'month',
    'day' => 'day',
    'hour' => 'hour',
    'request_id' => 'request_id',
    'user_agent' => 'user_agent',
    'request_scheme' => 'request_scheme',
    'request_path' => 'request_path',
    'inner_height' => 'inner_height',
    'inner_width' => 'inner_width',
    'outer_height' => 'outer_height',
    'outer_width' => 'outer_width',
    'screen_height' => 'screen_height',
    'screen_width' => 'screen_width',
    'referrer_uri' => 'referrer_uri',
    'request_query' => 'request_query',
    'request_fragment' => 'request_fragment',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'month' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'day' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'hour' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'user_agent' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_scheme' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_path' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'inner_height' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'inner_width' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'outer_height' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'outer_width' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'screen_height' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'screen_width' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'referrer_uri' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_query' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_fragment' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Request statistics: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['separator'] = '';
  /* Field: Request statistics: Month */
  $handler->display->display_options['fields']['month']['id'] = 'month';
  $handler->display->display_options['fields']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['month']['field'] = 'month';
  $handler->display->display_options['fields']['month']['separator'] = '';
  /* Field: Request statistics: Day */
  $handler->display->display_options['fields']['day']['id'] = 'day';
  $handler->display->display_options['fields']['day']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['day']['field'] = 'day';
  $handler->display->display_options['fields']['day']['separator'] = '';
  /* Field: Request statistics: Hour */
  $handler->display->display_options['fields']['hour']['id'] = 'hour';
  $handler->display->display_options['fields']['hour']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['hour']['field'] = 'hour';
  $handler->display->display_options['fields']['hour']['separator'] = '';
  /* Field: Request statistics: Request id */
  $handler->display->display_options['fields']['request_id']['id'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_id']['field'] = 'request_id';
  /* Field: Request statistics: User agent */
  $handler->display->display_options['fields']['user_agent']['id'] = 'user_agent';
  $handler->display->display_options['fields']['user_agent']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['user_agent']['field'] = 'user_agent';
  /* Field: Request statistics: Request scheme */
  $handler->display->display_options['fields']['request_scheme']['id'] = 'request_scheme';
  $handler->display->display_options['fields']['request_scheme']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_scheme']['field'] = 'request_scheme';
  /* Field: Request statistics: Request path */
  $handler->display->display_options['fields']['request_path']['id'] = 'request_path';
  $handler->display->display_options['fields']['request_path']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_path']['field'] = 'request_path';
  /* Field: Request statistics: Inner height */
  $handler->display->display_options['fields']['inner_height']['id'] = 'inner_height';
  $handler->display->display_options['fields']['inner_height']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['inner_height']['field'] = 'inner_height';
  $handler->display->display_options['fields']['inner_height']['separator'] = '';
  /* Field: Request statistics: Inner width */
  $handler->display->display_options['fields']['inner_width']['id'] = 'inner_width';
  $handler->display->display_options['fields']['inner_width']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['inner_width']['field'] = 'inner_width';
  $handler->display->display_options['fields']['inner_width']['separator'] = '';
  /* Field: Request statistics: Outer height */
  $handler->display->display_options['fields']['outer_height']['id'] = 'outer_height';
  $handler->display->display_options['fields']['outer_height']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['outer_height']['field'] = 'outer_height';
  $handler->display->display_options['fields']['outer_height']['separator'] = '';
  /* Field: Request statistics: Outer width */
  $handler->display->display_options['fields']['outer_width']['id'] = 'outer_width';
  $handler->display->display_options['fields']['outer_width']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['outer_width']['field'] = 'outer_width';
  $handler->display->display_options['fields']['outer_width']['separator'] = '';
  /* Field: Request statistics: Screen height */
  $handler->display->display_options['fields']['screen_height']['id'] = 'screen_height';
  $handler->display->display_options['fields']['screen_height']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['screen_height']['field'] = 'screen_height';
  $handler->display->display_options['fields']['screen_height']['separator'] = '';
  /* Field: Request statistics: Screen width */
  $handler->display->display_options['fields']['screen_width']['id'] = 'screen_width';
  $handler->display->display_options['fields']['screen_width']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['screen_width']['field'] = 'screen_width';
  $handler->display->display_options['fields']['screen_width']['separator'] = '';
  /* Field: Request statistics: Referrer URI */
  $handler->display->display_options['fields']['referrer_uri']['id'] = 'referrer_uri';
  $handler->display->display_options['fields']['referrer_uri']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['referrer_uri']['field'] = 'referrer_uri';
  /* Field: Request statistics: Request query */
  $handler->display->display_options['fields']['request_query']['id'] = 'request_query';
  $handler->display->display_options['fields']['request_query']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_query']['field'] = 'request_query';
  /* Field: Request statistics: Request fragment */
  $handler->display->display_options['fields']['request_fragment']['id'] = 'request_fragment';
  $handler->display->display_options['fields']['request_fragment']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_fragment']['field'] = 'request_fragment';
  /* Sort criterion: Request statistics: Year */
  $handler->display->display_options['sorts']['year']['id'] = 'year';
  $handler->display->display_options['sorts']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['sorts']['year']['field'] = 'year';
  /* Sort criterion: Request statistics: Month */
  $handler->display->display_options['sorts']['month']['id'] = 'month';
  $handler->display->display_options['sorts']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['sorts']['month']['field'] = 'month';
  /* Sort criterion: Request statistics: Day */
  $handler->display->display_options['sorts']['day']['id'] = 'day';
  $handler->display->display_options['sorts']['day']['table'] = 'request_statistics_request';
  $handler->display->display_options['sorts']['day']['field'] = 'day';
  /* Sort criterion: Request statistics: Hour */
  $handler->display->display_options['sorts']['hour']['id'] = 'hour';
  $handler->display->display_options['sorts']['hour']['table'] = 'request_statistics_request';
  $handler->display->display_options['sorts']['hour']['field'] = 'hour';
  /* Sort criterion: Request statistics: Request id */
  $handler->display->display_options['sorts']['request_id']['id'] = 'request_id';
  $handler->display->display_options['sorts']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['sorts']['request_id']['field'] = 'request_id';
  /* Filter criterion: Request statistics: Year */
  $handler->display->display_options['filters']['year']['id'] = 'year';
  $handler->display->display_options['filters']['year']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['year']['field'] = 'year';
  $handler->display->display_options['filters']['year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['operator_id'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['year']['expose']['operator'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['identifier'] = 'year';
  $handler->display->display_options['filters']['year']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Request statistics: Month */
  $handler->display->display_options['filters']['month']['id'] = 'month';
  $handler->display->display_options['filters']['month']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['month']['field'] = 'month';
  $handler->display->display_options['filters']['month']['exposed'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['operator_id'] = 'month_op';
  $handler->display->display_options['filters']['month']['expose']['label'] = 'Month';
  $handler->display->display_options['filters']['month']['expose']['operator'] = 'month_op';
  $handler->display->display_options['filters']['month']['expose']['identifier'] = 'month';
  $handler->display->display_options['filters']['month']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['month']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Request statistics: Day */
  $handler->display->display_options['filters']['day']['id'] = 'day';
  $handler->display->display_options['filters']['day']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['day']['field'] = 'day';
  $handler->display->display_options['filters']['day']['exposed'] = TRUE;
  $handler->display->display_options['filters']['day']['expose']['operator_id'] = 'day_op';
  $handler->display->display_options['filters']['day']['expose']['label'] = 'Day';
  $handler->display->display_options['filters']['day']['expose']['operator'] = 'day_op';
  $handler->display->display_options['filters']['day']['expose']['identifier'] = 'day';
  $handler->display->display_options['filters']['day']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['day']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Request statistics: Hour */
  $handler->display->display_options['filters']['hour']['id'] = 'hour';
  $handler->display->display_options['filters']['hour']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['hour']['field'] = 'hour';
  $handler->display->display_options['filters']['hour']['exposed'] = TRUE;
  $handler->display->display_options['filters']['hour']['expose']['operator_id'] = 'hour_op';
  $handler->display->display_options['filters']['hour']['expose']['label'] = 'Hour';
  $handler->display->display_options['filters']['hour']['expose']['operator'] = 'hour_op';
  $handler->display->display_options['filters']['hour']['expose']['identifier'] = 'hour';
  $handler->display->display_options['filters']['hour']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['hour']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Request */
  $handler = $view->new_display('page', 'Request', 'request');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Request statistics request';
  $handler->display->display_options['display_comment'] = 'List all the columns and rows by the primary keys of year, month, day, hour, and request id.';
  $handler->display->display_options['display_description'] = 'Request statistics table sorted by year, month, day, hour, request id.';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/request';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics by request';
  $handler->display->display_options['menu']['description'] = 'List all columns and rows in the request table by the primary keys of year, month, day, hour, and request id.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'request_statistics_user_agent';
  $view->description = 'User agent is the identification string sent by the Web browser or robot visiting your site.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_request';
  $view->human_name = 'Request statistics user agent';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics user agent';
  $handler->display->display_options['display_comment'] = 'User agent is an optional string sent by most of the Web browsers and robots visiting your site. The string may be fake. The robot may pretend to be a popular Web browser. The Browser Capabilities Project, http://browscap.org/, provides a file containing an extensive list of user agent strings and characteristics. The Drupal Browscap add-on module provides the browscap data to Drupal.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'user_agent' => 'user_agent',
    'browser_type' => 'browser_type',
    'request_id' => 'request_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'user_agent' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'browser_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'request_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Request statistics: User agent */
  $handler->display->display_options['fields']['user_agent']['id'] = 'user_agent';
  $handler->display->display_options['fields']['user_agent']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['user_agent']['field'] = 'user_agent';
  /* Field: Request statistics: Browser type */
  $handler->display->display_options['fields']['browser_type']['id'] = 'browser_type';
  $handler->display->display_options['fields']['browser_type']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['browser_type']['field'] = 'browser_type';
  /* Field: COUNT(Request statistics: Request id) */
  $handler->display->display_options['fields']['request_id']['id'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['table'] = 'request_statistics_request';
  $handler->display->display_options['fields']['request_id']['field'] = 'request_id';
  $handler->display->display_options['fields']['request_id']['group_type'] = 'count';
  $handler->display->display_options['fields']['request_id']['label'] = 'Requests';
  /* Filter criterion: Request statistics: User agent */
  $handler->display->display_options['filters']['user_agent']['id'] = 'user_agent';
  $handler->display->display_options['filters']['user_agent']['table'] = 'request_statistics_request';
  $handler->display->display_options['filters']['user_agent']['field'] = 'user_agent';
  $handler->display->display_options['filters']['user_agent']['operator'] = 'contains';
  $handler->display->display_options['filters']['user_agent']['exposed'] = TRUE;
  $handler->display->display_options['filters']['user_agent']['expose']['operator_id'] = 'user_agent_op';
  $handler->display->display_options['filters']['user_agent']['expose']['label'] = 'User agent contains';
  $handler->display->display_options['filters']['user_agent']['expose']['operator'] = 'user_agent_op';
  $handler->display->display_options['filters']['user_agent']['expose']['identifier'] = 'user_agent';
  $handler->display->display_options['filters']['user_agent']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['user_agent']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: User agent */
  $handler = $view->new_display('page', 'User agent', 'user_agent');
  $handler->display->display_options['display_comment'] = 'User agent listed with browser type and request count. The user agent string is provided by the Web browsers and robots visiting your site. The string may be fake. Robots sometimes pretend to be popular Web browsers. The browser type is derived from user agent.';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/user-agent';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics user agent';
  $handler->display->display_options['menu']['description'] = 'User agent listed with browser type and request count';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  $view = new view();
  $view->name = 'request_statistics_visitor';
  $view->description = 'List every column and row of the visitor table.';
  $view->tag = 'default';
  $view->base_table = 'request_statistics_visitor';
  $view->human_name = 'Request statistics visitor';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Request statistics visitor';
  $handler->display->display_options['display_comment'] = 'The master lists every column and row so you can see all the available data. Other displays reduce the columns, rows, or both.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer site configuration';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'visitor_id' => 'visitor_id',
    'user_id' => 'user_id',
  );
  $handler->display->display_options['style_options']['default'] = 'visitor_id';
  $handler->display->display_options['style_options']['info'] = array(
    'visitor_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'user_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['caption'] = 'Visitors with user id, if available.';
  /* Field: Request statistics: Visitor id */
  $handler->display->display_options['fields']['visitor_id']['id'] = 'visitor_id';
  $handler->display->display_options['fields']['visitor_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['fields']['visitor_id']['field'] = 'visitor_id';
  $handler->display->display_options['fields']['visitor_id']['separator'] = '';
  /* Field: Request statistics: User id */
  $handler->display->display_options['fields']['user_id']['id'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['fields']['user_id']['field'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['user_id']['separator'] = '';
  /* Sort criterion: Request statistics: Visitor id */
  $handler->display->display_options['sorts']['visitor_id']['id'] = 'visitor_id';
  $handler->display->display_options['sorts']['visitor_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['sorts']['visitor_id']['field'] = 'visitor_id';

  /* Display: Visitor */
  $handler = $view->new_display('page', 'Visitor', 'visitor');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Request statistics visitor by visitor';
  $handler->display->display_options['display_comment'] = 'Visitor id is the primary key of this table. List every column and row by the visitor id.';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/visitor';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics visitor by visitor id';
  $handler->display->display_options['menu']['description'] = 'All columns and rows in the request table sorted by the primary key of visitor id.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: User */
  $handler = $view->new_display('page', 'User', 'user');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Request statistics visitor by user';
  $handler->display->display_options['display_comment'] = 'A Visitor row may have a user id if the visitor was logged in. List the visitor rows by user id to see the logged in visitors.';
  $handler->display->display_options['display_description'] = 'Visitor data by user id';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Request statistics: User id */
  $handler->display->display_options['fields']['user_id']['id'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['fields']['user_id']['field'] = 'user_id';
  $handler->display->display_options['fields']['user_id']['element_label_colon'] = FALSE;
  /* Field: Request statistics: Visitor id */
  $handler->display->display_options['fields']['visitor_id']['id'] = 'visitor_id';
  $handler->display->display_options['fields']['visitor_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['fields']['visitor_id']['field'] = 'visitor_id';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Request statistics: User id */
  $handler->display->display_options['sorts']['user_id']['id'] = 'user_id';
  $handler->display->display_options['sorts']['user_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['sorts']['user_id']['field'] = 'user_id';
  /* Sort criterion: Request statistics: Visitor id */
  $handler->display->display_options['sorts']['visitor_id']['id'] = 'visitor_id';
  $handler->display->display_options['sorts']['visitor_id']['table'] = 'request_statistics_visitor';
  $handler->display->display_options['sorts']['visitor_id']['field'] = 'visitor_id';
  $handler->display->display_options['path'] = 'admin/reports/request-statistics/user';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Request statistics visitor by user id';
  $handler->display->display_options['menu']['description'] = 'All columns and rows from the visitor table sorted by user id.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views.
  $views[$view->name] = $view;

  // Return list of default views.
  return $views;
}
