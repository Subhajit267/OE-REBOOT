/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Installer
File: app_table.c
About: Defines all OE installable applications.
------------------------------------------------------------
*/

#include "app_table.h"

/* -------- Application Registry -------- */

app_t apps[] = {

    /* Core Apps */
    {"calculator",       "calculator.rg"},
    {"quiz",             "quiz.rg"},
    {"temp_conv",        "temp_conv.rg"},

    /* Math Utilities */
    {"eqn_solve",        "eqn_solve.rg"},
    {"quad_eqn_solve",   "quad_eqn_solve.rg"},

    /* Games */
    {"tictactoe",        "tictactoe.rg"},

    /* Additional Tools */
    {"atc",              "atc.rg"}
};

/* -------- App Count -------- */

int app_count = sizeof(apps) / sizeof(apps[0]);