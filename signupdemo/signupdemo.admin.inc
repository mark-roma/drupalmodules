<?php

/**
 * @file
 * Provide admin for module
 */

/**
 * Defines the signupdemo admin settings form.
 */
function signupdemo_admin_settings_form() {
  $form = array();
  $form['signupdemo_types'] = array(
    '#title' => t('These are the content types users can subscribe to'),
    '#description' => t('for these node types, users can subscribe even while the node is being edited'),
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => variable_get('signupdemo_types', array()),
  );
  return system_settings_form($form);
}

/**
 * Menu callback.
 *
 * Displays signups.
 */
function signupdemo_signups() {
  $output = '';
  $rows = array();
  $header = array(
   'User',
   'Node',
   'Email',
   'Created',
  );

  // table schema
  $fields = drupal_get_schema('signupdemo');

  // create wrapper
  $query = db_select('signupdemo', 'm');

  // Join table
  $table_alias = $query->innerJoin('node', 'n', 'n.nid = m.nid', array());

  // Add fields
  $results = $query->fields('m', array_keys($fields['fields']))
    ->fields($table_alias, array('title'))
    ->orderBy('m.created', $direction = 'ASC')
    ->execute()
    ->fetchAll();

  foreach ($results as $value) {
    $account = $value->uid ? user_load($value->uid) : '';
    $rows[] = array(
      $value->uid ? theme('username', array('account' => $account)) : '',
      $value->nid ? l($value->title, 'node/' . $value->nid) : '',
      $value->mail,
      date('F j, Y g:i A', $value->created),
    );
  }

  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}
