<?php
/**
 * @file
 * Implements Feeds support for Birthdays fields.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 */
function birthdays_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'birthdays_date') {
      $targets[$name] = array(
        'name' => check_plain($instance['label']),
        'callback' => 'birthdays_feeds_set_target',
        'description' => t('The @label field of the node.', array('@label' => $instance['label'])),
      );
    }
  }
}

/**
 * Callback for mapping. Here is where the actual mapping happens.
 *
 * When the callback is invoked, $target contains the name of the field the
 * user has decided to map to and $value contains the value of the feed item
 * element the user has picked as a source.
 */
function birthdays_feeds_set_target($source, $entity, $target, $value, $mapping) {
  if (empty($value)) {
    return;
  }

  // Handle non-multiple value fields.
  if (!is_array($value)) {
    $value = array($value);
  }

  $entity_type = $entity->feeds_item->entity_type;
  $bundle = $entity->type;
  $instance = field_info_instance($entity_type, $target, $bundle);
  $dateformat = $instance['widget']['settings']['dateformat'];
  $dateformat_noyear = str_ireplace(array('y-', '-y', 'y/', '/y', 'y'), '', $dateformat);

  // Iterate over all values.
  $i = 0;
  $info = field_info_field($target);

  $field = array();
  foreach ($value as $v) {
    if (empty($v[0])) {
      continue;
    }
    if (!is_array($v) && !is_object($v)) {
      $parsed = date_parse_from_format($dateformat, $v);
      if (empty($parsed['year']) || empty($parsed['month']) || empty($parsed['day'])) {
        $parsed = date_parse_from_format($dateformat_noyear, $v);
      }
      if ($parsed['error_count'] == 0) {
        $field[$entity->language][$i] = array(
          'day' => $parsed['day'],
          'month' => $parsed['month'],
          'year' => !empty($parsed['year']) ? $parsed['year'] : 0,
          'triggers' => !empty($instance['settings']['triggers']['user']) ? 1 : 0,
        );
      }
    }
    if ($info['cardinality'] == 1) {
      break;
    }
    $i++;
  }
  $entity->{$target} = $field;
}

