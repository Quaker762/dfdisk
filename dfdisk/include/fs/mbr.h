/*+===================================================================
  File:     mbr.h

  Summary:  Master Boot Record functions/data structures

  Author:   Jesse Buhagiar [@quaker762]

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef MBR_H_INCLUDED
#define MBR_H_INCLUDED

#include <stdinc.h>

#pragma pack(1)
#define BYTES_PER_SECTOR 512

typedef uint8_t bool;


//PARTITION DATA STRUCTURE
typedef struct
{
    uint8_t     boot_flag; //Is this partition bootable??
    uint8_t     start_cyl; //Starting cylinder of partition
    uint8_t     start_head; //Starting head of partition
    uint8_t     start_sect; //Starting sector of partition
    uint8_t     part_type; //Partition type
    uint8_t     end_cyl; //Ending cylinder of partition
    uint8_t     end_head; //Ending head of partition
    uint8_t     end_sect; //Ending sector of partition
    uint32_t    start_sect_lba; //Starting sector LBA
    uint32_t    part_size; //Size of partition (in sectors)
}PARTITION;

//MBR DATA STRUCTURE
typedef struct
{
    uint8_t     bootstrap[446]; //446 bytes of bootstrap code
    PARTITION   partitions[4]; //4 partitions
    uint16_t    bootsig; //Boot signature. Usually AA55h
}MBR;

bool        mbr_bootable(PARTITION* part);
char*       mbr_gettype(PARTITION* part);
uint32_t    mbr_get_part_size(PARTITION* part);
char*       mbr_get_fsys(PARTITION* part);




#endif // MBR_H_INCLUDED
