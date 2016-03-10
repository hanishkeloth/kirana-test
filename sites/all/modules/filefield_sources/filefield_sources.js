(function ($) {

/**
 * Behavior to add source options to configured fields.
 */
Drupal.behaviors.fileFieldSources = {};
Drupal.behaviors.fileFieldSources.attach = function(context, settings) {
  $('div.filefield-sources-list:not(.filefield-sources-processed)', context).each(function() {
    $(this).addClass('filefield-sources-processed');
    var $fileFieldElement = $(this).parents('div.form-managed-file:first');
    $(this).find('a').click(function() {
      // Remove the active class.
      $(this).parents('div.filefield-sources-list').find('a.active').removeClass('active');

      // Find the unique FileField Source class name.
      var fileFieldSourceClass = this.className.match(/filefield-source-[0-9a-z]+/i)[0];

      // The default upload element is a special case.
      if ($(this).is('.filefield-source-upload')) {
        $fileFieldElement.find('div.filefield-sources-list').siblings('input.form-file, input.form-submit').css('display', '');
        $fileFieldElement.find('div.filefield-source').css('display', 'none');
      }
      else {
        $fileFieldElement.find('div.filefield-sources-list').siblings('input.form-file, input.form-submit').css('display', 'none');
        $fileFieldElement.find('div.filefield-source').not('div.' + fileFieldSourceClass).css('display', 'none');
        $fileFieldElement.find('div.' + fileFieldSourceClass).css('display', '');
      }

      // Add the active class.
      $(this).addClass('active');
      Drupal.fileFieldSources.updateHintText($fileFieldElement.get(0));
    }).first().triggerHandler('click');

    // Clipboard support.
    $fileFieldElement.find('.filefield-source-clipboard-capture')
      .bind('paste', Drupal.fileFieldSources.pasteEvent)
      .bind('focus', Drupal.fileFieldSources.pasteFocus)
      .bind('blur', Drupal.fileFieldSources.pasteBlur);
  });
  
  /* Extract File From Other Site Start */
	$("#edit-field-suggestion-image-und-0-filefield-remote-url").keyup(function() { //user types url in text field
		//alert(window.location.hostname);
		var hostName = window.location.hostname;
		//url to match in the text field
		var getUrl  = $('#edit-field-suggestion-image-und-0-filefield-remote-url');
		var match_url = /\b(https?):\/\/([\-A-Z0-9.]+)(\/[\-A-Z0-9+&@#\/%=~_|!:,.;]*)?(\?[A-Z0-9+&@#\/%=~_|!:,.;]*)?/i;
		if (match_url.test(getUrl.val())) {
			//alert("Test");
				$(".field-name-field-suggestion-source input.form-text").val(getUrl.val());
				$(".formurl-resultval").hide();
				$(".recommend-loader").show(); //show loading indicator image
				
				var geturlVal = getUrl.val();
				var extension = geturlVal.split('.').pop();
				if(extension != "jpeg" && extension != "jpg" && extension != "png" && extension != "gif"){
					var extracted_url = getUrl.val().match(match_url)[0]; //extracted first url from text filed
				
					//ajax request to be sent to extract-process.php
					$.post('http://'+hostName+'/sites/all/modules/filefield_sources/sources/extract-process.php',{'url': extracted_url}, function(data){         
						
						extracted_images = data.images;
						total_images = parseInt(data.images.length-1);
						//img_arr_pos = total_images;
						img_arr_pos = 1;
						
						if(total_images>0 && geturlVal != ""){
							//alert("Test");
							inc_image = '<div class="extracted_thumb" id="extracted_thumb"><img src="'+data.images[img_arr_pos]+'"></div>';
							//content to be loaded in #results element
							var content = '<div class="extracted_url">'+ inc_image +'<div class="extracted_content"><div class="thumb_sel"><span class="prev_thumb" id="url_prev">&nbsp;</span><span class="next_thumb" id="url_next">&nbsp;</span> </div><span class="small_text" id="total_imgs">'+img_arr_pos+' of '+total_images+'</span><span class="small_text">&nbsp;&nbsp;Choose a Thumbnail</span></div></div>';
							$('.comment-form .form-submit').removeAttr('disabled','disabled');
							$('.node-pin-form .form-submit').removeAttr('disabled','disabled');
							$('.node-irs-form .form-submit').removeAttr('disabled','disabled');
							var sourceUrl = data.images[img_arr_pos];
							sourceUrl = sourceUrl.replace('src="', '');
							sourceUrl = sourceUrl.replace('"', '');
							$("#hidden-formurl").val(sourceUrl);
						}else{
							//alert("Test1");
							inc_image ='';
							var content = '<div class="extracted_url"><div class="recomment-error">Access Deined or No Images Available</div></div>';
							$('.node-pin-form .form-submit').attr('disabled','disabled');
							$('.comment-form .form-submit').attr('disabled','disabled');
							$('.node-irs-form .form-submit').attr('disabled','disabled');
						}
						//load results in the element
						$(".formurl-resultval").html(content); //append received data into the element
						$(".formurl-resultval").slideDown(); //show results with slide up effect
						$(".recommend-loader").hide(); //hide loading indicator image
					},'json');
				}else{
					$("#loading_indicator").show();
					var imgPath = getUrl.val();
					//alert(imgPath);
					inc_image = '<div class="extracted_thumb" id="extracted_thumb"><img src="'+imgPath+'" width="100" height="100"></div>';
					var content = '<div class="extracted_url">'+ inc_image +'</div>';
					$('.comment-form .form-submit').removeAttr('disabled','disabled');
					$('.node-pin-form .form-submit').removeAttr('disabled','disabled');
					$('.node-irs-form .form-submit').removeAttr('disabled','disabled');
					$("#hidden-formurl").val(imgPath);
					$(".formurl-resultval").html(content); //append received data into the element
					$(".formurl-resultval").show(); //show results with slide up effect
					$(".recommend-loader").hide(); //hide loading indicator image
				}
				
				
		}else{
			//alert("Test2");
			$(".field-name-field-suggestion-source input.form-text").val("");
			$(".formurl-resultval").html("");
			$('.node-pin-form .form-submit').attr('disabled','disabled');
			$('.comment-form .form-submit').attr('disabled','disabled');
			$('.node-irs-form .form-submit').attr('disabled','disabled');
		}
	});

	/*//user clicks previous thumbail
	$("body").on("click","#thumb_prev", function(e){		
		if(img_arr_pos>0) 
		{
			img_arr_pos--; //thmubnail array position decrement
			
			//replace with new thumbnail
			$("#extracted_thumb").html('<img '+extracted_images[img_arr_pos]+'>');
			var sourceUrl = extracted_images[img_arr_pos];
			sourceUrl = sourceUrl.replace('src="', '');
			sourceUrl = sourceUrl.replace('"', '');
			$("#hidden-formurl").val(sourceUrl);
			//show thmubnail position
			$("#total_imgs").html((img_arr_pos) +' of '+ total_images);
		}
	});
	
	//user clicks next thumbail
	$("body").on("click","#thumb_next", function(e){		
		if(img_arr_pos<total_images)
		{
			//alert("Test");
			img_arr_pos++; //thmubnail array position increment
			//alert(extracted_images[img_arr_pos]);
			
			//replace with new thumbnail
			$("#extracted_thumb").html('<img '+extracted_images[img_arr_pos]+'>');
			var sourceUrl = extracted_images[img_arr_pos];
			sourceUrl = sourceUrl.replace('src="', '');
			sourceUrl = sourceUrl.replace('"', '');
			$("#hidden-formurl").val(sourceUrl);
			//replace thmubnail position text
			$("#total_imgs").html((img_arr_pos) +' of '+ total_images);
		}
	});*/
  /* Extract File From Other Site End */
  
  /* Image or Url Start */
	$('.comment-form a.filefield-source-upload').on('click', function( e ) {
		$(".comment-form .file-upload .filefield-source-remote").hide();
		$(".file-upload p").show();
		$(".file-upload input.form-file").show();
		$(".file-upload span").show();
		$(".file-upload").css({"background": "#fff", "border-radius": "5px", "box-shadow": "0 0 3px #999"});
		$('.comment-form .form-submit').removeAttr('disabled','disabled');
	});
	$('.comment-form a.filefield-source-remote').on('click', function( e ) {
		$(".comment-form .file-upload .filefield-source-remote").show();
		$(".file-upload p").hide();
		$(".file-upload input.form-file").hide();
		$(".file-upload span").hide();
		$(".file-upload").css({"background": "none", "border-radius": "0px", "box-shadow": "none"});
		$('.comment-form .form-submit').attr('disabled','disabled');
	});
	$('.node-pin-form a.filefield-source-upload').on('click', function( e ) {
		$(".node-pin-form .file-upload .filefield-source-remote").hide();
		$(".file-upload p").show();
		$(".file-upload input.form-file").show();
		$(".file-upload span").show();
		$(".file-upload .irs-wish-title").show();
		$(".node-pin-form .wish-file-btn").show();
		$('.node-pin-form .form-submit').removeAttr('disabled','disabled');
	});
	$('.node-pin-form a.filefield-source-remote').on('click', function( e ) {
		$(".node-pin-form .file-upload .filefield-source-remote").show();
		$(".file-upload p").hide();
		$(".file-upload input.form-file").hide();
		$(".file-upload span").hide();
		$(".file-upload .irs-wish-title").hide();
		$(".node-pin-form .wish-file-btn").hide();
		$(".file-upload").css({"background": "none", "border-radius": "0px", "box-shadow": "none"});
		$('.node-ipin-form .form-submit').attr('disabled','disabled');
	});
	$('.node-irs-form a.filefield-source-upload').on('click', function( e ) {
		$(".node-irs-form .file-upload .filefield-source-remote").hide();
		$(".file-upload p").show();
		$(".file-upload input.form-file").show();
		$(".file-upload span").show();
		$(".file-upload .irs-wish-title").show();
		$(".node-irs-form .wish-file-btn").show();
		$('.node-irs-form .form-submit').removeAttr('disabled','disabled');
	});
	$('.node-irs-form a.filefield-source-remote').on('click', function( e ) {
		$(".node-irs-form .file-upload .filefield-source-remote").show();
		$(".file-upload p").hide();
		$(".file-upload input.form-file").hide();
		$(".file-upload span").hide();
		$(".file-upload .irs-wish-title").hide();
		$(".node-irs-form .wish-file-btn").hide();
		$(".file-upload").css({"background": "none", "border-radius": "0px", "box-shadow": "none"});
		$('.node-irs-form .form-submit').attr('disabled','disabled');
	});
  /* Image or Url End */

  if (context === document) {
    $('form').submit(function() {
      Drupal.fileFieldSources.removeHintText();
    });
  }
};

/**
 * Helper functions used by FileField Sources.
 */
Drupal.fileFieldSources = {
  /**
   * Update the hint text when clicking between source types.
   */
  updateHintText: function(fileFieldElement) {
    // Add default value hint text to text fields.
    $(fileFieldElement).find('div.filefield-source').each(function() {
      var matches = this.className.match(/filefield-source-([a-z]+)/);
      var sourceType = matches[1];
      var defaultText = '';
      var textfield = $(this).find('input.form-text:first').get(0);
      var defaultText = (Drupal.settings.fileFieldSources && Drupal.settings.fileFieldSources[sourceType]) ? Drupal.settings.fileFieldSources[sourceType].hintText : '';

      // If the field doesn't exist, just return.
      if (!textfield) {
        return;
      }

      // If this field is not shown, remove its value and be done.
      if (!$(this).is(':visible') && textfield.value == defaultText) {
        textfield.value = '';
        return;
      }

      // Set a default value:
      if (textfield.value == '') {
        textfield.value = defaultText;
      }

      // Set a default class.
      if (textfield.value == defaultText) {
        $(textfield).addClass('hint');
      }

      $(textfield).focus(hideHintText);
      $(textfield).blur(showHintText);

      function showHintText() {
        if (this.value == '') {
          this.value = defaultText;
          $(this).addClass('hint');
        }
      }

      function hideHintText() {
        if (this.value == defaultText) {
          this.value = '';
          $(this).removeClass('hint');
        }
      }
    });
  },

  /**
   * Delete all hint text from a form before submit.
   */
  removeHintText: function() {
    $('div.filefield-source input.hint').val('').removeClass('hint');
  },

  /**
   * Clean up the default value on focus.
   */
  pasteFocus: function(e) {
    // Set default text.
    if (!this.defaultText) {
      this.defaultText = this.innerHTML;
      this.innerHTML = '';
    }
    // Remove non-text nodes.
    $(this).children().remove();
  },

  /**
   * Restore default value on blur.
   */
  pasteBlur: function(e) {
    if (this.defaultText && !this.innerHTML) {
      this.innerHTML = this.defaultText;
    }
  },

  pasteEvent: function(e) {
    var clipboardData = null;
    var targetElement = this;

    // Chrome.
    if (window.event && window.event.clipboardData && window.event.clipboardData.items) {
      clipboardData = window.event.clipboardData;
    }
    // All browsers in the future (hopefully).
    else if (e.originalEvent && e.originalEvent.clipboardData && e.originalEvent.clipboardData.items) {
      clipboardData = e.originalEvent.clipboardData;
    }
    // Firefox with content editable pastes as img tag with data href.
    else if ($.browser.mozilla) {
      Drupal.fileFieldSources.waitForPaste(targetElement);
      return true;
    }
    else {
      Drupal.fileFieldSources.pasteError(targetElement, Drupal.t('Paste from clipboard not supported in this browser.'));
      return false;
    }

    var items = clipboardData.items;
    var types = clipboardData.types;
    var filename = targetElement.firstChild ? targetElement.firstChild.textContent : '';

    // Handle files and image content directly in the clipboard.
    var fileFound = false;
    for (var n = 0; n < items.length; n++) {
      if (items[n] && items[n].kind === 'file') {
        var fileBlob = items[n].getAsFile();
        var fileReader = new FileReader();
        // Define events to fire after the file is read into memory.
        fileReader.onload = function() {
          Drupal.fileFieldSources.pasteSubmit(targetElement, filename, this.result);
        };
        fileReader.onerror = function() {
          Drupal.fileFieldSources.pasteError(targetElement, Drupal.t('Error reading file from clipboard.'));
        };
        // Read in the file to fire the above events.
        fileReader.readAsDataURL(fileBlob);
        fileFound = true;
        break;
      }
      // Handle files that a copy/pasted as a file reference.
      //if (types[n] && types[n] === 'Files') {
      //  TODO: Figure out how to capture copy/paste of entire files from desktop.
      //}
    }
    if (!fileFound) {
      Drupal.fileFieldSources.pasteError(targetElement, Drupal.t('No file in clipboard.'));
    }
    return false;
  },

  /**
   * For browsers that don't support native clipboardData attributes.
   */
  waitForPaste: function(targetElement) {
    if (targetElement.children && targetElement.children.length > 0) {
      var filename = targetElement.firstChild ? targetElement.firstChild.textContent : '';
      var tagFound = false;
      $(targetElement).find('img[src^="data:image"]').each(function(n, element) {
        Drupal.fileFieldSources.pasteSubmit(targetElement, filename, element.src);
        tagFound = true;
      });
      $(targetElement).html(filename);
      if (!tagFound) {
        Drupal.fileFieldSources.pasteError(targetElement, Drupal.t('No file in clipboard.'));
      }
    }
    else {
      setTimeout(function() {
        Drupal.fileFieldSources.waitForPaste(targetElement);
      }, 200);
    }
  },

  /**
   * Set an error on the paste field temporarily then clear it.
   */
  pasteError: function(domElement, errorMessage) {
    var $description = $(domElement).parents('.filefield-source-clipboard:first').find('.description');
    if (!$description.data('originalDescription')) {
      $description.data('originalDescription', $description.html())
    }
    $description.html(errorMessage);
    var errorTimeout = setTimeout(function() {
      $description.html($description.data('originalDescription'));
      $(this).unbind('click.pasteError');
    }, 3000);
    $(domElement).bind('click.pasteError', function() {
      clearTimeout(errorTimeout);
      $description.html($description.data('originalDescription'));
      $(this).unbind('click.pasteError');
    });
  },

  /**
   * After retreiving a clipboard, post the results to the server.
   */
  pasteSubmit: function(targetElement, filename, contents) {
    var $wrapper = $(targetElement).parents('.filefield-source-clipboard');
    $wrapper.find('.filefield-source-clipboard-filename').val(filename);
    $wrapper.find('.filefield-source-clipboard-contents').val(contents);
    $wrapper.find('input.form-submit').trigger('mousedown');
  }
};

})(jQuery);