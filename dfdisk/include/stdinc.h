/*+===================================================================
  File:     stdinc.h

  Summary:  Standard include files

  Author:   Jesse Buhagiar [@quaker762]

  Rev History:

----------------------------------------------------------------------
  Copyright 2015-2016 Radial Technologies, Pty Ltd
===================================================================+*/
#ifndef STDINC_H_INCLUDED
#define STDINC_H_INCLUDED

#include <stdint.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

uint64_t query_disk_size(FILE* file);

#endif // STDINC_H_INCLUDED
