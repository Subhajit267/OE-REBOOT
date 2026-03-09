/*
------------------------------------------------------------
Author: Subhajit Halder
Date Created: 2026-02-21
Date Last Modified: 2026-03-10
Module: Help Documentation
File: prompt_help.c
About: Displays help information for main prompt
Revisions:
- 2026-02-21  Converted legacy gotoxy help to PAL-based layout
- 2026-03-05  Added filesystem command documentation
- 2026-03-05  Improved layout and color scheme
- 2026-03-10  Added notepad command documentation
------------------------------------------------------------
*/

#include "pal.h"
#include "help.h"

void help_show_prompt(void)
{
	int row = 13, column = 78;
	pal_set_cursor(row++, column);
	pal_print(green bold "Welcome to PROMPT HELP Documentation Ver: 2.1" reset);

	pal_set_cursor(row++, column);
	pal_print(yellow bold "--------------------------------------------" reset);


	/* -------- INSTALLABLE APPLICATIONS -------- */

	pal_set_cursor(row++, column);
	pal_print(yellow bold "Installable Applications:" reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tTicTacToe        " purple ": Two player or computer TicTacToe game." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tQuiz             " purple ": Multiround quiz system with scoreboard." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tTemp_Conv        " purple ": Convert Celsius, Fahrenheit and Kelvin." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\teqn_solve        " purple ": Solve linear equations in two variables." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tquad_eqn_solve   " purple ": Solve quadratic equations." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tatc              " purple ": Area of Triangle calculator." reset);


	/* -------- SYSTEM COMMANDS -------- */

	row++;

	pal_set_cursor(row++, column);
	pal_print(yellow bold "System Commands:" reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\texit             " purple ": Exit the OE environment." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tver              " purple ": Display OE version." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tlogin            " purple ": Re-login to OE system." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tsettings         " purple ": Modify OE settings." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tregistryeditor   " purple ": Enter registry editor mode." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tsysteminfo       " purple ": Display system hardware information." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tcalculator       " purple ": Evaluate mathematical expressions." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tnotepad [file]   " purple ": Open text editor. Optionally pass a filename." reset);


	/* -------- APPLICATION MANAGEMENT -------- */

	row++;

	pal_set_cursor(row++, column);
	pal_print(yellow bold "Application Management:" reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tinst_all         " purple ": Install all available applications." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tunst_all         " purple ": Uninstall all installed applications." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tinst_<appname>   " purple ": Install specific application." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tunst_<appname>   " purple ": Uninstall specific application." reset);


	/* -------- FILESYSTEM COMMANDS -------- */

	row++;

	pal_set_cursor(row++, column);
	pal_print(yellow bold "Filesystem Commands:" reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tmdr <n>          " purple ": Create directory." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\trdr <n>          " purple ": Remove directory." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tldr              " purple ": List directory contents." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tcdr <dir>        " purple ": Change directory." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tcdr ..           " purple ": Move to parent directory." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tpwd              " purple ": Show current working directory." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\trmf <file>       " purple ": Remove file." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tcpf <src> <dst>  " purple ": Copy file." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\trdf <file>       " purple ": Read file contents." reset);

	pal_set_cursor(row++, column);
	pal_print(cyan bold "\tmvf <src> <dst>  " purple ": Move file." reset);

	pal_pause();

}