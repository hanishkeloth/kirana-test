(function ($, Drupal, window, document) {

    Drupal.behaviors.asi_common = {
        attach: function(context) {

            /*
             Apply Masonry
             */
            var container = $('.block-wishary-blog .block-asi-common', context);
            // apply masonry once images are loaded
            container.imagesLoaded(function() {
                container.masonry({
                    // options
                    itemSelector: '.block-asi-common li.masonry-list-item'
                });
            });

            // necessary to apply masonry to new items pulled in from views_infinite_scroll
            container.bind('change', function() {
                container.masonry('reloadItems');
                // ensure images have been loaded
                container.imagesLoaded(function() {
                    container.masonry({
                        transitionDuration: 0
                    });
                    // re-apply fitVids as well
                    $(".field-video").fitVids();
                    // Remove the loader class.
                    $('#view-more').removeClass('ajax-loader');
                });

                // disable "View more" button if we don't get the max number of nodes (i.e. we've reached the end of the content)
                var $view_more_count = document.querySelectorAll(".masonry-list-item .node").length;
                if ($view_more_count % 9 != 0) {
                    $('#view-more').hide();
                }
            });

            /*
             Apply Infinite Scroll
             */
            // Make sure that autopager plugin is loaded
            if($.autopager) {
                var content_selector = '.block-asi-common ul.masonry';
                var items_selector = content_selector + '> li';
                var next_selector = '.pager-next a';
                var pager_selector = '.pager';

                $(pager_selector).hide();
                var handle = $.autopager({
                    autoLoad: false,
                    appendTo: content_selector,
                    content: items_selector,
                    link: next_selector,
                    load: function() {
                        $(content_selector).trigger('change');
                    }
                });

                // disable "View more" button out of the gate if we don't get the max number of Node blocks (i.e. we've reached the end of the content)
                var $view_more_count = document.querySelectorAll(".masonry-list-item .node").length;
                // disable "View more" button if we don't get the max number of nodes (i.e. we've reached the end of the content)
                if ($view_more_count % 9 != 0) {
                    $('#view-more').hide();
                }

                // Trigger autoload if "View more" button is clicked and we haven't reached the end of the content
                $('#view-more').click(function(event) {
                    event.preventDefault();
                    // Add a loader class, to indicate that something is happening.
                    $('#view-more').addClass('ajax-loader');
                    handle.autopager('load');
                });

            }
            else {
                alert(Drupal.t('Autopager jquery plugin in not loaded.'));
            }
        }
    };

})(jQuery, Drupal, this, this.document);