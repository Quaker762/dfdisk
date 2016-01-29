/*+===================================================================
  File:     mbr.c

  Summary:

  Author:

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#include <fs/mbr.h>

char* part_id[] =
{
    "UKNWN",
    "FAT12",
    "XENIX",
    "XENIX",
    "FAT16",
    "     ",
    "FAT16",
    "NTFS "
};


bool mbr_bootable(PARTITION* part)
{
    if(part->boot_flag)
        return 1;

    return 0;
}

char* mbr_gettype(PARTITION* part)
{
    if(part->part_type == MS_DOS || part->part_type == MS_DOS2)
        return "PRI DOS";

    if(part->part_type == MS_DOS_EXT)
        return "EXT DOS";

    if(part->part_type == LINUX_FS)
        return "LINUXFS";

    return "       ";
}

char* mbr_get_fsys(PARTITION* part)
{
    //Sorta hacked together...
    if(part->part_type == LINUX_FS)
        return "extfs";

    return part_id[part->part_type];
}


