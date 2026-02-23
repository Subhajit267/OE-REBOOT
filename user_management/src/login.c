/*
------------------------------------------------------------
Author: Subhajit Halder
Module: User Management
File: login.c
About: Original OE login function – updated for new 209×50 box.
Revisions:
- 2026-02-21  Replaced timerS() with util_timer()
- 2026-02-22  Fixed reg_status values, replaced reg_edit/source with regedit_run/extras_show_source
- 2026-02-23  Adjusted coordinates, added trim_whitespace for password comparison
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "file.h"
#include "utils.h"
#include "user.h"
#include "regedit.h"
#include "extras.h"
#include "prompt.h"

char current_user[USERNAME_MAX] = "";
int reg_status = 0;

void login(void)
{
    char name1[USERNAME_MAX];
    char password1[PASSWORD_MAX];
    char password[PASSWORD_MAX];

    ui_init();
    logo();

    if (file_exists(USER_FILE))
    {
        reg_status = 0;   /* normal user */

        ui_title(13, 69, "",
            "  To begin press enter or type password (if you have created a User-ID).");

        ui_title(16, 79, "", "User-ID:");
        file_read_string(USER_FILE, name1, USERNAME_MAX);
        ui_title(16, 90, "", name1);
        file_read_string(PASS_FILE, password1, PASSWORD_MAX);

        if (pal_strcmp(password1, "0") == 0)
        {
            pal_pause();
            prompt();
        }
        else
        {
            ui_title(17, 79, "", "Password:  ");
            pal_print(invisible);
            util_get_string(password, PASSWORD_MAX, "");
            pal_print(reset);

            /* Trim both stored and entered passwords to avoid whitespace mismatches */
            trim_whitespace(password1);
            trim_whitespace(password);

            if (pal_strcmp(password1, password) == 0)
                prompt();
            else if (pal_strcmp(password, "registryeditor") == 0)
                reg_edit();
            else if (pal_strcmp(password, "guess_it") == 0)
                extras_show_source();
            else
            {
                util_timer(10, RED bold "Access Denied");
                pal_exit();
            }
        }
    }
    else
    {
        reg_status = 1;
        ui_title(14, 11, "",
            " /* To just test the program (*with limited features) press enter */ ");
        ui_title(22, 42, "", "USER-ID: GUEST");
        pal_pause();
        ui_init();
        prompt();
    }
}