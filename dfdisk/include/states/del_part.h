/*+===================================================================
  File:

  Summary:

  Author:

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef DEL_PART_H_INCLUDED
#define DEL_PART_H_INCLUDED

state_t del_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");    //Print out the partition info here

    printf_cent("Partition Info\n", 4);
    printf("    Partition   Flags    Type    Vol Label    Size    System    Disk Use\n");

    FILE* img = fopen("dos.img", "rb+"); //Open the
    MBR mbr;

    fread(&mbr, 512, 1, img); //Read sector 1
    rewind(img);

    uint32_t disk_size      = query_disk_size(img);
    uint32_t disk_sizemb    = disk_size / (1024 * 1024);
    char* boot = "    ";

    uint8_t i;
    uint8_t nparts;
    for(i = 0; i < 4; i++)
    {
        if(mbr.partitions[i].part_size > 0)
        {
            nparts++;
            if(mbr_bootable(&mbr.partitions[i]))
                boot = "boot";

            uint32_t part_size = (mbr.partitions[i].part_size * BYTES_PER_SECTOR) / (1024 * 1024); //MiB size of partition
            uint32_t disk_usage = (part_size * 100) / disk_sizemb;

            printf("        %d       %s   %s               %dMiB    %s       %d%% \n", i + 1, boot, mbr_gettype(&mbr.partitions[i]), part_size, mbr_get_fsys(&mbr.partitions[i]), disk_usage);
        }
    }

    set_cur_pos(0, 10);
    printf_col("Which partition would you like to delete: [ ]");
    set_cur_pos(0, 23);
    printf_col("Press ESC to return");
    set_cur_pos(43, 10);

    char choice;
    char lastchar;

    //We have no partitions to delete! display a message
    if(nparts == 0)
    {
        printf("\n\nNo Partitions to delete! Press any key to return!");

        while((choice = getch()) <= ' ');

        change_state(0);
    }

    while((choice = getch()))
    {
        char* c[1];
        c[0] = lastchar;

        printf("%c", choice);
        set_cur_pos(43, 10);

        if(choice == 27)
        {
            change_state(0);
            break;
        }

        if(choice == '\r')
        {
            int part_num = atoi(c);

            if(lastchar >= '1' && lastchar <= '4')
            {
                mbr.partitions[part_num - 1] = (const PARTITION){0x00};

                printf_col("\n\nWARNING! ");
                printf(" THIS WILL ERASE THIS PARTITION FROM THE DISK!\nDATA WILL EXIST, BUT WILL BE INVISIBLE! DELETE? (y/n)");

                while((choice = getch()))
                {
                    if(choice == 'y' || choice == 'Y')
                        break;
                    else if(choice == 'n' || choice == 'N')
                        change_state(0);
                }

                //Let's rewind the file to the beginning!
                rewind(img);
                fwrite(&mbr, sizeof(MBR), 1, img);
                fclose(img);

                printf_col("\n\nDone! Press any key to return!!");

                //Await key press
                while((choice = getch()) <= ' ');

                change_state(0);
                break;
            }
        }
        lastchar = choice;
    }

    return NULL;
}

#endif // DEL_PART_H_INCLUDED
