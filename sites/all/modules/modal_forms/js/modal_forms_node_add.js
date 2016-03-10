(function ($) {

Drupal.behaviors.initModalFormsNodeAdd = {
  attach: function (context, settings) {
    var types = Drupal.settings.modal_forms_node_settings;
    $.each( types, function( index, value ){
      $("a[href*='/node/add/" + value + "'], a[href*='?q=node/add/" + value +"']", context).once('init-modal-forms-add-' + value, function () {
        this.href = this.href.replace('node/add/' + value,'modal_forms/nojs/add/' + value + '/type');
      }).addClass('ctools-use-modal ctools-modal-modal-popup-small');
    });
    
  }
};

})(jQuery);
