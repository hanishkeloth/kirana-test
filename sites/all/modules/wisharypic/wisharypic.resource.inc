<?php
function _wisharypic_user_resource_update($uid, $data)
{
   $account = _services_arg_value($account, 'data');
  if(isset($data['picture']) && is_numeric($data['picture']))
  {
    $file = file_load($data['picture']);
    if($file)
    {
      $account = user_load($uid);
      $edit['picture'] = $file;
      user_save($account, $edit);
    }
  }

  // Pass the data to the original callback for this resource, so that the
  // rest of the data can be processed as necessary.
  module_load_include('inc', 'services', 'resources/user_resource');
  _user_resource_update($uid, $data);
     if ($errors = form_get_errors()) {
    return services_error(implode(" ", $errors), 406, array('form_errors' => $errors));
  }
  else {
    $account = (object) $account;
    services_remove_user_data($account);
    $account = (array) $account;
    _user_resource_update_services_user($uid, time());
     $account_loaded = user_load($uid);
    return $account_loaded;
  }
}