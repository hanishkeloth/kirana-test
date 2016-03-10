<?php

/**
 * @file
 * faq.views_default.inc
 */

/**
 * Implementation of hook_views_default_views().
 */
function fboauth_extras_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'facebook_friends';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'fboauth_friends';
  $view->human_name = 'Facebook Friends';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Facebook Friends';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'picture' => 'picture',
    'uid_1' => 'uid_1',
    'first_name' => 'first_name',
    'invite_fboauth_friend_link' => 'invite_fboauth_friend_link',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'first_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'invite_fboauth_friend_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 0;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Facebook Friends: Friend's Facebook ID */
  $handler->display->display_options['relationships']['fbid']['id'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['fbid']['field'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['label'] = 'friend_fboauth';
  $handler->display->display_options['relationships']['fbid']['required'] = 0;
  /* Relationship: Facebook Friends: Base user's UID */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'base_user';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Facebook OAuth Users: User ID */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'friend_user';
  $handler->display->display_options['relationships']['uid_1']['required'] = 0;
  /* Field: Facebook Friends: Profile Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['external'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture']['empty_zero'] = 0;
  $handler->display->display_options['fields']['picture']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['picture']['width'] = '50';
  $handler->display->display_options['fields']['picture']['height'] = '50';
  $handler->display->display_options['fields']['picture']['alt'] = '[name]';
  $handler->display->display_options['fields']['picture']['title'] = '[name]';
  /* Field: Facebook Friends: Facebook Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid_1]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Facebook OAuth Users: User ID */
  $handler->display->display_options['fields']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['fields']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['fields']['uid_1']['field'] = 'uid';
  $handler->display->display_options['fields']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['fields']['uid_1']['label'] = '';
  $handler->display->display_options['fields']['uid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid_1']['empty'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid_1']['link_to_user'] = 1;
  /* Sort criterion: Facebook Friends: Facebook Name: Last Name */
  $handler->display->display_options['sorts']['last_name']['id'] = 'last_name';
  $handler->display->display_options['sorts']['last_name']['table'] = 'fboauth_friends';
  $handler->display->display_options['sorts']['last_name']['field'] = 'last_name';
  /* Contextual filter: Facebook Friends: Base user's UID */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'fboauth_friends';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['uid']['not'] = 0;
  /* Filter criterion: Facebook Friends: Still Friends */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Page (all) */
  $handler = $view->new_display('page', 'Page (all)', 'page_1');
  $handler->display->display_options['path'] = 'people/facebook-friends';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Facebook Friends';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block (all) */
  $handler = $view->new_display('block', 'Block (all)', 'block_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Friends on TrustPages';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['wrapper_class'] = 'user-list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Facebook Friends: Friend's Facebook ID */
  $handler->display->display_options['relationships']['fbid']['id'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['fbid']['field'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['label'] = 'friend_fboauth';
  $handler->display->display_options['relationships']['fbid']['required'] = 0;
  /* Relationship: Facebook Friends: Base user's UID */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'base_user';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Facebook OAuth Users: User ID */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'friend_user';
  $handler->display->display_options['relationships']['uid_1']['required'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture_1']['id'] = 'picture_1';
  $handler->display->display_options['fields']['picture_1']['table'] = 'users';
  $handler->display->display_options['fields']['picture_1']['field'] = 'picture';
  $handler->display->display_options['fields']['picture_1']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['picture_1']['label'] = '';
  $handler->display->display_options['fields']['picture_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['picture_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['picture_1']['link_photo_to_profile'] = 1;
  $handler->display->display_options['fields']['picture_1']['image_style'] = 'profile_picture_small';
  /* Field: Facebook Friends: Facebook Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid_1]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Facebook OAuth Users: User ID */
  $handler->display->display_options['fields']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['fields']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['fields']['uid_1']['field'] = 'uid';
  $handler->display->display_options['fields']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['fields']['uid_1']['label'] = '';
  $handler->display->display_options['fields']['uid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid_1']['empty'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid_1']['link_to_user'] = 1;
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = '';
  $handler->display->display_options['fields']['ops']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ops']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ops']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ops']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ops']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ops']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ops']['hide_alter_empty'] = 1;

  /* Display: Page (on site) */
  $handler = $view->new_display('page', 'Page (on site)', 'page');
  $handler->display->display_options['display_description'] = 'A list of Facebook friends who have Drupal account on this site.';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Facebook Friends: Still Friends */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Facebook OAuth Users: Facebook ID */
  $handler->display->display_options['filters']['fbid']['id'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['table'] = 'fboauth_users';
  $handler->display->display_options['filters']['fbid']['field'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['relationship'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['fbid']['group'] = 1;
  $handler->display->display_options['path'] = 'people/facebook-friends';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Facebook Friends';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block (on site) */
  $handler = $view->new_display('block', 'Block (on site)', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Friends on TrustPages';
  $handler->display->display_options['display_description'] = 'A list of Facebook friends who have Drupal account on this site.';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['wrapper_class'] = 'user-list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Facebook Friends: Friend's Facebook ID */
  $handler->display->display_options['relationships']['fbid']['id'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['fbid']['field'] = 'fbid';
  $handler->display->display_options['relationships']['fbid']['label'] = 'friend_fboauth';
  $handler->display->display_options['relationships']['fbid']['required'] = 0;
  /* Relationship: Facebook Friends: Base user's UID */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'fboauth_friends';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'base_user';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Relationship: Facebook OAuth Users: User ID */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'friend_user';
  $handler->display->display_options['relationships']['uid_1']['required'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture_1']['id'] = 'picture_1';
  $handler->display->display_options['fields']['picture_1']['table'] = 'users';
  $handler->display->display_options['fields']['picture_1']['field'] = 'picture';
  $handler->display->display_options['fields']['picture_1']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['picture_1']['label'] = '';
  $handler->display->display_options['fields']['picture_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['picture_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['picture_1']['link_photo_to_profile'] = 1;
  $handler->display->display_options['fields']['picture_1']['image_style'] = 'profile_picture_small';
  /* Field: Facebook Friends: Facebook Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid_1]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Facebook OAuth Users: User ID */
  $handler->display->display_options['fields']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['fields']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['fields']['uid_1']['field'] = 'uid';
  $handler->display->display_options['fields']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['fields']['uid_1']['label'] = '';
  $handler->display->display_options['fields']['uid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid_1']['empty'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid_1']['link_to_user'] = 1;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Facebook Friends: Still Friends */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Facebook OAuth Users: Facebook ID */
  $handler->display->display_options['filters']['fbid']['id'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['table'] = 'fboauth_users';
  $handler->display->display_options['filters']['fbid']['field'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['relationship'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['fbid']['group'] = 1;

  /* Display: Block - (off site, short) */
  $handler = $view->new_display('block', 'Block - (off site, short)', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Invite Friends';
  $handler->display->display_options['display_description'] = 'A list of Facebook friends who do not have Drupal account on this site.';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class'] = 'clearfix';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = 'Feeling lonely? Some of your friends still aren\'t on TrustPages!';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Facebook Friends: Facebook Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid_1]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Facebook Friends: Profile Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['external'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture']['empty_zero'] = 0;
  $handler->display->display_options['fields']['picture']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['picture']['alt'] = '[name]';
  $handler->display->display_options['fields']['picture']['title'] = '[name]';
  /* Field: Facebook OAuth Users: User ID */
  $handler->display->display_options['fields']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['fields']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['fields']['uid_1']['field'] = 'uid';
  $handler->display->display_options['fields']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['fields']['uid_1']['label'] = '';
  $handler->display->display_options['fields']['uid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid_1']['empty'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid_1']['link_to_user'] = 1;
  /* Field: Facebook Friends: Facebook Name: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['first_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['first_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['first_name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['first_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['first_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['first_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['first_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['first_name']['hide_alter_empty'] = 1;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Global: Random */
  $handler->display->display_options['sorts']['random']['id'] = 'random';
  $handler->display->display_options['sorts']['random']['table'] = 'views';
  $handler->display->display_options['sorts']['random']['field'] = 'random';
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Facebook Friends: Still Friends */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: Facebook OAuth Users: Facebook ID */
  $handler->display->display_options['filters']['fbid']['id'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['table'] = 'fboauth_users';
  $handler->display->display_options['filters']['fbid']['field'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['relationship'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['operator'] = 'empty';

  /* Display: Block - (off site) */
  $handler = $view->new_display('block', 'Block - (off site)', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Invite Friends to TrustPages';
  $handler->display->display_options['display_description'] = 'A list of Facebook friends who do not have Drupal account on this site.';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Find';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 1;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Facebook Friends: Facebook Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'user/[uid_1]';
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  /* Field: Facebook Friends: Profile Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['external'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['picture']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['picture']['alter']['html'] = 0;
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['picture']['hide_empty'] = 0;
  $handler->display->display_options['fields']['picture']['empty_zero'] = 0;
  $handler->display->display_options['fields']['picture']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['picture']['width'] = '50';
  $handler->display->display_options['fields']['picture']['height'] = '50';
  $handler->display->display_options['fields']['picture']['alt'] = '[name]';
  $handler->display->display_options['fields']['picture']['title'] = '[name]';
  /* Field: Facebook OAuth Users: User ID */
  $handler->display->display_options['fields']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['fields']['uid_1']['table'] = 'fboauth_users';
  $handler->display->display_options['fields']['uid_1']['field'] = 'uid';
  $handler->display->display_options['fields']['uid_1']['relationship'] = 'fbid';
  $handler->display->display_options['fields']['uid_1']['label'] = '';
  $handler->display->display_options['fields']['uid_1']['alter']['alter_text'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['text'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['uid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['uid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['uid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['uid_1']['empty'] = '[name]';
  $handler->display->display_options['fields']['uid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['uid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['uid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['uid_1']['link_to_user'] = 1;
  /* Field: Facebook Friends: Facebook Name: First Name */
  $handler->display->display_options['fields']['first_name']['id'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['table'] = 'fboauth_friends';
  $handler->display->display_options['fields']['first_name']['field'] = 'first_name';
  $handler->display->display_options['fields']['first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['first_name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['first_name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['first_name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['first_name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['first_name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['first_name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['first_name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['first_name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['first_name']['hide_alter_empty'] = 1;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Facebook Friends: Still Friends */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: Facebook OAuth Users: Facebook ID */
  $handler->display->display_options['filters']['fbid']['id'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['table'] = 'fboauth_users';
  $handler->display->display_options['filters']['fbid']['field'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['relationship'] = 'fbid';
  $handler->display->display_options['filters']['fbid']['operator'] = 'empty';
  /* Filter criterion: Facebook Friends: Facebook Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'fboauth_friends';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['operator'] = 'contains';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Facebook Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['required'] = 0;
  $handler->display->display_options['filters']['name']['expose']['multiple'] = FALSE;

  $export[$view->name] = $view;

  return $export;
}

