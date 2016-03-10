<?php

class OpenGraphMeta {
  /** Singleton instance. */
  private static $instance = NULL;

  /** Get singleton instance. */
  public static function instance() {
    if (empty(self::$instance)) {
      self::$instance = new OpenGraphMeta();
    }
    return self::$instance;
  }

  /**
   * Harvest all images from the given node.
   *
   * @return array(array('title' => , 'alt' => , 'url' =>))
   */
  public function harvest_images_from_node($node) {
    // extract image fields
    $ret = array();
    OpenGraphMetaDrupalLayer::extract_image_fields((array)$node, $ret);

    // extract all images from body content
    $body = OpenGraphMetaDrupalLayer::get_node_body($node);
    if (!empty($body)) {
      libxml_use_internal_errors(TRUE); // turn off libxml errors for now
      $doc = new DOMDocument();
      $doc->loadHTML($body);
      $list = $doc->getElementsByTagName('img');
      for ($i=0; $list->length > $i; ++$i) {
        $item = $list->item($i);
        if ($item->hasAttribute('src')) {
          $url = $item->getAttribute('src');
          if (!empty($url)) {
            $thumb_url = image_style_url('thumbnail', $url);
            $ret[$url] = array('title' => $url, 'alt' => $url, 'url' => $thumb_url);
          }
        }
      }
      libxml_use_internal_errors(FALSE); // turn libxml errors back on
    }

    return $ret;
  }

}

/**
 * Drupal compatibility layer.
 *
 * Abstracts away differences between Drupal versions.
 */
class OpenGraphMetaDrupalLayer {

  /**
   * Get contents of node body.
   * @param  $node the node object.
   * @return empty string if no body found.
   */
  public static function get_node_body($node) {
    $body = '';
    $lang = field_language('node', $node, 'body');
    $lang = $lang ? $lang : LANGUAGE_NONE;
    if (!empty($node->body[$lang]['0']['value'])) {
      $body = $node->body[$lang]['0']['value'];
    }
    return $body;
  }


  /**
   * Harvest images from node's image fields.
   *
   * array_walk_recursive() doesn't give us enough flexibility so we do the recursion manually.
   *
   * @param $resultarray will hold results.
   */
  public static function extract_image_fields($fields, array &$resultarray) {
    if (is_array($fields)) {
      if (!empty($fields['filemime']) && FALSE !== stripos($fields['filemime'], 'image') && !empty($fields['uri'])) {
        $url = $fields['uri'];
        $thumb_url = image_style_url('thumbnail', $fields['uri']);

        $resultarray[$url] = array(
          'title' => !empty($fields['title']) ? $fields['title'] : $url,
          'alt' => !empty($fields['alt']) ? $fields['alt'] : $url,
          'url' => $thumb_url,
        );
      }
      else {
        foreach ($fields as $cv) {
          self::extract_image_fields($cv, $resultarray);
        }
      }
    }
  }
}

class OpengraphImageMetaTag extends DrupalTextMetaTag {
  public function getValue(array $options = array()) {
    $value = parent::getValue($options);
    $new_urls = [];
    foreach (explode(',', $value) as $p) {
      $new_urls[] = url(file_create_url(ltrim($p,'/')), array('absolute' => TRUE));
    }
    return implode(',', $new_urls);
  }
}

