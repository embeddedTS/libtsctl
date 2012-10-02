#ifndef __ts8900DIORaw_H
#define __ts8900DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct ts8900DIORaw ts8900DIORaw;

struct ts8900DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
  int adrs;
};

void *ts8900DIORawInit(ts8900DIORaw *,void *bus);
void ts8900DIORawFini(ts8900DIORaw *);
void ts8900DIORawDirSet(ts8900DIORaw *,int num,int asOutput);
void ts8900DIORawDataSet(ts8900DIORaw *,int num,int asHigh);
int ts8900DIORawDirGet(ts8900DIORaw *,int num);
int ts8900DIORawDataGet(ts8900DIORaw *,int num);
unsigned ts8900DIORawCount(ts8900DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
