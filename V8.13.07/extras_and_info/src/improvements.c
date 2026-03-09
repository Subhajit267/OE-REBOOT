/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-03-10
Module: Extras & Info
File: improvements.c
About: Displays the list of improvements and bug fixes for the
       current version of OE_REBOOT.

Revisions:
- 2026-02-21  Initial implementation
- 2026-03-10  Updated improvements list for OE Version 8
              and integrated branding system
------------------------------------------------------------
*/

#include "pal.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "extras.h"
#include "branding.h"

void extras_show_improvements(void)
{
    ui_init();  /* clear screen and draw layout */

    int row = 14, column = 66;

    ui_title(row++, column, bold red underline,
        OE_NAME " - Improvements in Version " OE_VERSION);

    row++;

    ui_title(row++, column, bold blue, "i.)   Complete Platform Abstraction Layer (PAL) introduced");
    ui_title(row++, column, bold yellow, "ii.)  Cross-platform support for Windows and Linux");
    ui_title(row++, column, bold blue, "iii.) New filesystem command framework (mdr, ldr, cdr, cpf, rmf, mvf)");
    ui_title(row++, column, bold yellow, "iv.)  Binary file abstraction layer implemented");
    ui_title(row++, column, bold blue, "v.)   Modular application installer system added");
    ui_title(row++, column, bold yellow, "vi.)  Application registry system using .rg binary files");
    ui_title(row++, column, bold blue, "vii.) New system information tool for hardware inspection");
    ui_title(row++, column, bold yellow, "viii.) Built-in Notepad text editor introduced");
    ui_title(row++, column, bold blue, "ix.)  Advanced console UI layout and rendering engine");
    ui_title(row++, column, bold yellow, "x.)   Centralized branding system for version and build info");
    ui_title(row++, column, bold blue, "xi.)  Improved prompt shell with command based architecture");
    ui_title(row++, column, bold yellow, "xii.) Enhanced user account management system");
    ui_title(row++, column, bold blue, "xiii.) Modular source tree architecture for easier expansion");
    ui_title(row++, column, bold yellow, "xiv.) Performance and stability improvements across modules");

    row++;

    ui_title(row++, column, bold green,
        OE_SHORT_NAME " " OE_VERSION " (" OE_BUILD_TYPE ")");

    ui_title(row++, column, bold green,
        OE_COPYRIGHT " " OE_DEVELOPER);

    pal_pause();  /* Wait for key press before returning */
}