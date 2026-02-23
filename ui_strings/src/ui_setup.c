/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: UI Setup
File: ui_setup.c
About: Structured UI interaction utilities for OE_REBOOT.
Revisions:
- 2026-02-21  Initial implementation
- 2026-02-21  Removed stdlib & stdio usage
- 2026-02-21  Replaced atoi & snprintf with PAL versions
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_elements.h"
#include "ui_setup.h"

/* ================= SCREEN INIT ================= */

void ui_init(void)
{
    pal_clear_screen();
    layout();
}

/* ================= TITLE ================= */

void ui_title(int row, int col, const char* style, const char* text)
{
    pal_set_cursor(row, col);
    pal_print(style);
    pal_print(text);
    pal_print(reset);
}

/* ================= INTEGER PRINT ================= */

void ui_print_int(int value)
{
    char buffer[16];
    pal_itoa(value, buffer);
    pal_print(buffer);
}

void ui_title_int(int row, int col, const char* style, int value)
{
    char buffer[16];
    pal_itoa(value, buffer);
    ui_title(row, col, style, buffer);
}

/* ================= STATUS ================= */

static void print_status(const char* style, const char* message)
{
    ui_title(22, 75, style, message);
    pal_sleep(1);
    ///* Clear status line */
    //ui_title(22, 5, "", "                                                    ");
}

void ui_status(ui_status_code code)
{
    switch (code)
    {
    case STATUS_SUCCESS:
        print_status(blue bold,
            "Successfully completed the command.");
        break;

    case STATUS_ERROR:
        print_status(red bold,
            "No suitable record found.");
        break;

    case STATUS_WARNING:
        print_status(yellow bold,
            "Warning! Operation may alter system state.");
        break;

    case STATUS_INFO:
        print_status(cyan bold,
            "Information: Operation executed.");
        break;

    case STATUS_INVALID:
        print_status(red bold,
            "Invalid input detected /No such command.");
        break;

    case STATUS_NOT_INSTALLED:
        print_status(RED bold,
            "Application not installed.");
        break;

    default:////caution
        print_status(yellow bold,
            "Unknown system status.!!!!!!!!!!!!!!");
        break;
    }
}

/* ================= MENU ================= */

int ui_menu(
    int start_row,
    int col,
    const char* title,
    const char* options[],
    int count
)
{
    char input[10];

    ui_init();

    ui_title(start_row - 2, col, bold, title);

    for (int i = 0; i < count; i++)
    {
        ui_title(start_row + i, col, "", options[i]);
    }

    ui_title(start_row + count + 1, col, "", "Enter choice: ");
    pal_readline(input, sizeof(input));

    return pal_atoi(input);
}

/* ================= CONFIRM ================= */

int ui_confirm(int row, int col, const char* message)
{
    char input[10];

    ui_title(row, col, yellow bold, message);
    pal_print(" (y/n): ");

    pal_readline(input, sizeof(input));

    return (input[0] == 'y' || input[0] == 'Y');
}