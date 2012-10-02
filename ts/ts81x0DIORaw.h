#ifndef __ts81x0DIORaw_H
#define __ts81x0DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct ts81x0DIORaw ts81x0DIORaw;

struct ts81x0DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
  int adrs;
};

void *ts81x0DIORawInit(ts81x0DIORaw *,void *bus);
void ts81x0DIORawFini(ts81x0DIORaw *);
void ts81x0DIORawDirSet(ts81x0DIORaw *,int num,int asOutput);
void ts81x0DIORawDataSet(ts81x0DIORaw *,int num,int asHigh);
int ts81x0DIORawDirGet(ts81x0DIORaw *,int num);
int ts81x0DIORawDataGet(ts81x0DIORaw *,int num);
unsigned ts81x0DIORawCount(ts81x0DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
