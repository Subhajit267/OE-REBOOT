/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: UI
File: bootscreen.c
About: Classic OE bootscreen (identical look).
Revisions:
- 2026-02-21  Rewritten using ui_setup + PAL
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "bootscreen.h"

void bootscreen_show(int app_id)
{
    ui_init();
    layout();

    pal_print(green bold);

    if (app_id == 1)
    {
        ui_title(8, 20, underline, "\t\t\t\t\t      TIC TAC TOE");
        ui_title(9, 20, yellow bold, "\t\t\t\t\t      Version:4.0");
    }
    else if (app_id == 2)
    {
        ui_title(8, 20, underline, "\t\t\t\t\t      QUIZ__APP");
        ui_title(9, 20, yellow bold, "\t\t\t\t\t      Version:10.8");
    }
    else if (app_id == 3)
    {
        ui_title(8, 20, underline, "\t\t\t\t\t      TEMP_CONV");
        ui_title(9, 20, yellow bold, "\t\t\t\t\t      Version:4.05");
    }
    else if (app_id == 4)
    {
        ui_title(8, 20, underline, "\t\t\t\t\t      CALCULATOR");
        ui_title(9, 20, yellow bold, "\t\t\t\t\t      Version:3.05");
    }
    else
    {
        logo();
    }

    ui_title(32, 68, cyan bold, "\t\t\t\t Please_Wait.");
    ui_title(33, 68, yellow bold, "\t\t\t\t LOADING......");

    progressbar(36, 80, 50);

    pal_print(reset);
}