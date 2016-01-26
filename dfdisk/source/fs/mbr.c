/*+===================================================================
  File:     mbr.c

  Summary:

  Author:

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#include <fs/mbr.h>

const char* part_id[] =
{
    "UKNWN",
    "FAT12",
    "XENIX",
    "XENIX",
    "FAT16",
    "     ",
    "FAT16",
    "NTFS"
};


bool mbr_bootable(PARTITION* part)
{
    if(part->boot_flag)
        return 1;

    return 0;
}

char* mbr_gettype(PARTITION* part)
{
    if(part->part_type == 0x06 || part->part_type == 0x04)
        return "PRI DOS";

    if(part->part_type == 0x05)
        return "EXT DOS";

    return "       ";
}

char* mbr_get_fsys(PARTITION* part)
{
    return part_id[part->part_type];
}


