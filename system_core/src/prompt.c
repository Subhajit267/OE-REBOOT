/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-22
Date Last Modified: 2026-02-23
Module: System Core
File: prompt.c
About: Main shell – command loop with table‑driven dispatch.
       Handles guest restrictions, install/uninstall patterns,
       and all original OE commands. Updated for new 209×50 box.
Revisions:
- 2026-02-22  Initial full implementation
- 2026-02-23  Adjusted row coordinates to place prompt below logo,
              fixed install/uninstall prefix detection,
              integrated ui_status for standard messages.
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "user.h"
#include "app_installer.h"
#include "app_table.h"
#include "regedit.h"
#include "settings.h"
#include "help.h"
#include "utils.h"
#include "extras.h"
#include "bootscreen.h"
#include "prompt.h"
#include <stdlib.h>

/* -------- External application placeholders (to be implemented later) -------- */
static void app_tictactoe(void) {
    ui_title(33, 62, green bold, "TicTacToe placeholder");
    pal_pause();
}
static void app_quiz(void) {
    ui_title(33, 62, green bold, "Quiz placeholder");
    pal_pause();
}
static void app_temp_conv(void) {
    ui_title(33, 62, green bold, "Temperature Converter placeholder");
    pal_pause();
}
static void app_calculator(void) {
    ui_title(33, 32, green bold, "Calculator placeholder");
    pal_pause();
}
static void app_eqn_solve(void) {
    ui_title(33, 62, green bold, "Equation Solver placeholder");
    pal_pause();
}
static void app_quad_eqn_solve(void) {
    ui_title(33, 62, green bold, "Quadratic Equation Solver placeholder");
    pal_pause();
}
static void app_atc(void) {
    ui_title(33, 62, green bold, "Area of Triangle placeholder");
    pal_pause();
}

/* -------- Built‑in command handlers -------- */
static void cmd_help(void) {
    help_show_prompt();
}
static void cmd_exit(void) {
    ui_init();
    ui_title(25, 82, RED bold, "Program is shutting down. Thank you for using. Bye!!!");
    pal_sleep(2);
    pal_clear_screen();
    exit(0);
}
static void cmd_ver(void) {
    ui_title(33, 62, RED bold, "VER: 5.01.08");
    pal_pause();
}
static void cmd_login(void) {
    login();   /* This will re‑authenticate and eventually call prompt() again */
}
static void cmd_regedit(void) {
    reg_edit();   /* Use the modular registry editor */
}
static void cmd_settings(void) {
    settings_run();
}
static void cmd_inst_all(void) {
    install_all();
    ui_status(STATUS_SUCCESS);
    //pal_pause();
}
static void cmd_unst_all(void) {
    uninstall_all();
    ui_status(STATUS_SUCCESS);
   // pal_pause();
}

/* -------- Command table entry -------- */
typedef struct {
    const char* name;               /* command name (lowercase) */
    void (*handler)(void);           /* function to call */
    int guest_ok;                    /* 1 if allowed in guest mode */
    int need_installed;              /* 1 if app must be installed */
    const app_t* app;                 /* pointer to app registry entry (if app) */
} cmd_entry_t;

/* -------- Command table -------- */
static const cmd_entry_t cmd_table[] = {
    /* built‑ins */
    { "help",            cmd_help,       1, 0, NULL },
    { "exit",            cmd_exit,       1, 0, NULL },
    { "ver",             cmd_ver,        1, 0, NULL },
    { "login",           cmd_login,      1, 0, NULL },
    { "registryeditor",  cmd_regedit,    1, 0, NULL },
    { "settings",        cmd_settings,   0, 0, NULL },
    { "inst_all",        cmd_inst_all,   0, 0, NULL },
    { "unst_all",        cmd_unst_all,   0, 0, NULL },

    /* applications (must match app_table order) */
    { "tictactoe",       app_tictactoe,  0, 1, &apps[0] },
    { "quiz",            app_quiz,       0, 1, &apps[1] },
    { "temp_conv",       app_temp_conv,  0, 1, &apps[2] },
    { "calculator",      app_calculator, 0, 1, &apps[3] },
    { "eqn_solve",       app_eqn_solve,  0, 1, &apps[4] },
    { "quad_eqn_solve",  app_quad_eqn_solve, 0, 1, &apps[5] },
    { "atc",             app_atc,        0, 1, &apps[6] },

    { NULL, NULL, 0, 0, NULL }  /* sentinel */
};

/* -------- Convert string to lowercase (in‑place) -------- */
static void str_lower(char* s) {
    for (; *s; s++) {
        if (*s >= 'A' && *s <= 'Z')
            *s += 'a' - 'A';
    }
}

/* -------- Main prompt loop -------- */
void prompt(void) {
    char cmd_raw[64];
    char cmd_lower[64];
    int is_guest = reg_status;   /* 0 = normal, 1 = guest */

    while (1) {
        /* Redraw screen each iteration */
        ui_init();
        logo();
        ui_title(10, 60, RED bold underline, "Operating Environment ver: 5.01.08");

        if (is_guest) {
            ui_title(11, 60, "",
                "Only available commands are install, login, registryeditor and exit");
            ui_title(13, 60, green bold, "Command->");
        }
        else {
            ui_title(11, 60, green bold, "Type help to get list of commands");
            ui_title(10, 160, purple bold, "Welcome ");
            ui_title(11, 170, cyan bold, current_user);
            ui_title(13, 60, blue bold, "Command->");
        }

        /* Get command */
        pal_set_cursor(13, 71);
        pal_readline(cmd_raw, sizeof(cmd_raw));
        pal_strcpy(cmd_lower, cmd_raw);
        str_lower(cmd_lower);

        /* ----- Handle install/uninstall patterns ----- */
        if (pal_strcmp(cmd_lower, "inst_") == 0) {
            if (is_guest) {
                ui_status(STATUS_INVALID);
               // pal_pause();
                continue;
            }
            const char* app_name = cmd_lower + 5;
            const app_t* app = find_app(app_name);
            if (app) {
                install_app(app);
                ui_status(STATUS_SUCCESS);
            }
            else {
                ui_status(STATUS_INVALID);
               // pal_pause();
            }
            continue;
        }

        if (pal_strcmp(cmd_lower, "unst_" ) == 0) {
            if (is_guest) {
                ui_status(STATUS_INVALID);
               // pal_pause();
                continue;
            }
            const char* app_name = cmd_lower + 5;
            const app_t* app = find_app(app_name);
            if (app) {
                uninstall_app(app);
                ui_status(STATUS_SUCCESS);
            }
            else {
                ui_status(STATUS_INVALID);
               // pal_pause();
            }
            continue;
        }

        /* ----- Search command table ----- */
        int found = 0;
        for (int i = 0; cmd_table[i].name != NULL; i++) {
            if (pal_strcmp(cmd_lower, cmd_table[i].name) == 0) {
                found = 1;
                if (is_guest && !cmd_table[i].guest_ok) {
                    ui_status(STATUS_INVALID);
                }
                else if (cmd_table[i].need_installed && !app_is_installed(cmd_table[i].app)) {
                    ui_status(STATUS_NOT_INSTALLED);
                }
                else {
                    cmd_table[i].handler();
                }
                break;
            }
        }

        if (!found) 
            ui_status(STATUS_INVALID);
        
        //pal_pause();
        continue;
    }
}