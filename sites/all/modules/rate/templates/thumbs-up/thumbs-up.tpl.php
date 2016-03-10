<?php

/**
 * @file
 * Rate widget theme
 */

print $up_button;

if ($info) {
  print '<span class="rate-info">' . $info . '</span>';
}

if ($display_options['description']) {
  print '<div class="rate-description">' . $display_options['description'] . '</div>';
}
