<?php

/**
 * @file
 * Feeds tamper plugin to fetch remote URLS.
 *
 * If the source data is a remote URL,
 * and the local equivalent does not exist in the system
 * fetch it,
 * copy it into an equivalent local filepath
 * update the files_managed to index it
 * return the local file wrapper URI.
 *
 * @see file_feeds_set_target()
 */

$plugin = array(
  'form'     => 'feeds_tamper_file_fetcher_form',
  'callback' => 'feeds_tamper_file_fetcher_callback',
  'name'     => 'File fetcher',
  'multi'    => 'skip',
  'category' => 'Other',
);

/**
 * Settings form.
 */
function feeds_tamper_file_fetcher_form($importer, $element_key, $settings) {
  $form = array();

  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => t('This plugin expects to be given a full remote URL as a file to download. It will save it locally, and transform the URL into a local Drupal URI path. The value of the field being tampered will be transformed from a remote URL to a local file URI, and that local file will become valid (registered in the database) and available. Intended for use when mapping the media.module/file_entity.module URI value.'),
  );
  $form['directory_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Directory prefix'),
    '#default_value' => isset($settings['directory_prefix']) ? $settings['directory_prefix'] : '',
  );
  $form['directory_strip'] = array(
    '#type' => 'textfield',
    '#title' => t('String to remove from the filepath when saving'),
    '#default_value' => isset($settings['directory_strip']) ? $settings['directory_strip'] : '',
    '#description' => t('Include directory slashes if needed'),
  );
  return $form;
}

/**
 * Fetcher callback.
 */
function feeds_tamper_file_fetcher_callback($result, $item_key, $element_key, &$field, $settings, $source) {
  // Seems I can't use Feeds log(). Make noise in watchdog instead.
  $item = $result->items[$item_key];

  // Figure out where is SHOULD be saved.
  $url_parts = parse_url($field);
  $expected_filepath = $url_parts['path'];

  // Remove unwanted path fragments.
  if (! empty($settings['directory_strip'])) {
    $expected_filepath = str_replace($settings['directory_strip'], '', $expected_filepath);
  }

  $expected_uri = file_build_uri($settings['directory_prefix'] . ltrim($expected_filepath, '/'));


  $strings = array(
    '%field' => $field,
    '%expected_uri' => $expected_uri,
    '!source' => l(basename($field), $field),
  );

  // Check local filesystem.
  if (!file_exists($expected_uri)) {
    watchdog(__FUNCTION__, 'Remote File %field does not have a local copy. Need to fetch it to %expected_uri now.', $strings, WATCHDOG_NOTICE);
    $source_file = file_uri_to_object($expected_uri);

    // MAYBE can background the actual fetch into a queue job
    // just make the DB entry, and hope nobody notices until it's needed.
    $fake_it = FALSE;
    // Fake it can't work if we are using stage_file_proxy pointing at a site
    // that is not the same source.
    if (!$fake_it) {
      $dirname = dirname($expected_uri);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      if (!copy($field, $expected_uri)) {
        // This is a pain, but non-fatal.
        drupal_set_message(t("File copy from remote %field to local location (%expected_uri) failed, aborting. Maybe it's not available from the source.", $strings));
        watchdog(__FUNCTION__, "File copy from remote %field to local location (%expected_uri) failed, aborting. Maybe it's not available from the source.", $strings, WATCHDOG_INFO);
        // Can I invalidate it here?
        // $entity->feeds_item->skip = TRUE;
        return NULL;
      }
      drupal_set_message(t("File copy from remote !source to %expected_uri Succeeded.", $strings));
      watchdog(__FUNCTION__, 'Remote File import from !source SUCCEEDED and is now available at %expected_uri.', $strings, WATCHDOG_INFO);
    }
    else {
      // If not faking it, cannot use the temporary dl method
      // as file_move then complains.
      // Instead, make a db entry assuming it's in its final place.
      $source_file = file_uri_to_object($expected_uri);
    }

    // Whether we fetched the file or not, if it's on the system, it needs to
    // have an entry in file_managed

    // IF we want to recycle fids, we need to insert a fake placeholder into the
    // file table, to fool the API. This allows me to define my own fid.
    if (!empty($item['file id'])) {
      $source_file->fid = $item['file id'];
      $source_file->status = FILE_STATUS_PERMANENT;
      $strings += array(
        '%fid' => $source_file->fid,
      );

      watchdog(__FUNCTION__, 'Attempting to recycle a file id fid:%fid.', $strings, WATCHDOG_INFO);
      // But look-ahead first.
      $existing_file_record = file_load($source_file->fid);
      // Now insert our placeholder.
      if (!$existing_file_record) {

        // Additional paranoia - manual replacements may now be getting
        // in the way with a new fid.
        // Occasionally happens when the import breaks.
        $additional_lookahead = file_load_multiple(array(), array('uri' => $expected_uri));
        if ($existing_by_uri = reset($additional_lookahead)) {
          // Found one in the slot I was about to fill.
          $strings['%existing_fid'] = $existing_by_uri->fid;
          drupal_set_message(t("Cannot recycle an old file fid:%fid id as fid:%existing_fid already exists for %expected_uri. That just means we don't need to add the placeholder, and it should sort itself out anyway", $strings));
          watchdog(__FUNCTION__, "Cannot recycle an old file fid:%fid id as fid:%existing_fid already exists for %expected_uri. That just means we don't need to add the placeholder, and it should sort itself out anyway", $strings, WATCHDOG_NOTICE);
          // That's ok, as the data update will look it up by uri later anyway.
          // Gah, this happens too much. It's due to media.module auto-indexing
          // the file dir.
          // BRUTALLY reset it by CHANGING THS FID in the KEY COLUMN in the DB!
          // If anyone NEW is using the new fid, they lose. We need to recover
          // it for the oldies.
          $existing_by_uri->fid = $source_file->fid;
          drupal_write_record('files', $existing_by_uri);
          drupal_set_message(t("Brutally resetting the fid for %expected_uri back to fid:%fid from fid:%existing_fid . This means new usages of the file may get unhooked, but old expectations will work again.", $strings));
        }
        else {
          drupal_set_message(t('Recycling a file id. %field is fid:%fid and there is no pre-existing entry for %expected_uri', $strings));
          watchdog(__FUNCTION__, 'Recycling a file id. %field is fid:%fid and there is no pre-existing entry for %expected_uri', $strings);
          $source_file->type = 'placeholder';
          drupal_write_record('file_managed', $source_file);
        }
      }
    }
    // It would seem that as long as the file uri I set here matches
    // the entity file uri that gets set on feeds item save,
    // then all ends up matched together!
  }
  else {
    watchdog(__FUNCTION__, 'Remote File %field already has a local copy at %expected_uri.', array('%field' => $field, '%expected_uri' => $expected_uri), WATCHDOG_WARNING);
  }
  $field = $expected_uri;
}
