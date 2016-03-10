(function ($) {

Drupal.behaviors.initModalFormsComment = {
  attach: function (context, settings) {
        var $comment = $("a[href*='/comment/'], a[href*='?q=comment/']", context).filter(function() {
      return this.href.match(/(\/edit|\/reply)/);
    });
   $comment.once('init-modal-forms-comment', function () {
     this.href = this.href.replace(/comment\//,'modal_forms/nojs/comment/');
     }).addClass('ctools-use-modal ctools-modal-modal-popup-medium');
   }
 }; 
})(jQuery);