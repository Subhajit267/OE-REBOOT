/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Help Documentation
File: regedit_help.c
About: Displays help information for registry editor
Revisions:
- 2026-02-21  Converted legacy registry help to PAL-based system
------------------------------------------------------------
*/

#include "pal.h"
#include "help.h"

void help_show_regedit(void)
{
    //ui_title(33, 69, yellow bold, "start_admin_reg_edit -> Activate admin mode");
	int row = 24, column = 67;
    pal_set_cursor(row++, column);
    pal_print(green bold "Welcome to HELP Documentation Ver: 1.0 :" yellow bold);
    pal_set_cursor(row++, column);
    pal_print("  install  -> Install all applications");
    pal_set_cursor(row++, column);
    pal_print("  temp     -> Temporary app access (TTT/quiz)");
    pal_set_cursor(row++, column);
    pal_print("  exit     -> Return to login");
    pal_set_cursor(row++, column);
    pal_print("  reset    -> Reset all apps");
    pal_set_cursor(row++, column);
    pal_print("  prompt   -> Go to main shell");
    pal_set_cursor(row++, column);
    pal_print("  help     -> Show this help");
    pal_set_cursor(row++, column);
    pal_print("  clear    -> Clear output screen.");
    pal_set_cursor(row++, column);
    pal_print("  user     -> Edit existing /add new user");
}