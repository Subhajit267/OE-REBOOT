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
#define OE_VERSION_MINOR   13
#define OE_VERSION_PATCH   07


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
#define OE_COPYRIGHT       "(C) 2026 Subhajit Halder"


/* ================= BUILD INFORMATION ================= */

#define OE_BUILD_DATE      "10/03/2026"
#define OE_BUILD_TIME      "2:47 am"


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

/* Guest mode info */
#define OE_GUEST_MESSAGE \
"Only available commands are install, login, registryeditor, notepad, calculator, settings and exit"

/* Normal prompt hint */
#define OE_USER_MESSAGE \
"Type help to get list of commands"


#endif