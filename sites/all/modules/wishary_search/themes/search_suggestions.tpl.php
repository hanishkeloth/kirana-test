<?php
  $search_keyword_array = explode(" ", arg(1));
  if(!empty($suggestions)) {
    $suggestions_array = array_udiff($suggestions, $search_keyword_array, 'strcasecmp');
    if(!empty($suggestions_array)) {
?>
      <div id="search-opt-container" class="hashtag-products-container">
          <div class="hashtag-products">
              <ul class="hashtag-wrapper jcarousel-skin-default">
                  <?php
                      foreach($suggestions as $suggestion_name) {
                        $term_list = taxonomy_get_term_by_name($suggestion_name);
                        if(!empty($term_list)){
                          foreach ($term_list as $key => $term_det) {
                            if(isset($term_det->field_categories_image)){
                              if(isset($term_det->field_categories_image['und'])){
                                $term_image = file_create_url($term_det->field_categories_image['und'][0]['uri']);
                              } else {
                                $term_image = '';
                              }
                            } else {
                                $term_image = '';
                            }
                            //echo "<pre>";print_r($term_image);
                          }
                        }
                        if(empty($term_image)) {
                            $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
                            $term_image = base_path().$theme_path."/images/default-search-bg.jpg";
                        }
                  ?>
                      <li class="hashtag-item" style="background:url('<?php print $term_image;?>') left top no-repeat;">
                      <!--<li class="hashtag-item">-->
                          <a href="javascript:"><?php if(isset($suggestion_name)){ print $suggestion_name; }?></a>
                      </li>
                  <?php
                      }
                  ?>
              </ul>
          </div>
      </div>
<?php
    }
}
if(count($search_keyword_array)==1){
  $hashtag_term = taxonomy_get_term_by_name('#'.$search_keyword_array[0],'hashtags');
  if(!empty($hashtag_term)){
    $i=0;
    foreach ($hashtag_term as $hashtag) {
      if($i==0){
?>
<div class="hashtag-follow">
    <span class="hashtag-title"><?php print $hashtag->name;?></span>
    <span class="hashtag-content">Like this hashtag contents?</span>
    <span class="hashtag-button"><?php print flag_create_link('hashtag', $hashtag->tid); ?></span>
</div>
<?php
      }
      $i++;
    }
  }
}
?>
