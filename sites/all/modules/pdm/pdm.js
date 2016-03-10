(function ($) {

  Drupal.behaviors.PDM = {
    attach : function (context) {

      $("a.pdm-dismiss-link").once('pdm-link').click(function(ev){
        ev.preventDefault();
        var wrapper = $(this).parents(".pdm-message-wrapper")
        wrapper.slideUp(300);
        var pdm_link = $(this).attr('href');
        if (Drupal.settings.uid != 0) {
          // User is logged in, hide by ajax
          if (!pdm_link.match('/#/gi')) {
            $.ajax({
              url: pdm_link
            });
          }
        }
        else {
          // User is not logged in, hide via local browser storage
          if (localStorage) {
            localStorage.setItem(wrapper.attr('id'), 'hidden');
          }
        }
        return false;
      });

      $(".pdm-message-wrapper").each(function(){
        var pdm_id = $(this).attr('id');
          if (localStorage && localStorage.getItem(pdm_id) == 'hidden') {
            $(this).hide();
          }
      });
    }
  }

  Drupal.behaviors.PDM_cluetips_attach = {
    attach : function (context) {

      var cluetip = $('.cluetip');

      cluetip.find('.pdm-dismiss-link').click(function(){
        $(this).parents('.pdm-message-wrapper').next('.tip').hide();
      });

      positionCluetips();

      function positionCluetips() {

        cluetip.each(function(){

          if ($('body').find('#' + $(this).attr('data')).length > 0) {
            $('#' + $(this).attr('data')).before($(this));
            $(this).find('.pdm-message-wrapper').once().after('<div class="tip"></div>').css({
              'margin-top' : '-' + ($(this).find('.pdm-message-wrapper').outerHeight() / 3) + 'px',
              'margin-left' : '-' + ($(this).find('.pdm-message-wrapper').outerWidth() + 20) + 'px'
            })

          }
        });
      };
    }
  }

})(jQuery);
