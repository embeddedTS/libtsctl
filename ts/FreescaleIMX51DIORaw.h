#ifndef __FreescaleIMX51DIORaw_H
#define __FreescaleIMX51DIORaw_H
#include "DIORaw.h"
#include "Bus.h"

typedef struct FreescaleIMX51DIORaw FreescaleIMX51DIORaw;

struct FreescaleIMX51DIORaw {
  DIORaw;
  int deferlockR,deferlockW;
  Bus *sub;
};

void *FreescaleIMX51DIORawInit(FreescaleIMX51DIORaw *,void *bus);
void FreescaleIMX51DIORawFini(FreescaleIMX51DIORaw *);
void FreescaleIMX51DIORawDirSet(FreescaleIMX51DIORaw *,int num,int asOutput);
void FreescaleIMX51DIORawDataSet(FreescaleIMX51DIORaw *,int num,int asHigh);
int FreescaleIMX51DIORawDirGet(FreescaleIMX51DIORaw *,int num);
int FreescaleIMX51DIORawDataGet(FreescaleIMX51DIORaw *,int num);
unsigned FreescaleIMX51DIORawCount(FreescaleIMX51DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
