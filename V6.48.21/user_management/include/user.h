/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-02-22
Module: User Management
File: user.h
About: Original OE user management system converted
       to C with binary file storage.
Revisions:
- 2026-02-21  Switched to binary storage (user.bd, pwd.bd)
- 2026-02-21  Removed C++ dependencies
- 2026-02-22  Added user_enter_guest() and user_exists()
------------------------------------------------------------
*/

#ifndef USER_H
#define USER_H

/* -------- FILES -------- */
#define USER_FILE  "user.bd"
#define PASS_FILE  "pwd.bd"

/* -------- LIMITS -------- */
#define USERNAME_MAX 64
#define PASSWORD_MAX 64

/* -------- GLOBAL STATE -------- */
extern char current_user[USERNAME_MAX];
extern int reg_status;  /* 0 = normal user, 1 = guest */

/* -------- ORIGINAL OE FUNCTIONS -------- */
void login(void);
void add_user(void);
void password_change(void);
void userid_change(void);

/* -------- GUEST MODE -------- */
void user_enter_guest(void);

/* -------- UTILITY -------- */
int user_exists(void);

#endif