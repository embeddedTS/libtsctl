#ifndef __ts4800DIORaw_H
#define __ts4800DIORaw_H
#include "DIORaw.h"
#include "Bus.h"

typedef struct ts4800DIORaw ts4800DIORaw;

struct ts4800DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *ts4800DIORawInit(ts4800DIORaw *,void *bus);
void ts4800DIORawFini(ts4800DIORaw *);
void ts4800DIORawDirSet(ts4800DIORaw *,int num,int asOutput);
void ts4800DIORawDataSet(ts4800DIORaw *,int num,int asHigh);
int ts4800DIORawDirGet(ts4800DIORaw *,int num);
int ts4800DIORawDataGet(ts4800DIORaw *,int num);
unsigned ts4800DIORawCount(ts4800DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
