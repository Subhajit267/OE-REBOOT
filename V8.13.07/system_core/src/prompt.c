/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-22
Date Last Modified: 2026-03-10
Module: System Core
File: prompt.c
About: Main shell – command loop with table-driven dispatch.
       Handles guest restrictions, install/uninstall patterns,
       and all original OE commands. Updated for new 209x50 box.
Revisions:
- 2026-02-22  Initial full implementation
- 2026-02-23  Adjusted row coordinates to place prompt below logo,
              fixed install/uninstall prefix detection,
              integrated ui_status for standard messages.
- 2026-02-23  Fixed install/uninstall prefix detection,
              restored guest-mode install command,
              corrected command table.
- 2026-03-04  Added systeminfo command and integrated PAL OE info abstraction.
- 2026-03-05  Added filesystem command support (mdr,rdr,ldr,cdr,rmf,cpf,rdf,mvf,pwd)
- 2026-03-10  BUG FIX: Removed undefined-behaviour function-pointer cast.
              Command table now uses a tagged union: handler_type 0 = void(*)(void),
              handler_type 1 = void(*)(char*). Dispatch calls the correct member.
              No casts anywhere. Casting void(*)(void) to void(*)(char*) and
              calling it is UB per C11 s6.3.2.3p8.
- 2026-03-10  BUG FIX: Fixed app_table indices to match app_table.c order.
              apps[0]=quiz apps[1]=temp_conv apps[2]=eqn_solve
              apps[3]=quad_eqn_solve apps[4]=atc apps[5]=tictactoe
- 2026-03-10  Added notepad command and using branding.
- 2026-03-10  Added inst_<app> / unst_<app> prefix dispatch (was missing).
------------------------------------------------------------
*/

#include "pal.h"
#include "pal_dir_file_cmds.h"
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
#include "installer.h"
#include "calculator.h"
#include "systeminfo.h"
#include "notepad.h"
#include "branding.h"
/* -------- Command parsing helpers -------- */

static void parse_command(char* input, char* cmd, char* args)
{
    int i = 0, j = 0;

    while (input[i] != ' ' && input[i] != 0)
    {
        cmd[i] = input[i];
        i++;
    }

    cmd[i] = 0;

    if (input[i] == ' ')
        i++;

    while (input[i] != 0)
        args[j++] = input[i++];

    args[j] = 0;
}

static void parse_two_args(char* args, char* a, char* b)
{
    int i = 0, j = 0, k = 0;

    while (args[i] != ' ' && args[i] != 0)
        a[j++] = args[i++];

    a[j] = 0;

    if (args[i] == ' ')
        i++;

    while (args[i] != 0)
        b[k++] = args[i++];

    b[k] = 0;
}


/* -------- FILESYSTEM COMMAND HANDLERS -------- */

static void cmd_mdr(char* args) { if (pal_strlen(args) == 0) { ui_status(STATUS_INVALID); return; } pal_mdr(args); ui_status(STATUS_SUCCESS); }
static void cmd_rdr(char* args) { if (pal_strlen(args) == 0) { ui_status(STATUS_INVALID); return; } pal_rdr(args); ui_status(STATUS_SUCCESS); }
static void cmd_ldr(char* args) { if (pal_strlen(args) == 0) pal_ldr("."); else pal_ldr(args); pal_pause(); }
static void cmd_cdr(char* args) { if (pal_strlen(args) == 0) { ui_status(STATUS_INVALID); return; } pal_cdr(args); }
static void cmd_rmf(char* args) { if (pal_strlen(args) == 0) { ui_status(STATUS_INVALID); return; } pal_rmf(args); ui_status(STATUS_SUCCESS); }
static void cmd_rdf(char* args) { if (pal_strlen(args) == 0) { ui_status(STATUS_INVALID); return; } pal_rdf(args); pal_pause(); }

static void cmd_cpf(char* args)
{
    char a[128], b[128];
    parse_two_args(args, a, b);

    if (pal_strlen(a) == 0 || pal_strlen(b) == 0) { ui_status(STATUS_INVALID); return; }

    pal_cpf(a, b);
    ui_status(STATUS_SUCCESS);
}

static void cmd_mvf(char* args)
{
    char a[128], b[128];
    parse_two_args(args, a, b);

    if (pal_strlen(a) == 0 || pal_strlen(b) == 0) { ui_status(STATUS_INVALID); return; }

    pal_mvf(a, b);
    ui_status(STATUS_SUCCESS);
}

static void cmd_pwd(char* args)
{
    char path[512];
    (void)args;

    if (pal_pwd(path, sizeof(path)) == 0)
        ui_title(33, 62, green bold, path);
    else
        ui_status(STATUS_ERROR);

    pal_pause();
}

static void cmd_notepad(char* args) { oe_notepad_run(args); }   /* args = optional filename */


