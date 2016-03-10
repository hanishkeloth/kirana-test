<div>
    <div class="search-suggestions">
        <?php
            $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
        ?>
        <div class="hashtag-search">
         	<div class="hashtag-search-leftimg">
            	<!--img src="<?php print base_path() . $theme_path .'/' ?>images/search-logo.jpg" alt="HashtagSearch logo" / -->
                <?php global $user;if ($user->uid == 0) { ?>
                <?php
                // First include css and js for modal dialog.
                _ajax_register_include_modal();
                // Build classes for ajax modal link.
                $classes = array();
                $classes[] = 'ctools-use-modal';
                $classes[] = 'tooltips1 header-signup';
				$mytest = "Search by Images";
                $classes[] = 'ctools-modal-ctools-ajax-register-style';
                // Provide default options for ajax modal link.
                $options = array('attributes' => array('class' => $classes, 'rel' => 'nofollow'));
                print l($mytest, 'ajax_register/register/nojs', $options);
                ?>
                <?php }else{ ?>
                <a href="/modal/node/add/pin/nojs" class="ctools-use-modal tooltips1 header-signup">Search by Images</a>
                <?php } ?>
            </div>
            <?php
                $search_word = '';
                if(arg(0) && arg(0) == 'search_results'){
                    $search_word = arg(1);
                    //$search_tags = explode("+", urlencode($search_word));
                    $search_tags = explode("+", $search_word);
                    $search_tags = array_values(array_unique($search_tags));
                    $keyword = '';
                    foreach($search_tags as $search_tag){
                        $keyword.=$search_tag.' ';
                    }
                }
            ?>
            <input type="text"  id="hashtag-value" placeholder="Search by Keywords" class="jquery-once-5-processed" value="<?php print $keyword;?>">
            <div class="hashtag-search-rightimg">
            <?php
                if((arg(0) && arg(0) == 'search_results')){
                    $filter_image = base_path().$theme_path."/images/hash-search-btn-filter.gif";
                } else {
                    $filter_image = base_path().$theme_path."/images/hash-search-btn.gif";
                }
            ?>
            <img src="<?php print $filter_image; ?>" alt="HashtagSearch Btn"  class="hashtag-search-btn" id="hashtag-search-menus" />
            </div>
            <input type="hidden" id="search_keyword" name="search_keyword" value ="<?php if(arg(0) && arg(0)=='search_results') { print arg(1);}?>" />
            <input type="hidden" id="new_hashtags" name="new_hashtags" />
            <ul>
            <?php if(!empty($search_tags)) {
                foreach($search_tags as $search_tag){
                    print "<li>".$search_tag."</li>";
                }
            } ?>
            </ul>

            <?php
            $category_vocabulary = taxonomy_vocabulary_machine_name_load('categories');
            $category_tree = taxonomy_get_tree($category_vocabulary->vid,0,1,1);
            if(!empty($category_tree)){ ?>
            <div class="search-main-category">
               <div class="search-main">
                <?php foreach ($category_tree as $main_cat) {
                    if($main_cat->name!='Women - Beauty'){
                        print '<div class="searchproductInner">';
                        //Print main categories
                        print '<span class="searchproductText">'.$main_cat->name.'</span>';
                        $child_terms = taxonomy_get_children($main_cat->tid,$category_vocabulary->vid);
                        $main_category_name = $main_cat->name;
                        $main_category_name = str_replace("-","_",$main_category_name);
                        $main_category_name = strtolower($main_category_name);
                        print '<span class="searchproductList">';
                        //Print sub categories
                        foreach ($child_terms as $child_cat) {
                            $textchange = trim($child_cat->name);
                            $textchange = str_replace("-","_",$textchange);
                            $textchange = str_replace(" ","_",$textchange);
                            $textchange = strtolower($textchange);
                            echo "<a href='javascript:' class='".$main_category_name.'_'.$textchange."' id='".$child_cat->tid."'>".$child_cat->name."</a>";
                        }
                        print '</span>';
                        print '</div>';
                    }
                }
                ?>
                </div>
            </div>
            <?php } ?>
        </div>
        <?php if(arg(0) && arg(0)=='search_results'){ ?>
        <div class="search_suggestions">
            <?php
                $search_suggestions = module_invoke('wishary_search', 'block_view', 'search_suggestions');
                print render($search_suggestions['content']);
            ?>
        </div>
        <?php } ?>
    </div>
</div>
