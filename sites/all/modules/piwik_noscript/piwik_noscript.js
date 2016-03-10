(function ($) {

Drupal.behaviors.piwikNoscript = {
  attach: function (context, settings) {
    $('#piwik-noscript', context).once('piwik-noscript', function() {
      // Append some parameters to the src attribute before creating the image tag.
      var image = $(settings.piwikNoscript.image.replace('PIWIK_NOSCRIPT_PLACEHOLDER=', 'action_name=' + encodeURIComponent(document.title) + '&urlref=' + encodeURIComponent(document.referrer)));
      $(this).html(image);
    });
  }
};

}(jQuery));
