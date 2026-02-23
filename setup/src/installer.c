/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-22
Module: Installer
File: installer.c
About: Classic OE installer flow.
Revisions:
- 2026-02-21  Integrated user module + app_installer
- 2026-02-22  Added user_enter_guest() for trial, fixed app_id 0
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "app_installer.h"
#include "user.h"
#include "extras.h"
#include "installer.h"
#include"utils.h"
void installer_prompt(int app_id)
{
    ui_init(); layout(); logo();

    ui_title(8, 65, BLUE bold,
        "Do you want to directly install this application or use it once before installation?");
    ui_title(10, 72, purple bold underline, "Help Me Decide:");
    ui_title(12, 72, yellow bold, "If you wish to install directly press y.");
    ui_title(13, 72, "", "If you want to test before installing press n.");
    ui_title(14, 72, "", "Trial mode allows limited commands: login, install and exit only.");
    ui_title(18, 72, cyan bold, "Enter your choice (y/n): ");

    char choice = util_get_char("");

    if (choice == 'n' || choice == 'N')
    {
        ui_init(); layout(); logo();
        ui_title(7, 5, "", "After completion of trial type 'install' to restart setup.");
        user_enter_guest();
        return;
    }
    else if (choice == 'y' || choice == 'Y')
    {
        ui_init(); layout(); logo();
        ui_title(8, 62, underline red bold, "While the program is loading let us know its working:");
        ui_title(10, 62, yellow, "At first type help command at the prompt.");
        ui_title(11, 62, "", "You will get list of available commands.");
        ui_title(12, 62, yellow, "Use it to install your desired program.");
        ui_title(13, 62, yellow, "Enjoy using it!!!");
        ui_title(20, 118, green, "DEVELOPER: ");
        ui_title(20, 130, RED, "Subhajit Halder");
        progressbar(36, 80, 50);

        if (!user_exists()) add_user();

        if (app_id != 0)
        {
            const char* app_name = NULL;
            switch (app_id)
            {
            case 1: app_name = "tictactoe"; break;
            case 2: app_name = "quiz"; break;
            case 3: app_name = "temp_conv"; break;
            case 4: app_name = "calculator"; break;
            default: break;
            }
            if (app_name)
            {
                const app_t* app = find_app(app_name);
                if (app) install_app(app);
            }
        }

        extras_show_improvements();
        login();
    }
}