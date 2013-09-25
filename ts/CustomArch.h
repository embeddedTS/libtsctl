#ifndef __CustomArch_h
#define __CustomArch_h
#include "ts.h"
TS_CPU TSCustomCPUGet(char *cpuinfo);
Arch *ArchCustomBBInit(int model);
Arch *ArchCustomInit(TS_CPU cpu);
#endif
