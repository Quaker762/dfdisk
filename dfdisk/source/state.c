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
#include <fs/mbr.h>

#include <states/welcome.h>
#include <states/create_part.h>
#include <states/del_part.h>
#include <states/view_part.h>

state_t current_state;
state_t states[4]; //Our 4 states!


void init_states()
{
    states[0] = welcome;
    states[1] = create_part;
    states[2] = del_part;
    states[3] = view_part;

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
