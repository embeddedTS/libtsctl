#include <stdio.h>
#include "arch.h"
#include "ArchArch.h"
#include "tsRelay8DIORaw.h"
#include "DummyDIO.h"
#include "PhysicalDIO.h"
#include "Lock.h"
extern char *tsrelay8_dioctl_config[];
#include "tsrelay8_dioctl_config.c"

Arch *tsrelay8ArchInit();
void *tsrelay8Function(int class,int inst);
Arch *tsrelay8ArchNextSubArch();
void tsrelay8NextSubArchSet(Arch *arch);

Arch tsrelay8Arch = {
  .Init = tsrelay8ArchInit,
  .Function = tsrelay8Function,
  .NextSubArch = tsrelay8ArchNextSubArch,
  .NextSubArchSet = tsrelay8NextSubArchSet
};

int r8present[4];

Arch *tsrelay8ArchInit(int model) {
  static Arch *tsrelay8;
  Bus *pc104;
  int i,val;

  if (tsrelay8) return tsrelay8;
  pc104 = BusInit(2);
  pc104->Lock(pc104,0,SHARED);
  for (i=0;i<4;i++) {
    val = pc104->Peek8(pc104,0x140+0x10*i);
    if (val == 0x9B) r8present[i] = 1;
  }
  pc104->Unlock(pc104,0,SHARED);
  if (r8present[0] == 0 && r8present[0] == 0 && r8present[0] == 0 && r8present[0] == 0){
    return 0;
  }
  tsrelay8 = &tsrelay8Arch;
  dioctl_config_add2(Xtsrelay8_dioctl_config,Xtsrelay8_dioctl_config_len,Ytsrelay8_dioctl_config_len);
  return tsrelay8;
}

Arch *tsrelay8Next;

Arch *tsrelay8ArchNextSubArch() {
  return tsrelay8Next;
}

void tsrelay8NextSubArchSet(Arch *arch) {
  tsrelay8Next = arch;
}

tsRelay8DIORaw r8dio[4];
PhysicalDIO r8pdio[4];
unsigned char Relay8DIOCapabilities[8];
DummyDIO r8dummyDIO[4];

DIORaw *tsrelay8__DIORawInit3(DIORaw *dioraw0,int inst);
DIORaw *tsrelay8__DIORawInit0(DIORaw *dioraw0,int inst) {
  if (!r8present[0]) {
    return tsrelay8__DIORawInit3(dioraw0,inst);
  }
  return tsRelay8DIORawInit(&r8dio[inst],BusInit(2),0x140 + inst * 0x10);
}
DIORaw *tsrelay8__DIORawInit1(DIORaw *dioraw0,int inst) {
  if (!r8present[1]) {
    return tsrelay8__DIORawInit0(dioraw0,inst);
  }
  return tsRelay8DIORawInit(&r8dio[inst],BusInit(2),0x140 + inst * 0x10);
}
DIORaw *tsrelay8__DIORawInit2(DIORaw *dioraw0,int inst) {
  if (!r8present[2]) {
    return tsrelay8__DIORawInit1(dioraw0,inst);
  }
  return tsRelay8DIORawInit(&r8dio[inst],BusInit(2),0x140 + inst * 0x10);
}
DIORaw *tsrelay8__DIORawInit3(DIORaw *dioraw0,int inst) {
  if (!r8present[3]) {
    return tsrelay8__DIORawInit2(dioraw0,inst);
  }
  return tsRelay8DIORawInit(&r8dio[inst],BusInit(2),0x140 + inst * 0x10);
}

DIO *tsrelay8__DIOInit0(DIO *dio,int inst) {
  int i;
  DIORaw *dioraw = tsrelay8__DIORawInit0(0,inst);
  if (inst >= 0 && inst <= 3 && r8present[inst]) {
    for (i=0;i<8;i++) {
      Relay8DIOCapabilities[i] = DIO_OUTPUT_ONLY;
    }
    r8pdio[inst].Caps = Relay8DIOCapabilities;
    return PhysicalDIOInit(&r8pdio[inst],BusInit(2),dioraw);
  } else {
    return DummyDIOInit(&r8dummyDIO[inst],8);
  }
}
DIO *tsrelay8__DIOInit1(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}
DIO *tsrelay8__DIOInit2(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}
DIO *tsrelay8__DIOInit3(DIO *dio,int inst) {
  return tsrelay8__DIOInit0(dio,inst);
}

void *tsrelay8Function(int class,int inst) {
  if (class == ClassDIORaw && inst == 0) return tsrelay8__DIORawInit0;
  if (class == ClassDIORaw && inst == 1) return tsrelay8__DIORawInit1;
  if (class == ClassDIORaw && inst == 2) return tsrelay8__DIORawInit2;
  if (class == ClassDIORaw && inst == 3) return tsrelay8__DIORawInit3;
  if (class == ClassDIO && inst == 0) return tsrelay8__DIOInit0;
  if (class == ClassDIO && inst == 1) return tsrelay8__DIOInit1;
  if (class == ClassDIO && inst == 2) return tsrelay8__DIOInit2;
  if (class == ClassDIO && inst == 3) return tsrelay8__DIOInit3;
  return 0;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2013-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
