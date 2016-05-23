<?php
/**
 * @file
 *   add data to views
 */

/**
 * Implements hook_views_data().
 *
 */
function signupdemo_views_data() {
  $data['signupdemo']['table']['group']  = t('subscriptions');
  $data['signupdemo']['table']['base'] = array(
    'field' => 'id',
    'title' => t('signupdemo'),
    'help' => t('subscriptions for site nodes'),
  );
  $data['mailfish']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'user' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['users']['table']['join']['signupdemo'] = array(
    'left_field' => 'uid',
    'field' => 'uid',
    'type' => 'LEFT',
  );
  $data['node']['table']['join']['signupdemo'] = array(
    'left_field' => 'nid',
    'field' => 'nid',
    'type' => 'LEFT',
  );

  $data['signupdemo']['mail'] = array(
    'title' => t('E-mail'),
    'help' => t('user\'s email address'),
    'field' => array(
      'handler' => 'views_handler_field_user_mail',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );

  $data['signupdemo']['uid'] = array(
    'title' => t('User'),
    'help' => t('connect subscription with user'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('user'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_user_uid',
      'name field' => 'name',
    ),
  );
  $data['signupdemo']['nid'] = array(
    'title' => t('Node'),
    'help' => t('connect node with subscription'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'node',
      'base field' => 'nid',
      'label' => t('node'),
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'parent' => 'views_handler_argument_numeric',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );
  $data['signupdemo']['created'] = array(
    'title' => t('Created date'),
    'help' => t('date of last revision'),
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
  return $data;
}
