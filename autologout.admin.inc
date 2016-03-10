<?php

/**
 * @file
 * Contains all admin pages, settings, and validate.
 */

/**
 * Settings form for menu callback
 */
function autologout_settings() {
  // set config for each role.
	autologout_set_role_timeout();

  $form = array();
  $timeout = config_get('autologout.settings','autologout_timeout');

  if (module_exists('jstimer')) {
    if (!module_exists('jst_timer')) {
      backdrop_set_message(t('The "Widget: timer" module must also be enabled for the dynamic countdown to work in the automated logout block.'), 'error');
    }

    if (config_get('autologout.settings','jstimer_js_load_option') != 1) {
      backdrop_set_message(t("The Javascript timer module's 'Javascript load options' setting should be set to 'Every page' for the dynamic countdown to work in the automated logout block."), 'error');
    }
  }

  $form['autologout_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout value in seconds'),
    '#default_value' => $timeout,
    '#size' => 8,
    '#weight' => -10,
    '#description' => t('The length of inactivity time, in seconds, before automated log out.  Must be 60 seconds or greater. Will not be used if role timeout is activated.'),
  );

  $form['autologout_max_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Max timeout setting'),
    '#default_value' => config_get('autologout.settings','autologout_max_timeout'),
    '#size' => 10,
    '#maxlength' => 12,
    '#weight' => -8,
    '#description' => t('The maximum logout threshold time that can be set by users who have the permission to set user level timeouts.'),
  );

  $form['autologout_padding'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout padding'),
    '#default_value' => config_get('autologout.settings','autologout_padding'),
    '#size' => 8,
    '#weight' => -6,
    '#description' => t('How many seconds to give a user to respond to the logout dialog before ending their session.'),
  );

  $form['autologout_role_logout'] = array(
    '#type' => 'checkbox',
    '#title' => t('Role Timeout'),
    '#default_value' => config_get('autologout.settings','autologout_role_logout'),
    '#weight' => -4,
    '#description' => t('Enable each role to have its own timeout threshold, a refresh maybe required for changes to take effect. Any role not ticked will use the default timeout value. Any role can have a value of 0 which means that they will never be logged out.'),
  );

  $form['autologout_redirect_url']  = array(
    '#type' => 'textfield',
    '#title' => t('Redirect URL at logout'),
    '#default_value' => config_get('autologout.settings','autologout_redirect_url'),
    '#size' => 40,
    '#description' => t('Send users to this internal page when they are logged out.'),
  );

  $form['autologout_no_dialog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not display the logout dialog'),
    '#default_value' => config_get('autologout.settings','autologout_no_dialog'),
    '#description' => t('Enable this if you want users to logout right away and skip displaying the logout dialog.'),
  );

  $form['autologout_use_alt_logout_method'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use alternate logout method'),
    '#default_value' => config_get('autologout.settings','autologout_use_alt_logout_method'),
    '#description' => t('Normally when auto logout is triggered, it is done via an AJAX service call. Sites that use an SSO provider, such as CAS, are likely to see this request fail with the error "Origin is not allowed by Access-Control-Allow-Origin". The alternate appraoch is to have the auto logout trigger a page redirect to initiate the logout process instead.'),
  ); 

  $form['autologout_message']  = array(
    '#type' => 'textarea',
    '#title' => t('Message to display in the logout dialog'),
    '#default_value' => config_get('autologout.settings','autologout_message'),
    '#size' => 40,
    '#description' => t('This message must be plain text as it might appear in a JavaScript confirm dialog.'),
  );

  $form['autologout_inactivity_message']  = array(
    '#type' => 'textarea',
    '#title' => t('Message to display to the user after they are logged out.'),
    '#default_value' => config_get('autologout.settings','autologout_inactivity_message'),
    '#size' => 40,
    '#description' => t('This message is displayed after the user was logged out due to inactivity. You can leave this blank to show no message to the user.'),
  );

  $form['autologout_use_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable watchdog Automated Logout logging'),
    '#default_value' => config_get('autologout.settings','autologout_use_watchdog'),
    '#description' => t('Enable logging of automatically logged out users'),
  );

  $form['autologout_enforce_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enforce auto logout on admin pages'),
    '#default_value' => config_get('autologout.settings','autologout_enforce_admin'),
    '#description' => t('If checked, then users will be automatically logged out when administering the site.'),
  );

  if (module_exists('jstimer') && module_exists('jst_timer')) {
    $form['autologout_jstimer_format']  = array(
      '#type' => 'textfield',
      '#title' => t('Autologout block time format'),
      '#default_value' => config_get('autologout.settings','autologout_jstimer_format'),
      '#description' => t('Change the display of the dynamic timer.  Available replacement values are: %day%, %month%, %year%, %dow%, %moy%, %years%, %ydays%, %days%, %hours%, %mins%, and %secs%.'),
    );
  }

  $form['table'] = array(
    '#type' => 'item',
    '#weight' => -2,
    '#title' => t('If Enabled every user in role will be logged out based on that roles timeout, unless the user has an individual timeout set.'),
    '#theme' => 'autologout_render_table',
  );

  foreach (user_roles(TRUE) as $key => $role) {

    $form['table']['autologout_roles']['autologout_role_' . $key . '_timeout'] = array(
      '#type' => 'textfield',
      '#default_value' => config_get('autologout.settings','autologout_role.' . $key . '.timeout'),
      '#size' => 8,
      '#theme' => 'textfield',
    );

  }

  foreach (user_roles(TRUE) as $key => $role) {
    $form['table']['autologout_roles']['autologout_role_' . $key] = array(
      '#type' => 'checkbox',
      '#default_value' => config_get('autologout.settings','autologout_role.' . $key . '.active'),
      '#theme' => 'checkbox',
    );
  }

  // Add a submit button
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Settings validation.
 */
