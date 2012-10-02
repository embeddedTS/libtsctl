#ifndef __Cavium2132DIORaw_H
#define __Cavium2132DIORaw_H
#include "DIORaw.h"
#include "Bus.h"
typedef struct Cavium2132DIORaw Cavium2132DIORaw;

struct Cavium2132DIORaw {
  DIORaw;
  int deferlockW,deferlockR;
  Bus *sub;
};

void *Cavium2132DIORawInit(Cavium2132DIORaw *,void *bus);
void Cavium2132DIORawFini(Cavium2132DIORaw *);
void Cavium2132DIORawDirSet(Cavium2132DIORaw *,int num,int asOutput);
void Cavium2132DIORawDataSet(Cavium2132DIORaw *,int num,int asHigh);
int Cavium2132DIORawDirGet(Cavium2132DIORaw *,int num);
int Cavium2132DIORawDataGet(Cavium2132DIORaw *,int num);
unsigned Cavium2132DIORawCount(Cavium2132DIORaw *);

#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
