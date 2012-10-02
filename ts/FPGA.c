#include <assert.h>
#include <signal.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include "FPGA.h"
#include "feature.h"
#include "Array.h"

 /*
 * This function records a PID so that ts7500ctl --loadfpga will send
 * a SIGHUP to the PID after FPGA reconfiguration.
 *
 * Predefined slots:
 *  0 - sdctl NBD service
 *  1 - nand NBD service
 *  2 - SPI flash NBD service
 *  3 - xuartctl --server service
 *  4 - canctl --server service
 *  5 - dmxctl --server service
 *  6 - spictl --server service
 *  7 - dioctl --server service
 *  8 - reserved
 *  >= 9 is invalid
 *
 * Before calling, application should setup or ignore the SIGHUP signal.
 * e.g. signal(SIGHUP, SIG_IGN);
 */
static int FPGAReloadPIdRegister(int slot) {
  key_t shmkey;
  int shmid;
  unsigned int *sbus_shm;

  shmkey = 0x75000000;
  shmid = shmget(shmkey, 0x1000, IPC_CREAT);
  if (shmid == -1) {
    return FPGAErrorShmgetBase-errno;
  }
  sbus_shm = shmat(shmid, NULL, 0);
  sbus_shm += (slot * 32);
  sbus_shm[0] = getpid();
  sbus_shm -= (slot * 32);

  if (shmdt(sbus_shm) == -1) {
    return FPGAErrorShmdtBase-errno;
  }
  return 0;
}

int* *flag;

static void ProcessHangup(int signal) {
  if (!flag) return;
  int i,len = ArrayLength(flag);
  for (i=0;i<len;i++) {
    flag[i][0] = 1;
  }
}

static void ProcessSignalRegister(int signal,void (*func)(int)) {
  struct sigaction sa[8]; 
  // uClibc 0.9.28 sizes this struct differently than 0.9.31
  // in case the user has the older library, we deliberately allocate
  // more space than necessary to avoid sigemptyset smashing our stack
  sa[0].sa_handler = func;
  sigemptyset(&sa[0].sa_mask);
  sa[0].sa_flags = 0;
  sigaction(signal, &sa[0], NULL);
}

int FPGAReloadRegister(int *HangupFlag,int slot) {
  static int registered = 0,ret;

  if (!registered) {
    ProcessSignalRegister(SIGHUP,ProcessHangup);
    if ((ret = FPGAReloadPIdRegister(slot)) < 0) {
      return ret;
    }
    registered = 1;
  }
  if (!flag) {
    flag = ArrayAlloc(1,sizeof(int *));
    flag[0] = HangupFlag;
  } else {
    flag = ArrayQueue(flag,A(int *,HangupFlag));
  }
  return 0;
}

void FPGAReloadUnregister(int *HangupFlag) {
  if (!flag) return;
  int i,len = ArrayLength(flag);
  for (i=0;i<len;i++) {
    if (flag[i] == HangupFlag) {
      flag = ArrayDelete(flag,i,1);
      return;
    }
  }
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Partially based on code by Jesse Off (joff@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
