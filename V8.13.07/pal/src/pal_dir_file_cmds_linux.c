/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-03-05
Date Last Modified: 2026-03-10
Module: PAL
File: pal_dir_file_cmds_linux.c
About: Linux implementation of PAL filesystem commands.
       Implements directory and file operations using
       POSIX filesystem APIs.
Revisions:
- 2026-03-05  Initial creation
- 2026-03-10  BUG FIX: pal(reset) typo corrected to pal_print(reset)
------------------------------------------------------------
*/
#include "pal_dir_file_cmds.h"
#ifdef OE_FILE_DIR_CMDS_LINUX
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>


/*
* -------- DIRECTORY COMMANDS --------
*/


int pal_mdr(const char* path)
{
    return mkdir(path, 0755);
}


int pal_rdr(const char* path)
{
    return rmdir(path);
}


int pal_cdr(const char* path)
{
    return chdir(path);
}


int pal_ldr(const char* path)
{
    DIR* d;
    struct dirent* dir;

    struct stat st;

    char fullpath[512];

    int row = 15;
    int page_count = 0;

    const char* p = path ? path : ".";

    d = opendir(p);

    if (!d)
        return -1;


    /* -------- HEADER -------- */
    pal_set_cursor(row, 60);
    pal_print(yellow bold"NAME");

    pal_set_cursor(row, 165);
    pal_print("TYPE");

    pal_set_cursor(row, 180);
    pal_print("SIZE(kb)");
    pal_print(reset);
    row++;

    pal_set_cursor(row++, 60);
    pal_print(red bold "--------------------------------------------------------------------------------------------------------------------------------"reset green);


    while ((dir = readdir(d)) != NULL)
    {
        if (pal_strcmp(dir->d_name, ".") == 0 || pal_strcmp(dir->d_name, "..") == 0)
            continue;

        /* ---- FULL PATH ---- */

        pal_strcpy(fullpath, p);
        pal_strcat(fullpath, "/");
        pal_strcat(fullpath, dir->d_name);

        stat(fullpath, &st);


        /* ---- NAME (truncate to 100 chars) ---- */

        char namebuf[101];
        int i;

        for (i = 0; i < 100 && dir->d_name[i] != 0; i++)
            namebuf[i] = dir->d_name[i];

        namebuf[i] = 0;

        pal_set_cursor(row, 60);
        pal_print(namebuf);


        /* ---- TYPE ---- */

        if (S_ISDIR(st.st_mode))
        {
            pal_set_cursor(row, 165);
            pal_print("DIR");

            pal_set_cursor(row, 180);
            pal_print("-");
        }
        else
        {
            char sizebuf[32];

            pal_itoa(st.st_size, sizebuf);

            pal_set_cursor(row, 165);
            pal_print("FILE");

            pal_set_cursor(row, 180);
            pal_print(sizebuf);
        }
        pal_print(reset);

        row++;
        page_count++;


        /* ---- PAGE BREAK ---- */

        if (page_count == 30)
        {
            pal_set_cursor(row + 1, 60);
            pal_print(red bold "Press Enter for next page..."reset);
            pal_pause();

            pal_clear_screen();

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
            pal_print(red bold"--------------------------------------------------------------------------------------------------------------------------------"green);
        }

    }

    closedir(d);


    /* ---- FINAL RETURN ---- */

    pal_set_cursor(row + 1, 60);
    pal_print(red bold"Press Enter to return to prompt..." reset);
    pal_pause();

    return 0;
}

int pal_rnmdr(const char* oldname, const char* newname)
{
    return rename(oldname, newname);
}


int pal_mvdr(const char* src, const char* dst)
{
    return rename(src, dst);
}


int pal_cpdr(const char* src, const char* dst)
{
    char cmd[512];

    snprintf(cmd, sizeof(cmd), "cp -r \"%s\" \"%s\"", src, dst);

    return system(cmd);
}


/*
* -------- FILE COMMANDS --------
*/


int pal_rmf(const char* file)
{
    return remove(file);
}


int pal_rnmf(const char* oldname, const char* newname)
{
    return rename(oldname, newname);
}


int pal_mvf(const char* src, const char* dst)
{
    return rename(src, dst);
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
    FILE* fs = fopen(src, "rb");
    FILE* fd = fopen(dst, "wb");

    char buffer[4096];
    size_t bytes;

    if (!fs)
        return -1;

    if (!fd)
    {
        fclose(fs);
        return -1;
    }

    while ((bytes = fread(buffer, 1, sizeof(buffer), fs)) > 0)
        fwrite(buffer, 1, bytes, fd);

    fclose(fs);
    fclose(fd);

    return 0;
}
int pal_pwd(char* buffer, int size)
{
    if (getcwd(buffer, size) == NULL)
        return -1;

    return 0;
}
#endif