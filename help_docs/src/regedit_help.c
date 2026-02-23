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
    pal_set_cursor(20, 5);
    pal_print(blue bold "Welcome to HELP Documentation Ver: 1.0 :" reset);

    pal_set_cursor(21, 5);
    pal_print("\ta.) install: Install all programs at once.");

    pal_set_cursor(22, 5);
    pal_print("\tb.) add_key: Install only TicTacToe and Quiz (admin only).");

    pal_set_cursor(23, 5);
    pal_print("\tc.) exit: Exit Registry Editor and open login screen.");

    pal_set_cursor(24, 5);
    pal_print("\td.) temp: Temporary program access.");

    pal_set_cursor(25, 5);
    pal_print("\te.) user: Add new user or password bypass.");

    pal_set_cursor(26, 5);
    pal_print("\tf.) reset: Uninstall all applications.");

    pal_set_cursor(27, 5);
    pal_print("\tg.) clear: Clear output screen.");

    pal_pause();
}