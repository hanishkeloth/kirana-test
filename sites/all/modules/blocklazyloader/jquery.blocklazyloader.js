/**
 * @file
 * Block Lazyloader JQuery plugin
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 * Settings:
 * - distance = distance of the block to the viewable browser screen before it gets loaded
 * - icon     = animating block that appears before the actual block is loaded
 *
 */

(function($){

  // Process block lazyloader
  $.fn.blocklazyloader = function(options){
    var settings = $.extend($.fn.blocklazyloader.defaults, options);
    var blocks = this;

    blocks.each(function(){
      if($.inArray($(this).attr('id'), settings['excludedBlocks']) == -1) {
        $(this).addClass('block-lazyload');
        // add the loader icon
        if(settings['icon'] != '') $('.' + settings['contentClass'], this).addClass('blocklazyloader-content').css({ position: 'relative', display: 'block'}).append('<img class="blocklazyloader-icon" src="' + settings['icon'] + '" />');
      }
    });  
    
    // Load on refresh
    loadActualBlocks(blocks, settings);

    // Load on scroll
    $(window).bind('scroll', function(e){
      loadActualBlocks(blocks, settings);
    });

    // Load on resize
    $(window).resize(function(e){
      loadActualBlocks(blocks, settings);
    });

    return this;
  };

  // Defaults
  $.fn.blocklazyloader.defaults = {
    excludedBlocks: ['block-system-main','block-user-login'],
    contentClass: "content", 
    distance:     0, // the distance (in pixels) of block when loading of the actual block will happen
    icon:         7  // display animating icon
  };


  // Loading actual blocks
  function loadActualBlocks(blocks, settings){
    blocks.each(function(){
      var blockHeight = $('.' + settings['contentClass'], this).height(), blockWidth = $('.' + settings['contentClass'], this).width();
      var iconTop = Math.round(blockHeight/2), iconLeft = Math.round(blockWidth/2), iconFactor = Math.round($('img.blocklazyloader-icon', this).height()/2);
      $('img.blocklazyloader-icon', this).css({ top: iconTop - iconFactor, left: iconLeft - iconFactor });

      if (windowView(this, settings) && $(this).hasClass('block-lazyload')){
        loadBlock(this, settings);
      }
    });
  };


  // Check if the blocks are within the window view (top, bottom, left and right)
  function windowView(block, settings){

        // window variables
    var windowHeight = $(window).height(),
        windowWidth  = $(window).width(),

        windowBottom = windowHeight + $(window).scrollTop(),
        windowTop    = windowBottom - windowHeight,
        windowRight  = windowWidth + $(window).scrollLeft(),
        windowLeft   = windowRight - windowWidth,

        // block variables
        blockHeight  = $('.' + settings['contentClass'], block).height(),
        blockWidth   = $('.' + settings['contentClass'], block).width(),

        blockTop     = $('.' + settings['contentClass'], block).offset().top - settings['distance'],
        blockBottom  = blockTop + blockHeight + settings['distance'],
        blockLeft    = $('.' + settings['contentClass'], block).offset().left - settings['distance'],
        blockRight   = blockLeft + blockWidth + settings['distance'];

           // This will return true if any corner of the block is within the screen 
    return (((windowBottom >= blockTop) && (windowTop <= blockTop)) || ((windowBottom >= blockBottom) && (windowTop <= blockBottom))) &&
           (((windowRight >= blockLeft) && (windowLeft <= blockLeft)) || ((windowRight >= blockRight) && (windowLeft <= blockRight)));
  };


  // Load the block
  function loadBlock(block, settings){
    var blockId      = $(block).attr('id'),
        blockmd      = blockId.split('-'),
        blockModule  = blockmd[1],
        blockDelta   = '';
        
    // This will only get the module name and delta from the block id
    if(blockmd[2] && blockmd[3] && blockmd[4] && blockmd[5]) {
      blockDelta = blockmd[2] + '-' + blockmd[3] + '_' + blockmd[4] + '_' + blockmd[5];
    }        
    else if(blockmd[2] && blockmd[3] && blockmd[4]) {
      blockDelta = blockmd[2] + '-' + blockmd[3] + '_' + blockmd[4];
    }
    else if(blockmd[2] && blockmd[3]) {
      blockDelta = blockmd[2] + '-' + blockmd[3];       
    }
    else if(blockmd[2]) {
      blockDelta = blockmd[2];
    }

    var blockContent = '#block-' + blockModule + '-' + blockDelta + ' .' + settings['contentClass'];    
        
    $.ajax({
      url: Drupal.settings.basePath + 'blocklazyloader',
      type: 'GET',
      dataType: 'json',
      data: ({module: blockModule, delta: blockDelta, nocache: 1}),
      //cache: false,
      success: function(data){

        // Replace the content of the block content
        // with the result from the ajax call
        $(block).removeClass('block-lazyload');
        $(blockContent).removeClass('blocklazyloader-content');
        $(blockContent).find('img.blocklazyloader-icon').remove();
        $(blockContent).html(data);
        // fixed blank blocks when lazyloader module is installed
        if(jQuery().lazyloader) loadImage(block);
      }
    });
  };

  // Load the block's images
  function loadImage(block){
    var images = $(block).find('img[data-src]');
      images.each(function() {
      $(this).attr('src', $(this).data('src')).removeAttr('data-src');
    });  
  };  

})(jQuery);



