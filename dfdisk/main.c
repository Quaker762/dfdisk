#include <stdio.h>
#include <stdlib.h>
#include <window/terminal.h>

int main()
{
    titlebar("dfdisk Fixed Disk Setup");

    set_cur_pos(0, 2);
    printf("Please choose one of the following:\n\n");
    printf("1. Create logical partition.\n");
    printf("2. Display partition info.\n\n");
    printf("Choice: ");

    char choice = getchar();;

    while(1)
    {
        //TODO: Fixme! This is REALLY gross...
       if(choice == '1' || choice == '2' || choice == '3')
        break;
    }

    return 0;
}
