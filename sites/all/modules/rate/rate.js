(function ($) {
  Drupal.behaviors.rate = {
    attach: function(context) {
    $('.rate-widget').once('rate-widget').each(function () {
         var widget = $(this);
         var ids = widget.attr('id').match(/^rate\-([a-z]+)\-([0-9]+)\-([0-9]+)\-([0-9])$/);
         var data = {
          content_type: ids[1],
          content_id: ids[2],
          widget_id: ids[3],
          widget_mode: ids[4]
        };

        $('a.rate-button', widget).click(function() {
          var token = this.getAttribute('href').match(/rate\=([a-zA-Z0-9\-_]{32,64})/)[1];
          return Drupal.rateVote(widget, data, token);
        });
      });
    }
  };

  Drupal.rateVote = function(widget, data, token) {
    // Invoke JavaScript hook.
    widget.trigger('eventBeforeRate', [data]);

    $(".rate-info", widget).text(Drupal.t('.'));

    // Random number to prevent caching, see http://drupal.org/node/1042216#comment-4046618
    var random = Math.floor(Math.random() * 99999);
Drupal.settings.rate.basePath = Drupal.settings.rate.basePath instanceof Array ? Drupal.settings.rate.basePath[0] : Drupal.settings.rate.basePath;
Drupal.settings.rate.destination = Drupal.settings.rate.destination instanceof Array ? Drupal.settings.rate.destination[0] : Drupal.settings.rate.destination;
    var q = (Drupal.settings.rate.basePath.match(/\?/) ? '&' : '?') + 'widget_id=' + data.widget_id + '&content_type=' + data.content_type + '&content_id=' + data.content_id + '&widget_mode=' + data.widget_mode + '&token=' + token + '&destination=' + encodeURIComponent(Drupal.settings.rate.destination) + '&r=' + random;
    if (data.value) {
      q = q + '&value=' + data.value;
    }

    $.get(Drupal.settings.rate.basePath + q, function(response) {
      if (response.match(/^(\s+)?https?\:\/\/[^\/]+\/(.*)$/)) { 
        // We got a redirect.
        document.location = response;
      }
      else {
        // get parent object
        /*var p = widget.parent();*/

        // Invoke JavaScript hook.
        widget.trigger('eventAfterRate', [data]);

       /* widget.before(response);*/

        // remove widget
       /* widget.remove();
        widget = undefined;

        Drupal.attachBehaviors(p.get(0));*/
      // Replace all widgets on a page with the same ID.
       $.each($('div[id="' + widget.attr('id') + '"]'), function() {
         $(this).replaceWith(response);
        });

       // Ajaxify all recently added links.
       Drupal.behaviors.rate.attach();
       }
     });
 
    return false;
  }
})(jQuery);