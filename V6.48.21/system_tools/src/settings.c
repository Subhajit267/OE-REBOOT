/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-24
Module: System Tools
File: settings.c
About: Settings panel – efficient menu‑driven code,
       restored original OE UI with personalization menu
       and separate color change wizard (exact original table),
       base row = 15, col = 67.
Revisions:
- 2026-02-21  Initial menu‑based version
- 2026-02-22  Fixed user_accounts to use existing functions
- 2026-02-24  Base row 15, split personalization/color_change,
              reset & restore loops correctly,
              color change table now matches original OE exactly

//ALL CHECKED ALL WORKS                
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
#include "prompt.h"
#include "installer.h"

/* Base coordinates for all settings panels */
#define BASE_ROW 15
#define BASE_COL 67

#define LOOKS_FILE "looks.bd"

/* Forward declarations */
static void user_accounts(void);
static void reset_restore(void);
static void personalization(void);
static void color_change(void);

/* ================= USER ACCOUNTS ================= */
static void user_accounts(void)
{
    const char* options[] = {
        green bold "1.) Add /Remove /Create Password for your accounts",
        green bold "2.) Change Your User_ID.",
        green bold "3.) EXIT."
    };
    int choice;
    do
    {
        choice = ui_menu(BASE_ROW, BASE_COL,
            red bold underline "Welcome to User Account Control Panel:"reset yellow "\n\t\t\t\t\t\t\t\t  Pick a task" reset , options, 3);
        if (choice == 1) password_change();
        else if (choice == 2) userid_change();
        if (choice>3 || choice<1) ui_status(STATUS_INVALID);
    } while (choice != 3);
}

///* ================= RESET & RESTORE ================= */
//static void reset_restore(void)
//{
//    char a[4];
//    int row = BASE_ROW, col = BASE_COL;
//
//    while (1)
//    {
//        ui_init();
//
//        ui_title(row, col, red bold underline, "Welcome to Reset and Restore Panel:");
//        ui_title(row + 1, col + 2, yellow bold, "Pick a task: ");
//        ui_title(row + 2, col + 4, blue bold, "1.) Reset your applications");
//        ui_title(row + 3, col + 4, blue bold, "2.) Restore your system by re-installing it.");
//        ui_title(row + 4, col + 4, blue bold, "3.) EXIT.");
//        ui_title(row + 5, col + 2, red bold,
//            "Warning!! Any of the above task(command) will reset all your applications thus delete /alter data. ");
//        //ui_title(row + 6, col + 2, green bold, "Do you want to continue(y/n)?");
//        //ui_confirm(row+6, col+2, "Do you want to continue");
//        //pal_set_cursor(row + 6, col + 32);
//        //pal_readline(a, sizeof(a));
//
//        if (ui_confirm(row + 6, col + 2, "Do you want to continue");)
//        {
//            ui_title(row + 7, col + 4, green bold, "Enter choice(1-3): ");
//            pal_set_cursor(row + 7, col + 26);
//            pal_readline(a, sizeof(a));
//
//            if (pal_strcmp(a, "1") == 0)
//            {
//                uninstall_all(1);
//                /* loop continues – back to reset panel */
//            }
//            else if (pal_strcmp(a, "2") == 0)
//            {
//                installer_prompt();   /* full installer – may not return */
//                /* if it returns, continue loop */
//            }
//            else if (pal_strcmp(a, "3") == 0)
//                return;   /* exit to main settings */
//            else
//                ui_status(STATUS_ERROR);
//        }
//        else
//            return;//ui_status(STATUS_ERROR);
//            //continue;   /* user chose not to continue */
//    }
//}
/* ================= RESET & RESTORE ================= */
static void reset_restore(void)
{
    int row = BASE_ROW, col = BASE_COL;
    const char* options[] = {
        green bold "1.) Reset your applications",
        green bold "2.) Restore your system by re-installing it.",
        green bold "3.) EXIT."
    };
    int choice;
    do
    {
        choice = ui_menu(BASE_ROW, BASE_COL,
            red bold underline "Welcome to Reset and Restore Panel:"reset yellow "\n\t\t\t\t\t\t\t\t  Pick a task" reset, options, 3);
        if (choice == 1 || choice == 2)
        {
            ui_title(row + 5, col + 2, red bold, "Warning!! Any of the above task(command) will reset all your applications thus delete /alter data. ");
            if (!ui_confirm(row + 6, col + 2, "Do you want to continue"))
                return;
        }
        if (choice == 1) uninstall_all(1);
        else if (choice == 2) installer_prompt();
        if (choice > 3 || choice < 1) ui_status(STATUS_INVALID);
    } while (choice != 3);
}

