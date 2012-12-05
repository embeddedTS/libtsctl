#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "ts.h"
#include "peekpoke.h"
#include "arch.h"
#include "Bus.h"

Bus *BusInit(int inst);

TS_CPU TSCPUGet(void) {
  FILE *cpuinfo;
  char buf[4096];
  static unsigned int checked = 0;
  static TS_CPU cpu = 0;

  if (!checked) { // once checked it's not going to change!
    cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
      system("mount -t proc proc /proc");
      cpuinfo = fopen("/proc/cpuinfo", "r");
      if (cpuinfo == NULL) {
	fprintf(stderr,"Unable to open /proc/cpuinfo\n");
	exit(3);
      }
    }
    bzero(buf, 4096);
    fread(buf, 1, 4095, cpuinfo);
    fclose(cpuinfo);
    if (strstr(buf, "FA526")) {
      cpu = CPU_CAVIUM;
    } else if (strstr(buf, "ARM920T") && strstr(buf, "crunch")) {
      cpu = CPU_EP9302;
    } else if (strstr(buf,"ARM926EJ-S") && strstr(buf,"Atmel")
	       || strstr(buf,"TS-42xx")) {
      cpu = CPU_ATMEL;
    } else if (strstr(buf,"ARM926EJ-S") && strstr(buf,"MV-88fxx81")) {
      cpu = CPU_MARVELL_MV88F5182;
    } else if (strstr(buf,"Intel") || strstr(buf,"AMD")) {
      cpu = CPU_X86;
    } else if (strstr(buf,"Freescale MX51") || strstr(buf,"TS-48XX")) {
      cpu = CPU_FREESCALE;
    } else if (strstr(buf,"Marvell Mohawk")) {
      cpu = CPU_MARVELL_PXA168;
    } else {
      cpu = CPU_UNKNOWN;
    }
    checked = 1;
  }
  return cpu;
}

const char *TSArchGet() {
  TS_CPU cpu = TSCPUGet();
  switch (cpu) {
  case CPU_UNKNOWN: return "unknown";
  case CPU_EP9302: return "ep9302";
  case CPU_CAVIUM: return "cavium";
  case CPU_ATMEL: return "atmel";
  case CPU_X86: return "x86";
  case CPU_FREESCALE: return "freescale";
  case CPU_MARVELL_PXA168: return "marvell_pxa168";
  case CPU_MARVELL_MV88F5182: return "marvel_mv88f5182";
  default: return "error";
  }
}


// returns 0 if it doesn't know what board this is
int TSModelGet() {
  TS_CPU cpu = TSCPUGet();
  volatile unsigned short *syscon;
  volatile unsigned *syscon32;
  int id,err;
  static int modelId = -1;

  if (modelId != -1) {
    return modelId;
  }
  switch (cpu) {
  case CPU_UNKNOWN:
    return (modelId=0);
  case CPU_EP9302:
    // no support for detecting EP9302 boards at the moment...
    return (modelId=0);
  case CPU_CAVIUM: {
    Bus *sbus = BusInit(0);
    int ret;
    if (sbus->InitStatus <= 0) return (modelId=0);
    //ret = ThreadMutexLock(0,0);
    //if (ret <= 0) fprintf(stderr,"SNAKE! %d\n",ret);
    sbus->Lock(sbus,0,0);
    id = sbus->Peek16(sbus,0x60);
    sbus->Unlock(sbus,0,0);
    //ThreadMutexUnlock(0);
    break;
    }
  case CPU_MARVELL_MV88F5182:
    syscon32 = MemMap(0xE8000000,1);
    id = (syscon32[0] >> 8);
    MemUnmap(syscon32);
    if (id == 0xB480) {
      id = 0x7800;
    } else {
      id = 0;
    }
    break;
  case CPU_ATMEL:
    syscon = MemMap(0x30000000,1);
    id = syscon[0];
    MemUnmap(syscon);
    break;
  case CPU_X86:
    return (modelId=0x86);
  case CPU_MARVELL_PXA168:
    syscon = MemMap(0x80004000,1);
    id = syscon[0];
    MemUnmap(syscon);
    break;
  case CPU_FREESCALE:
    id = 0x4800; 
    // Don't know how to differentiate the TS-4800 with any future boards
    // that might also use a Freescale CPU...
  }
  modelId = id;
  return id;
}


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