function autologout_settings_validate($form, &$form_state) {
  $max_timeout = $form_state['values']['autologout_max_timeout'];

  // Validate timeouts for each role.
  foreach (user_roles(TRUE) as $key => $role) {
    if (empty($form_state['values']['autologout_role_' . $key])) {
      // Don't validate role timeouts for non enabled roles.
      continue;
    }

    $timeout = $form_state['values']['autologout_role_' . $key . '_timeout'];
    $validate = autologout_timeout_validate($timeout, $max_timeout);

    if (!$validate) {
      form_set_error('autologout_role_' . $key . '_timeout', t('%role role timeout must be an integer greater than 60, less then %max or 0 to disable autologout for that role.', array('%role' => $role, '%max' => $max_timeout)));
    }
  }

  $timeout = $form_state['values']['autologout_timeout'];

  // Validate timeout.
  if (!is_numeric($timeout) || ((int) $timeout != $timeout) || $timeout < 60 || $timeout > $max_timeout) {
    form_set_error('autologout_timeout', t('The timeout must be an integer greater than 60 and less then %max.', array('%max' => $max_timeout)));
  }
}


/**
 * Submit handler for module_settings_form().
 */
function autologout_settings_submit($form, &$form_state){
  $config = config('autologout.settings');
  $config->set('autologout_timeout', $form_state['values']['autologout_timeout']);
  $config->set('autologout_max_timeout', $form_state['values']['autologout_max_timeout']);
  $config->set('autologout_padding', $form_state['values']['autologout_padding']);
  $config->set('autologout_role_logout', $form_state['values']['autologout_role_logout']);
  $config->set('autologout_redirect_url', $form_state['values']['autologout_redirect_url']);
  $config->set('autologout_no_dialog', $form_state['values']['autologout_no_dialog']);
  $config->set('autologout_use_alt_logout_method', $form_state['values']['autologout_use_alt_logout_method']);
  $config->set('autologout_message', $form_state['values']['autologout_message']);
  $config->set('autologout_inactivity_message', $form_state['values']['autologout_inactivity_message']);
  $config->set('autologout_use_watchdog', $form_state['values']['autologout_use_watchdog']);
  $config->set('autologout_enforce_admin', $form_state['values']['autologout_enforce_admin']);
  $config->save();

	if (module_exists('jstimer') && module_exists('jst_timer')) {
	  $config_set('autologout.settings','autologout_jstimer_format', $form_state['values']['autologout_jstimer_format']);
	}

	// For each role, update config setting
	$roles = user_roles(TRUE);
  foreach ($roles as $rid => $role) {
	  config_set('autologout.settings','autologout_role.' . $rid . '.active',$form_state['values']["autologout_role_" . $rid]);
	  config_set('autologout.settings','autologout_role.' . $rid . '.timeout', $form_state['values']["autologout_role_" . $rid . "_timeout"]);
  }
}
