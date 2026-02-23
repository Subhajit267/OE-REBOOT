/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-21
Module: Utilities
File: timer.c
About: Countdown timer using PAL abstraction.
Revisions:
- 2026-02-21  Initial implementation
- 2026-02-21  Converted to PAL-only backend
------------------------------------------------------------
*/

#include "utils.h"

void util_timer(int seconds, const char* message)
{
    int t = seconds;

    while (t >= 0)
    {
        pal_set_cursor(25, 160);
        pal_print("TIME LEFT: ");

        char buf[12];
        int i = 0;

        if (t == 0)
            buf[i++] = '0';
        else
        {
            int tmp = t;
            char rev[12];
            int j = 0;

            while (tmp > 0)
            {
                rev[j++] = (tmp % 10) + '0';
                tmp /= 10;
            }

            while (j > 0)
                buf[i++] = rev[--j];
        }

        buf[i] = '\0';

        pal_print(buf);
        pal_print("   ");

        pal_sleep(1);
        t--;
    }

    if (message)
    {
        pal_print("\n");
        pal_print(message);
    }
}