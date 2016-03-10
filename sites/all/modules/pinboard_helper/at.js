
/**
 * @file
 * Changes taxonomy tags fields to Active Tags style widgets.
 */

(function ($) {

var activeTags = {};
var activeBaccs = {};

activeTags.parseCsv = function (string, sep) {
  for (var result = string.split(sep = sep || ","), x = result.length - 1, tl; x >= 0; x--) {
    if (result[x].replace(/"\s+$/, '"').charAt(result[x].length - 1) == '"') {
      if ((tl = result[x].replace(/^\s+"/, '"')).length > 1 && tl.charAt(0) == '"') {
        result[x] = result[x].replace(/^\s*"|"\s*$/g, '').replace(/""/g, '"');
      }
      else if (x) {
        result.splice(x - 1, 2, [result[x - 1], result[x]].join(sep));
      }
      else {
        result = result.shift().split(sep).concat(result);
      }
    }
    else {
      result[x].replace(/""/g, '"');
    }
  }
  return result;
};

activeBaccs.parseCsv = function (string, sep) {
  for (var result = string.split(sep = sep || ","), x = result.length - 1, tl; x >= 0; x--) {
    if (result[x].replace(/"\s+$/, '"').charAt(result[x].length - 1) == '"') {
      if ((tl = result[x].replace(/^\s+"/, '"')).length > 1 && tl.charAt(0) == '"') {
        result[x] = result[x].replace(/^\s*"|"\s*$/g, '').replace(/""/g, '"');
      }
      else if (x) {
        result.splice(x - 1, 2, [result[x - 1], result[x]].join(sep));
      }
      else {
        result = result.shift().split(sep).concat(result);
      }
    }
    else {
      result[x].replace(/""/g, '"');
    }
  }
  return result;
};

activeTags.checkEnter = function (event) {
  if (event.keyCode == 13) {
    $('#autocomplete').each(function () {
      this.owner.hidePopup();
    });
    $(this).parent().find('.at-add-btn').click();
    event.preventDefault();
    return false;
  }
};

activeBaccs.checkEnter = function (event) {
  if (event.keyCode == 13) {
    $('#autocomplete').each(function () {
      this.owner.hidePopup();
    });
    $(this).parent().find('.at-add-btn-bacc').click();
    event.preventDefault();
    return false;
  }
};

activeTags.addTermOnSubmit = function () {
  $('.at-add-btn').click();
};

activeBaccs.addTermOnSubmit = function () {
  $('.at-add-btn-bacc').click();
};

activeTags.addTerms = function (context, terms) {
  terms = activeTags.parseCsv(terms);
  for (i in terms) {
    activeTags.addTerm(context, terms[i]);
  }
};

activeBaccs.addTerms = function (context, terms) {
  terms = activeBaccs.parseCsv(terms);
  for (i in terms) {
    activeBaccs.addTerm(context, terms[i]);
  }
};

activeTags.addTerm = function (context, term) {
  // Hide the autocomplete drop down.
  $('#autocomplete').each(function () {
    this.owner.hidePopup();
  });

  // Removing all HTML tags. Need to wrap in tags for text() to work correctly.
  term = $('<div>' + term + '</div>').text();
  term = Drupal.checkPlain(term);
  term = jQuery.trim(term);

  if (term != '') {
    var termDiv = $(context);
    var termList = termDiv.parent().find('.at-term-list');
    termList.append(Drupal.theme('activeTagsTermRemove', term));
    // Attach behaviors to new DOM content.
    Drupal.attachBehaviors(termList);
    activeTags.updateFormValue(termList);
    termList.parent().find('.at-term-entry').val('');
  }

  return false;
};

activeBaccs.addTerm = function (context, term) {
  // Hide the autocomplete drop down.
  $('#autocomplete').each(function () {
    this.owner.hidePopup();
  });

  // Removing all HTML tags. Need to wrap in tags for text() to work correctly.
  term = $('<div>' + term + '</div>').text();
  term = Drupal.checkPlain(term);
  term = jQuery.trim(term);

  if (term != '') {
    var termDiv = $(context);
    var termList = termDiv.parent().find('.at-term-list-bacc');
    termList.append(Drupal.theme('activeBaccsTermRemove', term));
    // Attach behaviors to new DOM content.
    Drupal.attachBehaviors(termList);
    activeBaccs.updateFormValue(termList);
    termList.parent().find('.at-term-entry-bacc').val('');
  }

  return false;
};

activeTags.removeTerm = function (context) {
  var tag = $(context);
  var termList = tag.parent();
  tag.remove();
  activeTags.updateFormValue(termList);
};

activeBaccs.removeTerm = function (context) {
  var tag = $(context);
  var termList = tag.parent();
  tag.remove();
  activeBaccs.updateFormValue(termList);
};

activeTags.updateFormValue = function (termList) {
  var tags = '';
  termList.find('.at-term-text').each(function (i) {
    // Get tag and revome quotes to prevent doubling
    var tag = $(this).text().replace(/["]/g, '');
    // Wrap in quotes if tag contains a comma.
    if (tag.search(',') != -1) {
      tag = '"' + tag + '"';
    }
    // Collect tags as a comma seperated list.
    tags = (i == 0) ? tag : tags + ', ' + tag;
  });
  // Set comma seperated tags as value of form field.
  termList.parent().find('input.at-terms').val(tags);
};

activeBaccs.updateFormValue = function (termList) {
  var tags = '';
  termList.find('.at-term-text-bacc').each(function (i) {
    // Get tag and revome quotes to prevent doubling
    var tag = $(this).text().replace(/["]/g, '');
    // Wrap in quotes if tag contains a comma.
    if (tag.search(',') != -1) {
      tag = '"' + tag + '"';
    }
    // Collect tags as a comma seperated list.
    tags = (i == 0) ? tag : tags + ', ' + tag;
  });
  // Set comma seperated tags as value of form field.
  termList.parent().find('input.at-terms-bacc').val(tags);
  if (tags) { termList.parent().find('.at-baccmy').addClass('hideA'); }
  else { termList.parent().find('.at-baccmy').removeClass('hideA'); }
};

/**
 * Theme a selected term.
 */
Drupal.theme.prototype.activeTagsTermRemove = function (term) {
  return '<div class="at-term at-term-remove"><span class="at-term-text">' + term + '</span><span class="at-term-action-remove">x</span></div> ';
};

Drupal.theme.prototype.activeBaccsTermRemove = function (term) {
  return '<div class="at-term-bacc at-term-remove-bacc"><span class="at-term-text-bacc">' + term + '</span><span class="at-term-action-remove-bacc">x</span></div> ';
};

Drupal.behaviors.activeTagsOnEnter = {
  attach: function (context, settings) {
    if ($.browser.mozilla) {
      $('.at-term-entry:not(.activeTagsOnEnter-processed)')
        .addClass('activeTagsOnEnter-processed')
        .keypress(activeTags.checkEnter);
    }
    else {
      $('.at-term-entry:not(.activeTagsOnEnter-processed)')
        .addClass('activeTagsOnEnter-processed')
        .keydown(activeTags.checkEnter);
    }
  }
};

Drupal.behaviors.activeBaccsOnEnter = {
  attach: function (context, settings) {
    if ($.browser.mozilla) {
      $('.at-term-entry-bacc:not(.activeTagsOnEnter-processed-bacc)')
        .addClass('activeTagsOnEnter-processed-bacc')
        .keypress(activeBaccs.checkEnter);
    }
    else {
      $('.at-term-entry-bacc:not(.activeTagsOnEnter-processed-bacc)')
        .addClass('activeTagsOnEnter-processed-bacc')
        .keydown(activeBaccs.checkEnter);
    }
  }
};

Drupal.behaviors.activeTagsRemove = {
  attach: function (context, settings) {
    $('div.at-term-remove:not(.activeTagsRemove-processed)', context)
      .addClass('activeTagsRemove-processed')
      .each(function () {
        $(this).click(function () {
          activeTags.removeTerm(this);
        })
      });
  }
};

Drupal.behaviors.activeBaccsRemove = {
  attach: function (context, settings) {
    $('div.at-term-remove-bacc:not(.activeTagsRemove-processed-bacc)', context)
      .addClass('activeTagsRemove-processed-bacc')
      .each(function () {
        $(this).click(function () {
          activeBaccs.removeTerm(this);
        })
      });
  }
};

Drupal.behaviors.activeTagsAdd = {
  attach: function (context, settings) {
    $('input.at-add-btn:not(.activeTagsAdd-processed)', context)
      .addClass('activeTagsAdd-processed')
      .each(function () {
        $(this).click(function (e) {
          var tag = $(this).parent().find('.at-term-entry').val().replace(/["]/g, '');
          if (Drupal.settings.activeTags.mode === 'csv') {
            activeTags.addTerms(this, tag);
          }
          else {
            // Default to single tag entry mode.
            activeTags.addTerm(this, tag);
          }
          return false;
        });
      });
  }
};

Drupal.behaviors.activeBaccsAdd = {
  attach: function (context, settings) {
    $('input.at-add-btn-bacc:not(.activeTagsAdd-processed-bacc)', context)
      .addClass('activeTagsAdd-processed-bacc')
      .each(function () {
        $(this).click(function (e) {
          var tag = $(this).parent().find('.at-term-entry-bacc').val().replace(/["]/g, '');
          if (Drupal.settings.activeBaccs.mode === 'csv') {
            activeBaccs.addTerms(this, tag);
          }
          else {
            // Default to single tag entry mode.
            activeBaccs.addTerm(this, tag);
          }
          return false;
        });
      });
  }
};


$(window).load(function () {
  // Setup tags to be added on form submit.
  $('#node-form').submit(activeTags.addTagOnSubmit);
  $('#node-form').submit(activeBaccs.addTagOnSubmit);
});

})(jQuery);
