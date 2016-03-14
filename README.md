# Automated Logout

This module provides a site administrator with the ability to set
the system to log users out after a specified time of inactivity.
It is highly customisable and includes "site policies" per role to
set different timeouts for each role. It is also possible to allow
users to set their own personal values.

After a given timeout has passed, users are given a
configurable session-expired prompt. They can reset the timeout,
logout, or ignore it in which case they'll be logged out after
the padding time has elapsed. This is all backed up by a
server side logout if js is disable or bypassed.


This is a port from the Drupal module of the same name, v7.x-4.4,
with some additions to provide the per role and per user
optional settings.


## Status

This initial release for Backdrop (1.x-4.4.0) can be installed and
will automatically log-out a user after the prescribed interval.
However, it has not yet been fully tested and it is not passing
all its inbuilt tests. please report any issues you may find.


## Features

  + Different timeouts based on role
  + Disabling of timeouts based on role
  + Permission for users to set their own timeout
  + Includes some JS mechanisms to keep uses logged in even if
    multiple tabs are open or if the user is working on a form
    for a long period of time.
  + Includes developer hooks to allow users to remain logged in
    depending on your own project specific requirements
  + Optional integration with Javascript Timer


## Installation

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Use the configuration page at /admin/config/people/autologout
  [ Configuration > User Accounts > Auto Logout ]
  to set various values.


## Help & Documentation</h2>

See readme.txt for more information about installation and use.

Checkout this blog post from Lullabot "Module Monday: Auto Logout"
http://www.lullabot.com/blog/article/module-monday-auto-logout


## License

This project is GPL v2 software. See the LICENSE.txt file in this directory for complete text.
    
        
## Current Maintainer for Backdrop

Graham Oliver (github.com/Graham-72/)

## Credits

### Maintainers for Drupal:

- Ajit Shinde (AjitS)
- John Ennew (ceng)
- Sumit Madan (sumitmadan)
- str8
- Prabin Giri (prabeen.giri)

### Supporting organizations:
- Deeson
- QED42 (Drupal 8 release)


### Acknowledgement

This port to Backdrop would not, of course, be possible without all
the work done by the developers and maintainers of the Drupal module.

