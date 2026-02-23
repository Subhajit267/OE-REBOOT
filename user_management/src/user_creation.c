/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-23
Module: User Management
File: user_creation.c
About: Original OE add_user() – now validates inputs,
       rejects empty user ID, and prevents password "0".
Revisions:
- 2026-02-21  Converted to PAL + binary storage
- 2026-02-22  Added user_exists()
- 2026-02-23  Added input validation for empty user ID and password
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "file.h"
#include "utils.h"
#include "user.h"

void add_user(void)
{
    char id[USERNAME_MAX];
    char c[8];
    char pass[PASSWORD_MAX];

    while (1) {
        ui_init(); layout();
        ui_title(15, 60, underline RED bold, "Welcome to USER-ID Password Creation Wizard Ver: 1.7.9");
        ui_title(16, 60, "", "FOLLOW THE ONSCREEN INSTRUCTIONS TO CREATE A USER");
        ui_title(17, 60, yellow, "Please create a user id password for safety reasons:");

        ui_title(18, 60, "", "User-Id:");
        util_get_string_echo(id, USERNAME_MAX, "");
        trim_whitespace(id);

        if (id[0] == '\0') {
            ui_title(19, 60, RED bold, "User-ID cannot be empty. Press Enter to try again.");
            pal_pause();
            continue;
        }

        file_write_string(USER_FILE, id);

        ui_title(20, 60, "", "Do you want to create a password(y/n):");
        util_get_string_echo(c, 8, "");

        if (c[0] == 'y' || c[0] == 'Y')
        {
            while (1) {
                ui_title(21, 60, "", "Enter password:");
                util_get_string(pass, PASSWORD_MAX, "");
                trim_whitespace(pass);
                if (pass[0] == '\0') {
                    ui_title(22, 60, RED bold, "Password cannot be empty. Try again.");
                    pal_pause();
                    continue;
                }
                if (pal_strcmp(pass, "0") == 0) {
                    ui_title(22, 60, RED bold, "The password cannot be 0. Choose another.");
                    pal_pause();
                    continue;
                }
                break;
            }
            file_write_string(PASS_FILE, pass);
        }
        else
        {
            file_write_string(PASS_FILE, "0");
        }

        ui_title(25,60, RED bold, "You are Successful in creating a user.");
        pal_pause();
        break;
    }
}

int user_exists(void)
{
    return file_exists(USER_FILE);
}