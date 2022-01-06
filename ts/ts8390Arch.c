#include "arch.h"
#include "ArchArch.h"
extern char *ts8390_dioctl_config[];
#include "ts8390_dioctl_config.c"

Arch *ts8390ArchInit();
Arch *ts8390ArchNextSubArch() {
  return 0;
}
void *ts8390Function(int class,int inst) {
  return 0;
}

Arch ts8390Arch = {
  .Init = ts8390ArchInit,
  .Function = ts8390Function,
  .NextSubArch = ts8390ArchNextSubArch
};


Arch *ts8390ArchInit() {
  static Arch *ts8390;
  if (ts8390) return ts8390;
  ts8390 = &ts8390Arch;
  dioctl_config_add2(Xts8390_dioctl_config,Xts8390_dioctl_config_len,Yts8390_dioctl_config_len);
  return ts8390;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2013-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
