/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-20
Date Last Modified: 2026-02-22
Module: PAL (Platform Abstraction Layer)
File: pal.h
About: Platform-independent console abstraction layer.
       ONLY module allowed to use standard C library.
Revisions:
- 2026-02-20  Initial console abstraction
- 2026-02-21  Added string wrapper API
- 2026-02-21  Added file abstraction API
- 2026-02-22  Added pal_readline and pal_get_bg
------------------------------------------------------------
*/

#ifndef PAL_H
#define PAL_H

#include <stddef.h>

/* ================= PLATFORM ================= */

#ifdef _WIN32
    #define OE_PLATFORM_WINDOWS
       /* Reduce Windows header bloat and avoid pulling in msxml.h */
    #define WIN32_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #define NOMINMAX
    /* Disable deprecation warnings for standard C functions */
    //#define _CRT_SECURE_NO_WARNINGS
   // #define _CRT_NONSTDC_NO_DEPRECATE
#else
    #define OE_PLATFORM_LINUX
#endif

/* ================= INIT ================= */

void pal_init(void);

/* ================= CONSOLE ================= */

void pal_print(const char* text);
void pal_println(const char* text);
void pal_putchar(char c);
char pal_getchar(void);
void pal_pause(void);
void pal_clear_screen(void);
void pal_set_cursor(int row, int col);
void pal_sleep(double seconds);
void pal_readline(char* buffer, int max_len);  /* Read a line with echo/backspace */
void pal_exit(void);
/* ================= STRING WRAPPERS ================= */

size_t pal_strlen(const char* str);
int    pal_strcmp(const char* s1, const char* s2);
char* pal_strcpy(char* dest, const char* src);
int    pal_atoi(const char* str);
void pal_itoa(int value, char* buffer);

/* ================= RANDOM NUMBER GENERATOR ================= */
void pal_srand(unsigned int seed);
int  pal_rand(void);  /* returns a pseudo‑random int in range 0..32767 */

/* ================= FILE API ================= */

typedef struct pal_file pal_file_t;

pal_file_t* pal_file_open_read(const char* filename);
pal_file_t* pal_file_open_write(const char* filename);

int  pal_file_read(pal_file_t* file, void* buffer, int size);
int  pal_file_write(pal_file_t* file, const void* buffer, int size);

void pal_file_close(pal_file_t* file);
int  pal_file_exists(const char* filename);

/* ================= BACKGROUND COLORS ================= */

/* Returns ANSI background code for color number (1-15) */
const char* pal_get_bg(int color);

/* ================= STYLE MACROS ================= */

/* Text styles */
#define bold        "\033[1m"
#define underline   "\033[4m"
#define reset       "\033[0m"
#define invisible   "\x1B[8m"

/* Foreground colors */
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define purple  "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"

/* Bright foreground */
#define RED     "\033[91m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define BLUE    "\033[94m"

/* Background colors (B1–B15) */
#define B1  "\x1B[41m"
#define B2  "\x1B[42m"
#define B3  "\x1B[43m"
#define B4  "\x1B[44m"
#define B5  "\x1B[45m"
#define B6  "\x1B[46m"
#define B7  "\x1B[47m"
#define B8  "\x1B[100m"
#define B9  "\x1B[101m"
#define B10 "\x1B[102m"
#define B11 "\x1B[103m"
#define B12 "\x1B[104m"
#define B13 "\x1B[105m"
#define B14 "\x1B[106m"
#define B15 "\x1B[107m"

/* ================= ECHO CONTROL ================= */
void pal_set_echo(int enable);   /* 1 = echo on, 0 = echo off */

/* Raw character input without any processing (for manual echo) */
char pal_getchar_raw(void);

/* ================= BOOLEAN TYPE ================= */

#ifndef OE_BOOL_DEFINED
#define OE_BOOL_DEFINED
typedef enum { false = 0, true = 1 } bool;
#endif

#endif