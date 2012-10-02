#ifndef __ts8820DIORaw_H
#define __ts8820DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct ts8820DIORaw ts8820DIORaw;

struct ts8820DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
  int adrs;
};

void *ts8820DIORawInit(ts8820DIORaw *,void *bus);
void ts8820DIORawFini(ts8820DIORaw *);
void ts8820DIORawDirSet(ts8820DIORaw *,int num,int asOutput);
void ts8820DIORawDataSet(ts8820DIORaw *,int num,int asHigh);
int ts8820DIORawDirGet(ts8820DIORaw *,int num);
int ts8820DIORawDataGet(ts8820DIORaw *,int num);
unsigned ts8820DIORawCount(ts8820DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
