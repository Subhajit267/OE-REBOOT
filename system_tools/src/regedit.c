/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: System Tools
File: regedit.c
About: Registry Editor – Structured UI (Menu Based)
Revisions:
- 2026-02-21  Converted to ui_menu based system
- 2026-02-21  Removed command shell style
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "app_installer.h"
#include "user.h"
#include "help.h"
#include "regedit.h"
#include "utils.h"

int reg_admin_mode = 0;

/* ================= COMMANDS ================= */

static void cmd_install(void)
{
    install_all();
    ui_status(STATUS_SUCCESS);
}

static void cmd_temp(void)
{
    char input[50];

    ui_title(18, 5, "", "Enter App (TTT / quiz): ");
    util_get_string(input, 50, "");

    if (pal_strcmp(input, "TTT") == 0 ||
        pal_strcmp(input, "ttt") == 0)
    {
        if (reg_admin_mode)
            ui_title(20, 5, green bold,
                "Launching TicTacToe (temp mode)...");
        else
            ui_status(STATUS_INVALID);

        pal_pause();
    }
    else if (pal_strcmp(input, "quiz") == 0)
    {
        if (reg_admin_mode)
            ui_title(20, 5, green bold,
                "Launching Quiz (temp mode)...");
        else
            ui_title(20, 5, yellow bold,
                "Launching Quiz in trial mode...");

        pal_pause();
    }
    else
    {
        ui_status(STATUS_INVALID);
    }
}

static void cmd_reset(void)
{
    if (ui_confirm(18, 5,
        "Warning! This will reset all applications. Continue?"))
    {
        uninstall_all();
        ui_status(STATUS_SUCCESS);
    }
}

static void cmd_prompt(void)
{
    ui_title(20, 5, cyan bold, "Returning to prompt...");
    pal_pause();
}

static void cmd_add_key(void)
{
    if (!reg_admin_mode)
    {
        ui_status(STATUS_INVALID);
        return;
    }

    const char* options[] = {
        "1.) Install Both (TTT + Quiz)",
        "2.) Install Quiz",
        "3.) Install TicTacToe",
        "4.) Back"
    };

    int choice = ui_menu(10, 5,
        "Add Key Options:",
        options, 4);

    switch (choice)
    {
    case 1:
        install_app(find_app("tictactoe"));
        install_app(find_app("quiz"));
        ui_status(STATUS_SUCCESS);
        break;

    case 2:
        install_app(find_app("quiz"));
        ui_status(STATUS_SUCCESS);
        break;

    case 3:
        install_app(find_app("tictactoe"));
        ui_status(STATUS_SUCCESS);
        break;

    default:
        return;
    }

    pal_pause();
}

static void cmd_user(void)
{
    if (!reg_admin_mode)
    {
        ui_status(STATUS_INVALID);
        return;
    }

    if (ui_confirm(18, 5,
        "Warning! This will reset user account. Continue?"))
    {
        add_user();
    }
}

static void cmd_help(void)
{
    help_show_regedit();
}

static void cmd_start_admin(void)
{
    reg_admin_mode = 1;
    ui_status(STATUS_SUCCESS);
}

/* ================= MAIN LOOP ================= */

void reg_edit(void)
{
    int choice;

    const char* options[] = {
        "1.) Install All Applications",
        "2.) Temp Mode",
        "3.) Reset Applications",
        "4.) Return to Prompt",
        "5.) Add Key",
        "6.) User Management",
        "7.) Help",
        "8.) Activate Admin Mode",
        "9.) Exit"
    };

    do
    {
        choice = ui_menu(10, 5,
            "Registry Editor 3.5.0 (Power Users)",
            options, 9);

        switch (choice)
        {
        case 1: cmd_install(); break;
        case 2: cmd_temp(); break;
        case 3: cmd_reset(); break;
        case 4: cmd_prompt(); return;
        case 5: cmd_add_key(); break;
        case 6: cmd_user(); break;
        case 7: cmd_help(); break;
        case 8: cmd_start_admin(); break;
        case 9: return;
        default: ui_status(STATUS_INVALID);
        }

        pal_pause();

    } while (choice != 9);
}