/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-03-10
Date Last Modified: 2026-03-10
Module: System Core
File: branding.h
About: Centralised branding and version information for OE.

       All system-wide identity strings are defined here:
         - System name
         - Version
         - Codename
         - Developer
         - Build information
         - Standard UI text messages

Revisions:
- 2026-03-10  Initial implementation
- 2026-08-26  BUG FIX: OE_GUEST_MESSAGE was 88 visible chars, printed
              on one row at col 19 (UI_PROMPT_MSG_COL) in prompt.c —
              overflowed the col-79 edge by ~27 columns on every
              guest-mode screen. Split into two shorter lines the
              caller prints on two separate rows.
------------------------------------------------------------
*/

#ifndef OE_BRANDING_H
#define OE_BRANDING_H


/* ================= SYSTEM IDENTITY ================= */

#define OE_NAME            "Operating Environment"
#define OE_SHORT_NAME      "OE"
#define OE_BUILD_TYPE      "(Pre Release Build C and PAL Based)"


/* ================= VERSION ================= */

/*
Version format:
  major.minor.patch
*/
#define OE_VERSION_MAJOR   8
#define OE_VERSION_MINOR   42
#define OE_VERSION_PATCH   28


/* ---- internal helpers for string conversion ---- */

#define OE_STR_HELPER(x) #x
#define OE_STR(x) OE_STR_HELPER(x)


/* ---- final version string ---- */

#define OE_VERSION \
OE_STR(OE_VERSION_MAJOR) "." \
OE_STR(OE_VERSION_MINOR) "." \
OE_STR(OE_VERSION_PATCH)

/* ================= DEVELOPER INFO ================= */

#define OE_DEVELOPER       "Subhajit Halder"
#define OE_COPYRIGHT       "(C) 2026 Operating Environment"


/* ================= BUILD INFORMATION ================= */

#define OE_BUILD_DATE      "12/04/2026"
#define OE_BUILD_TIME      "8:40 pm"


/* ================= DERIVED STRINGS ================= */

//#define OE_FULL_NAME       OE_NAME " " OE_CODENAME
#define OE_VERSION_STRING  OE_NAME " ver: " OE_VERSION


/* ================= UI TEXT STRINGS ================= */

/* Startup / welcome */
#define OE_WELCOME_TEXT \
"Welcome to Operating Environment"

/* Shutdown message */
#define OE_SHUTDOWN_TEXT \
"Program is shutting down. Thank you for using."

/* Guest mode info — split across two lines, see caller (prompt.c) */
#define OE_GUEST_MESSAGE_LINE1 \
"Available commands: install, login, registryeditor,"
#define OE_GUEST_MESSAGE_LINE2 \
"notepad, calculator, exit"

/* Normal prompt hint */
#define OE_USER_MESSAGE \
"Type help to get list of commands"
/*

FUTURE PLAN:
___________

Adding kernel
Building bootloader
HAL ( arm, arm64 x86, x64)

*/

#endif