/* -------- External application placeholders (to be implemented later) -------- */
static void app_tictactoe(void) {
    bootscreen_show(1);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "TicTacToe placeholder");
    pal_pause();
}
static void app_quiz(void) {
    bootscreen_show(2);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "Quiz placeholder");
    pal_pause();
}
static void app_temp_conv(void) {
    bootscreen_show(3);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "Temperature Converter placeholder");
    pal_pause();
}
static void app_eqn_solve(void) {
    bootscreen_show(5);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "Equation Solver placeholder");
    pal_pause();
}
static void app_quad_eqn_solve(void) {
    bootscreen_show(6);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "Quadratic Equation Solver placeholder");
    pal_pause();
}
static void app_atc(void) {
    bootscreen_show(7);   /* show app-specific bootscreen */
    ui_title(33, 62, green bold, "Area of Triangle placeholder");
    pal_pause();
}

/* -------- Built-in command handlers -------- */
static void cmd_help(void) { help_show_prompt(); }
static void cmd_exit(void) {
    ui_init();
    ui_title(25, 82, RED bold, OE_SHUTDOWN_TEXT);
    pal_sleep(2);
    pal_clear_screen();
    pal_exit();
}
static void cmd_ver(void) {
    ui_title(15, 62, RED bold, OE_VERSION);
	ui_title(16, 62, YELLOW bold, "BUILD DETAILS: "OE_BUILD_TYPE" " OE_BUILD_DATE" " OE_BUILD_TIME);
	ui_title(17, 62, green bold, "Developer: " OE_DEVELOPER " " OE_COPYRIGHT);
    pal_pause();
}
static void cmd_login(void) { login(); }

static void cmd_inst_all(void) { install_all(); }
static void cmd_unst_all(void) { uninstall_all(1); }

/* -------- SYSTEM TOOLS -------- */
static void cmd_regedit(void) { reg_edit(); }
static void cmd_settings(void) { settings_run(); }
static void cmd_calculator(void) { calculator(); }
static void cmd_systeminfo(void) { oe_systeminfo_entry(); }

/* -------- Guest-mode install handler (original OE behavior) -------- */
static void cmd_install_guest(void) {
    if (user_exists()) {
        ui_title(15, 60, RED bold, "Already installed.");
        ui_title(16, 60, RED bold, "Type login and re login with your user ID password (if exists).");
        pal_pause();
    }
    else {
        installer_prompt();
    }
}

/* -------- Command table entry -------- */
/*
 * BUG FIX: original table stored all handlers as void(*)(void) then cast
 * filesystem handlers (which take char*) back to void(*)(char*) at call
 * site. Casting between incompatible function pointer types and calling
 * through the result is undefined behaviour (C11 s6.3.2.3p8).
 * Fixed with a tagged union – handler_type 0 calls fn0 (no args),
 * handler_type 1 calls fn1 (char* args). No casts anywhere.
 */
typedef struct {
    const char* name;
    union {
        void (*fn0)(void);
        void (*fn1)(char*);
    } handler;
    int handler_type;   /* 0 = fn0, 1 = fn1 */
    int guest_ok;
    int need_installed;
    const app_t* app;
} cmd_entry_t;

/* -------- Command table -------- */
/*
 * App table indices – must match app_table.c order:
 * apps[0]=quiz  apps[1]=temp_conv  apps[2]=eqn_solve
 * apps[3]=quad_eqn_solve  apps[4]=atc  apps[5]=tictactoe
 */
