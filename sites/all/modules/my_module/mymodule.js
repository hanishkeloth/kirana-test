// within my_module.js
var container = $('#my-module-masonry-content');
container.masonry({
  // Masonry options
  itemSelector: '#my-module-masonry-content article.node'
});

// necessary to apply masonry to new items pulled in from infinite_scroll.js
container.bind('change', function() {
  container.masonry('reloadItems');
    container.masonry()
  });
});

if($.autopager) {
  // define autopager parameters
  var content_selector = '#my-module-masonry-content';
  var items_selector = content_selector + 'article.node';
  var next_selector = '.pager-next a';
  var pager_selector = '.pager'
 var handle = $.autopager({
  autoLoad: false,
  appendTo: content_selector,
  content: items_selector,
  link: next_selector,
  load: function() {
    $(content_selector).trigger('change');
  }
});