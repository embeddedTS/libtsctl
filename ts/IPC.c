#include <assert.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include "IPC.h"
#include "generic.h"
#include "nosig.h"

int SemaphoresGet(int key,int count) {
  struct sembuf sop[count];
  int i,semid;
  unsigned short arr[count];
  union semun se;
  struct semid_ds ds;

  semid = semget(key, count, IPC_CREAT|IPC_EXCL|0777);

  if (semid != -1) {
    //printf("Creating semaphore\n");
    for (i=0;i<count;i++) arr[i] = 1;
    se.array=arr;
    semctl(semid,0,SETALL,se);
    /*
    for (i=0;i<count;i++) {
      sop[i].sem_num = i;
      sop[i].sem_op = 1;
      sop[i].sem_flg = 0;
    }
    if (TEMP_FAILURE_RETRY(semop(semid, sop, count)) != 0) {
      return LockErrorSemopBase-errno; 
    }
    */
  } else {
    //printf("Semaphore exists\n");
    semid = semget(key, 0, 0777);

    se.buf = &ds;
    i = semctl(semid,0,IPC_STAT,se);
    if (i >= 0) assert (ds.sem_nsems >= count);
  }
  if (semid == -1) { 
    return LockErrorSemgetBase-errno;
  }
  return semid;
}

int SemaphoresQuery(int semid,unsigned short **arrptr) {
    union semun se;
    struct semid_ds ds;
    int r;
    unsigned short *arr=0;

    se.buf = &ds;
    r = semctl(semid,0,IPC_STAT,se);
    if (r < 0) {
      return LockErrorSemctlBase-errno;
    }
    //printf("semaphores=%d\n",ds.sem_nsems);
    
    arr = malloc(4+sizeof(unsigned short)*ds.sem_nsems);
    arr += 2; // skip 4 bytes which hold length
    ArrayLen(arr) = ds.sem_nsems;

    se.array = arr;
    r = semctl(semid, 0, GETALL,se);
    if (r < 0) { 
      return LockErrorSemctlBase;
    }
    *arrptr = arr;
    return ds.sem_nsems;
}


/*
 */
// flags: IPC_NOWAIT, SEM_UNDO
int SemaphoresOp(int op,int semid,int len,int *num,int flags,unsigned us) {
  struct sembuf sop[len];
  struct timespec timeout;
  int i,r,n;

  //printf("Begin: %d (%u)\n",len,us);
  if (len <= 0) return 0;

  if (us == 0) flags |= IPC_NOWAIT;
  if (us != 0xFFFFFFFF) {
    timeout.tv_sec = us / 1000000;
    timeout.tv_nsec = (us % 1000000) * 1000;
  }
  for (i=0,n=0;i<len;i++) {
    //printf("%d ",num[i]);
    if (num[i] >= 0) {
      sop[n].sem_num = num[i];
      sop[n].sem_op = op;
      sop[n].sem_flg = flags;
      n++;
    }
  }
  //printf("\n");
  if (us == 0xFFFFFFFF || us == 0) {
    r = TEMP_FAILURE_RETRY(semop(semid, sop, n));
  } else {
    assert(0); // uclibc doesn't have semtimedop.  WHY NOT?!
    //r = TEMP_FAILURE_RETRY(semtimedop(semid, sop, n,&timeout));
    if (r == -1 && errno == EAGAIN) {
      return LockErrorSemopBase-errno;
    }
  }
  //printf("Done\n");
  if (r != 0) { 
    //printf("Error %d:%d:%m\n",flags,flags & IPC_NOWAIT ? 1 : 0);
    return LockErrorSemopBase - errno;
  }
  return 0;
}
#include <stdio.h>
void *SharedMemoryGet(int key,int len,int *err) {
  key_t shmkey;
  int shmid;
  void *ret;

  shmkey = key;
  shmid = shmget(shmkey, len, IPC_CREAT);

  if (shmid == -1) {
    fprintf(stderr,"errno=%d, len=%d\n",errno,len);
    if (err) *err = IPCErrorShmgetBase-errno;
    return 0;
  }
  ret = shmat(shmid, NULL, 0);

  return ret;
}

int SignalCapture(int signal,SignalHandler h) {
  struct sigaction sa;

  sa.sa_handler = h;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  return sigaction(signal, &sa, NULL);
}

int SignalIgnore(int signal) {
  struct sigaction sa;

  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  return sigaction(signal, &sa, NULL);
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Partially based on code by Jesse Off (joff@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
