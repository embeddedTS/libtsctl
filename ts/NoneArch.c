#include "arch.h"
#include "ArchArch.h"
#include "SystemTime.h"
#include "LocalSystem.h"

Arch *NoneArchInit();
void *NoneFunction(int class,int inst);
Arch *NoneArchNextSubArch();

Arch NoneArch = {
  .Init = NoneArchInit,
  .Function = NoneFunction,
  .NextSubArch = NoneArchNextSubArch
};

Arch *NoneArchInit() {
  static Arch *None;
  if (None) return None;
  None = &NoneArch;
  return None;
}

Arch *NoneArchNextSubArch() {
  return 0;
}

SystemTime NoneTime0;
LocalSystem Nonesys;

void *None__SystemInit0(void *s,int inst) {
  return LocalSystemInit(&Nonesys);
}

Time *None__TimeInit0(Time *t,int inst) {
  return SystemTimeInit(&NoneTime0);
}

void *NoneFunction(int class,int inst) {
  switch(class) {
  case ClassSystem:
    switch (inst) {
    case 0: return None__SystemInit0;
    default: return 0;
    }
  case ClassTime:
    switch (inst) {
    case 0: return None__TimeInit0;
    default: return 0;
    }
  default: return 0;
  }
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2013-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
