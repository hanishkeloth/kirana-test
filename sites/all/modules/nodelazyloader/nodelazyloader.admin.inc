<?php
/**
 * @file
 * Node Lazyloader Admin
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 */

/**
 * Admin Form: UI
 *
 */
function nodelazyloader_admin($form, &$form_state, $op = NULL) {

  global $_nodelazyloader_set;

  $settings = $_nodelazyloader_set;

  $form = array();

  $form['nodelazyloader'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Node Lazyloader Configuration',
    '#collapsible'   => TRUE,
    '#collapsed'     => FALSE,
    '#tree'          => TRUE,
    '#description'   => t(''),
  );

  $form['nodelazyloader']['enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enabled'),
    '#default_value' => $settings['enabled'],
    '#description'   => t('Enable/Disable Node Lazyloader (Useful for testing)'),
    '#prefix'        => '<div class="lazy-columns clearfix"><div class="lazy-column lazy-column-1">',
  );

  $form['nodelazyloader']['class'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Node Content Class'),
    '#default_value' => $settings['class'],
    '#description'   => t('Your theme\'s node content class, without the leading period.'),
  );

  $form['nodelazyloader']['distance'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Distance'),
    '#default_value' => $settings['distance'],
    '#size'          => 5,
    '#maxlength'     => 5,
    '#description'   => t('The distance (in pixels) of image to the viewable browser window before it loads the actual image.'),
  );

  $loader_dir = base_path() . drupal_get_path('module', 'nodelazyloader') . '/loader/';
  $loader = array(0 => t('None'));
  for ($i = 1; $i <= 8; $i++) {
    $loader[$i] = '<img alt="Node Lazyloader Icon" src="' . $loader_dir . 'loader-' . $i . '.gif" />';
  }

  $form['nodelazyloader']['loader_icon'] = array(
    '#type'          => 'radios',
    '#title'         => t('Loader Icon'),
    '#options'       => $loader,
    '#default_value' => $settings['loader_icon'],
    '#description'   => t('This icon will show when the actual image is not yet fully loaded.'),
    '#suffix'        => '</div>',
  );


  $form['nodelazyloader']['excludednodes'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Excluded Nodes'),
    '#default_value' => $settings['excludednodes'],
    '#description'   => t('List the node IDs to be excluded from lazyloading separated by comma. This is useful when a node is not behaving well with lazyloader. Ex. 1, 2, 3'),
    '#prefix'        => '<div class="lazy-column lazy-column-2">',
  );

  $form['nodelazyloader']['exclude'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Excluded Pages'),
    '#default_value' => $settings['exclude'],
    '#description'   => t('List the page paths to be excluded from lazyloading on each line. This is useful when you want to redirect your user with disabled javascript browser on pages with the same content but not using node lazyloading. Ex. node/1'),
    '#suffix'        => '</div></div>',
  );

  $form['save']      = array( '#type' => 'submit', '#value' => t('Save'), );
  $form['reset']     = array( '#type' => 'submit', '#value' => t('Reset'), );

  //dsm($form);
  return $form;
}


/**
 * Admin Form: Submit
 *
 */
function nodelazyloader_admin_submit($form, $form_state) {

  global $_nodelazyloader_defaults;

  $form_values = $form_state['values'];

  if ($form_values['op'] == 'Save') {
    $settings = $form_values['nodelazyloader']; // save user settings
  }
  elseif ($form_values['op'] == 'Reset') {
    $settings = $_nodelazyloader_defaults;      // save default settings
  }

  variable_set('nodelazyloader', $settings);
}
