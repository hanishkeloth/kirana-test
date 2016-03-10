<div class="pf-quiz-wrapper">
  <div class="pf-quiz-container">
    <div class="pf-quiz-section">
      <div class="pf-quiz-title">Follow stuff you love & get a feed tailored just for you.</div>
      <div class="pin_page">
        <?php
          global $user;
          $user_det = user_load($user->uid);
          if(!isset($user_det->field_gender_profile['und']) || (isset($user_det->field_gender_profile['und']) && $user_det->field_gender_profile['und'][0]['value']=='Unisex')){
            print views_embed_view("gender", "block");
          }
        ?>
        <?php
          if(isset($user_det->field_gender_profile['und'])){
            $gender = $user_det->field_gender_profile['und'][0]['value'];
            $gender = str_replace('Female','women',$gender);
            $gender = str_replace('Male','men',$gender);
          }else{
            $gender = 'unisex';
          }
          print views_embed_view("personalised_feeds", "page", array($gender));
        ?>

        <div class="pf-quiz-btn" style="<?php if($hashtags_count<5) { ?>display:none;<?php } ?>">
        <?php
          $gender_val = '';
          if(isset($user_det->field_gender_profile['und']) && $user_det->field_gender_profile['und'][0]['value']!='unisex') {
            $gender_val = $user_det->field_gender_profile['und'][0]['value'];
          } else {
            $gender_val = 'Unisex';
          }
        ?>
      <input type="hidden" name="profile_gender" id="profile_gender" value="<?php print $gender_val;?>">
      <input type="hidden" name="hashtags_count" id="hashtags_count" value="<?php print $hashtags_count;?>">
      <input type="button" name="update_feed" id="update_feed" value="Get Started">
    </div>
    </div>
    </div>

  </div>
</div>
