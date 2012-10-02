#ifndef __tsRelay8DIORaw_H
#define __tsRelay8DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct tsRelay8DIORaw tsRelay8DIORaw;

struct tsRelay8DIORaw {
  DIORaw;
  int deferlockW,deferlockR;
  Bus *sub;
  int adrs;
};

void *tsRelay8DIORawInit(tsRelay8DIORaw *,void *bus,int adrs);
void tsRelay8DIORawFini(tsRelay8DIORaw *);
void tsRelay8DIORawDirSet(tsRelay8DIORaw *,int num,int asOutput);
void tsRelay8DIORawDataSet(tsRelay8DIORaw *,int num,int asHigh);
int tsRelay8DIORawDirGet(tsRelay8DIORaw *,int num);
int tsRelay8DIORawDataGet(tsRelay8DIORaw *,int num);
unsigned tsRelay8DIORawCount(tsRelay8DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
