<?php
/**
 * @file
 * Request statistics view data through Views.
 *
 * There is some ugly code in here because pareview rejects some of the better
 * code practices. Pareview also complains about use of t() as a normal
 * function.
 */

/**
 * Menu callback. Reports page.
 */
function request_statistics_view_reports() {
  $content = array();
  $content[] = '<p>' . t('Request statistics view data through Views.') . '</p>';
  require_once 'request_statistics_view.views_default.inc';
  $views = request_statistics_view_views_default_views();
  foreach ($views as $view) {
    foreach ($view->display as $view_display) {
      $display_options = $view_display->display_options;
      if (isset($display_options['path'])) {
        $path = $display_options['path'];
        $title = $path;
        if (isset($display_options['title'])) {
          $title = $display_options['title'];
        }
        elseif (isset($view->human_name)) {
          $title = $view->human_name;
        }
        $content[] = '<p><strong>' . l($title, $path) . '</strong></p>';
        if (isset($display_options['display_description'])) {
          $content[] = '<p>' . t('@text', array('@text' => $display_options['display_description'])) . '</p>';
        }
        if (isset($display_options['display_comment'])) {
          $content[] = '<p>' . t('@text', array('@text' => $display_options['display_comment'])) . '</p>';
        }
      }
    }
  }
  return implode("\n", $content);
}
