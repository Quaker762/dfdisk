/*+===================================================================
  File:     terminal.c

  Summary:  Terminal Stuff for Windows

  Author:   Jesse Buhagiar [@Quaker762]

  Rev History:
        18/1/2016: Initial Revision

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#include <stdio.h>
#include <string.h>
#include <windows.h> //WE NEED TO CHECK FOR WINDOWS HERE!!!!!
#include <window/terminal.h>

/* Set the cursor position */
void set_cur_pos(int x, int y)
{
    COORD   loc = {x, y}; //The COORD structure we want to go to.
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Get the current window handle

    SetConsoleCursorPosition(hConsole, loc);
}

/* Create a titlebar at row 0*/
void titlebar(const char* str)
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Get the current window handle
    int     len = strlen(str);
    int     x = (80 - len) / 2; //Centre the text
    int     attr = (7 << 4) | 0;



    SetConsoleTextAttribute(hConsole, attr);

    //REALLY REALLY HACKY!!
    int i;
    for(i = 0; i < x; i++)
    {
        putchar(' ');
    }

    set_cur_pos(x, 0); //Reset the cursor
    printf(str);

    for(i = x + len; i < 80; i++)
    {
        putchar(' ');
    }

    SetConsoleTextAttribute(hConsole, 7); //Reset original console colours
}

/* Clear the screen of all text.*/
void clear()
{
    system("cls");

    set_cur_pos(0, 0);
}

/* Coloured Printf */
void printf_col(const char* str)
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Get the current window handle

    SetConsoleTextAttribute(hConsole, 0xF); //Reset original console colours
    printf("%s", str);
    SetConsoleTextAttribute(hConsole, 7); //Reset original console colours
}

/* Print a centered string */
void printf_cent(const char* str, int y)
{
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Get the current window handle
    int     len = strlen(str);
    int     x = (80 - len) / 2; //Centre the text

    set_cur_pos(x, y);
    printf("%s\n", str);
}



