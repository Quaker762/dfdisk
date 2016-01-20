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

state_t states[4]; //Our 4 states!

state_t welcome()
{
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
                int idx = atoi(lastchar);
                change_state(idx - 1);
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

}

void init_states()
{
    states[0] = welcome;
    states[1] = NULL;
    states[2] = NULL;
    states[3] = NULL;

    change_state(0);
}

void change_state(int state)
{
    states[state]();
}

void register_state(int idx, state_t state)
{
    states[idx] = state;
}
