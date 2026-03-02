/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Extras & Info
File: improvements.c
About: Displays the list of improvements and bug fixes for the
       current version, similar to the original Improvements().
Revisions:
- 2026-02-21  Initial implementation

ALL CHECKED AND WORKING
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "extras.h"

void extras_show_improvements(void)
{
    ui_init();  /* clear screen and draw layout */
    int row = 14, column = 66;
    ui_title(row++, column, bold red underline, "New Improvements and Bug Fixes:");    
    ui_title(row+=2-1, column, bold blue,   "i.)   Change in programming");
    ui_title(row++, column, bold yellow,    "ii.)  New app Quadratic Eqn solver");
    ui_title(row++, column, bold blue,      "iii.) Quad Eqn solver can determine nature of roots");
    ui_title(row++, column, bold yellow,    "iv.)  Added trial for quiz in registry editor");
    ui_title(row++, column, bold blue,      "v.)   Introduction of a brand new UI");
    ui_title(row++, column, bold red,       "vi.)  Introduction of settings application");
    ui_title(row++, column, bold yellow,    "vii.) Parts of Registry Editor accessible by normal user");
    ui_title(row++, column, bold blue,      "viii.) Now you can change your User-ID");
    ui_title(row++, column, bold yellow,    "ix.)  Password can be removed via settings");
    ui_title(row++, column, bold blue,      "x.)   Option for system restore by reinstallation");
    ui_title(row++, column, bold yellow,    "xi.)  Added support for Kelvin in Temperature Converter");
    ui_title(row++, column, bold blue,      "xii.) One can directly move into prompt from registry editor");
    ui_title(row++, column, bold green,     "Next version coming with more features");

	pal_pause();  /* Wait for key press before returning */

}