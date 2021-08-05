<?php

/**
 * @file
 * Rewrite a field using tokens.
 */

$plugin = array(
  'form'     => 'feeds_tamper_civicrm_contact_sort_name_form',
  'callback' => 'feeds_tamper_civicrm_contact_sort_name_callback',
  'name'     => 'Sort Name to Contact ID',
  'multi'    => 'loop',
  'category' => 'CiviCRM',
);

function feeds_tamper_civicrm_contact_sort_name_form($importer, $element_key, $settings) {
  $form = array();
  $form['help'] = array(
    '#markup' => t('Given a sort name, returns the corresponding CiviCRM contact ID.'),
  );
  return $form;
}

function feeds_tamper_civicrm_contact_sort_name_callback($result, $item_key, $element_key, &$field, $settings, $source) {
  civicrm_initialize();
  $result = \Civi\Api4\Contact::get(FALSE)
    ->addSelect('id')
    ->addWhere('sort_name', '=', $field)
    ->execute()
    ->column('id');
  $field = $result[0] ?? NULL;
}
