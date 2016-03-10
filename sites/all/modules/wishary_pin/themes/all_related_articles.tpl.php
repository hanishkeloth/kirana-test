<div class="article-middleout">

        <?php if(!empty($search_blogs)){ ?>
            <div class="related-articles">
            <?php
               foreach($search_blogs as $blog){
                $node = node_load($blog);
            ?>
            <div class="blogpage-author">
                <div class="relevant-articles-leftsugg">
                     <?php
                        if ($node->type == 'blog') {
                        $article_image = file_create_url($node->field_image_blog['und'][0]['uri']);
                        }else{
                        $article_image = file_create_url($node->field_image_article['und'][0]['uri']);
                        }
                        $article_image = parse_url($article_image);
                    ?>
                    <img alt="Blog Image" src="<?php print $article_image['path'];?>" />
                </div>
                <div class="relevant-articles-rightsugg">
                    <div class="relevant-articles-name">
                        <?php
                        if ($node->type == 'article') {
                        print $node->field_url_article['und'][0]['value'];
                        ?>
                        <a href="<?php print render($node-> field_url_article['und'][0]['url']); ?>"><?php strlen($node->title) > 10 ? print substr($node->title,0,10)."..." : print $node->title;?></a>

                        <?php  }else{ ?>

                        <?php $blog_path = drupal_get_path_alias('node/'.$node->nid);
                        ?>
                        <?php print render($node-> field_url_article['und'][0]['url']); ?>
                        <a href="../<?php print $blog_path;?>"><?php print $node->title;?></a>
                        <?php }
                        ?>
                    </div>
                    <div class="relevant-articles-description">
                        <p><?php
                        strlen($node->body['und'][0]['value']) > 50 ? print substr($node->body['und'][0]['value'], 0, 50)."..." : print $node->body['und'][0]['value'];?></p>
                    </div>
                    <div class="relevant-articles-href">
                        <?php
                        if ($node->type == 'article') {
                            //print $node->field_url_article['und'][0]['value'];
                            strlen($node->field_url_article['und'][0]['value']) > 50 ? print substr($node->field_url_article['und'][0]['value'], 0, 50)."..." : print $node->field_url_article['und'][0]['value'];
                        ?>
                        <a target="_blank" rel="nofollow" href="<?php print render($node-> field_url_article['und'][0]['url']); ?>" class="blog-more">Read More</a>

                        <?php  }else{ ?>
                        <a href="../<?php print $blog_path;?>" class="blog-more">Read More</a>
                        <?php } ?>
                    </div>
                </div>
            </div>
            <?php } ?>
            </div>
            <?php
            }
            ?>
</div>
