<?php
/**
 * @file
 * Block Lazyloader Admin
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 */

/**
 * Admin Form: UI
 *
 */
function blocklazyloader_admin($form, &$form_state, $op = NULL) {

  global $_blocklazyloader_set;

  $settings = $_blocklazyloader_set;

  $form = array();

  $form['blocklazyloader'] = array(
    '#type'          => 'fieldset',
    '#title'         => 'Block Lazyloader Configuration',
    '#collapsible'   => TRUE,
    '#collapsed'     => FALSE,
    '#tree'          => TRUE,
    '#description'   => t(''),
  );

  $form['blocklazyloader']['enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enabled'),
    '#default_value' => $settings['enabled'],
    '#description'   => t('Enable/Disable Block Lazyloader (Useful for testing)'),
    '#prefix'        => '<div class="lazy-columns clearfix"><div class="lazy-column lazy-column-1">',
  );

  $form['blocklazyloader']['class'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Block Content Class'),
    '#default_value' => $settings['class'],
    '#description'   => t('Your theme\'s block content class, without the leading period.'),
  );

  $form['blocklazyloader']['distance'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Distance'),
    '#default_value' => $settings['distance'],
    '#size'          => 5,
    '#maxlength'     => 5,
    '#description'   => t('The distance (in pixels) of image to the viewable browser window before it loads the actual image.'),
  );

  $loader_dir = base_path() . drupal_get_path('module', 'blocklazyloader') . '/loader/';
  $loader = array(0 => t('None'));
  for ($i = 1; $i <= 8; $i++) {
    $loader[$i] = '<img alt="Block Lazyloader Icon" src="' . $loader_dir . 'loader-' . $i . '.gif" />';
  }

  $form['blocklazyloader']['loader_icon'] = array(
    '#type'          => 'radios',
    '#title'         => t('Loader Icon'),
    '#options'       => $loader,
    '#default_value' => $settings['loader_icon'],
    '#description'   => t('This icon will show when the actual image is not yet fully loaded.'),
    '#suffix'        => '</div>',
  );


  $form['blocklazyloader']['excludedblocks'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Excluded Blocks'),
    '#default_value' => $settings['excludedblocks'],
    '#description'   => t('List the block IDs to be excluded from lazyloading separated by comma. This is useful when a block is not behaving well with lazyloader. Ex. block-system-main'),
    '#prefix'        => '<div class="lazy-column lazy-column-2">',
  );

  $form['blocklazyloader']['exclude'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Excluded Pages'),
    '#default_value' => $settings['exclude'],
    '#description'   => t('List the page paths to be excluded from lazyloading on each line. This is useful when you want to redirect your user with disabled javascript browser on pages with the same content but not using block lazyloading. Ex. node/1'),
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
function blocklazyloader_admin_submit($form, $form_state) {

  global $_blocklazyloader_defaults;

  $form_values = $form_state['values'];

  if ($form_values['op'] == 'Save') {
    $settings = $form_values['blocklazyloader']; // save user settings
  }
  elseif ($form_values['op'] == 'Reset') {
    $settings = $_blocklazyloader_defaults;      // save default settings
  }

  variable_set('blocklazyloader', $settings);
}
