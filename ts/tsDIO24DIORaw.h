#ifndef __tsDIO24DIORaw_H
#define __tsDIO24DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct tsDIO24DIORaw tsDIO24DIORaw;

struct tsDIO24DIORaw {
  DIORaw;
  int deferlockW,deferlockR;
  Bus *sub;
  int adrs;
};

void *tsDIO24DIORawInit(tsDIO24DIORaw *,void *bus,int adrs);
void tsDIO24DIORawFini(tsDIO24DIORaw *);
void tsDIO24DIORawDirSet(tsDIO24DIORaw *,int num,int asOutput);
void tsDIO24DIORawDataSet(tsDIO24DIORaw *,int num,int asHigh);
int tsDIO24DIORawDirGet(tsDIO24DIORaw *,int num);
int tsDIO24DIORawDataGet(tsDIO24DIORaw *,int num);
unsigned tsDIO24DIORawCount(tsDIO24DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
