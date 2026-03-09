/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-03-05
Date Last Modified: 2026-03-05
Module: PAL
File: pal_file_cmds_windows.c
About: Windows implementation of PAL filesystem commands.
       Uses Win32 filesystem APIs to provide directory
       and file operations.

Revisions:
- 2026-03-05  Initial creation
------------------------------------------------------------
*/

#include "pal_dir_file_cmds.h"
#ifdef OE_FILE_DIR_CMDS_WINDOWS
#include <stdio.h>
#include <windows.h>
#include <string.h>


/*
* -------- DIRECTORY COMMANDS --------
*/


int pal_mdr(const char* path)
{
    return CreateDirectory(path, NULL) ? 0 : -1;
}


int pal_rdr(const char* path)
{
    return RemoveDirectory(path) ? 0 : -1;
}


int pal_cdr(const char* path)
{
    return SetCurrentDirectory(path) ? 0 : -1;
}


int pal_ldr(const char* path)
{
    WIN32_FIND_DATA fd;
    HANDLE h;

    char search[260];

    int row = 15;
    int page_count = 0;

    const char* p = path ? path : ".";

    pal_strcpy(search, p);
    pal_strcat(search, "\\*");

    h = FindFirstFile(search, &fd);

    if (h == INVALID_HANDLE_VALUE)
        return -1;


    /* -------- HEADER -------- */

    pal_set_cursor(row, 60);
    pal_print(yellow bold"NAME");

    pal_set_cursor(row, 165);
    pal_print("TYPE");

    pal_set_cursor(row, 180);
    pal_print("SIZE(kb)");

    row++;

    pal_set_cursor(row++, 60);
    pal_print(red bold"--------------------------------------------------------------------------------------------------------------------------------"green);


    do
    {
        if (pal_strcmp(fd.cFileName, ".") == 0 || pal_strcmp(fd.cFileName, "..") == 0)
            continue;

        /* ---- NAME (truncate to 100 chars) ---- */

        char namebuf[101];
        int i;

        for (i = 0; i < 100 && fd.cFileName[i] != 0; i++)
            namebuf[i] = fd.cFileName[i];

        namebuf[i] = 0;

        pal_set_cursor(row, 60);
        pal_print(namebuf);


        /* ---- TYPE ---- */

        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            pal_set_cursor(row, 165);
            pal_print("DIR");

            pal_set_cursor(row, 180);
            pal_print("-");
        }
        else
        {
            char sizebuf[32];

            pal_itoa(fd.nFileSizeLow, sizebuf);

            pal_set_cursor(row, 165);
            pal_print("FILE");

            pal_set_cursor(row, 180);
            pal_print(sizebuf);
        }

        row++;
        page_count++;

        /* ---- PAGE BREAK ---- */

        if (page_count == 10)
        {
            pal_set_cursor(row + 1, 60);
            pal_print(red bold"Press Enter for next page..."reset);
            pal_pause();

			ui_init();

            row = 15;
            page_count = 0;

            /* redraw header */

            pal_set_cursor(row, 60);
            pal_print(yellow bold"NAME");

            pal_set_cursor(row, 165);
            pal_print("TYPE");

            pal_set_cursor(row, 180);
            pal_print("SIZE(kb)");

            row++;

            pal_set_cursor(row++, 60);
            pal_print(red bold "--------------------------------------------------------------------------------------------------------------------------------"green bold);
        }

    } while (FindNextFile(h, &fd));

    FindClose(h);

    /* ---- FINAL RETURN ---- */

    pal_set_cursor(row + 1, 60);
    pal_print(red bold"Press Enter to return to prompt..."reset);
    pal_pause();

    return 0;
}

int pal_rnmdr(const char* oldname, const char* newname)
{
    return MoveFile(oldname, newname) ? 0 : -1;
}


int pal_mvdr(const char* src, const char* dst)
{
    return MoveFile(src, dst) ? 0 : -1;
}


int pal_cpdr(const char* src, const char* dst)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "xcopy \"%s\" \"%s\" /E /I /Y", src, dst);

    return system(cmd);
}


/*
* -------- FILE COMMANDS --------
*/


int pal_rmf(const char* file)
{
    return DeleteFile(file) ? 0 : -1;
}


int pal_rnmf(const char* oldname, const char* newname)
{
    return MoveFile(oldname, newname) ? 0 : -1;
}


int pal_mvf(const char* src, const char* dst)
{
    return MoveFile(src, dst) ? 0 : -1;
}


int pal_rdf(const char* file)
{
    FILE* f = fopen(file, "r");
    int ch;

    if (!f)
        return -1;

    while ((ch = fgetc(f)) != EOF)
        putchar(ch);

    fclose(f);

    return 0;
}


int pal_cpf(const char* src, const char* dst)
{
    return CopyFile(src, dst, FALSE) ? 0 : -1;
}

int pal_pwd(char* buffer, int size)
{
    if (GetCurrentDirectory(size, buffer) == 0)
        return -1;

    return 0;
}

#endif  