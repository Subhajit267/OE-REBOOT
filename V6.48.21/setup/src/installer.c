/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-23
Module: Installer
File: installer.c
About: Classic OE installer flow – original strings restored,
       invisible input, backdoor commands preserved.
Revisions:
- 2026-02-21  Integrated user module + app_installer
- 2026-02-22  Added user_enter_guest() for trial, fixed app_id 0
- 2026-02-23  Restored original OE texts, made input invisible

ALL CHECKED AND WORKING
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "app_installer.h"
#include "user.h"
#include "extras.h"
#include "installer.h"
#include "regedit.h"
#include "prompt.h"

void installer_prompt()
{
    while (1)
    {
        char input[32];

        ui_init();

        int row = 12, col = 55;   /* base coordinates */

        /* ===== Main Installer Screen ===== */
        ui_title(row++, col, BLUE bold,
            "Do you want to directly install this application or you want to use it once before installation?(Enter choice below).");
        ++row; col += 12;
        /* Indented section for "Help Me Decide" – note col+18 offset */
        ui_title(row++, col, purple bold underline, "Help Me Decide:" reset);
        /* Return to base column for remaining lines */
        ui_title(row++, col, yellow bold,
            "If you wish to install the program directly on the browser without testing for once press y.");
        ui_title(row++, col, yellow bold,
            "If you want to test the progarm before installing i.e. if you want to have a look at the user");
        ui_title(row++, col, yellow bold,
            "interface press n and it will load you into the guest user login screen. Just Press enter there");
        ui_title(row++, col, yellow bold,
            "to login. As it is trial so only three commands login, install and exit would be there.");
        ui_title(row++, col, cyan bold, "Enter your choice(y/n):");

        /* Invisible input (like original cout<<invisible) */
        pal_print(invisible);
        pal_readline(input, sizeof(input));
        pal_print(reset);

        /* ===== Trial Mode ===== */
        if (pal_strcmp(input, "n") == 0 || pal_strcmp(input, "N") == 0)
        {
            ui_title(27, 60, "",
                "After completion of your trial type 'install' to restart the setup to continue.");
            pal_pause();
            login();
            user_enter_guest();
            return;
        }
        /* ===== Registry Editor Admin Backdoor ===== */
        else if (pal_strcmp(input, "registryeditor_admin") == 0)
        {
            reg_admin_mode = 1;   /* set guest mode to admin */
            reg_edit();
            return;
        }
        else if (pal_strcmp(input, "registryeditor") == 0)
        {
            reg_admin_mode = 0;   /* set guest mode to regular */
            reg_edit();
            return;
        }
        /* ===== Prompt Backdoor (skip setup) ===== */
        else if (pal_strcmp(input, "prompt") == 0)
        {
            reg_status = 0;
            prompt();
            return;
        }
        /* ===== Direct Install ===== */
        else if (pal_strcmp(input, "y") == 0 || pal_strcmp(input, "Y") == 0)
        {
            ui_init();

            row = 15;
            col = 60;              /* reset for direct install screen */
            int column2 = 118;

            ui_title(row++, col, underline red bold,
                "While the program is loading let us know its working:");
            ui_title(row++, col, yellow bold,
                "At first type help command at the prompt.");
            ui_title(row++, col, yellow bold,
                "You will be given a list of available commands, use it  ");
            ui_title(row++, col, yellow bold,
                "to install your desired program");
            ui_title(row++, col, yellow bold,
                "Enjoy using it!!!");
            ui_title(row + 4, column2, green bold, "DEVELOPER: ");
            ui_title(row + 4, column2 + 12, RED bold, "Subhajit Halder");

            /* Additional original lines placed appropriately */
            ui_title(row - 3, column2, purple bold, "Desingned for ease");
            ui_title(row - 2, column2, purple bold, "For ease in using ");
            ui_title(row - 1, column2, purple bold, "softwares");

            progressbar(36, 80, 50);
            ///if (!user_exists())
            add_user();

            //if (app_id != 0)
            //{
            //    const char* app_name = NULL;
            //    switch (app_id)
            //    {
            //    case 1: app_name = "tictactoe"; break;
            //    case 2: app_name = "quiz"; break;
            //    case 3: app_name = "temp_conv"; break;
            //    case 4: app_name = "calculator"; break;
            //    default: break;
            //    }
            //    if (app_name)
            //    {
            //        const app_t* app = find_app(app_name);
            //        if (app) install_app(app);
            //    }
            //}
            /* Create all app registry files with value 0 (uninstalled) */
            uninstall_all(0); // flag set to 0 to supress "Uninstalled" status messages
            extras_show_improvements();
            login();
        }
        /* ===== Invalid Input ===== */
        else
        {
            ui_status(STATUS_INVALID);
            continue;
        }
    }
}