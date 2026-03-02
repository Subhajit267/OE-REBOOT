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

ALL CHECKED AND WORKING
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "bootscreen.h"

void bootscreen_show(int app_id)
{
    ui_init();
    pal_print(green bold);
	int row = 18 , column = 68;
    if (app_id == 1)
    {
        ui_title(row++, column, underline, "\t\t\t\t   TIC TAC TOE  ");
        ui_title(row++, column, yellow bold, "\t\t\t\t   Version:4.0");
    }
    else if (app_id == 2)
    {
        ui_title(row++, column, underline, "\t\t\t\t   QUIZ__APP    ");
        ui_title(row++, column, yellow bold, "\t\t\t\t   Version:10.8");
    }
    else if (app_id == 3)
    {
        ui_title(row++, column, underline, "\t\t\t\t   TEMP_CONV    ");
        ui_title(row++, column, yellow bold, "\t\t\t\t   Version:4.05");
    }
    else if (app_id == 4)
    {
        ui_title(row++, column, underline, "\t\t\t\t   CALCULATOR   ");
        ui_title(row++, column, yellow bold, "\t\t\t\t    Version:3.05");
    }
    else if (app_id == 5)
    {
        ui_title(row++, column, underline, "\t\t\t\t   EQN_SOLVER   ");
        ui_title(row++, column, yellow bold, "\t\t\t\t    Version:3.05");
    }
    else if (app_id == 6)
    {
        ui_title(row++, column, underline, "\t\t\t\t   QUAD_EQN_S   ");
        ui_title(row++, column, yellow bold, "\t\t\t\t    Version:3.05");
    }
    else if (app_id == 7)
    {
        ui_title(row++, column, underline, "\t\t\t\t   Ar(T)CALC    ");
        ui_title(row++, column, yellow bold, "\t\t\t\t    Version:3.05");
    }
    else if (app_id == 0)
        ;
    else
        ui_status(STATUS_ERROR);

    ui_title(32, column, cyan bold, "\t\t\t\t   Please_Wait.");
    ui_title(33, column, yellow bold, "\t\t\t\t   LOADING......");

    progressbar(36, 80, 50);

    pal_print(reset);
}