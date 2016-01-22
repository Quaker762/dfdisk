/*+===================================================================
  File:

  Summary:

  Author:

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef WELCOME_H_INCLUDED
#define WELCOME_H_INCLUDED

state_t welcome()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");
    set_cur_pos(0, 23);
    printf_col("Press ESC to exit.");
    set_cur_pos(0, 2);
    printf("Please choose one of the following:\n\n");
    printf("1. Create logical partition.\n");
    printf("2. Delete logical partition.\n");
    printf("3. Display partition info.\n\n");
    printf("Choice:[ ]");
    set_cur_pos(8, 8);

    char choice;
    char lastchar;

    while((choice = getch()))
    {
        printf("%c", choice);
        set_cur_pos(8, 8);

        if(choice == '\r')
        {
            if(lastchar >= '1' && lastchar <= '3')
            {
                //REALLY REALLY YUCKY HACK TO USE ATOI!!!!
                char* c[1];
                c[0] = lastchar;

                int idx = atoi(c);
                change_state(idx);
                break;
            }
            else
            {
                set_cur_pos(0, 23);
                printf_col("Invalid Selection. Please choose from 1-3");
                set_cur_pos(8, 8); //This is a bit of a hack tbh...
            }
        }
        if(choice == 27) //Escape key pressed.
        {
            break;
        }
            lastchar = choice;
    }
}

#endif // WELCOME_H_INCLUDED
