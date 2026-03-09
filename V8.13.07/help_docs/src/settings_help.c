/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Help Documentation
File: settings_help.c
About: Displays help information for settings module
Revisions:
- 2026-02-21  Converted legacy settings help to PAL-based layout
------------------------------------------------------------
*/

#include "pal.h"
#include "help.h"

void help_show_settings(void)
{
	int row = 24, column = 75;
    pal_set_cursor(row++, column);
    pal_print(green bold "Welcome to Help Documentation Ver: 1.0" reset yellow bold);
    pal_set_cursor(row++, column);
    pal_print("1.) Press 1 to change/delete/apply new password or change USER_ID.");
    pal_set_cursor(row++, column);
    pal_print("2.) Press 2 to reset or restore your account.");
    pal_set_cursor(row++, column);
    pal_print("3.) Press 3 to personalize account by changing colors.");
    pal_set_cursor(row++, column);
    pal_print("4.) Press 5 to exit settings.");

    pal_pause();
}