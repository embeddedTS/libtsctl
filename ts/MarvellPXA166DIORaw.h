#ifndef __MarvellPXA166DIORaw_H
#define __MarvellPXA166DIORaw_H
#include "DIORaw.h"
#include "Bus.h"

typedef struct MarvellPXA166DIORaw MarvellPXA166DIORaw;

struct MarvellPXA166DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *MarvellPXA166DIORawInit(MarvellPXA166DIORaw *,void *bus);
void MarvellPXA166DIORawFini(MarvellPXA166DIORaw *);
void MarvellPXA166DIORawDirSet(MarvellPXA166DIORaw *,int num,int asOutput);
void MarvellPXA166DIORawDataSet(MarvellPXA166DIORaw *,int num,int asHigh);
int MarvellPXA166DIORawDirGet(MarvellPXA166DIORaw *,int num);
int MarvellPXA166DIORawDataGet(MarvellPXA166DIORaw *,int num);
unsigned MarvellPXA166DIORawCount(MarvellPXA166DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
