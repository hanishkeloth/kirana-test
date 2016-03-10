<?php

function tb_wall_layout_vocabularies() {
  return array(
    'tb_wall_styles' => array(
      'title' => t('TB Wall Styles'),
      'description' => t('TB Wall styles vocabulary'),
      'terms' => array(
        'tb-wall-double-style' => t('Double Style'),
        'tb-wall-triple-style' => t('Triple Style'),
      ),
      'field' => array(
      	'name' => 'field_tb_wall_style',
        'weight' => 49,
      ),
      'bundles' => array(
        'except' => array('page')
      ),
    ),
    'tb_wall_backgrounds' => array(
      'title' => t('TB Wall Backgrounds'),
      'description' => t('TB Wall backgrounds vocabulary'),
      'terms' => array(
        'tb-wall-black-background' => t('Black'),
        'tb-wall-blue-background' => t('Blue'),
        'tb-wall-green-background' => t('Green'),
        'tb-wall-yellow-background' => t('Yellow'),
      ),
      'field' => array(
      	'name' => 'field_tb_wall_background',
        'weight' => 49,
      ),
      'bundles' => array(
        'except' => array('page')
      ),
    ),
    'tb_wall_badges' => array(
      'title' => t('TB Wall Badges'),
      'description' => t('TB Wall badges vocabulary'),
      'terms' => array(
        'tb-wall-adv-badge' => t('Advertisement'),
        'tb-wall-hot-badge' => t('Hot'),
        'tb-wall-new-badge' => t('New'),
      ),
      'field' => array(
      	'name' => 'field_tb_wall_badge',
        'weight' => 49,
      ),
      'bundles' => array(
        'except' => array('page')
      ),
    ),
  );
}
