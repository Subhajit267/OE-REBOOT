/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-03-03
Date Last Modified: 2026-03-03
Module: System Tools
File: systeminfo.c
About: Final OE System Information Tool.
       Multi-color disciplined layout version.

Revisions:
- 2026-03-03  Initial advanced version
- 2026-03-03  Unified column layout
- 2026-03-03  Multi-color semantic design
------------------------------------------------------------
*/

#include "systeminfo.h"
#include "pal.h"
#include "pal_oe_info.h"
#include "ui_setup.h"
#include "ui_elements.h"
#include "user.h"
#include "branding.h"

static unsigned long long to_mb(unsigned long long bytes)
{
    return bytes / (1024ULL * 1024ULL);
}
static void format_uptime(unsigned long long seconds, int* h, int* m, int* s)
{
    *h = seconds / 3600;
    *m = (seconds % 3600) / 60;
    *s = seconds % 60;
}

void oe_systeminfo_entry(void)
{
    pal_oe_info_t info;

    if (!pal_get_oe_info(&info))
    {
        ui_status(STATUS_ERROR);
        return;
    }

    ui_init();

    int row = 8;
    int col = 66;

    unsigned long long total = info.total_ram / (1024ULL * 1024ULL);
    unsigned long long free = info.free_ram / (1024ULL * 1024ULL);
    unsigned long long used = total - free;
    int percent = (total != 0) ? (int)((used * 100) / total) : 0;

    /* ================= TOP BORDER ================= */

    ui_title(row++, col, BLUE bold,
        " ============================================================================== ");

    ui_title(row++, col, BLUE bold,
        "|                            " RED bold underline " " OE_SHORT_NAME " SYSTEM INFORMATION " reset BLUE bold "                     | ");

    ui_title(row++, col, BLUE bold,
        " ============================================================================== ");

    /* ================= OE INFO ================= */

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    ui_title(row++, col, BLUE bold,
        "| " cyan "OE BUILD DETAILS:                                                            " BLUE "|");

    ui_title(row++, col, BLUE bold,
        "| " purple "----------------------------------------------------------------------------" BLUE bold " |");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Version:");
    ui_title(row, col + 20, GREEN, OE_VERSION);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Build Details:");
    ui_title(row, col + 20, GREEN,
        OE_BUILD_TYPE " " OE_BUILD_DATE " " OE_BUILD_TIME);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Developer:");
    ui_title(row, col + 20, purple bold,
        OE_DEVELOPER " " OE_COPYRIGHT);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "USER:");

    if (user_exists())
    {
        ui_title(row, col + 20, red bold, current_user);
    }
    else
    {
        ui_title(row, col + 20, red bold, "GUEST");
    }

    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    /* ================= PAL ================= */

    ui_title(row++, col, BLUE bold,
        "| " cyan "PAL RUNTIME                                                                  " BLUE "|");

    ui_title(row++, col, BLUE bold,
        "| " purple "----------------------------------------------------------------------------" BLUE bold " |");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Backend:");
    ui_title(row, col + 20, GREEN, info.backend_name);
    ui_title(row++, col + 79, BLUE bold, "|");

    /* ================= CPU ================= */

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    ui_title(row++, col, BLUE bold,
        "| " cyan "CPU INFORMATION                                                              " BLUE "|");

    ui_title(row++, col, BLUE bold,
        "| " purple "----------------------------------------------------------------------------" BLUE bold " |");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Model:");
    ui_title(row, col + 20, GREEN, info.cpu_name);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Cores:");
    ui_title_int(row, col + 20, GREEN, info.cpu_cores);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Threads:");
    ui_title_int(row, col + 20, GREEN, info.cpu_threads);
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Clock Speed:");
    ui_title_int(row, col + 20, GREEN, (int)info.cpu_mhz);
    ui_title(row, col + 28, white, "MHz");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Architecture:");
    ui_title(row, col + 20, GREEN, info.architecture);
    ui_title(row++, col + 79, BLUE bold, "|");

    /* ================= MEMORY ================= */

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    ui_title(row++, col, BLUE bold,
        "| " cyan "MEMORY INFORMATION                                                          " BLUE " |");

    ui_title(row++, col, BLUE bold,
        "| " purple "----------------------------------------------------------------------------" BLUE bold " |");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Total RAM:");
    ui_title_int(row, col + 20, GREEN, (int)total);
    ui_title(row, col + 28, white, "MB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Free RAM:");
    ui_title_int(row, col + 20, GREEN, (int)free);
    ui_title(row, col + 28, white, "MB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Used RAM:");
    ui_title_int(row, col + 20, GREEN, (int)used);
    ui_title(row, col + 28, white, "MB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Usage:");
    ui_title_int(row, col + 20, GREEN, percent);
    ui_title(row, col + 28, white, "%");
    ui_title(row++, col + 79, BLUE bold, "|");

    /* ================= DISK ================= */

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    unsigned long long disk_total =
        info.disk_total / (1024ULL * 1024ULL * 1024ULL);

    unsigned long long disk_free =
        info.disk_free / (1024ULL * 1024ULL * 1024ULL);

    unsigned long long disk_used =
        (info.disk_total - info.disk_free) / (1024ULL * 1024ULL * 1024ULL);

    int disk_percent =
        (disk_total != 0)
        ? (int)((disk_used * 100) / disk_total)
        : 0;

    ui_title(row++, col, BLUE bold,
        "| " cyan "DISK INFORMATION                                                             " BLUE "|");

    ui_title(row++, col, BLUE bold,
        "| " purple "----------------------------------------------------------------------------" BLUE " |");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Total Disk:");
    ui_title_int(row, col + 20, GREEN, (int)disk_total);
    ui_title(row, col + 28, white, "GB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Free Disk:");
    ui_title_int(row, col + 20, GREEN, (int)disk_free);
    ui_title(row, col + 28, white, "GB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Used Disk:");
    ui_title_int(row, col + 20, GREEN, (int)disk_used);
    ui_title(row, col + 28, white, "GB");
    ui_title(row++, col + 79, BLUE bold, "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Usage:");
    ui_title_int(row, col + 20, GREEN, disk_percent);
    ui_title(row, col + 28, white, "%");
    ui_title(row++, col + 79, BLUE bold, "|");

    /* ================= UPTIME ================= */

    ui_title(row++, col, BLUE bold,
        "|                                                                              |");

    int h, m, s;
    format_uptime(info.uptime_seconds, &h, &m, &s);

    ui_title(row++, col, BLUE bold,
        "| " cyan "SYSTEM UPTIME                                                                " BLUE "|");

    ui_title(row++, col, BLUE bold,
        "| " purple "---------------------------------------------------------------------------- " BLUE "|");

    ui_title(row, col, BLUE bold, "| ");
    ui_title(row, col + 2, yellow bold, "Uptime:");
    ui_title_int(row, col + 20, GREEN, h);
    ui_title(row, col + 24, white, "h ");
    ui_title_int(row, col + 27, GREEN, m);
    ui_title(row, col + 31, white, "m ");
    ui_title_int(row, col + 34, GREEN, s);
    ui_title(row, col + 38, white, "s");
    ui_title(row++, col + 79, BLUE bold, "|");

    /* ================= BOTTOM ================= */

    ui_title(row++, col, BLUE bold,
        " ============================================================================== ");

    pal_pause();
}