<?php

/**
 * @file
 * Rate widget theme
 */
?>
<ul>
  <li class="thumb-up">
    <?php print $up_button; ?>
    <div class="percent"><?php print $results['count']; ?></div>
  </li>
  <li class="thumb-down">
    <?php print $down_button; ?>
    <div class="percent"><?php print $results['count']; ?></div>
  </li>
</ul>
<?php

if ($info) {
  print '<div class="rate-info">' . $info . '</div>';
}

if ($display_options['description']) {
  print '<div class="rate-description">' . $display_options['description'] . '</div>';
}