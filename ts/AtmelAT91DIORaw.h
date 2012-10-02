#ifndef __AtmelAT91DIORaw_H
#define __AtmelAT91DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct AtmelAT91DIORaw AtmelAT91DIORaw;

struct AtmelAT91DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *AtmelAT91DIORawInit(AtmelAT91DIORaw *,void *bus);
void AtmelAT91DIORawFini(AtmelAT91DIORaw *);
void AtmelAT91DIORawDirSet(AtmelAT91DIORaw *,int num,int asOutput);
void AtmelAT91DIORawDataSet(AtmelAT91DIORaw *,int num,int asHigh);
int AtmelAT91DIORawDirGet(AtmelAT91DIORaw *,int num);
int AtmelAT91DIORawDataGet(AtmelAT91DIORaw *,int num);
unsigned AtmelAT91DIORawCount(AtmelAT91DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
