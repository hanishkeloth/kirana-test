<?php

/**
 * @file
 * Views integration for the mydons custom module
 */

/**
 * Implements hook_views_data()
 *
 */
function content_notification_views_data() {

    $table = array(
        'content_notification' => array(  // content_notification Custom table
            'table' => array(
                'group' => 'Notification',      // Groupname Notifications
                'base' => array(
                    'field' => 'notify_id',  //Primary key
                    'title' => 'Content Notification',
                    'help' => 'Content notification Custom database table'
                )
            ),

            'notify_id' => array(
                'title' => t('Notify Id'),
                'help' => t('Notification custom table  Id field'),
                // is notify_id field sortable TRUE
                'field' => array(
                    'click sortable' => TRUE,
                ),
                //Filter handler for filtering records by mydons_custom_id
                'filter' => array(
                    'handler' => 'views_handler_filter_numeric'
                ),

                'sort' => array(
                    'handler' => 'views_handler_sort'
                )
            ),

            'noty_message' => array(
                'title' => t('Message'),
                'help' => t('content notification Custom table message field'),
                'field' => array(
                    'click sortable' => TRUE,
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                ),

                'sort' => array(
                    'handler' => 'views_handler_sort'
                )
            ),

            'read_status' => array(
                'title' => t('Read status'),
                'help' => t('Content notification Custom table read status field'),
                'field' => array(
                    'click sortable' => TRUE,
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                )
            ),

            'received_uid' => array(
                'title' => t('User Id'),
                'help' => t('Content notification Custom table notification received user id field'),
                'field' => array(
                    'click sortable' => TRUE,
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'relationship' => array(
                    'handler' => 'views_handler_relationship',
                    'base' => 'users',
                    'base field' => 'uid',
                    'label' => t('Notification received user'),
                ),
            ),
            'sent_uid' => array(
                'title' => t('User Id'),
                'help' => t('Content notification Custom table notification sent user id field'),
                'field' => array(
                    'click sortable' => TRUE,
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                ),
                'relationship' => array(
                    'handler' => 'views_handler_relationship',
                    'base' => 'users',
                    'base field' => 'uid',
                    'label' => t('Notification sent user'),
                ),
            ),
            'created' => array(
                'title' => t('Created'),
                'help' => t('Content notification Custom table created field'),
                'field' => array(
                    'click sortable' => TRUE,
                ),
                'filter' => array(
                    'handler' => 'views_handler_filter_string'
                ),
                'sort' => array(
                    'handler' => 'views_handler_sort'
                )
            )
        )
    );
    return $table;
}