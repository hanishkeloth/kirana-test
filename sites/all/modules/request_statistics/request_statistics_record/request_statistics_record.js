/**
 * @file
 * Request statistics record data for visitor and page.
 *
 * The following value might exist.
 * var request_statistics_record_visitor_id = ''.
 */

(function ($, Drupal, window, document, undefined) {
  var date_time = new Date();
  var record_url = 'request_statistics_record';
  var request_id = '';
  // Wait 200 milliseconds, 0.2 second, before recording.
  var resize_wait = 200;
  var previous_inner_width = 0;
  function id_create()
    {
    var mi = '' + date_time.getMinutes();
    if (mi.length == 1) {
      mi = '0' + mi;
    }
    var s = '' + date_time.getSeconds();
    if (s.length == 1) {
      s = '0' + s;
    }
    var ms = '' + date_time.getMilliseconds();
    if (ms.length == 1) {
      ms = '00' + ms;
    }
    if (ms.length == 2) {
      ms = '0' + ms;
    }
    var r = Math.random().toString() + '00000000000000000';
    r = r.substring(1, 18);
    return mi + s + '.' + ms + r;
    }
  function record()
    {
    var post = {};
    if (request_id == '') {
      post.query = 'insert';
      request_id = id_create();
    }
    else {
      post.query = 'update';
    }
    post.request_id = request_id;
    if (typeof window.innerWidth != 'undefined') {
      post.inner_width = window.innerWidth;
    }
    else {
      post.inner_width = window.clientWidth;
    }
    if (post.query == 'update') {
      if (post.inner_width == previous_inner_width) {
        // No update because nothing changed.
        return;
      }
    }
    previous_inner_width = post.inner_width;
    post.year = date_time.getFullYear();
    // Month is 0-11.
    var month = date_time.getMonth();
    month = month + 1;
    post.month = '' + month;
    if (post.month.length == 1) {
      post.month = '0' + post.month;
    }
    post.day = '' + date_time.getMonth();
    if (post.day.length == 1) {
      post.day = '0' + post.day;
    }
    post.hour = '' + date_time.getHours();
    if (post.hour.length == 1) {
      post.hour = '0' + post.hour;
    }
    post.referrer_uri = document.referrer;
    post.request_uri = window.location.href;
    if (typeof request_statistics_record_visitor_id !== 'undefined') {
      post.visitor_id = request_statistics_record_visitor_id;
    }
    post.user_agent = navigator.userAgent;
    if (typeof window.innerHeight !== 'undefined') {
      post.inner_height = window.innerHeight;
    }
    else {
      post.inner_height = window.clientHeight;
    }
    if (typeof window.outerHeight !== 'undefined') {
      post.outer_height = window.outerHeight;
    }
    if (typeof window.outerWidth !== 'undefined') {
      post.outer_width = window.outerWidth;
    }
    if (typeof window.screen.availHeight !== 'undefined') {
      post.screen_height = window.screen.availHeight;
    }
    else if (typeof window.screen.height !== 'undefined') {
      post.screen_height = window.screen.height;
    }
    if (typeof window.screen.availWidth !== 'undefined') {
      post.screen_width = window.screen.availWidth;
    }
    else if (typeof window.window.screen.width !== 'undefined') {
      post.screen_width = window.window.screen.width;
    }
    $.post(Drupal.settings.basePath + record_url, post);
    return false;
    // Return false so the navigation stops here and not continue to the page in the link.
    }
  // Wait for slick.
  $(document).ready(function() {
    record();
  });
  // Update the size when the display is resized.
  var wait;
  $(window).resize(function() {
    clearTimeout(wait);
    wait = setTimeout(record, resize_wait);
  });
 })(jQuery, Drupal, this, this.document);
