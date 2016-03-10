<?php

/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances - admin.
 */

function deeplink_workflow_settings() {
  $form = array();

  $form[DEEPLINK_WORKFLOW_CONTENT_TYPES] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Select the content types where workflow state can be changed.'),
    '#options' => _node_types_build()->names,
    '#default_value' => variable_get(DEEPLINK_WORKFLOW_CONTENT_TYPES, array()),
  );

  $form['deeplink_workflow_state_use_alt_name'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use alternative name for workflow states'),
      '#description' => t("Use alternative name for workflow states, which means to show the 2nd part of workflow name separated by vertical bar (pipe). E.g. If the state has name 'Accepted|Accept', the state name will be 'Accept'."),
      '#default_value' => variable_get('deeplink_workflow_state_use_alt_name', FALSE),
  );

  return system_settings_form($form);
}

