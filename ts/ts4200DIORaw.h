#ifndef __ts4200DIORaw_H
#define __ts4200DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct ts4200DIORaw ts4200DIORaw;

struct ts4200DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *ts4200DIORawInit(ts4200DIORaw *,void *bus);
void ts4200DIORawFini(ts4200DIORaw *);
void ts4200DIORawDirSet(ts4200DIORaw *,int num,int asOutput);
void ts4200DIORawDataSet(ts4200DIORaw *,int num,int asHigh);
int ts4200DIORawDirGet(ts4200DIORaw *,int num);
int ts4200DIORawDataGet(ts4200DIORaw *,int num);
unsigned ts4200DIORawCount(ts4200DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
