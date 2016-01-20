/*+===================================================================
  File:     state.h

  Summary:  dfdisk state manager

  Author:   Jesse Buhagiar [@quaker762]

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

typedef void (*state_t)();

void change_state(int state);
void register_state(int idx, state_t state);
void init_states();



#endif // STATE_H_INCLUDED
