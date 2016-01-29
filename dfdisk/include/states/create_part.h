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

/*  Create a primary DOS partition in the MBR
    This currently does not set any CHS values.. */
void create_primary()
{
    MBR         mbr; //Our MBR
    PARTITION   new_part; //Partition we are creating
    char        tmp[10]; //Size of the partition we are creating (in sectors)

    uint32_t    partition_size;
    uint32_t    part_size_lba;
    int         part_num; //Partition number we are dealing with
    uint32_t    disk_left;
    uint32_t    disk_size;

    FILE* image = fopen("dos.img", "rb+");

    rewind(image);
    disk_size = query_disk_size(image) / (1024 * 1024); //Get the size of the disk
    disk_left = disk_size;

    rewind(image);
    fread(&mbr, sizeof(MBR), 1, image); //Read the current mbr into our mbr struct

    int i;
    for(i = 0; i < 4; i++)
    {
        if(mbr.partitions[i].part_size > 0)
        {
            disk_left -= (mbr.partitions[i].part_size * BYTES_PER_SECTOR) / (1024 * 1024);
            continue;
        }
        else
        {
            part_num = i;
            break;
        }
    }


    //Zero out the partition we are creating
    memset(&new_part, 0x00, sizeof(PARTITION));

    //If we have no disk space left, let's return!
    if(disk_left <= 0)
    {
        printf("\nAll disk space occupied!\n\n");
        printf_col("Press any key to return!");

        char key;
        while((key = getch()) <= ' ');
        change_state(0);
        return;
    }

    printf("\nPartition Size(MiB) [max = %d]: ", disk_left);
    gets(tmp);
    partition_size = atoi(tmp);

    if(atoi(tmp) > disk_size || atoi(tmp) > disk_left)
    {
        printf("Partition is too large!\n");
        create_primary();
        return;
    }

    printf("File System?");
    gets(tmp);

    if(strcmp(tmp, "linux") == 0)
        new_part.part_type = LINUX_FS;
    else
        new_part.part_type = MS_DOS;

    printf("Boot? (y/n)");
    while(gets(tmp))
    {
        if(strcmp(tmp, "y") == 0)
        {
            new_part.boot_flag = 0x80; //No boot
            break;
        }
        else if(strcmp(tmp, "n") == 0)
        {
            new_part.boot_flag = 0x00; //No boot
            break;
        }
        printf("Boot? (y/n)");
        continue;
    }

    //We need to do some conversions here. Size to CHS and size to LBA
    part_size_lba = (partition_size * (1024 * 1024)) / BYTES_PER_SECTOR;

    new_part.start_sect_lba = ((disk_size - disk_left) * (1024 * 1024)) / BYTES_PER_SECTOR;
    new_part.part_size = part_size_lba;

    //We now set the partition in the MBR
    mbr.partitions[part_num] = new_part;
    rewind(image);
    fwrite(&mbr, sizeof(MBR), 1, image);
    fclose(image);
    return;
}

void create_ext()
{
    return;
}

state_t create_part()
{
    clear();
    titlebar("dfdisk Fixed Disk Setup");

    set_cur_pos(0, 2);
    printf("Please choose one of the following:\n\n");
    set_cur_pos(0, 4);
    printf("1. Create Primary Partition\n\n");
    //printf("2. Create Extended DOS Partition\n\n");
    printf("Choice: [ ]");

    set_cur_pos(0, 23);
    printf_col("Press ESC to return");
    set_cur_pos(9, 6);

    char choice;
    char lastchar;
    while((choice = getch()))
    {
        if(choice == '\r')
        {
            if(lastchar == '1')
                create_primary();
            if(lastchar == '2')
                create_ext();
        }

        if(choice == 27)
        {
            change_state(0);
            break;
        }

        printf("%c", choice);
        set_cur_pos(9, 6);
        lastchar = choice;
    }

    return NULL;
}

#endif // CREATE_PART_H_INCLUDED
