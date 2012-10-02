#ifndef __TS_H
#define __TS_H

typedef enum TS_CPU {
  CPU_UNKNOWN=0,CPU_EP9302, CPU_CAVIUM, CPU_ATMEL, CPU_X86, CPU_FREESCALE,
  CPU_MARVELL_PXA168, CPU_MARVELL_MV88F5182
} TS_CPU;
TS_CPU TSCPUGet(void);
const char *TSArchGet();
int TSModelGet();

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
