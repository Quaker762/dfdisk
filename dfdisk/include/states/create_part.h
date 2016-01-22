/*+===================================================================
  File:

  Summary:

  Author:

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef CREATE_PART_H_INCLUDED
#define CREATE_PART_H_INCLUDED

state_t create_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");

    char choice;

    while((choice = getch()))
    {
        if(choice == 27)
        {
            change_state(0);
            break;
        }

    }

    return NULL;
}

#endif // CREATE_PART_H_INCLUDED
