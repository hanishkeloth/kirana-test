<?php
namespace AKlump\LoftDataGrids;

/**
 * Class DrupalTableExporter
 */
class DrupalTableExporter extends Exporter implements ExporterInterface {
  protected $extension = '.html';
  public $format;

  public function getInfo() {
    $info = parent::getInfo();
    $info = array(
      'name' => 'Drupal table formatter',
      'shortname' => 'theme_table', 
      'description' => 'Export data using theme_table().',
    ) + $info;

    return $info;
  }

  public function compile($page_id = NULL) {
    $pages = $this->getData()->get();
    if ($page_id && array_key_exists($page_id, $pages)) {
      $pages = array($pages[$page_id]);
    }
    
    $build    = '';
    foreach ($pages as $page_id => $data) {
      $vars['#ExportData'] = $this;
      $vars['#page_id'] = $page_id;
      $vars['attributes'] = array();
      $vars['caption'] = $page_id;
      $vars['header'] = array();
      $column_no = 1;
      foreach ($this->getHeader($page_id) as $header_key => $value) {
        $header_classes = array();
        $header_classes[] = 'column-' . $column_no;
        if ($column_no === count($row) - 1) {
          $header_classes[] = 'last';
        }
        elseif ($column_no === 0) {
          $header_classes[] = 'first';
        }
        $string = preg_replace('/[^a-z0-9\-\.]/', '-', strtolower($header_key));
        $string = preg_replace('/^\d/', 'c-\0', $string);
        $header_classes[] = preg_replace('/-{2,}/', '-', $string);

        $vars['header'][] = array('data' => t($value), 'class' => implode(' ', $header_classes));
        $column_no++;
      }
      $vars['rows'] = array();
      foreach (array_values($data) as $row_no => $row) {
        $row_classes = array();
        $row_classes[] = 'row-' . $row_no;
        if ($row_no === count($data) - 1) {
          $row_classes[] = 'last';
        }
        elseif ($row_no === 0) {
          $row_classes[] = 'first';
        }

        $columns = array();
        $array_keys = array_keys($row);
        foreach (array_values($row) as $column_no => $column) {
          $column_classes = array();
          $column_classes[] = 'column-' . $column_no;
          if ($column_no === count($row) - 1) {
            $column_classes[] = 'last';
          }
          elseif ($column_no === 0) {
            $column_classes[] = 'first';
          }
          $string = preg_replace('/[^a-z0-9\-\.]/', '-', strtolower($array_keys[$column_no]));
          $string = preg_replace('/^\d/', 'c-\0', $string);
          $column_classes[] = preg_replace('/-{2,}/', '-', $string);

          $columns[] = array('data' => $column, 'class' => implode(' ', $column_classes));
        }
        $vars['rows'][] = array('data' => $columns, 'class' => implode(' ', $row_classes));
      }
      $build['table'] = array(
        '#theme' => 'table',
        '#rows' => $vars['rows'],
        '#header' => $vars['header'],
        '#attributes' => $vars['attributes'],
        '#caption' => $vars['caption'],
      );

      drupal_alter('loft_data_grids_table', $build, $this, $page_id);
    }

    $this->output = drupal_render($build);

    print '<pre>'; print __FILE__ . '/' . __FUNCTION__ . "():\n"; print_r($this->output); print '</pre>'; die;
  }
}
