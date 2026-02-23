/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-23
Module: User Management
File: password_management.c
About: Original OE password_change() – now handles “0” (no password)
       correctly and validates new password.
Revisions:
- 2026-02-21  Integrated util_timer()
- 2026-02-22  Replaced settings() with settings_run()
- 2026-02-23  Fixed old password check for “0”, added input validation
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "file.h"
#include "utils.h"
#include "user.h"
#include "settings.h"

void password_change(void)
{
    char name[USERNAME_MAX], name1[USERNAME_MAX];
    char password[PASSWORD_MAX], password1[PASSWORD_MAX], passnew[PASSWORD_MAX];
    char pc;

    ui_init(); layout();
    ui_title(15, 60, red bold underline, "Welcome to password changing wizard Ver 1.7.9");
    ui_title(16, 60, yellow, "Enter Following details :");
    ui_title(17, 60, "", "User-ID:");
    util_get_string(name, USERNAME_MAX, "");
    file_read_string(USER_FILE, name1, USERNAME_MAX);
    trim_whitespace(name1);
    trim_whitespace(name);

    if (pal_strcmp(name1, name) != 0)
    {
        util_timer(10, "Access Denied");
        return;
    }

    file_read_string(PASS_FILE, password1, PASSWORD_MAX);
    trim_whitespace(password1);

    ui_title(5, 10, "", "Do you wish to keep a Password? (y/n)");
    pc = util_get_char("");

    if (pc == 'y' || pc == 'Y')
    {
        ui_title(5, 11, "", "Enter your last Password (0 if none):");
        pal_print(invisible);
        util_get_string(password, PASSWORD_MAX, "");
        pal_print(reset);
        trim_whitespace(password);

        int old_ok = 0;
        if (pal_strcmp(password1, "0") == 0) {
            // No password currently: accept empty or "0" as correct
            if (password[0] == '\0' || pal_strcmp(password, "0") == 0)
                old_ok = 1;
        }
        else {
            if (pal_strcmp(password1, password) == 0)
                old_ok = 1;
        }

        if (!old_ok)
        {
            util_timer(10, "Access Denied");
            return;
        }

        while (1) {
            ui_title(5, 12, "", "Enter new password:");
            util_get_string(passnew, PASSWORD_MAX, "");
            trim_whitespace(passnew);
            if (passnew[0] == '\0') {
                ui_title(5, 16, RED bold, "Password cannot be empty.");
                pal_pause();
                continue;
            }
            if (pal_strcmp(passnew, "0") == 0) {
                ui_title(5, 16, RED bold, "The password cannot be 0.");
                pal_pause();
                continue;
            }
            break;
        }
        file_write_string(PASS_FILE, passnew);
        ui_title(5, 13, "", "Your password has been changed");
        pal_pause();
    }
    else
    {
        // Remove password
        file_write_string(PASS_FILE, "0");
        ui_title(5, 13, "", "Your password has been removed");
        pal_pause();
    }

    settings_run();
}