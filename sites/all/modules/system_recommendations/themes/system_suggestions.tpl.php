<div class="cmt-suggestion">
    <?php
     $theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));
    if(!empty($suggestions)){
    foreach($suggestions as $item){
        $redirect_url = $item['redirect_url']."&domain=".$item['origin_url_base'];
     ?>
    <div class="comment ajax-comment-wrapper comment-wrapper-14232 clearfix">
        <div class="suggestion-right-box" href="<?php print $redirect_url;?>">
        	<a href="<?php print $redirect_url;?>" rel="nofollow" class="buyButton suggestion-outclick" target="_blank" onClick="_gaq.push(['_trackEvent', 'Wish_detail_buy', 'Click', 'Buy_<?php print $baseurl;?>']);"></a>
            <div class="left-box">
                <div class="field field-name-field-suggestion-image field-type-image field-label-hidden">
                    <div class="field-items">
                        <div class="field-item odd"><img width="360" height="480" alt="" src="<?php print $item['img_url'];?>"></div>
                    </div>
                </div>
            </div>
            <div class="right-box">
                <div class="right-box-text1">
                    <div class="titletext jquery-once-5-processed">
                        <div class="field field-name-field-suggestion-title field-type-text field-label-hidden">
                            <div class="field-items">
                                <div class="field-item odd"><?php print $item['name'];?></div>
                            </div>
                        </div>
                        <span class="img-more" style="display: inline;"></span>
                        <div class="title-fulltext">
                            <div class="field field-name-field-suggestion-title field-type-text field-label-hidden">
                                <div class="field-items">
                                    <div class="field-item odd"><?php print $item['name'];?></div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="price-listtext">Price <?php print $item['price_unit'];?>:
                        <div class="field field-name-field-suggestion-price field-type-number-decimal field-label-hidden">
                            <div class="field-items">
                                <div class="field-item odd">
                                    <?php
                                        if(empty($item['price'])){
                                            $item_site_name = explode(".",$item['origin_url_base']);
                                            print 'Go to '.$item_site_name[1].' to check price';
                                        }else{
                                            print $item['price'];
                                        }
                                    ?>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="field field-name-field-suggestion-source field-type-link-field field-label-hidden">
                        <div class="field-items">
                            <div class="field-item odd"><a rel="nofollow" class="form-group form-groupform-groupform-groupform-groupform-groupform-group buyButton" target="_blank" onClick="_gaq.push(['_trackEvent', 'Wish_detail_buy', 'Click', 'Buy_<?php print $item['origin_url_base'];?>']);" href="<?php print $redirect_url;?>"><?php print $item['origin_url_base'];?></a></div>
                        </div>
                    </div>
                    <!-- <div class="like-button">
                        <div id="rate-comment-14232-1-1" class="rate-widget-1 rate-widget clear-block rate-user rate-widget-thumbs_up rate-4919f5bfeee9e06d001c2c267d087d20 rate-widget-processed">
                            <a title="" href="/wish/whiteshirt-partywear-womenclothing-celebrity-blacktrouser-blackheels?rate=L9ezxG4vaEXAza8mUcLz_4rKIBfw5SLcB-xJz-pBCS0" target="_top" rel="nofollow" id="rate-button-3" class="rate-button rate-thumbs-up-btn-up user-not-voted"></a>
                            <span class="rate-info"><?php //(isset($item['score'])) ? print $item['score'] : '';?></span>
                        </div>
                	</div> -->
                    <div class="clock-button">
                    <?php
                    $cdate = strtotime($item['cdate']);
                    print gmdate('d/m/Y',$cdate);?></div>
                    <div class="comment_link">
                        <ul class="links inline">
                            <li class="comment_forbidden first last">
                                <span><a href="/user/login?destination=node/7257%23comment-form">Log in</a> or <a href="http://www.wishary.in/modal_forms/nojs/register?destination=node/7257%23comment-form" class="init-modal-forms-register-processed ctools-use-modal ctools-modal-modal-popup-medium ctools-use-modal-processed">register</a> to post comments</span>
                            </li>
                        </ul>
                    </div>
                </div>
                <div class="right-box-text2">
                    <div class="user-picture">
                    <?php
                        $uri = 'public://';
                        $path= file_create_url($uri);
                        $user_picture_path = $path.'/pictures/picture-2196-1417582651.png';
                    ?>
                        <img title="user's picture" alt="user's picture" src="<?php print $user_picture_path;?>">
                    </div>
                    <span class="tooltipsle"><a href="<?php print $redirect_url;?>" rel="nofollow" class="buyButton" target="_blank" onClick="_gaq.push(['_trackEvent', 'Wish_detail_buy', 'Click', 'Buy_<?php print $item['origin_url_base'];?>']);" >Shop</a>
                        <!--span class="tltp">Check more details and buy from partner site</span-->
                    </span>
                </div>
            </div>
        </div>
    </div>
    <?php
    	}
    }

    ?>
</div>
