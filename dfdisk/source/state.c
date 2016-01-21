/*+===================================================================
  File:     state.c

  Summary:  Implementation of state.h

  Author:   Jesse Buhagiar [@quaker762]

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#include <stdinc.h>
#include <state.h>
#include <window/terminal.h>

state_t current_state;
state_t states[4]; //Our 4 states!

state_t welcome()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");
    set_cur_pos(0, 2);
    printf("Please choose one of the following:\n\n");
    printf("1. Create logical partition.\n");
    printf("2. Display partition info.\n\n");
    printf("Choice:[ ]");

    set_cur_pos(8, 7);
    char choice;
    char lastchar;

    while((choice = getch()))
    {
        printf("%c", choice);
        set_cur_pos(8, 7);

        if(choice == '\r')
        {
            if(lastchar >= '1' && lastchar <= '4')
            {
                //REALLY REALLY YUCKY HACK TO USE ATOI!!!!
                char* c[1];
                c[0] = lastchar;

                int idx = atoi(c);
                change_state(idx);
                //I need to do something here I think

                //
                return;
            }
            else
            {
                set_cur_pos(0, 24);
                printf_col("Invalid Selection. Please choose from 1-4");
                set_cur_pos(8, 7); //This is a bit of a hack tbh...
            }
        }
            lastchar = choice;
    }
}

state_t create_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");

    char choice;
    char lastchar;

    while((choice = getch()))

        if(choice == 27)
        {
            change_state(0);
            return;
        }

}

state_t del_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");

    char choice;
    char lastchar;

    while((choice = getch()))

        if(choice == 27)
        {
            change_state(1);
            return;
        }

}

state_t view_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");

    char choice;
    char lastchar;

    while((choice = getch()))

        if(choice == 27)
        {
            change_state(2);
            return;
        }

}

void init_states()
{
    states[0] = &welcome;
    states[1] = &create_part;
    states[2] = &del_part;
    states[3] = &view_part;

    change_state(0);
}

void change_state(int state)
{
    current_state = NULL;
    current_state = states[state];
    current_state();
}

void register_state(int idx, state_t state)
{
    states[idx] = state;
}
