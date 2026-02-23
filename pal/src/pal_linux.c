/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-20
Date Last Modified: 2026-02-23
Module: PAL
File: pal_linux.c
About: Linux implementation of PAL with echo control.
Revisions:
- 2026-02-20  Initial ANSI console implementation
- 2026-02-21  Added string wrapper functions
- 2026-02-21  Added file abstraction API
- 2026-02-22  Added pal_readline, pal_get_bg
- 2026-02-23  Added pal_set_echo, pal_getchar_raw, and pal_srand/pal_rand
------------------------------------------------------------
*/

#include "pal.h"
#ifdef OE_PLATFORM_LINUX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

struct pal_file { FILE* fp; };

static struct termios original_termios;
static int termios_saved = 0;

/* Random generator state */
static unsigned long next = 1;

/* ================= INIT ================= */
void pal_init(void)
{
    pal_set_echo(0);   /* disable terminal echo globally */
    /* Additional init if needed */
}

/* ================= CONSOLE ================= */
void pal_print(const char* text) { printf("%s", text); fflush(stdout); }
void pal_println(const char* text) { printf("%s\n", text); fflush(stdout); }
void pal_putchar(char c) { putchar(c); fflush(stdout); }

char pal_getchar(void) { return getchar(); }
char pal_getchar_raw(void) { return getchar(); }  /* same as getchar in cooked mode? but we have disabled echo, so it's raw enough */

void pal_pause(void) { while (getchar() != '\n'); }
void pal_clear_screen(void) { printf("\033[2J\033[H"); fflush(stdout); }
void pal_set_cursor(int row, int col) { printf("\033[%d;%dH", row, col); fflush(stdout); }
void pal_sleep(double seconds) { sleep(seconds); }

void pal_readline(char* buffer, int max_len)
{
    int i = 0;
    char c;
    while (i < max_len - 1) {
        c = pal_getchar_raw();
        if (c == '\n' || c == '\r') break;
        if (c == 8 || c == 127) {
            if (i > 0) { i--; printf("\b \b"); fflush(stdout); }
        }
        else {
            buffer[i++] = c;
            putchar(c); fflush(stdout);
        }
    }
    buffer[i] = '\0';
    putchar('\n');
    fflush(stdout);
}

/* ================= ECHO CONTROL ================= */
void pal_set_echo(int enable)
{
    if (!termios_saved) {
        tcgetattr(STDIN_FILENO, &original_termios);
        termios_saved = 1;
    }

    struct termios newt = original_termios;
    if (enable)
        newt.c_lflag |= ECHO;
    else
        newt.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

/* ================= STRING ================= */
size_t pal_strlen(const char* str) { return strlen(str); }
int pal_strcmp(const char* s1, const char* s2) { return strcmp(s1, s2); }
char* pal_strcpy(char* dest, const char* src) { return strcpy(dest, src); }
int pal_atoi(const char* str) { return atoi(str); }
void pal_itoa(int value, char* buffer) { sprintf(buffer, "%d", value); }

/* ================= RANDOM ================= */
void pal_srand(unsigned int seed) { next = seed; }
int pal_rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

/* ================= FILE ================= */
pal_file_t* pal_file_open_read(const char* filename)
{
    pal_file_t* f = malloc(sizeof(pal_file_t));
    if (!f) return NULL;
    f->fp = fopen(filename, "rb");
    if (!f->fp) { free(f); return NULL; }
    return f;
}
pal_file_t* pal_file_open_write(const char* filename)
{
    pal_file_t* f = malloc(sizeof(pal_file_t));
    if (!f) return NULL;
    f->fp = fopen(filename, "wb");
    if (!f->fp) { free(f); return NULL; }
    return f;
}
int pal_file_read(pal_file_t* file, void* buffer, int size)
{
    return (int)fread(buffer, 1, size, file->fp);
}
int pal_file_write(pal_file_t* file, const void* buffer, int size)
{
    return (int)fwrite(buffer, 1, size, file->fp);
}
void pal_file_close(pal_file_t* file) { if (file) { fclose(file->fp); free(file); } }
int pal_file_exists(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (!f) return 0;
    fclose(f);
    return 1;
}

/* ================= BACKGROUND COLORS ================= */
const char* pal_get_bg(int color)
{
    static const char* codes[] = {
        "", "\x1B[41m", "\x1B[42m", "\x1B[43m", "\x1B[44m",
        "\x1B[45m", "\x1B[46m", "\x1B[47m", "\x1B[100m",
        "\x1B[101m", "\x1B[102m", "\x1B[103m", "\x1B[104m",
        "\x1B[105m", "\x1B[106m", "\x1B[107m"
    };
    if (color < 1 || color > 15) return "\x1B[44m";
    return codes[color];
}

#endif