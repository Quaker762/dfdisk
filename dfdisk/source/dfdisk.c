/*+===================================================================
  File:     dfdisk.c

  Summary:  dfdisk. DOSX FDISK (in Windows!!)
            Used to initialise and write virtual volume images!

  Author:   Jesse Buhagiar [@quaker762]

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#include <state.h>
#include <window/terminal.h>

int main()
{
    titlebar("dfdisk Fixed Disk Setup");
    init_states();

    return 0;
}
