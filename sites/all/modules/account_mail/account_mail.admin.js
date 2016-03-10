(function ($) {

/**
 * Auto-hide summary textarea if empty and show hide and unhide links.
 */
Drupal.behaviors.accountMail = {
  setState: function (mode) {
    // ID of the textfield element to enabled/disable.
    textfield_element_id = 'edit-instance-widget-settings-account-mail-uid';
    element = $('#' + textfield_element_id);

    // If the widget is configured for using a custom UID, enable the textfield
    // element.
    if (mode == 'use_custom_uid') {
      element.removeAttr('disabled').removeClass('disabled');
      element.parent().removeClass('disabled');
    }
    else {
      element.attr('disabled', 'disabled').addClass('disabled');
      element.parent().addClass('disabled');
    }
  },

  attach: function (context, settings) {
    // Class of the div which contains the User ID source radio-buttons.
    target = 'form-item-instance-widget-settings-account-mail-uid-source';

    // Set the initial value.
    val = $('.' + target + ' input:checked').val();
    this.setState(val);

    // Attach an on-change behaviour.
    $('.' + target + ' input', context).change(function() {
      val = $('.' + target + ' input:checked').val();
      Drupal.behaviors.accountMail.setState(val);
    });
  }
}

})(jQuery);
