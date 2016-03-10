<?php
/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_invite_fboauth_friend_link extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => t('Invite'), 'translatable' => TRUE);
    $options['link'] = array('default' => '', 'translatable' => TRUE);
    //$options['redirect_base'] = array('default' => '', 'translatable' => TRUE);
    $options['redirect_uri'] = array('default' => '', 'translatable' => TRUE);
    $options['name'] = array(
      'default' => t('Join @site_name!', array('@site_name' => variable_get('site_name', 'my site'))), 
      'translatable' => TRUE);
    $options['description'] = array(
      'default' => t("I'm inviting you to join @site_name. Just follow this link to sign up!", array('@site_name' => variable_get('site_name', 'my site'))), 
      'translatable' => TRUE);
    $options['picture'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#description' => t('The text that will appear in the hyperlink.'),
      '#default_value' => $this->options['text'],
    );
    $form['link'] = array(
      '#type' => 'textfield',
      '#title' => t('Invite URL'),
      '#description' => t('Optionally enter the absolute URL of the page that the recipient will be invited to. 
      <ul>
        <li>This must be a real URL and accessible to the public.</li>
        <li>This must be an absolute URL, including the protocol prefix</li>
        <li>You must enter only the protocol and domain name, without any trailing page arguments. This seems to be a facebook-enforced security policy.</li>
        <li>If left blank, this will default to this site\'s base URL. E.g., @link</li>
        <li>If this is not done correctly, your send dialog request will fail and the popup will not correctly redirect.</li>
      </ul>', array('@link' => url('', array('absolute' => TRUE)))),
      '#default_value' => $this->options['link'],
    );
    /*
    $form['redirect_base'] = array(
      '#type' => 'textfield',
      '#title' => t('Redirect URI base'),
      '#description' => t('Optionally enter the absolute URL of your site\'s domain name. 
      <ul>
        <li>This must be a real URL, accessible to the public, and must match the domain name specified for your Facebook application at https://developers.facebook.com.</li>
        <li>A relative path will be appending to this, so please enter only the protocol, domain name, and a trailing slash.</li>
        <li>If left blank, this will default to this site\'s base path. E.g., @link</li>
        <li>If this is not done correctly, your send dialog request will fail and the popup will not correctly redirect.</li>
      </ul>', array('@link' => url('', array('absolute' => TRUE)))),
      '#default_value' => $this->options['redirect_base'],
    );
    */
    $form['redirect_uri'] = array(
      '#type' => 'textfield',
      '#title' => t('Redirect URI'),
      '#description' => t('Optionally enter a custom redirect URI for you dialogs. 
      <ul>
        <li>This must be a real URL, accessible to the public, and must match the Site URL specified for your Facebook application at https://developers.facebook.com.</li>
        <li>If this is not done correctly, your send dialog request will fail and the popup will not correctly redirect.</li>
      </ul>', array('@link' => url('', array('absolute' => TRUE)))),
      '#default_value' => $this->options['redirect_uri'],
    );
    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Send dialog title'),
      '#description' => t('The title of the invite page within the send dialog.'),
      '#default_value' => $this->options['name'],
    );
    $form['description'] = array(
      '#type' => 'textfield',
      '#title' => t('Send dialog description'),
      '#description' => t('The description of the invite page within the send dialog.'),
      '#default_value' => $this->options['description'],
    );
    $form['picture'] = array(
      '#type' => 'textfield',
      '#title' => t('Send dialog picture'),
      '#description' => t('The absolute URL of a thumbnail picture to be included within the send dialog.'),
      '#default_value' => $this->options['picture'],
    );

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($fbid = $this->get_value($values)) {
      return $this->render_link($fbid, $values);
    }
  }

  function render_link($fbid, $values) {
    if (user_access('invite facebook friends')) {  
      global $user;

      $this->options['alter']['make_link'] = TRUE;
      // We leave the path as # because jQuery will take care of behaviors.
      $this->options['alter']['path'] = '##';
      $this->options['alter']['link_class'] = 'fboauth-friends-invite';

      // If current user has already invited this Facebook user, disable link.
      $invited = FALSE;
      $fbuser = new stdClass;
      $fbuser->id = $fbid;
      if ($invites = fboauth_extras_find_invites($fbuser, $user)) {
        $invited = TRUE;
      }

      // Set link text.
      if ($invited) {
        $text = t('Invited');
      }
      elseif (!empty($this->options['text'])) {
        $text = $this->options['text'];
      }
      else {
        $text = t('Invite friend');
      }

      // Build JSON data to pass to fboauth_extras.js via rel attribute.
      $variables = array(
        'action' => 'fboauth_extras_invite',
        'to' => $fbid,
        'link' => $this->options['link'] ? $this->options['link'] : url('', array('absolute' => TRUE)),
        'name' => $this->options['name'],
        'description' => $this->options['description'],
        'picture' => $this->options['picture'],
        'senderUid' => $user->uid,
      );

      $redirect_uri = 'fboauth_extras/redirect_uri/' . $variables['action'] . '/' . $variables['to'];
      $variables['redirectUri'] =  url($redirect_uri, array('absolute' => TRUE));
      //$variables['redirectUri'] = $this->options['redirect_uri'] ? $this->options['redirect_uri'] : url('fboauth_extras/redirect_uri', array('absolute' => TRUE));
      $rel = drupal_json_encode($variables);
      $this->options['alter']['rel'] = $rel;

      return $this->tokenize_value($text);
    }
  }

  function add_self_tokens(&$tokens, $item) { 
    $tokens['[invite_fboauth_friend_link-path]'] = '##';
    parent::add_self_tokens($tokens, $item);
  }
  
}