/* ================= COLOR CHANGE WIZARD (full table – exact original) ================= */
static void color_change(void) {
    char input[4];
    int base_row = BASE_ROW;
    int base_col = BASE_COL;
    int r, c;

    const char* color_names[] = {
        "Red", " ","Green"," ", "Yellow"," ", "Blue", " ","Purple"," ",
        "Cyan", " ","Light Grey", " ","Grey", "","Light Red", " ","Light Green",
        " ","Light Yellow"," ", "Light Blue", " ","Light Purple"," ", "Light Cyan", "","White", " ","Blank"," "
    };

    const char* color_samples[] = {
        B1, B2, B3, B4, B5, B6, B7, B8, B9, B10,
        B11, B12, B13, B14, B15, B16   /* blank has no sample */
    };

    int num_colors = 16;

    while (1)
    {
        ui_init();

        r = base_row - 7;
        c = base_col+14;

        /* Title */
        ui_title(r++, c, underline RED bold, "Welcome to background border color changer wizard.");
        ui_title(r++, c + 2, yellow bold, "Available options:");
        r++; /* blank line */
        ui_title(r++, c + 4, "", " -------------------------------------------");

        /* Header row */
        ui_title(r, c + 4, "", "|    ");
        ui_title(r, c + 9, green bold, "COLOR_NAME");
        ui_title(r, c + 24, "", "       |        ");
        ui_title(r, c + 35, green bold, "  SAMPLE ");
        ui_title(r, c + 45, "", "   |");
        r++; /* move to next row */

        int j = 0, k = 1;

        /* Data rows */
        for (int i = 0; i < num_colors; i++)
        {
            /* Left part: border, number and color name */
            char left[40];
            char num[4];

            pal_strcpy(left, "| ");
            pal_itoa(k, num);
            pal_strcat(left, num);
            pal_strcat(left, ".) ");
            pal_strcat(left, color_names[i * 2]);

            ui_title(r, c + 4, "", left);

            /* Separator */
            pal_set_cursor(r, c + 26);
            pal_print("     |    ");

            /* Sample block (two spaces with background) */
            pal_set_cursor(r, c + 37);
            pal_print(color_samples[j]);
            pal_print("      ");
            pal_print(reset);

            /* Right border */
            pal_set_cursor(r, c + 44);
            pal_print("    |");

            r++; /* move to next row */

            /* Blank gap row with margins */
            pal_set_cursor(r, c + 4);
            pal_print("|");
            pal_set_cursor(r, c + 26);
            pal_print("     |");
            pal_set_cursor(r, c + 41);
            pal_print("       |");

            r++; /* one blank line after each row */

            j++;
            k++;
        }

        /* Remove extra gap row after last data row */
        r--;

        ui_title(r++, c + 4, "", " -------------------------------------------  ");
        ui_title(r, c + 4, purple bold, "Enter choice (To exit press e): ");

        pal_set_cursor(r, c + 36);
        pal_readline(input, sizeof(input));

        if (pal_strcmp(input, "e") == 0 || pal_strcmp(input, "E") == 0)
            return;

        int num = pal_atoi(input);

        if (num >= 1 && num <= 15)
        {
            file_write_int(LOOKS_FILE, num);
            r++; /* blank line */
            ui_title(r, c + 4, green bold, "Color changed. Restart OE to see effect.");
            pal_pause();
            return;
        }
        else if (num == 16)
        {
            file_write_int(LOOKS_FILE, 16); /* store 16 for blank */
            r++; /* blank line */
            ui_title(r, c + 4, green bold, "Color changed (blank). Restart OE to see effect.");
            pal_pause();
            return;
        }
        else
        {
            r++; /* blank line */
            ui_title(r, c + 4, red bold, "No command.");
            pal_pause();
            /* loop continues – redraw table */
        }
    }
}

/* ================= PERSONALIZATION (menu) ================= */
static void personalization(void)
{
    const char* options[] = {
        green bold"1.) Change your border color.",
        green bold"2.) EXIT."
    };
    int choice;
    do
    {
        choice = ui_menu(BASE_ROW, BASE_COL,red bold underline
            "Welcome to Personalization Panel:" reset yellow "\n\t\t\t\t\t\t\t\t  Pick a task" reset, options, 2);
        if (choice == 1) color_change();
    } while (choice != 2);
}

/* ================= HELP (in settings) ================= */
static void settings_help(void)
{
	help_show_settings();
}

/* ================= MAIN SETTINGS LOOP ================= */
void settings_run(void)
{
	//color_change();   /* first run – direct to color change wizard */
    const char* options[] = {
        green bold "1.) USER ACCOUNTS",
        green bold "2.) RESET AND RESTORE",
        green bold "3.) PERSONALIZATION",
        green bold "4.) HELP",
        green bold "5.) EXIT"
    };
    int choice;

    do
    {
		//pal_set_cursor(35, BASE_COL);
  //      pal_print(yellow "Available sub-categories:");
        choice = ui_menu(BASE_ROW, BASE_COL,
            red underline "Welcome to the Settings!!"reset yellow "\n\t\t\t\t\t\t\t\t  Available sub-categories:" reset, options, 5);
        
        switch (choice)
        {
        case 1: user_accounts(); break;
        case 2: reset_restore(); break;
        case 3: personalization(); break;
        case 4: settings_help(); break;
        case 5: return;
        default:
            /* Hidden shortcuts */
            if (choice == 7)
                color_change();   /* direct to color change */
            else if (choice == 8)
                add_user();
            else
                ui_status(STATUS_INVALID);
        }
    } while (choice != 5);
}