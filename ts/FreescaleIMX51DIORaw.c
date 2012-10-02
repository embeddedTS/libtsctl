#ifndef FreescaleIMX51DIORaw_c
#define FreescaleIMX51DIORaw_c
#include "FreescaleIMX51DIORaw.h"

// Not sure why we need this, as we don't have negative DIOs.
// Get rid of it here and in the other DIORaw module(s)!
#define I(x) ( Num<0 ? ~(x) : (x))

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS FreescaleIMX51DIORaw
#include "TSLock.h"

static DIORawAPI FreescaleIMX51DIORawAPI = {
  .Init = (void *)FreescaleIMX51DIORawInit,
  .Fini = (void *)FreescaleIMX51DIORawFini,
  .Lock = (void *)FreescaleIMX51DIORawLock,
  .Unlock = (void *)FreescaleIMX51DIORawUnlock,
  .Preempt = (void *)FreescaleIMX51DIORawPreempt,
  .DirSet = (void *)FreescaleIMX51DIORawDirSet,
  .DataSet = (void *)FreescaleIMX51DIORawDataSet,
  .DirGet = (void *)FreescaleIMX51DIORawDirGet,
  .DataGet = (void *)FreescaleIMX51DIORawDataGet,
  .Count = (void *)FreescaleIMX51DIORawCount
};

void *FreescaleIMX51DIORawInit(FreescaleIMX51DIORaw *dio,void *bus1) {
  Bus *bus = bus1;

  if (dio->InitStatus > 0) return dio;

  dio->Init = (void *)FreescaleIMX51DIORawInit;
  dio->Fini = (void *)FreescaleIMX51DIORawFini;
  dio->Lock = (void *)FreescaleIMX51DIORawLock;
  dio->Unlock = (void *)FreescaleIMX51DIORawUnlock;
  dio->Preempt = (void *)FreescaleIMX51DIORawPreempt;
  dio->DirSet = (void *)FreescaleIMX51DIORawDirSet;
  dio->DataSet = (void *)FreescaleIMX51DIORawDataSet;
  dio->DirGet = (void *)FreescaleIMX51DIORawDirGet;
  dio->DataGet = (void *)FreescaleIMX51DIORawDataGet;
  dio->Count = (void *)FreescaleIMX51DIORawCount;

  FreescaleIMX51DIORawLockInit(dio);
  dio->sub = bus;
  if (dio->sub->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->InitStatus = 1;
  return dio;
}

void FreescaleIMX51DIORawFini(FreescaleIMX51DIORaw *dio) {
  dio->sub->Fini(dio->sub);
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

unsigned FreescaleIMX51DIORawCount(FreescaleIMX51DIORaw *dio) {
  return 16;
}

// DR @ 0
// DIR  @ 4
// IN @ 8
//-----------------------------------------------------------------------------
void FreescaleIMX51DIORawDirSet(FreescaleIMX51DIORaw *dio,
					      int Num,int asOutput) {
  FreescaleIMX51DIORawLockReal(dio,0);
  dio->sub->BitAssign32(dio->sub,I(4),I(Num),asOutput);
}

void FreescaleIMX51DIORawDataSet(FreescaleIMX51DIORaw *dio,
					       int Num,int asHigh) {
  FreescaleIMX51DIORawLockReal(dio,0);
  dio->sub->BitAssign32(dio->sub,I(0),I(Num),asHigh);
}

int FreescaleIMX51DIORawDirGet(FreescaleIMX51DIORaw *dio,int Num) {
  FreescaleIMX51DIORawLockReal(dio,SHARED);
  return dio->sub->BitGet32(dio->sub,I(4),I(Num));
}

int FreescaleIMX51DIORawDataGet(FreescaleIMX51DIORaw *dio,int Num) {
  FreescaleIMX51DIORawLockReal(dio,SHARED);
  return dio->sub->BitGet32(dio->sub,I(8),I(Num));
}
#endif
