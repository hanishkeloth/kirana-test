<?php

/**
 * @file
 * Default view definitions for Feeds.
 */

/**
 * Implementation of hook_views_default_views().
 */
function personalised_feed_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'personalised_feeds';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Personalised Feeds';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Personalised Feeds';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Hashtag image */
  $handler->display->display_options['fields']['field_hashtag_image']['id'] = 'field_hashtag_image';
  $handler->display->display_options['fields']['field_hashtag_image']['table'] = 'field_data_field_hashtag_image';
  $handler->display->display_options['fields']['field_hashtag_image']['field'] = 'field_hashtag_image';
  $handler->display->display_options['fields']['field_hashtag_image']['label'] = '';
  $handler->display->display_options['fields']['field_hashtag_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_hashtag_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_hashtag_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Taxonomy term: Term ID */
  $handler->display->display_options['fields']['tid']['id'] = 'tid';
  $handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['tid']['field'] = 'tid';
  $handler->display->display_options['fields']['tid']['label'] = '';
  $handler->display->display_options['fields']['tid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['tid']['separator'] = '';
  /* Field: Taxonomy term: Home feed */
  $handler->display->display_options['fields']['field_home_feed']['id'] = 'field_home_feed';
  $handler->display->display_options['fields']['field_home_feed']['table'] = 'field_data_field_home_feed';
  $handler->display->display_options['fields']['field_home_feed']['field'] = 'field_home_feed';
  $handler->display->display_options['fields']['field_home_feed']['label'] = '';
  $handler->display->display_options['fields']['field_home_feed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_home_feed']['settings'] = array(
    'field_delimiter' => '',
    'field_multiple_limit' => '-1',
    'field_multiple_limit_offset' => '0',
  );
  $handler->display->display_options['fields']['field_home_feed']['delta_offset'] = '0';
  /* Contextual filter: Taxonomy term: Home feed (field_home_feed) */
  $handler->display->display_options['arguments']['field_home_feed_value']['id'] = 'field_home_feed_value';
  $handler->display->display_options['arguments']['field_home_feed_value']['table'] = 'field_data_field_home_feed';
  $handler->display->display_options['arguments']['field_home_feed_value']['field'] = 'field_home_feed_value';
  $handler->display->display_options['arguments']['field_home_feed_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_home_feed_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_home_feed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_home_feed_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_home_feed_value']['limit'] = '0';
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'hashtags' => 'hashtags',
  );
  /* Filter criterion: Taxonomy term: Hashtag image (field_hashtag_image:fid) */
  $handler->display->display_options['filters']['field_hashtag_image_fid']['id'] = 'field_hashtag_image_fid';
  $handler->display->display_options['filters']['field_hashtag_image_fid']['table'] = 'field_data_field_hashtag_image';
  $handler->display->display_options['filters']['field_hashtag_image_fid']['field'] = 'field_hashtag_image_fid';
  $handler->display->display_options['filters']['field_hashtag_image_fid']['operator'] = 'not empty';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'personalised-feeds';
  $translatables['personalised_feeds'] = array(
    t('Master'),
    t('Personalised Feeds'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('.'),
    t('All'),
    t('Page'),
  );

  $views[$view->name] = $view;

  return $views;
}
