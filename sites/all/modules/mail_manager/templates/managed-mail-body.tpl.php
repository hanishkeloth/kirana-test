<?php

/**
 * @file
 * This is just an example template file and not used.
 * If you want to override the mail body template copy this file into your theme directory and customize it.
 * Clear cache for the template to be picked up.
 *
 * Available variables:
 * - $body: The raw body of the email (with tokens in place)
 * - $token_values: values array for the available tokens.
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
