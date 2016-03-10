<?php

/**
 * @file
 * Views custom cache first argument plugin.
 */

/**
 * Views caching given view's first argument.
 *
 * @see views_plugin_cache()
 */
class views_custom_cache_plugin_cache extends views_plugin_cache {

  /**
   * Implements views_plugin_cache#summary_title().
   */
  function summary_title() {
    return t("View's first argument");
  }

  /**
   * Implements views_object#option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['cache_time'] = array('default' => 3600);
    $options['per_role'] = array('default' => 1);
    return $options;
  }

  /**
   * Implements views_object#option_defaults().
   */
  function option_defaults(&$options) {
    $options['cache_time'] = 3600;
    $options['per_role'] = 1;
  }

  /**
   * Implements views_plugin#options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $options = array(
      86400 => t('1 day'),
      21600 => t('6 hours'),
      3600 => t('1 hour'),
      1800 => t('30 minutes'),
    );
    $options_per_user = array(1 => t('Yes'), 0 => t('No'));

    $form['cache_time'] = array(
      '#type' => 'select',
      '#title' => t('Cache duration time.'),
      '#options' => $options,
      '#default_value' => $this->options['cache_time'],
    );

    $form['per_role'] = array(
      '#type' => 'select',
      '#title' => t('Cache per role?'),
      '#options' => $options_per_user,
      '#default_value' => $this->options['per_role'],
    );
  }

  /**
   * Implements views_plugin_cache#get_results_key().
   */
  function get_results_key() {
    $per_role = isset($this->options['per_role']) ? $this->options['per_role'] : 1;
    if (!isset($this->_results_key)) {
      $this->_results_key = $this->view->name . ':' . $this->display->id . ':results:' . $this->get_first_arg();
      if ($per_role) {
        $this->_results_key .= ':' . $this->get_cache_key();
      }
    }
    return $this->_results_key;
  }

  /**
   * Implements views_plugin_cache#get_output_key().
   */
  function get_output_key() {
    $per_role = isset($this->options['per_role']) ? $this->options['per_role'] : 1;
    if (!isset($this->_output_key)) {
      $key_data = array(
        'theme' => $GLOBALS['theme'],
      );
      $this->_output_key = $this->view->name . ':' . $this->display->id . ':output:' . $this->get_first_arg();
      if ($per_role) {
        $this->_results_key .= ':' . $this->get_cache_key($key_data);
      }
    }

    return $this->_output_key;
  }

  /**
   * Implements views_plugin_cache#cache_expire().
   *
   * Determine the expiration time of the cache type, or NULL if no expire.
   *
   * @param string $type
   *   The cache type, either 'query', 'result' or 'output'.
   */
  function cache_expire($type) {
    $expiration_time = !empty($this->options['cache_time']) ? $this->options['cache_time'] : 3600;
    $cutoff = REQUEST_TIME - $expiration_time;

    return $cutoff;
  }

  /**
   * Implements views_plugin_cache#cache_set_expire().
   *
   * Determine expiration time in the cache table of the cache type
   * or CACHE_PERMANENT if item shouldn't be removed automatically from cache.
   *
   * @param string $type
   *   The cache type, either 'query', 'result' or 'output'.
   */
  function cache_set_expire($type) {
    $expiration_time = !empty($this->options['cache_time']) ? $this->options['cache_time'] : 3600;
    $expiration_time = REQUEST_TIME + $expiration_time;

    return $expiration_time;
  }

  /**
   * Custom function which takes the first argument of view.
   */
  function get_first_arg() {
    $key = '';

    if (!empty($_GET['page'])) {
      $key .= $_GET['page'];
    }
    elseif (!empty($_POST['page'])) {
      $key .= $_POST['page'];
    }

    if (!empty($_GET['f'])) {
      // search api facets.
      $key .= serialize($_GET['f']);
    }

    if (!empty($this->view->args)) {
      $key .= $this->view->args[0];
    }

    if (!empty($this->view->exposed_raw_input)) {
      $key .= $this->view->exposed_raw_input[0];
    }

    if (empty($key)) {
      $key = 'none';
    }
    else {
      $key = md5($key);
    }

    return $key;
  }

}
