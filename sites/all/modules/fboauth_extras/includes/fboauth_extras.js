(function ($) {
  Drupal.behaviors.fboauthFriends = {
    attach: function (context, settings) {
      
      /**
       * Handle invite link functionality.
       */ 
      $('a.fboauth-friends-invite:not(.disabled)', context).click(function () {
        // Pull JSON data from this link's rel attribute.
        var rel = jQuery.parseJSON($(this).attr('rel'));

        // assume we are already logged in
        FB.init({
          appId: Drupal.settings.fboauth_extras.appId, 
          xfbml: true, 
          cookie: true, 
          oauth: true});
          
        FB.ui({
          method: 'send',
          name: rel.name,
          description: rel.description,
          picture: rel.picture,
          to: rel.to,
          link: rel.link,
          // It seems like link MUST be the only the base domain name registered to the app. example.com will work,
          // but example.com/user/register will not. WTF?
          display: 'popup',
          redirect_uri: rel.redirectUri,
          },
          function(response) {
            alert('response' + response);
          });        
          
          /*
          $(this).text('Invited');
          $(this).addClass('disabled');
          $(this).attr("disabled", "disabled");
          $(this).unbind('click');
          */
       });
       
       /**
        * Handle popup login functionlity.
        *
        * The function assigned to window.fbAsyncInit is run as soon as the SDK is loaded. 
        * Any code that you want to run after the SDK is loaded should be placed within 
        * this function and after the call to FB.init.
        */
        /*
        window.fbAsyncInit = function() {
          FB.init({
            appId      : Drupal.settings.fboauth_extras.appId, // App ID
            channelUrl : Drupal.settings.fboauth_extras.channelUrl, // Channel File
            status     : true, // check login status
            cookie     : true, // enable cookies to allow the server to access the session
            xfbml      : true, // parse XFBML
            oauth      : true, 
          });

          // If the user is logging into facebook via this app request, redirect to fboauth connect page with access_token.
          FB.Event.subscribe('auth.login', function(response) {
            //alert('auth.login fired');
            window.location = Drupal.settings.fboauth_extras.redirect_uri + '?access_token=' + response.authResponse.accessToken;
          });
          
          // If the user is already logged into facebook when this app request is make, redirect to fboauth connect page with access_token.
          FB.getLoginStatus(function(response) {
            //alert('getting login status');
            //alert(response.authResponse.accessToken);
            //window.location = Drupal.settings.fboauth_extras.redirect_uri + '?access_token=' + response.authResponse.accessToken;
          });
          
          $("a[href^='" + Drupal.settings.basePath + "user/logout']", context).click(FB.logout());
        };
        */
        /*
        // Load the SDK Asynchronously
        (function(d){
         var js, id = 'facebook-jssdk', ref = d.getElementsByTagName('script')[0];
         if (d.getElementById(id)) {return;}
         js = d.createElement('script'); js.id = id; js.async = true;
         js.src = "//connect.facebook.net/en_US/all.js";
         ref.parentNode.insertBefore(js, ref);
        }(document));
        */
    }
  };

})(jQuery);