#ifndef __ts4500DIORaw_H
#define __ts4500DIORaw_H
#include "DIORaw.h"
#include "Bus.h"

typedef struct ts4500DIORaw ts4500DIORaw;

struct ts4500DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *ts4500DIORawInit(ts4500DIORaw *,void *bus);
void ts4500DIORawFini(ts4500DIORaw *);
void ts4500DIORawDirSet(ts4500DIORaw *,int num,int asOutput);
void ts4500DIORawDataSet(ts4500DIORaw *,int num,int asHigh);
int ts4500DIORawDirGet(ts4500DIORaw *,int num);
int ts4500DIORawDataGet(ts4500DIORaw *,int num);
unsigned ts4500DIORawCount(ts4500DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
