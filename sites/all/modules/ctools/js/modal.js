/**
 * @file
 *
 * Implement a modal form.
 *
 * @see modal.inc for documentation.
 *
 * This javascript relies on the CTools ajax responder.
 */

(function ($) {
  // Make sure our objects are defined.
  Drupal.CTools = Drupal.CTools || {};
  Drupal.CTools.Modal = Drupal.CTools.Modal || {};

  /**
   * Display the modal
   *
   * @todo -- document the settings.
   */
  Drupal.CTools.Modal.show = function(choice) {
    var opts = {};

    if (choice && typeof choice == 'string' && Drupal.settings[choice]) {
      // This notation guarantees we are actually copying it.
      $.extend(true, opts, Drupal.settings[choice]);
    }
    else if (choice) {
      $.extend(true, opts, choice);
    }

    var defaults = {
      modalTheme: 'CToolsModalDialog',
      throbberTheme: 'CToolsModalThrobber',
      animation: 'show',
      animationSpeed: 'fast',
      modalSize: {
        type: 'scale',
        width: .8,
        height: .8,
        addWidth: 0,
        addHeight: 0,
        // How much to remove from the inner content to make space for the
        // theming.
        contentRight: 25,
        contentBottom: 45
      },
      modalOptions: {
        opacity: .55,
        background: '#fff'
      }
    };

    var settings = {};
    $.extend(true, settings, defaults, Drupal.settings.CToolsModal, opts);

    if (Drupal.CTools.Modal.currentSettings && Drupal.CTools.Modal.currentSettings != settings) {
      Drupal.CTools.Modal.modal.remove();
      Drupal.CTools.Modal.modal = null;
    }

    Drupal.CTools.Modal.currentSettings = settings;

    var resize = function(e) {
      // When creating the modal, it actually exists only in a theoretical
      // place that is not in the DOM. But once the modal exists, it is in the
      // DOM so the context must be set appropriately.
      var context = e ? document : Drupal.CTools.Modal.modal;

      if (Drupal.CTools.Modal.currentSettings.modalSize.type == 'scale') {
        /*var width = $(window).width() * Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = $(window).height() * Drupal.CTools.Modal.currentSettings.modalSize.height;*/
		var width = 350 * Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = 350 * Drupal.CTools.Modal.currentSettings.modalSize.height;
      }
      else {
        var width = Drupal.CTools.Modal.currentSettings.modalSize.width;
        var height = Drupal.CTools.Modal.currentSettings.modalSize.height;
      }

      // Use the additionol pixels for creating the width and height.
      $('div.ctools-modal-content', context).css({
        'width': width + Drupal.CTools.Modal.currentSettings.modalSize.addWidth + 'px',
        'height': height + Drupal.CTools.Modal.currentSettings.modalSize.addHeight + 'px'
      });
      $('div.ctools-modal-content .modal-content', context).css({
        'width': (width - Drupal.CTools.Modal.currentSettings.modalSize.contentRight) + 'px',
        'height': (height - Drupal.CTools.Modal.currentSettings.modalSize.contentBottom) + 'px'
      });
    }

    if (!Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.modal = $(Drupal.theme(settings.modalTheme));
      if (settings.modalSize.type == 'scale') {
        $(window).bind('resize', resize);
      }
    }

    resize();

    $('span.modal-title', Drupal.CTools.Modal.modal).html(Drupal.CTools.Modal.currentSettings.loadingText);
    Drupal.CTools.Modal.modalContent(Drupal.CTools.Modal.modal, settings.modalOptions, settings.animation, settings.animationSpeed);
    $('#modalContent .modal-content').html(Drupal.theme(settings.throbberTheme));

    // Position autocomplete results based on the scroll position of the modal.
    $('#modalContent .modal-content').delegate('input.form-autocomplete', 'keyup', function() {
      $('#autocomplete').css('top', $(this).position().top + $(this).outerHeight() + $(this).offsetParent().filter('#modal-content').scrollTop());
    });
  };

  /**
   * Hide the modal
   */
  Drupal.CTools.Modal.dismiss = function() {
    if (Drupal.CTools.Modal.modal) {
      Drupal.CTools.Modal.unmodalContent(Drupal.CTools.Modal.modal);
    }
  };

  Drupal.theme.prototype.ThemeChange = function() {
	  Drupal.theme.prototype.CToolsModalDialog();
	  /*$.when(Drupal.theme.prototype.CToolsModalDialog()).done(function() {
		  alert("TestTh");
       Drupal.CTools.Modal.popupChange();
		});*/
  };

  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.CToolsModalDialog = function() {
	setTimeout(function(){
		Drupal.CTools.Modal.popupChange();
	}, 5000);
    var html = ''
    html += '  <div id="ctools-modal">'
    html += '    <div class="ctools-modal-content">' // panels-modal-content
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">';
	html +=            Drupal.CTools.Modal.currentSettings.closeImage;
    //html +=            Drupal.CTools.Modal.currentSettings.closeText + Drupal.CTools.Modal.currentSettings.closeImage;
    html += '        </a>';
    html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-content">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';
	$('body').css("overflow","hidden");
    return html;

	Drupal.CTools.Modal.popupChange();
  }

  /**
   * Provide the HTML to create the throbber.
   */
  Drupal.theme.prototype.CToolsModalThrobber = function () {
    var html = '';
    html += '  <div id="modal-throbber">';
    html += '    <div class="modal-throbber-wrapper">';
    html +=        Drupal.CTools.Modal.currentSettings.throbber;
    html += '    </div>';
    html += '  </div>';

    return html;
  };

  /**
   * Figure out what settings string to use to display a modal.
   */
  Drupal.CTools.Modal.getSettings = function (object) {
    var match = $(object).attr('class').match(/ctools-modal-(\S+)/);
    if (match) {
      return match[1];
    }
  }

  /**
   * Click function for modals that can be cached.
   */
  Drupal.CTools.Modal.clickAjaxCacheLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return Drupal.CTools.AJAX.clickAJAXCacheLink.apply(this);
  };

  /**
   * Handler to prepare the modal for the response
   */
  Drupal.CTools.Modal.clickAjaxLink = function () {
    Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(this));
    return false;
  };

  /**
   * Submit responder to do an AJAX submit on all modal forms.
   */
  Drupal.CTools.Modal.submitAjaxForm = function(e) {
    var $form = $(this);
    var url = $form.attr('action');

    setTimeout(function() { Drupal.CTools.AJAX.ajaxSubmit($form, url); }, 1);
    return false;
  }

  /**
   * Bind links that will open modals to the appropriate function.
   */
  Drupal.behaviors.ZZCToolsModal = {
    attach: function(context) {
      // Bind links
      // Note that doing so in this order means that the two classes can be
      // used together safely.
      /*
       * @todo remimplement the warm caching feature
       $('a.ctools-use-modal-cache', context).once('ctools-use-modal', function() {
         $(this).click(Drupal.CTools.Modal.clickAjaxCacheLink);
         Drupal.CTools.AJAX.warmCache.apply(this);
       });
        */

      $('area.ctools-use-modal, a.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        // Create a drupal ajax object
        var element_settings = {};
        if ($this.attr('href')) {
          element_settings.url = $this.attr('href');
          element_settings.event = 'click';
          element_settings.progress = { type: 'throbber' };
        }
        var base = $this.attr('href');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
      });

      // Bind buttons
      $('input.ctools-use-modal, button.ctools-use-modal', context).once('ctools-use-modal', function() {
        var $this = $(this);
        $this.click(Drupal.CTools.Modal.clickAjaxLink);
        var button = this;
        var element_settings = {};

        // AJAX submits specified in this manner automatically submit to the
        // normal form action.
        element_settings.url = Drupal.CTools.Modal.findURL(this);
        if (element_settings.url == '') {
          element_settings.url = $(this).closest('form').attr('action');
        }
        element_settings.event = 'click';
        element_settings.setClick = true;

        var base = $this.attr('id');
        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);

        // Make sure changes to settings are reflected in the URL.
        $('.' + $(button).attr('id') + '-url').change(function() {
          Drupal.ajax[base].options.url = Drupal.CTools.Modal.findURL(button);
        });
      });

      // Bind our custom event to the form submit
      $('#modal-content form', context).once('ctools-use-modal', function() {
        var $this = $(this);
        var element_settings = {};

        element_settings.url = $this.attr('action');
        element_settings.event = 'submit';
        element_settings.progress = { 'type': 'throbber' }
        var base = $this.attr('id');

        Drupal.ajax[base] = new Drupal.ajax(base, this, element_settings);
        Drupal.ajax[base].form = $this;

        $('input[type=submit], button', this).click(function(event) {
          Drupal.ajax[base].element = this;
          this.form.clk = this;
          // Stop autocomplete from submitting.
          if (Drupal.autocompleteSubmit && !Drupal.autocompleteSubmit()) {
            return false;
          }
          // An empty event means we were triggered via .click() and
          // in jquery 1.4 this won't trigger a submit.
          if (event.bubbles == undefined) {
            $(this.form).trigger('submit');
            return false;
          }
        });
      });

      // Bind a click handler to allow elements with the 'ctools-close-modal'
      // class to close the modal.
      $('.ctools-close-modal', context).once('ctools-close-modal')
        .click(function() {
          Drupal.CTools.Modal.dismiss();
          return false;
        });
    }
  };

  // The following are implementations of AJAX responder commands.

  /**
   * AJAX responder command to place HTML within the modal.
   */
  Drupal.CTools.Modal.modal_display = function(ajax, response, status) {
	  $('body').css("overflow","hidden");
    if ($('#modalContent').length == 0) {
      Drupal.CTools.Modal.show(Drupal.CTools.Modal.getSettings(ajax.element));
    }
    $('#modal-title').html(response.title);
    // Simulate an actual page load by scrolling to the top after adding the
    // content. This is helpful for allowing users to see error messages at the
    // top of a form, etc.
    $('#modal-content').html(response.output).scrollTop(0);

    // Attach behaviors within a modal dialog.
    var settings = response.settings || ajax.settings || Drupal.settings;
    Drupal.attachBehaviors('#modalContent', settings);
  }

  /**
   * AJAX responder command to dismiss the modal.
   */
  Drupal.CTools.Modal.modal_dismiss = function(command) {
    Drupal.CTools.Modal.dismiss();
    $('link.ctools-temporary-css').remove();
  }

  /**
   * Display loading
   */
  //Drupal.CTools.AJAX.commands.modal_loading = function(command) {
  Drupal.CTools.Modal.modal_loading = function(command) {
    Drupal.CTools.Modal.modal_display({
      output: Drupal.theme(Drupal.CTools.Modal.currentSettings.throbberTheme),
      title: Drupal.CTools.Modal.currentSettings.loadingText
    });
  }

  /**
   * Find a URL for an AJAX button.
   *
   * The URL for this gadget will be composed of the values of items by
   * taking the ID of this item and adding -url and looking for that
   * class. They need to be in the form in order since we will
   * concat them all together using '/'.
   */
  Drupal.CTools.Modal.findURL = function(item) {
    var url = '';
    var url_class = '.' + $(item).attr('id') + '-url';
    $(url_class).each(
      function() {
        var $this = $(this);
        if (url && $this.val()) {
          url += '/';
        }
        url += $this.val();
      });
    return url;
  };


  /**
   * modalContent
   * @param content string to display in the content box
   * @param css obj of css attributes
   * @param animation (fadeIn, slideDown, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Drupal.CTools.Modal.modalContent = function(content, css, animation, speed) {
    // If our animation isn't set, make it just show/pop
    if (!animation) {
      animation = 'show';
    }
    else {
      // If our animation isn't "fadeIn" or "slideDown" then it always is show
      if (animation != 'fadeIn' && animation != 'slideDown') {
        animation = 'show';
      }
    }

    if (!speed) {
      speed = 'fast';
    }

    // Build our base attributes and allow them to be overriden
    /*css = jQuery.extend({
      position: 'absolute',
      left: '0px',
      margin: '0px',
      background: '#000',
      opacity: '.55'
    }, css);

    // Add opacity handling for IE.
    css.filter = 'alpha(opacity=' + (100 * css.opacity) + ')';*/
    content.hide();

    // if we already ahve a modalContent, remove it
    if ( $('#modalBackdrop')) $('#modalBackdrop').remove();
    if ( $('#modalContent')) $('#modalContent').remove();

    // position code lifted from http://www.quirksmode.org/viewport/compatibility.html
    if (self.pageYOffset) { // all except Explorer
    var wt = self.pageYOffset;
    } else if (document.documentElement && document.documentElement.scrollTop) { // Explorer 6 Strict
      var wt = document.documentElement.scrollTop;
    } else if (document.body) { // all other Explorers
      var wt = document.body.scrollTop;
    }

    // Get our dimensions

    // Get the docHeight and (ugly hack) add 50 pixels to make sure we dont have a *visible* border below our div
    var docHeight = $(document).height() + 50;
    var docWidth = $(document).width();
    var winHeight = $(window).height();
    var winWidth = $(window).width();
    if( docHeight < winHeight ) docHeight = winHeight;

    // Create our divs
    $('body').append('<div id="modalBackdrop" style="z-index: 1000; display: none;"><a href="javascript:" class="modalOuter"></a><div id="modalContent" style="z-index: 1001;"><a href="javascript:" class="modalOuter"></a>' + $(content).html() + '</div></div>');

    // Keyboard and focus event handler ensures focus stays on modal elements only
    modalEventHandler = function( event ) {
      target = null;
      if ( event ) { //Mozilla
        target = event.target;
      } else { //IE
        event = window.event;
        target = event.srcElement;
      }

      var parents = $(target).parents().get();
      for (var i = 0; i < parents.length; ++i) {
        var position = $(parents[i]).css('position');
        if (position == 'absolute' || position == 'fixed') {
          return true;
        }
      }
      if( $(target).filter('*:visible').parents('#modalContent').size()) {
        // allow the event only if target is a visible child node of #modalContent
        return true;
      }
      if ( $('#modalContent')) $('#modalContent').get(0).focus();
      return false;
    };
    $('body').bind( 'focus', modalEventHandler );
    $('body').bind( 'keypress', modalEventHandler );

    // Create our content div, get the dimensions, and hide it
    var modalContent = $('#modalContent').css('top','-1000px');
    var mdcTop = wt + ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
    var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);
    /*$('#modalBackdrop').css(css).css('top', 0).css('height', docHeight + 'px').css('width', docWidth + 'px').show();
    modalContent.css({top: mdcTop + 'px', left: mdcLeft + 'px'}).hide()[animation](speed);*/
	$('#modalBackdrop').show();
    modalContent.hide()[animation](speed);

    // Bind a click for closing the modalContent
    modalContentClose = function(){
		close();
		$('body').css("overflow","auto");
		return false;
		};
    $('.close').bind('click', modalContentClose);

    // Bind a keypress on escape for closing the modalContent
    modalEventEscapeCloseHandler = function(event) {
      if (event.keyCode == 27) {
        close();
        return false;
      }
    };

	$('.modalOuter').click(function() {
		//alert("Test");
		close();
		$('body').css("overflow","auto");
	});

    $(document).bind('keydown', modalEventEscapeCloseHandler);

    // Close the open modal content and backdrop
    function close() {
      // Unbind the events
      $(window).unbind('resize',  modalContentResize);
      $('body').unbind( 'focus', modalEventHandler);
      $('body').unbind( 'keypress', modalEventHandler );
      $('.close').unbind('click', modalContentClose);
      $('body').unbind('keypress', modalEventEscapeCloseHandler);
      $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

      // Set our animation parameters and use them
      if ( animation == 'fadeIn' ) animation = 'fadeOut';
      if ( animation == 'slideDown' ) animation = 'slideUp';
      if ( animation == 'show' ) animation = 'hide';

      // Close the content
      modalContent.hide()[animation](speed);

      // Remove the content
      $('#modalContent').remove();
      $('#modalBackdrop').remove();
    };

    // Move and resize the modalBackdrop and modalContent on resize of the window
     modalContentResize = function(){
      // Get our heights
      var docHeight = $(document).height();
      var docWidth = $(document).width();
      var winHeight = $(window).height();
      var winWidth = $(window).width();
      if( docHeight < winHeight ) docHeight = winHeight;

      // Get where we should move content to
      var modalContent = $('#modalContent');
      var mdcTop = ( winHeight / 2 ) - (  modalContent.outerHeight() / 2);
      var mdcLeft = ( winWidth / 2 ) - ( modalContent.outerWidth() / 2);

      // Apply the changes
      /*$('#modalBackdrop').css('height', docHeight + 'px').css('width', docWidth + 'px').show();
      modalContent.css('top', mdcTop + 'px').css('left', mdcLeft + 'px').show();*/
	  $('#modalBackdrop').show();
      modalContent.show();
    };
    $(window).bind('resize', modalContentResize);

    $('#modalContent').focus();
  };

  /**
   * unmodalContent
   * @param content (The jQuery object to remove)
   * @param animation (fadeOut, slideUp, show)
   * @param speed (valid animation speeds slow, medium, fast or # in ms)
   */
  Drupal.CTools.Modal.unmodalContent = function(content, animation, speed)
  {
    // If our animation isn't set, make it just show/pop
    if (!animation) { var animation = 'show'; } else {
      // If our animation isn't "fade" then it always is show
      if (( animation != 'fadeOut' ) && ( animation != 'slideUp')) animation = 'show';
    }
    // Set a speed if we dont have one
    if ( !speed ) var speed = 'fast';

    // Unbind the events we bound
    $(window).unbind('resize', modalContentResize);
    $('body').unbind('focus', modalEventHandler);
    $('body').unbind('keypress', modalEventHandler);
    $('.close').unbind('click', modalContentClose);
    $(document).trigger('CToolsDetachBehaviors', $('#modalContent'));

    // jQuery magic loop through the instances and run the animations or removal.
    content.each(function(){
      if ( animation == 'fade' ) {
        $('#modalContent').fadeOut(speed, function() {
          $('#modalBackdrop').fadeOut(speed, function() {
            $(this).remove();
          });
          $(this).remove();
        });
      } else {
        if ( animation == 'slide' ) {
          $('#modalContent').slideUp(speed,function() {
            $('#modalBackdrop').slideUp(speed, function() {
              $(this).remove();
            });
            $(this).remove();
          });
        } else {
          $('#modalContent').remove();
          $('#modalBackdrop').remove();
        }
      }
    });
  };

  Drupal.CTools.Modal.popupChange = function() {
	$(".titletext").each(function(){
		var scrollHeight = $(this).prop("scrollHeight");
		var height = $(this).height();
		if(scrollHeight > height){
		$(this).children("span").show();
		}else{
		$(this).children("span").hide();
		}
	});
	$(".hello a").text("Buy");
  };

  $(document).ready(function(){
	  $(".suggestion-box").live("click", "a.morecomments-button",function(){
		setTimeout(function(){
			Drupal.CTools.Modal.popupChange();
		}, 2000);
	  });

	  $(".suggestion-box .logsugg-comment").live("click",function(){
			//alert("Test");
			$(".suggestion-comment").toggle();
	  });

	  	$(".modalOuter1").live("click",function(){
			//alert("Test1");
			//close();
			$("#modalContent").remove();
			$("#modalBackdrop").remove();
			$("body").css("overflow","auto");
		});
		//user clicks next thumbail
		$("#url_next").live("click",function(){
			if(img_arr_pos<total_images){
				img_arr_pos++; //thmubnail array position increment
				$("#extracted_thumb").html('<img src="'+extracted_images[img_arr_pos]+'">');
				//$("#extracted_thumb").html('<img '+extracted_images[img_arr_pos]+'>');
				var sourceUrl2 = extracted_images[img_arr_pos];
				sourceUrl2 = sourceUrl2.replace('src="', '');
				sourceUrl2 = sourceUrl2.replace('"', '');
				$("#hidden-formurl").val(sourceUrl2);
				$("#total_imgs").html((img_arr_pos) +' of '+ total_images);
			}
		});
		//user clicks previous thumbail
		$("#url_prev").live("click",function(){
			if(img_arr_pos>0){
				img_arr_pos--; //thmubnail array position decrement
				$("#extracted_thumb").html('<img src="'+extracted_images[img_arr_pos]+'">');
				//$("#extracted_thumb").html('<img '+extracted_images[img_arr_pos]+'>');
				var sourceUrl1 = extracted_images[img_arr_pos];
				sourceUrl1 = sourceUrl1.replace('src="', '');
				sourceUrl1 = sourceUrl1.replace('"', '');
				$("#hidden-formurl").val(sourceUrl1);
				$("#total_imgs").html((img_arr_pos) +' of '+ total_images);
			}
		});

	  $(".buyButton").live("click",function(){
			//alert("Test");
			var textUrl = $(this).attr("href");
			//alert(textUrl);
			var printUrl;

			var domainUrl = textUrl.split("/");
			//alert(domainUrl[2]+textUrl);

			if(domainUrl[2] == "flipkart.com" || domainUrl[2] == "www.flipkart.com"){
				//alert("Test");
				var affId = textUrl.split("&affid=wisharypo");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("&");
					var spiltValue = "&"+spiltUrl[spiltUrl.length-1];
					var spiltUrl1 = textUrl.split("?");
					var changeUrl;
					if(spiltUrl1.length > 1){
						changeUrl = textUrl.replace(spiltValue, "")+"&affid=wisharypo";
					}else{
						changeUrl = textUrl.replace(spiltValue, "")+"?affid=wisharypo";
					}
					if(domainUrl[2] == "flipkart.com"){
						printUrl = changeUrl.replace("flipkart.com", "dl.flipkart.com");
					}else if(domainUrl[2] == "www.flipkart.com"){
						printUrl = changeUrl.replace("www.flipkart.com", "dl.flipkart.com");
					}
				}else{
					printUrl = textUrl;
				}
			}else if(domainUrl[2] == "infibeam.com" || domainUrl[2] == "www.infibeam.com"){
				//alert("Test");
				var affId = textUrl.split("trackId=wish");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("?");
					if(spiltUrl.length > 1){
						printUrl = textUrl+"&trackId=wish";
					}else{
						printUrl = textUrl+"?trackId=wish";
					}
				}else{
					printUrl = textUrl;
				}
			}else if(domainUrl[2] == "snapdeal.com" || domainUrl[2] == "www.snapdeal.com"){
				//alert("Test");
				var affId = textUrl.split("&aff_id");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("?");
					if(spiltUrl.length > 1){
						printUrl = textUrl+"&utm_source=aff_prog&utm_campaign=afts&offer_id=17&aff_id=35536";
					}else{
						printUrl = textUrl+"?utm_source=aff_prog&utm_campaign=afts&offer_id=17&aff_id=35536";
					}
				}else{
					printUrl = textUrl;
				}
			}else if(domainUrl[2] == "amazon.in" || domainUrl[2] == "www.amazon.in"){
				//alert("Test");
				var affId = textUrl.split("tag=wisharyin-21");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("?");
					if(spiltUrl.length > 1){
						printUrl = textUrl+"&tag=wisharyin-21";
					}else{
						printUrl = textUrl+"?tag=wisharyin-21";
					}
				}else{
					printUrl = textUrl;
				}
			}else if(domainUrl[2] == "shimply.com" || domainUrl[2] == "www.shimply.com"){
				//alert("Test");
				var affId = textUrl.split("aff_id=372");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("?");
					if(spiltUrl.length > 1){
						printUrl = textUrl+"&aff_id=372";
					}else{
						printUrl = textUrl+"?aff_id=372";
					}
				}else{
					printUrl = textUrl;
				}
			}else if(domainUrl[2] == "shopclues.com" || domainUrl[2] == "www.shopclues.com"){
				//alert("Test");
				var affId = textUrl.split("a=406");
				if(affId.length <= 1){
					var spiltUrl = textUrl.split("?");
					if(spiltUrl.length > 1){
						printUrl = "http://affiliateshopclues.com/?a=406&c=19&p=r&s1=shopclues&ckmrdr="+textUrl+"&utm_source=wishary&utm_medium=CPS&s2=manulysale";
					}else{
						printUrl = "http://affiliateshopclues.com/?a=406&c=19&p=r&s1=shopclues&ckmrdr="+textUrl+"?utm_source=wishary&utm_medium=CPS&s2=manulysale";
					}
				}else{
					printUrl = textUrl;
				}
			}else{
				printUrl = textUrl;
			}
			$(this).attr("href",printUrl);
			//$("#printValue").html(printUrl);
	  });

	   $("input:radio[name=gender]").live("click",function(){
			var radioValue = $(this).val();
			if(radioValue == "Male"){
				$(".class_male").addClass("gender-opt-active");
		  		$(".class_female").removeClass("gender-opt-active");
			}else if(radioValue == "Female"){
				 $(".class_female").addClass("gender-opt-active");
		  		 $(".class_male").removeClass("gender-opt-active");
			}
	   });

	   /* Create Node Description Start */
	   $(".colorouter").live("click",function(){
			$(".colorpalet").toggle();
			$(".productpalet").hide();
		});

		$(".colorpalet a").live("click",function(){
			var colorValue = $(".colorvalue").val().toLowerCase();
			var colId = this.id;
			$(this).removeClass("GoogleAnalyticsET-processed");
			var colName = $(this).attr('class');
			var colChangeId = colName.replace("-", "");
			var colValueId = colorValue.replace("-", "").replace(/\s/g, "").toLowerCase();
			var textArea = $(".wish-des textarea").val();
			if(colorValue  == ""){
				var textChange = textArea+" #"+$.trim(colChangeId);
			}else{
				var textChange = textArea.replace(colValueId, colChangeId);
			}
			//alert(colorValue);
			$(".wish-des textarea").val(textChange);
			$(".colorpalet").hide();
			$(".colorouter").hide();
			$(".hidden_colorfield option").removeAttr("selected").filter("[value="+colId+"]").attr("selected", true);
		});

		$(".productouter").live("click",function(){
			$(".colorpalet").hide();
			$(".productpalet").toggle();
		});

		$(".productInner").live("click",function(){
			var postMenu = $(this).find('.productList');
			//alert(postMenu);
			if(postMenu.is(':hidden') ){
				$('.productList').slideUp();
				postMenu.slideDown();
			}else{
				postMenu.slideUp() ;
			}
		});

		$(".productList a").live("click",function(){
			var z;
			var colId = this.id;
			$(this).removeClass("GoogleAnalyticsET-processed");
			var className = $(this).attr('class');
			var categoryvalue = $(".categoryvalue").val().toLowerCase();
			var maincategoryvalue = $(".maincategoryvalue").val().toLowerCase();
			var textUpdate = className.replace("-", "");
			var textArray = textUpdate.split("_");
			if(categoryvalue != "" && maincategoryvalue != ""){
				var cateArray = categoryvalue.replace(" ", "-").split("-");
				var cateMainArray = maincategoryvalue.split("-");
				$.each(cateMainArray, function( i, val ) {
					var textArea = $(".wish-des textarea").val();
					var textChange = textArea.replace("#"+$.trim(val), "");
					$(".wish-des textarea").val(textChange);
				});
				$.each(cateArray, function( i, val ) {
					var textArea = $(".wish-des textarea").val();
					var textChange = textArea.replace("#"+$.trim(val), "");
					$(".wish-des textarea").val(textChange);
				});
				$('.hidden_categoryfield option').removeAttr('selected').filter('[value='+colId+']').attr('selected', true);
			}
			$.each(textArray, function( i, val ) {
				var textArea = $(".wish-des textarea").val();
				var textChange = textArea+" #"+$.trim(val);
				$(".wish-des textarea").val(textChange);
			});

			$(".productpalet").hide();
			$(".productouter").hide();
			$('.hidden_categoryfield option').removeAttr('selected').filter('[value='+colId+']').attr('selected', true);
			//alert("Cate Id"+colId+" Cate Value"+$("#edit-field-category1-und").val());
		});

		$(".wish-des textarea").live("click",function(){
			$(".colorpalet").hide();
			$(".productpalet").hide();
		});

		$(".resetButton").live("click",function(){
			//alert("Test");
			$(".productpalet").hide();
			$(".colorpalet").hide();
			$(".productouter").show();
			$(".colorouter").show();
			$(".autocomplete-1").show();
			$(".wish-des #automplete-1").val("");
			$(".brand-display input").val("");
			$(".brand-display").show();
			$(".hidden_categoryfield").val("");
			$(".hidden_colorfield").val("");
			//$("#edit-field-category1-en").val("");
			var resetValue = $(".descriptionvalue").val();
			if(resetValue  == ""){
				$(".wish-des textarea").val("");
			}else{
				$(".wish-des textarea").val(resetValue);
			}
		});

		$(".brand-display input").live("focus", function() {
			$(".colorpalet").hide();
			$(".productpalet").hide();
		});

		$("#ui-id-2 li a").live("click", function() {
			var brandNameValue = $(".brand-display input").val();
			var brandName = brandNameValue.replace(/\s/g, "").replace("-", "");
			var brandExValue = $(".brandvalue").val();
			var brandEx = brandExValue.replace(/\s/g, "").replace("-", "");
			var textArea = $(".wish-des textarea").val();
			if(brandExValue  == ""){
				var textChange = textArea+" #"+$.trim(brandName);
			}else{
				var textChange = textArea.replace(brandEx, brandName);
			}
			$(".wish-des textarea").val(textChange);
			$(".brand-display").hide();
		});

	   /* Create Node Description End */

    var price_min = 100;
    var price_max = 100000;
    $('#rangeslider').slider({
      range: true,
      min: parseInt(price_min),
      max: parseInt(price_max),
      values: [price_min, price_max],
      slide: function( event, ui ) {
        $('#rangeval').html("Rs "+ui.values[0]+" - Rs "+ui.values[1]);
      },
      change: function() {
        console.log("slider value changed");
        list_recommendations();
      }
    });

	});

  //Color palete click event in IRS edit form
  $(".colorpalet-irs a").live("click",function(){
      var colorValue = $(".colorvalue").val().toLowerCase();
      var colId = this.id;
      //console.log("colId="+colId);
      $("#edit-field-color-list-und option").removeAttr("selected");
      $("#edit-field-second-color-und option").removeAttr("selected");
      $('#edit-field-color-list-und option').map(function () {
        if ($(this).val() == colId) return this;
      }).attr('selected', 'selected');
      //$(this).removeClass("GoogleAnalyticsET-processed");
      var colName = $(this).attr('class');
      var predictions = $(".predictions-container-irs input").val();
      var description = $(".description-field-irs textarea").val();
      var new_col = $('#new_color').val().toLowerCase();
      console.log("new_col="+new_col);
      var new_predictions = predictions.replace(new_col,colName);
      console.log("new_predictions="+new_predictions);
      var new_description = description.replace(new_col,colName);
      if($('#second_color').val().length > 0){
        var second_color = $('#second_color').val().toLowerCase();
        console.log("second_color="+second_color);
        new_description = new_description.replace('#'+second_color,'');
        new_predictions = new_predictions.replace(' '+second_color,'');
        $('#second_color').val();
      }
      console.log("new_description="+new_description);
      $(".predictions-container-irs input").val(new_predictions);
      $(".description-field-irs textarea").val(new_description);
      //console.log($(".description-field-irs textarea").val());
      $('#new_color').val(colName);
      $(this).addClass('active');
    });

$(function() {
  Drupal.ajax.prototype.commands.modal_display = Drupal.CTools.Modal.modal_display;
  Drupal.ajax.prototype.commands.modal_dismiss = Drupal.CTools.Modal.modal_dismiss;
});

})(jQuery);

