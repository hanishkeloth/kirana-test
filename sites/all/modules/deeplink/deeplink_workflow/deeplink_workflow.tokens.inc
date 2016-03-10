<?php

/**
 * @file
 * Builds placeholder replacement tokens for deeplink-workflow-related data.
 */


/**
  * Implements hook_token_info().
  */
function deeplink_workflow_token_info() {
  $tokens['vbar-1st'] = array(
    'name' => t('1st part of current state name'),
    'description' => t('Returns 1st part of current workflow state of content separated by vertical bar (pipe).'),
    'type' => 'workflow',
  );
  $tokens['vbar-2nd'] = array(
    'name' => t('2nd part of current state name'),
    'description' => t('Returns 2nd part of current workflow state of content separated by vertical bar (pipe).'),
    'type' => 'workflow',
  );
  return $tokens;
}

/**
 * Implements hook_tokens().
 */
function deeplink_workflow_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();
  if ($type == 'workflow' && !empty($data['node'])) {
    $node = $data['node'];
    switch ($type) {
      case 'workflow': // make sure that we have workflow type token
        // Chained token relationships.
        foreach ($tokens as $name => $original) { // check each token...
          switch (end(explode(':', $name))) { // get the last bit of token
            case 'vbar-1st': // compare the last bit of token for selection
              $state_name = workflow_get_workflow_states_by_sid($node->workflow)->state;
              $replacements[$original] = current(explode('|', $state_name)); // get 1st part of workflow state (separated by pipe)
            break;
            case 'vbar-2nd': // compare the last bit of token for selection
              $replacements[$original] = end(explode('|', $state_name)); // get 2nd part of workflow state (separated by pipe)
            break;
          }
        }
        break;
    }
  }
  return $replacements;
}

