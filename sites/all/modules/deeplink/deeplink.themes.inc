<?php
/**
 * @file
 * Deep link - Allow direct access to a specific item of content under certain circumstances - themes.
 */

function theme_deeplink($deeplink, $style = 'short') {
  return token_replace('[deeplink-link], expires in [deeplink-expires-in]', 'deeplink', $deeplink);
}

