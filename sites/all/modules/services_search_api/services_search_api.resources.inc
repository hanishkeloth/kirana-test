<?php

/**
 * Callback function for the index service call.
 */
function _services_search_api_resource_retrieve($index, $filter, $sort, $limit, $offset, $fields) {
  $options = array(
    'parse mode' => 'terms',
    'limit' => $limit,
    'offset' => $offset,
  );

  // Initialize the query object.
  $query = search_api_query($index, $options);

  // Set the filters, transforming the query array in a SearchAPIQueryFilter
  // object.
  if (!empty($filter) && is_array($filter)) {
    $query_filter = new SearchApiQueryFilter();
    _services_search_api_add_filter($filter, $query_filter);
    $query->filter($query_filter);
  }

  // Also set sorts.
  if (!empty($sort) && is_array($sort)) {
    foreach ($sort as $field => $mode) {
      $query->sort($field, $mode);
    }
  }

  $result = $query->execute();
  return _services_search_api_process_results($result, $query, $fields);
}

function _services_search_api_process_results($result, $query, $fields) {
  if (empty($result['results']) || !is_array($result['results'])) {
    return FALSE;
  }

  module_load_include('inc', 'services_entity', 'services_entity.resources');
  $fields = _services_entity_transform_fields($fields);

  $entity_type = $query->getIndex()->item_type;
  $entities = entity_load($entity_type, array_keys($result['results']));

  // Allow other modules to alter the entities retrieved.
  drupal_alter('services_search_api_postprocess', $entities, $entity_type);

  foreach ($entities as $entity_id => $entity) {
    // Transform entities and add extra information to properties.
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $entities[$entity_id] = (object) services_entity_prepare_structure($wrapper, $fields, $entity_type);
  }

  return $entities;
}

/**
 * Prepare the query filters for the Search API query object.
 */
function _services_search_api_add_filter(array $filter, &$query_filter) {
  // Allow to use simpler queries such as filter[title]=toto and assume a ~and
  // conjuction fot those.
  if (empty($filter['~and']) && empty($filter['~or'])) {
    $filter = array('~and' => $filter);
  }

  foreach ($filter as $key => $value) {
    if (is_array($value) && !empty($value)) {
      $conjunction = 'AND';
      if ($key == '~or') {
        $conjunction = 'OR';
      }
      $process_filter = new SearchApiQueryFilter($conjunction);
      foreach ($value as $k => $v) {
        if ($k <> '~and' && $k <> '~or') {
          $field_name = $k;
          if (is_array($v) && !empty($v)) {
            $process_filter->condition($field_name, reset($v), _services_search_api_operator(key($v)));
          }
          else {
            $process_filter->condition($field_name, $v);
          }
        }
        else {
          _services_search_api_add_filter(array($k => $v), $process_filter);
        }
      }

      if (!empty($query_filter) && $query_filter instanceof SearchApiQueryFilter) {
        $query_filter->filter($process_filter);
      }
      else {
        $query_filter = $process_filter;
      }
    }
  }
}

/**
 * Transform the operator into Search API supported ones.
 */
function _services_search_api_operator($operator) {
  $operators = array(
    '~gt' => '>',
    '~lt' => '<',
    '~gte' => '>=',
    '~lte' => '<=',
    '~ne' => '<>',
  );
  return isset($operators[$operator]) ? $operators[$operator] : '=';
}