static const cmd_entry_t cmd_table[] = {
    /* built-ins */
    { "help",            {.fn0 = cmd_help          }, 0, 1, 0, NULL },
    { "exit",            {.fn0 = cmd_exit          }, 0, 1, 0, NULL },
    { "ver",             {.fn0 = cmd_ver           }, 0, 1, 0, NULL },
    { "login",           {.fn0 = cmd_login         }, 0, 1, 0, NULL },
    { "install",         {.fn0 = cmd_install_guest }, 0, 1, 0, NULL },
    { "inst_all",        {.fn0 = cmd_inst_all      }, 0, 0, 0, NULL },
    { "unst_all",        {.fn0 = cmd_unst_all      }, 0, 0, 0, NULL },

    /* system tools */
    { "calculator",      {.fn0 = cmd_calculator    }, 0, 0, 0, NULL },
    { "settings",        {.fn0 = cmd_settings      }, 0, 0, 0, NULL },
    { "registryeditor",  {.fn0 = cmd_regedit       }, 0, 1, 0, NULL },
    { "systeminfo",      {.fn0 = cmd_systeminfo    }, 0, 1, 0, NULL },

    /* notepad (takes optional filename as arg) */
    { "notepad",         {.fn1 = cmd_notepad       }, 1, 0, 0, NULL },

    /* filesystem commands (all take char* args) */
    { "mdr", {.fn1 = cmd_mdr }, 1, 0, 0, NULL },
    { "rdr", {.fn1 = cmd_rdr }, 1, 0, 0, NULL },
    { "ldr", {.fn1 = cmd_ldr }, 1, 0, 0, NULL },
    { "cdr", {.fn1 = cmd_cdr }, 1, 0, 0, NULL },
    { "rmf", {.fn1 = cmd_rmf }, 1, 0, 0, NULL },
    { "cpf", {.fn1 = cmd_cpf }, 1, 0, 0, NULL },
    { "rdf", {.fn1 = cmd_rdf }, 1, 0, 0, NULL },
    { "mvf", {.fn1 = cmd_mvf }, 1, 0, 0, NULL },
    { "pwd", {.fn1 = cmd_pwd }, 1, 1, 0, NULL },

    /* applications – indices corrected to match app_table.c */
    { "quiz",            {.fn0 = app_quiz           }, 0, 0, 1, &apps[0] },
    { "temp_conv",       {.fn0 = app_temp_conv      }, 0, 0, 1, &apps[1] },
    { "eqn_solve",       {.fn0 = app_eqn_solve      }, 0, 0, 1, &apps[2] },
    { "quad_eqn_solve",  {.fn0 = app_quad_eqn_solve }, 0, 0, 1, &apps[3] },
    { "atc",             {.fn0 = app_atc            }, 0, 0, 1, &apps[4] },
    { "tictactoe",       {.fn0 = app_tictactoe      }, 0, 0, 1, &apps[5] },

    { NULL, {.fn0 = NULL }, 0, 0, 0, NULL }
};

/* -------- Convert string to lowercase (in-place) -------- */
static void str_lower(char* s) {
    for (; *s; s++) {
        if (*s >= 'A' && *s <= 'Z')
            *s += 'a' - 'A';
    }
}

/* -------- Main prompt loop -------- */
void prompt(void) {

    char cmd_raw[128];
    char cmd_lower[64];
    char args[128];
    int is_guest = reg_status;

    while (1) {

        ui_init();
        ui_title(10, 60, RED bold underline, OE_VERSION_STRING);

        if (is_guest) {
            ui_title(11, 60, "",
                OE_GUEST_MESSAGE);
            ui_title(13, 60, green bold, "Command->");
        }
        else {
            ui_title(11, 60, green bold, OE_USER_MESSAGE);
            ui_title(10, 135, purple bold, "Welcome ");
            ui_title(10, 143, cyan bold, current_user);
            ui_title(13, 60, blue bold, "Command->");
        }

        pal_set_cursor(13, 71);
        pal_readline(cmd_raw, sizeof(cmd_raw));

        parse_command(cmd_raw, cmd_lower, args);
        str_lower(cmd_lower);

        /* -------- inst_<app> / unst_<app> prefix handling -------- */
        if (pal_strlen(cmd_lower) > 5 &&
            cmd_lower[0] == 'i' && cmd_lower[1] == 'n' &&
            cmd_lower[2] == 's' && cmd_lower[3] == 't' && cmd_lower[4] == '_')
        {
            if (!is_guest)
            {
                const app_t* app = find_app(cmd_lower + 5);
                if (app) install_app(app);
                else     ui_status(STATUS_INVALID);
            }
            else ui_status(STATUS_INVALID);
            continue;
        }

        if (pal_strlen(cmd_lower) > 5 &&
            cmd_lower[0] == 'u' && cmd_lower[1] == 'n' &&
            cmd_lower[2] == 's' && cmd_lower[3] == 't' && cmd_lower[4] == '_')
        {
            if (!is_guest)
            {
                const app_t* app = find_app(cmd_lower + 5);
                if (app) uninstall_app(app);
                else     ui_status(STATUS_INVALID);
            }
            else ui_status(STATUS_INVALID);
            continue;
        }

        /* -------- standard table lookup -------- */
        int found = 0;
        int i;

        for (i = 0; cmd_table[i].name != NULL; i++) {
            if (pal_strcmp(cmd_lower, cmd_table[i].name) == 0) {
                found = 1;

                if (is_guest && !cmd_table[i].guest_ok) {
                    ui_status(STATUS_INVALID);
                }
                else if (cmd_table[i].need_installed && !app_is_installed(cmd_table[i].app)) {
                    ui_status(STATUS_NOT_INSTALLED);
                }
                else {
                    /* Safe dispatch – no function pointer cast */
                    if (cmd_table[i].handler_type == 0)
                        cmd_table[i].handler.fn0();
                    else
                        cmd_table[i].handler.fn1(args);
                }
                break;
            }
        }

        if (!found)
            ui_status(STATUS_INVALID);
    }
}