#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "ts/nosig.h"
#include "ts/Array.h"

#include "libtsctl.c"


unsigned short* SemaphoresQ(int semid) {
  union semun se;
  struct semid_ds ds;
  unsigned short* arr;

  se.buf = &ds;
  if (semctl(semid,0,IPC_STAT,se) < 0) return 0;
  se.array = arr = ArrayAlloc(ds.sem_nsems,2);
  if (semctl(semid, 0, GETALL,se) < 0) {
    ArrayFree(arr);
    return 0;
  }
  return arr;
}

int check_locked() {
  int semid,ret;
  key_t semkey = 0x75000000;
  unsigned short *arr;

  semid = SemaphoresGet(semkey,1);
  arr = SemaphoresQ(semid);
  //printf("%d\n",arr[0]);
  ret = arr[0];
  ArrayFree(arr);
  return ret;
}

int main(int argc,char *argv[]) {
  Bus *bus = BusInit(0);
  Time *t = TimeInit(0);
  unsigned ft,st,last=-1,next,i;

  while (1) {
    ft = t->usFuture(t,st=t->Tick(t),1000000);
    while (!t->TimeoutQ(t,st,ft)) {
      next = check_locked();
      if (next != last) {
	fprintf(stderr,"%d",next);
	last = next;
      } 
    }
    fprintf(stderr,"<%d",check_locked());
    bus->Lock(bus,0,0);
    fprintf(stderr,"[");
    //for (i=0;i<32;i++) {
    //bus->Peek16(bus,0x74);
    //fprintf(stderr,"%02X",i);
    //}
    bus->Poke16(bus,0x74,2);
    fprintf(stderr,"]");
    bus->Unlock(bus,0,0);
    fprintf(stderr,">");
  }

}
