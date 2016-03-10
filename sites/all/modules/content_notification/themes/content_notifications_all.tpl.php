<?php
global $base_url, $user;
$url = '';
$theme_path = drupal_get_path('theme', variable_get('theme_default', NULL));

//print_r($user);
?>
<div class="notific-wrap">
<a href="/"></a>
	<div class="notific-container">
    	<div class="notific-close">
        	<a href="#" class="close"><img title="Close window" alt="Close window" src="http://www.wishary.in/profiles/commerce_kickstart/modules/contrib/ctools/images/icon-close-window.png"></a>
         </div>
    	<div class="notific-section">
        	<div class="notific-top">
                <img src="/<?php print $theme_path;?>/images/notification-logo.png" alt="notification logo">
                <p>Notification</p>
            </div>
            <div class="notif-info">
            	<div class="notif-mark-right">
            		<div class="notif-info-mark"><a href="javascript:"><span class="mark_all">Mark all as Read</span></a></div>
                	<div class="notif-info-mark"><a href="<?php echo url('user/'.$user->uid.'/'.'edit'); ?>">Settings</a>
                </div>
            </div>
    	</div>
			<?php if(!empty($push_notifications)){ ?>
            <div class="notific-popup-error">
				<?php foreach($push_notifications as $push_notify){ ?>
                <div class="notific-left-error notific-popup-left-<?php print $push_notify->notification_id;?>">
                    <a href="<?php print $push_notify->link;?>" target="_blank"><?php print $push_notify->message;?></a>
                </div>
				
                <div class="notific-left-cancel notific-popup-cancel-<?php print $push_notify->notification_id;?>">
                    <img id="<?php print $push_notify->notification_id;?>" src="<?php print base_path(). $theme_path;?>/images/notification-cancel.png" alt="notification cancel">
                </div>
				<?php } ?>
            </div>
			<?php } ?>
            
			<?php
				foreach($notifications as $notify){
					if($notify->entity_type == 'node'){
						$url = $base_url."/node/".$notify->entity_id."/".$notify->notify_id;
						$image_name = "notif-icon4.png";
					}
					else if($notify->entity_type == 'comment'){
						//$url = $base_url."/comment/".$notify->entity_id."#comment-".$notify->entity_id;
						$url = $base_url."/node/".$notify->entity_id."/".$notify->notify_id;
						$image_name = "notif-icon4.png";
					}
					else if($notify->entity_type == 'follow'){
						$started_find = strpos($notify->noty_message,'started');
						$username = substr($notify->noty_message, 0, $started_find-1);
						$url = $base_url."/users/".$username."?notify_id=".$notify->notify_id;
						$image_name = "notif-icon1.png";
					}
					if(strpos($notify->noty_message,'liked')){
						if($notify->entity_type == 'node'){
							$image_name = "notif-icon2.png";
						}
						else if($notify->entity_type == 'comment'){
							$image_name = "notif-icon3.png";
						}
					}
					$background_color = '';
					if($notify->read_status == 0){
						$background_color = "#fff8e5";
					}
            ?>
                <div class="notific-prd-box notific-popup-prd-box-<?php print $notify->notify_id;?>" style="background-color:<?php print $background_color;?>">
                    <div class="notific-cont-link">
                    <a href="<?php print $url;?>" target="_blank"></a>
                    	<div class="notific-left">
                            <div class="notific-lefticons"><img src="<?php print base_path(). $theme_path.'/images/'.$image_name;?>"></div>
                            <div class="notific-content"><a href="<?php print $url;?>" target="_blank"><?php print $notify->noty_message;?></a></div>
                        </div>
                        <div class="notific-right">
                            <div class="notific-date"><?php print format_date($notify->created,'custom','d-m-y'); ?></div>
                            <?php if($notify->entity_type == 'follow'){ ?>
                                <div class="notific-prd-icon-gender"><img src="<?php print $notify->image;?>" alt="Notification"></div> 
                            <?php } else { ?>
                             <img src="<?php print $notify->image;?>" alt="Notification" >
                             <?php } ?>
                        </div>
                   </div>
					<?php if($notify->read_status == 0){ ?>
						<div class="activity-notific-popup-cancel activity-notific-popup-cancel-<?php print $notify->notify_id;?>">
							<img id="<?php print $notify->notify_id;?>" src="<?php print base_path().$theme_path;?>/images/notification-cancel.png" alt="notification cancel">
						</div>
					<?php } ?>
                    
                </div>
            <?php } ?>
        </div>
    </div>
</div>
