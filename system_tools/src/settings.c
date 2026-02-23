/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-22
Module: System Tools
File: settings.c
About: Settings panel.
Revisions:
- 2026-02-21  Converted to ui_menu
- 2026-02-22  Fixed user_accounts to use existing functions
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "app_installer.h"
#include "user.h"
#include "help.h"
#include "settings.h"
#include "file.h"
#include "utils.h"

static void user_accounts(void);
static void reset_restore(void);
static void personalization(void);
static void color_change(void);

static void user_accounts(void)
{
    const char* options[] = { "1.) Change / Remove Password",
                              "2.) Change User-ID",
                              "3.) Back" };
    int choice;
    do
    {
        choice = ui_menu(10, 5, "User Account Control Panel:", options, 3);
        if (choice == 1) password_change();
        else if (choice == 2) userid_change();
    } while (choice != 3);
}

static void reset_restore(void)
{
    if (!ui_confirm(15, 5, "Warning! This will reset all applications. Continue?"))
        return;
    const char* options[] = { "1.) Reset Applications", "2.) Back" };
    int choice = ui_menu(10, 5, "Reset and Restore Panel:", options, 2);
    if (choice == 1) { uninstall_all(); ui_status(STATUS_SUCCESS); pal_pause(); }
}

#define LOOKS_FILE "looks.bd"
#define DEFAULT_COLOR 4
static void color_change(void)
{
    int current = file_read_int_default(LOOKS_FILE, DEFAULT_COLOR);
    const char* options[] = {
        "1.) Red", "2.) Green", "3.) Yellow", "4.) Blue", "5.) Purple",
        "6.) Cyan", "7.) Light Grey", "8.) Grey", "9.) Light Red",
        "10.) Light Green", "11.) Light Yellow", "12.) Light Blue",
        "13.) Light Purple", "14.) Light Cyan", "15.) White", "16.) Back"
    };
    int choice = ui_menu(8, 5, "Border Color Selection:", options, 16);
    if (choice >= 1 && choice <= 15)
    {
        file_write_int(LOOKS_FILE, choice);
        ui_title(20, 5, green bold, "Color changed. Restart OE to see effect.");
        pal_pause();
    }
}

static void personalization(void)
{
    const char* options[] = { "1.) Change Border Color", "2.) Back" };
    int choice = ui_menu(10, 5, "Personalization Panel:", options, 2);
    if (choice == 1) color_change();
}

void settings_run(void)
{
    const char* options[] = { "1.) USER ACCOUNTS",
                              "2.) RESET AND RESTORE",
                              "3.) PERSONALIZATION",
                              "4.) HELP",
                              "5.) EXIT" };
    int choice;
    do
    {
        choice = ui_menu(10, 5, "Welcome to Settings", options, 5);
        switch (choice)
        {
        case 1: user_accounts(); break;
        case 2: reset_restore(); break;
        case 3: personalization(); break;
        case 4: help_show_settings(); break;
        case 5: return;
        default: ui_status(STATUS_INVALID);
        }
    } while (choice != 5);
}