#include "arch.h"
#include "ArchArch.h"
extern char *ts9490_dioctl_config[];
#include "ts9490_dioctl_config.c"

Arch *ts9490ArchInit();
Arch *ts9490ArchNextSubArch() {
  return 0;
}
void *ts9490Function(int class,int inst) {
  return 0;
}

Arch ts9490Arch = {
  .Init = ts9490ArchInit,
  .Function = ts9490Function,
  .NextSubArch = ts9490ArchNextSubArch
};


Arch *ts9490ArchInit() {
  static Arch *ts9490;
  if (ts9490) return ts9490;
  ts9490 = &ts9490Arch;
  dioctl_config_add2(Xts9490_dioctl_config,Xts9490_dioctl_config_len,Yts9490_dioctl_config_len);
  return ts9490;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
