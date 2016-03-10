<h1><a href="/blog"><span>Style Guide : </span>Discover what's right for you</a></h1>
<?php if(!empty($search_blogs)){ ?>
    <div class="blog-div mCustomScrollbar">
    <?php
		foreach($search_blogs as $blog){
		$node = node_load($blog);
    ?>
    <div class="blog-div-inner">
            <div class="blog-div-image">
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
        <div class="blog-div-name">
			<?php
            if ($node->type == 'article') {
            print $node->field_url_article['und'][0]['value'];
            ?>
             <?php global $user;if ($user->uid == 0) { ?>
<a rel="nofollow" href="/ajax_register/login/nojs?destination=<?php print render($node-> field_url_article['und'][0]['url']); ?>" class="ctools-use-modal ctools-modal-ctools-ajax-register-style blog-more"><?php print $node->title;?></a>
<?php } else { ?>
            <a rel="nofollow" href="<?php print render($node-> field_url_article['und'][0]['url']); ?>"><?php print $node->title;?></a>
            <?php } ?>
            <?php  }else{ ?>
            
            <?php $blog_path = drupal_get_path_alias('node/'.$node->nid);
            ?>
            <?php print render($node-> field_url_article['und'][0]['url']); ?>
            <a href="../<?php print $blog_path;?>"><?php print $node->title;?></a>
            <?php }
            ?>
        </div>
        <div class="blog-div-description">
        	<p><?php print $node->body['und'][0]['value'];?></p>
        </div>
        <div class="blog-div-href">
        
        <?php
        if ($node->type == 'article') {
        print $node->field_url_article['und'][0]['value'];
        ?>
        <?php global $user;if ($user->uid == 0) { ?>
         <a rel="nofollow" href="/ajax_register/login/nojs?destination=<?php print render($node-> field_url_article['und'][0]['url']); ?>" class="ctools-use-modal ctools-modal-ctools-ajax-register-style blog-more">Read More</a>
<?php } else { ?>
        <a rel="nofollow" href="<?php print render($node-> field_url_article['und'][0]['url']); ?>" class="blog-more">Read More</a>
        <?php } ?>
        <?php  }else{ ?>
        <a href="../<?php print $blog_path;?>" class="blog-more">Read More</a>
        <?php } ?>
        </div>
    </div>
    <?php } ?>
    </div>
<?php } ?>
