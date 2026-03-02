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

ALLL CHECKED AND WORKING
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
    char pc[2];
	int row = 15, col = 60;
    ui_init();
    ui_title(row++, col, red bold underline, "Welcome to password changing wizard Ver 1.7.9");
    ui_title(row++, col, yellow, "Enter Following details :");
    ui_title(row++, col, "", "User-ID:");
    //util_get_string(name, USERNAME_MAX, "");
    pal_readline(name, USERNAME_MAX);
    file_read_string(USER_FILE, name1, USERNAME_MAX);
    trim_whitespace(name1);
    trim_whitespace(name);

    if (pal_strcmp(name1, name) != 0)
		lockdown("username");

    file_read_string(PASS_FILE, password1, PASSWORD_MAX);
    trim_whitespace(password1);

   // ui_title(row++, col, "", "Do you wish to keep a Password? (y/n)");
   // pal_readline(pc, sizeof(pc));

   int flag = ui_confirm(row++, col, "Do you wish to keep a Password?");
    ui_title(row++, col, "", "Enter your last Password (0 if none):");
    pal_print(invisible);
    //util_get_string(password, PASSWORD_MAX, "");
    pal_readline(password, PASSWORD_MAX);
    pal_print(reset);
    trim_whitespace(password);

    ///int old_ok = 0;
    //if (pal_strcmp(password1, "0") == 0) {
    //    // No password currently: accept empty or "0" as correct
    //    
    //if (password[0] == '\0' || pal_strcmp(password, "0") == 0)
    //        //old_ok = 1;
    //}
    //else if {
    //    if (pal_strcmp(password1, password) == 0)
    //        //old_ok = 1;
    //}

    if (!((pal_strcmp(password1, "0") == 0) ? (password[0] == '\0' || pal_strcmp(password, "0") == 0) : (pal_strcmp(password1, password) == 0)))
       lockdown("password");
    
    // Remove password
    if (!flag)
    {
        file_write_string(PASS_FILE, "0");
        ui_title(row++, col, "", "Your password has been removed");
        pal_pause();
        return;
    }

    while (1) {
            ui_title(row++, col, "", "Enter new password:");
            //util_get_string(passnew, PASSWORD_MAX, "");
            pal_readline(passnew, PASSWORD_MAX); 
            trim_whitespace(passnew);
            if (passnew[0] == '\0') 
                ui_title(row++, col, RED bold, "Password cannot be empty.");          
            else if (pal_strcmp(passnew, "0") == 0) 
                ui_title(row++, col, RED bold, "The password cannot be 0.");
            else
                break;
            pal_pause();
            continue;
    }
    file_write_string(PASS_FILE, passnew);
    ui_title(row++, col, "", "Your password has been changed");
    pal_pause();
    return;
    

    ///settings_run();
}