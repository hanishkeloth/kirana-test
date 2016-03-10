<?php
/**
 * @file
 * Provide views data and handlers for fboauth_extras.module.
 */

/**
 * Implements hook_views_data()
 */
function fboauth_extras_views_data() {

  // ----------------------------------------------------------------
  // fboauth table -- basic table information.
  
  $data['fboauth_users']['table']['group'] = t('Facebook OAuth Users');
  $data['fboauth_users']['table']['base'] = array(
    'field' => 'uid',
    'title' => t('Facebook Friends'),
    'weight' => -10,
    'defaults' => array(
      'field' => 'uid',
    ),
  );
  /*
  // For other base tables, explain how we join
  $data['fboauth_users']['table']['join'] = array(
    // this explains how the 'fboauth_friends' table (named in the line above)
    // links toward the fboauth_users table.
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  */
  // ----------------------------------------------------------------
  // fboauth -- fields

  // uid
  $data['fboauth_users']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The user ID.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // display this field in the summary
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'label' => 'User',
      'help' => t('Bring in data about the user.'),
    ),
  );
  // fbid
  $data['fboauth_users']['fbid'] = array(
    'title' => t('Facebook ID'),
    'help' => t('The user\'s ID on Facebook.'), // The help that appears on the UI,
    // Information for displaying the fbid
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    // Information for accepting a id as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'name', // the field to display in the summary.
      'numeric' => TRUE,
      //'validate type' => 'nid',
    ),
    // Information for accepting a id as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a id.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // ----------------------------------------------------------------
  // fboauth_friends table -- basic table information.

  $data['fboauth_friends']['table']['group'] = t('Facebook Friends');

  // Advertise this table as a possible base table
  $data['fboauth_friends']['table']['base'] = array(
    'field' => 'id',
    'title' => t('Facebook Friends'),
    'weight' => -10,
    /*'access query tag' => 'node_access',*/
    'defaults' => array(
      'field' => 'name',
    ),
  );
  //$data['node']['table']['entity type'] = 'node';

  // For other base tables, explain how we join
  $data['fboauth_friends']['table']['join'] = array(
    // this explains how the 'fboauth_friends' table (named in the line above)
    // links toward the fboauth_users table.
    'fboauth_users' => array(
      'left_field' => 'fbid',
      'field' => 'fbid',
    ),
  );
  
  // ----------------------------------------------------------------
  // fboauth_friends -- fields

  // uid
  $data['fboauth_friends']['uid'] = array(
    'title' => t('Base user\'s UID'),
    'help' => t('The user ID of the Drupal user to whom the Facebook friend belongs.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_user',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name', // display this field in the summary
    ),
    'filter' => array(
      'title' => t('Name'),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'label' => 'User',
      'help' => t('Bring in data about the user.'),
    ),
  );

  // fbid
  $data['fboauth_friends']['fbid'] = array(
    'title' => t('Friend\'s Facebook ID'),
    'help' => t('The friend\'s ID on Facebook.'), // The help that appears on the UI,
    // Information for displaying the fbid
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    // Information for accepting a id as an argument
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'name field' => 'name', // the field to display in the summary.
      'numeric' => TRUE,
      //'validate type' => 'nid',
    ),
    // Information for accepting a id as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a id.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'fboauth_users',
      'base field' => 'fbid',
      'relationship table' => 'fboauth_friends',
      'relationship field' => 'fbid',
      'label' => 'friend_user',
      'help' => t('Bring in data about the Drupal user account associated with this Facebook ID.'),
      'skip base' => 'fboauth_friends',
    ),
  );

  // name
  // This definition has more items in it than it needs to as an example.
  $data['fboauth_friends']['name'] = array(
    'title' => t('Facebook Name'), // The item it appears as on the UI,
    'help' => t('The friend\'s name on Facebook.'), // The help that appears on the UI,
     // Information for displaying a name as a field
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a name as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  
  $data['fboauth_friends']['first_name'] = array(
    'title' => t('Facebook Name: First Name'), // The item it appears as on the UI,
    'help' => t('The friend\'s first name on Facebook.'), // The help that appears on the UI,
     // Information for displaying a name as a field
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a name as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['fboauth_friends']['last_name'] = array(
    'title' => t('Facebook Name: Last Name'), // The item it appears as on the UI,
    'help' => t('The friend\'s last name on Facebook.'), // The help that appears on the UI,
     // Information for displaying a name as a field
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    // Information for accepting a name as a filter
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  // changed field
  $data['fboauth_friends']['changed'] = array(
    'title' => t('Updated date'), // The item it appears as on the UI,
    'help' => t('The date the friend was last updated.'), // The help that appears on the UI,
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // published status
  $data['fboauth_friends']['status'] = array(
    'title' => t('Still Friends'),
    'help' => t('Whether or not the Facebook friend is still a Facebook friend or has been defriended.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
      'output formats' => array(
        'published-notpublished' => array(t('Friended'), t('Defriended')),
      ),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Still friends'),
      'type' => 'yes-no',
      'use equal' => TRUE, // Use status = 1 instead of status <> 0 in WHERE statment
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );  
  
  // profile picture
  $data['fboauth_friends']['picture'] = array(
    'title' => t('Profile Picture'),
    'help' => t('The facebook profile picture.'),
    'real field' => 'fbid',
    'field' => array(
      'handler' => 'views_handler_field_fboauth_facebook_picture',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Has Avatar'),
      'type' => 'yes-no',
    ),
  );

  // Psuedo fields.
  if (module_exists('invite')) {
    $data['fboauth_friends']['invite_fboauth_friend_link'] = array(
      'real field' => 'fbid',
      'field' => array(
        'title' => t('Invite link'),
        'help' => t('Send an invitation via the Invite module.'),
        'handler' => 'views_handler_field_invite_fboauth_friend_link',
      ),
    );
  }

  // ----------------------------------------------------------------
  // users -- fields
  // fbid
  $data['users']['fbid'] = array(
    'title' => t('Facebook ID'),
    'help' => t('The users ID on Facebook.'), // The help that appears on the UI,
    'relationship' => array(
      'base' => 'fboauth_users',
      'base field' => 'uid',
      'relationship table' => 'users',
      'relationship field' => 'uid',
      'label' => 'user_fboauth',
      'help' => t('Bring in data about the Drupal user\'s Facebook account.'),
      'skip base' => 'fboauth_users',
    ),
  );

  $data['users']['base_uid'] = array(
    'title' => t('Facebook Friendship Base UID'),
    'help' => t('The Drupal uid in a facebook friendship.'), // The help that appears on the UI,
    'relationship' => array(
      'base' => 'fboauth_friends',
      'base field' => 'uid',
      'relationship table' => 'users',
      'relationship field' => 'uid',
      'label' => 'user_fboauth_friends',
      'help' => t('Bring in data about the Drupal user\'s Facebook friends.'),
      'skip base' => 'fboauth_friends',
    ),
  );


  return $data;
}