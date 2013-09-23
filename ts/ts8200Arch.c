#include "arch.h"
#include "ArchArch.h"
extern char *ts8200_dioctl_config[];
#include "ts8200_dioctl_config.c"

Arch *ts8200ArchInit();
Arch *ts8200ArchNextSubArch() {
  return 0;
}
void *ts8200Function(int class,int inst) {
  return 0;
}

Arch ts8200Arch = {
  .Init = ts8200ArchInit,
  .Function = ts8200Function,
  .NextSubArch = ts8200ArchNextSubArch
};


Arch *ts8200ArchInit() {
  static Arch *ts8200;
  if (ts8200) return ts8200;
  ts8200 = &ts8200Arch;
  dioctl_config_add2(Xts8200_dioctl_config,Xts8200_dioctl_config_len,Yts8200_dioctl_config_len);
  return ts8200;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
