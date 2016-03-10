<?php

/**
 * @file
 * This is just an example template file and not used.
 * If you want to override the mail wrapper template copy this file into your theme directory and customize it.
 * Clear cache for the template to be picked up.
 *
 * Available variables:
 * - $body: The rendered body of the email
 *
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions.
 *
 * This variable is provided for context:
 * - $mail: The MailManager_ManagedMail object.
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see MailManager::themeWrapper()
 */
?>

<?php print $body; ?>
