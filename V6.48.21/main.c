/*
------------------------------------------------------------
Author: Subhajit Halder
Module: ROOT
File: main.c
About: Entry point for OE_REBOOT. Initializes PAL, displays bootscreen,
       checks for existing user, and launches installer (first run)
       or login (subsequent runs).
Revisions:
- 2026-02-20  Initial implementation
- 2026-02-23  Updated to use new bootscreen and installer flow
------------------------------------------------------------
*/
#include "pal.h"
#include "bootscreen.h"
#include "user.h"
#include "installer.h"
#include "prompt.h"
#include "regedit.h"
#include "settings.h"
int main()
{
	//settings_run();   /* Settings panel – user account management and personalization */
	//reg_edit();   /* Registry Editor – main system tool and command shell */
    pal_init();
	pal_sleep(1);   /* brief pause before bootscreen */
    bootscreen_show(0);   /* generic OE bootscreen */

    if (user_exists())
        login();
    else
        installer_prompt();   /* first-time setup */

    return 0;
}