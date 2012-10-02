#ifndef __ts4700DIORaw_H
#define __ts4700DIORaw_H
#include "DIORaw.h"
#include "Bus.h"

typedef struct ts4700DIORaw ts4700DIORaw;

struct ts4700DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *ts4700DIORawInit(ts4700DIORaw *,void *bus);
void ts4700DIORawFini(ts4700DIORaw *);
void ts4700DIORawDirSet(ts4700DIORaw *,int num,int asOutput);
void ts4700DIORawDataSet(ts4700DIORaw *,int num,int asHigh);
int ts4700DIORawDirGet(ts4700DIORaw *,int num);
int ts4700DIORawDataGet(ts4700DIORaw *,int num);
unsigned ts4700DIORawCount(ts4700DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
