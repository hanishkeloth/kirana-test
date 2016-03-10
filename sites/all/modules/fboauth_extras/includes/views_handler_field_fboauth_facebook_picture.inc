<?php

/**
 * Field handler to provide simple renderer that allows using a themed user link.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_fboauth_facebook_picture extends views_handler_field {

  function element_type($none_supported = FALSE, $default_empty = FALSE, $inline = FALSE) {
    if ($inline) {
      return 'span';
    }
    if ($none_supported) {
      if ($this->options['element_type'] === '0') {
        return '';
      }
    }
    if ($this->options['element_type']) {
      return check_plain($this->options['element_type']);
    }
    if ($default_empty) {
      return '';
    }
    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }

    return 'div';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['type'] = array('default' => 'square');
    $options['width'] = array('default' => '');
    $options['height'] = array('default' => '');
    $options['alt'] = array('default' => '');
    $options['title'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['type'] = array(
      '#title' => t("Source image size"),
      '#type' => 'select',
      '#options' => drupal_map_assoc(array('square', 'small', 'normal', 'large')),
      '#default_value' => $this->options['type'],
      '#description' => t('Square: 50x50, Small: 50xVar, Normal, 100xVar, Large, 200xVar'),
    );
    $form['width'] = array(
      '#title' => t("Output width"),
      '#type' => 'textfield',
      '#default_value' => $this->options['width'],
    );
    $form['height'] = array(
      '#title' => t("Output height"),
      '#type' => 'textfield',
      '#default_value' => $this->options['height'],
    );
    $form['alt'] = array(
      '#title' => t("Alternate text"),
      '#type' => 'textfield',
      '#default_value' => $this->options['alt'],
    );    
    $form['title'] = array(
      '#title' => t("Image title text"),
      '#type' => 'textfield',
      '#default_value' => $this->options['title'],
    );
  }

  function render($values) {
    $types = array(
      'square' => array(
        'width' => '50',
        'height' => '50',
      ),
      'small' => array(
        'width' => '50',
      ),      
      'normal' => array(
        'width' => '100',
      ),      
      'large' => array(
        'width' => '200',
      ),
    );

    $type = $this->options['type'];
    if ($fbid = $this->get_value($values)) {
      $variables = array(
        'path' => 'https://graph.facebook.com/' . $fbid . '/picture/?type=' . $type,
        'alt' => $this->tokenize_value($this->options['alt']),
        'title' => $this->tokenize_value($this->options['title']),
        'width' => (is_numeric($this->options['width']) ? $this->options['width']: $types[$type]['width']),
        'height' => (is_numeric($this->options['height']) ? $this->options['height']: (isset($types[$type]['height']) ? $types[$type]['height'] : '')),
        'attributes' => array(
          'class' => 'fboauth-friends-profile-picture', 
          'id' => $fbid . '-fboauth-friends-profile-picture',
        ),
      );
      $output = theme('image', $variables);
      return $output;
    }
  }
}