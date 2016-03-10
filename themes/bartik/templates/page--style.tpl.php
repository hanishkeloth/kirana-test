<div class="stylequiz-wrap">
	<div class="stylequiz-container">
        <div class="stylequiz-section">
            <div class="stylequiz-top-title">Style Quiz</div>
            <div class="stylequiz-title">Select Left or Right cards to choose the option closest to your tastes</div>
            <div class="stylequiz-products">
                <div class="stylequiz-products-images">
                   <?php if ($messages): ?>
    <div id="messages"><div class="section clearfix">
      <?php print $messages; ?>
    </div></div> <!-- /.section, /#messages -->
  <?php endif; ?>
   <?php print render($page['content']); ?>
                    
                </div>
                <div class="stylequiz-desp">Select one option to begin quiz</div>
            </div>
           
        </div>
    </div>
</div>