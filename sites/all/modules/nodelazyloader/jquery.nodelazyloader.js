/**
 * @file
 * Node Lazyloader JQuery plugin
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 * Settings:
 * - distance = distance of the node to the viewable browser screen before it gets loaded
 * - icon     = animating node that appears before the actual node is loaded
 *
 */

(function($){

  // Process node lazyloader
  $.fn.nodelazyloader = function(options){
    var settings = $.extend($.fn.nodelazyloader.defaults, options);
    var nodes = this;

    nodes.each(function(){
      var nodeIDText = $(this).attr('id'),
          nodeID = nodeIDText.replace('node-', '');
      if($.inArray(nodeID, settings['excludedNodes']) == -1) {
        $(this).addClass('node-lazyload');
        // add the loader icon
        if(settings['icon'] != '') $('.' + settings['contentClass'], this).addClass('nodelazyloader-content').css({ position: 'relative', display: 'node'}).append('<img class="nodelazyloader-icon" src="' + settings['icon'] + '" />');
      }
    });  
    
    // Load on refresh
    loadActualNodes(nodes, settings);

    // Load on scroll
    $(window).bind('scroll', function(e){
      loadActualNodes(nodes, settings);
    });

    // Load on resize
    $(window).resize(function(e){
      loadActualNodes(nodes, settings);
    });

    return this;
  };

  // Defaults
  $.fn.nodelazyloader.defaults = {
    requestingPage: [],
    excludedNodes: [],
    contentClass: "content", 
    distance:     0, // the distance (in pixels) of node when loading of the actual node will happen
    icon:         7  // display animating icon
  };


  // Loading actual nodes
  function loadActualNodes(nodes, settings){
    nodes.each(function(){
      var nodeHeight = $('.' + settings['contentClass'], this).height(), nodeWidth = $('.' + settings['contentClass'], this).width();
      var iconTop = Math.round(nodeHeight/2), iconLeft = Math.round(nodeWidth/2), iconFactor = Math.round($('img.nodelazyloader-icon', this).height()/2);
      $('img.nodelazyloader-icon', this).css({ top: iconTop - iconFactor, left: iconLeft - iconFactor });

      if (windowView(this, settings) && $(this).hasClass('node-lazyload')){
        loadNode(this, settings);
      }
    });
  };


  // Check if the nodes are within the window view (top, bottom, left and right)
  function windowView(node, settings){

        // window variables
    var windowHeight = $(window).height(),
        windowWidth  = $(window).width(),

        windowBottom = windowHeight + $(window).scrollTop(),
        windowTop    = windowBottom - windowHeight,
        windowRight  = windowWidth + $(window).scrollLeft(),
        windowLeft   = windowRight - windowWidth,

        // node variables
        nodeHeight  = $('.' + settings['contentClass'], node).height(),
        nodeWidth   = $('.' + settings['contentClass'], node).width(),

        nodeTop     = $('.' + settings['contentClass'], node).offset().top - settings['distance'],
        nodeBottom  = nodeTop + nodeHeight + settings['distance'],
        nodeLeft    = $('.' + settings['contentClass'], node).offset().left - settings['distance'],
        nodeRight   = nodeLeft + nodeWidth + settings['distance'];

           // This will return true if any corner of the node is within the screen 
    return (((windowBottom >= nodeTop) && (windowTop <= nodeTop)) || ((windowBottom >= nodeBottom) && (windowTop <= nodeBottom))) &&
           (((windowRight >= nodeLeft) && (windowLeft <= nodeLeft)) || ((windowRight >= nodeRight) && (windowLeft <= nodeRight)));
  };


  // Load the node
  function loadNode(node, settings){
    var nodeIDText  = $(node).attr('id'),
        nodeID = nodeIDText.replace('node-', ''),
        buildMode = 'teaser';
        
    var nodeContent = '#node-' + nodeID + ' .' + settings['contentClass'];
    var request = settings['requestingPage']; 
    // identifies if it's a node page view
    if((request[0] == 'node') && request[1] && (request[2] == undefined)) {
      buildMode = 'full';
    }

    $.ajax({
      url: Drupal.settings.basePath + 'nodelazyloader',
      type: 'GET',
      dataType: 'json',
      data: ({nid: nodeID, mode: buildMode, nocache: 1}),
      //cache: false,
      success: function(data){

        // Replace the content of the node content
        // with the result from the ajax call
        $(node).removeClass('node-lazyload');
        $(nodeContent).removeClass('nodelazyloader-content');
        $(nodeContent).find('img.nodelazyloader-icon').remove();
        $(nodeContent).html(data);
        // fixed blank images when lazyloader module is installed
        if(jQuery().lazyloader) loadImage(node);
      }
    });
  };

  // Load the node's images
  function loadImage(node){
    var images = $(node).find('img[data-src]');
      images.each(function() {
      $(this).attr('src', $(this).data('src')).removeAttr('data-src');
    });  
  };  

})(jQuery);



