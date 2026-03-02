/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Help Documentation
File: prompt_help.c
About: Displays help information for main prompt
Revisions:
- 2026-02-21  Converted legacy gotoxy help to PAL-based layout

ALL CHECKED AND WORKING
------------------------------------------------------------
*/

#include "pal.h"
#include "help.h"

void help_show_prompt(void)
{
	int row = 21 , column = 75;

    pal_set_cursor(row++, column);
    pal_print(yellow bold "Type:" reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tTicTacToe" reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tCalculator" reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tQuiz" reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tTemp_Conv" reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\teqn_solve" reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tquad_eqn_solve, to open the applications(if installed)." reset);

    pal_set_cursor(row++, column);
    pal_print(yellow bold "Type:" reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\texit: To exit." reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tver: To see version number" reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tinst_all: Install all apps except TicTacToe and Quiz." reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tsettings: Change your existing settings." reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tType 'registryeditor' to enter the mode." reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tTo re-login type login." reset);

    pal_set_cursor(row++, column);
    pal_print(red bold "\tTo install app type inst_<appname>" reset);

    pal_set_cursor(row++, column);
    pal_print(blue bold "\tTo uninstall app type unst_<appname>" reset);

    pal_pause();
}