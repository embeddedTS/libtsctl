#ifndef AggregateDIO_c
#define AggregateDIO_c
#include <stdio.h>
#include <string.h>
#include "AggregateDIO.h"
#include "Array.h"
#include "Time.h"

void *AggregateDIOInit(AggregateDIO *dio,unsigned Count,void *pin1,
		       int *SubCount,DIO **pDIO) {
  int i;
  Pin *pin = pin1;

  if (dio->InitStatus > 0 && Count == dio->nCount) return dio;

  dio->Init = (void *)AggregateDIOInit;
  dio->Fini = (void *)AggregateDIOFini;
  dio->Lock = (void *)AggregateDIOLock;
  dio->Unlock = (void *)AggregateDIOUnlock;
  dio->Preempt = (void *)AggregateDIOPreempt;
  dio->Refresh = (void *)AggregateDIORefresh;
  dio->Commit = (void *)AggregateDIOCommit;
  dio->Set = (void *)AggregateDIOSet;
  dio->Get = (void *)AggregateDIOGet;
  dio->SetAsync = (void *)AggregateDIOSetAsync;
  dio->GetAsync = (void *)AggregateDIOGetAsync;
  dio->Wait = (void *)AggregateDIOWait;
  dio->Count = (void *)AggregateDIOCount;
  dio->Capabilities = (void *)AggregateDIOCapabilities;
  dio->GetMulti = (void *)AggregateDIOGetMulti;

  dio->pin = pin;
  if (dio->pin && dio->pin->InitStatus <= 0) {
    dio->InitStatus = -1;
    return dio;
  }
  dio->nCount = Count;
  dio->SubCount = SubCount;
  dio->dio = pDIO;
  for (i=0;i<Count;i++) {
    if (dio->dio[i]) {
      dio->SubCount[i] = dio->dio[i]->Count(dio->dio[i]);
    } else {
      dio->SubCount[i] = 0;
    }
  }
  for (i=0;i<Count;i++) {
    if (dio->dio[i] && dio->dio[i]->InitStatus <= 0) {
      dio->Fini(dio);
      dio->InitStatus = -1;
      return dio;
    }
  }
  dio->InitStatus = 1;
  return dio;
}

void AggregateDIOFini(AggregateDIO *dio) {
  int i;

  if (dio->pin) {
    dio->pin->Fini(dio->pin);
  }
  for (i=0;i<dio->nCount;i++) {
    if (dio->dio[i]) {
      dio->dio[i]->Fini(dio->dio[i]);
    }
  }
  if (dio->InitStatus > 0) dio->InitStatus = 0;
}

void AggregateDIORefresh(AggregateDIO *dio) {
  int i;
  for (i=0;i<dio->nCount;i++) {
    if (dio->dio[i]) {
      dio->dio[i]->Refresh(dio->dio[i]);
    }
  }
}

void AggregateDIOCommit(AggregateDIO *dio,int forceall) {
  int i;
  for (i=0;i<dio->nCount;i++) {
    if (dio->dio[i]) {
      dio->dio[i]->Commit(dio->dio[i],forceall);
    }
  }
}

static inline int DIOSub(AggregateDIO *dio,int *DIONum,int *i) {
  if (*DIONum < 0) return 0;
  for (*i=0;*i<dio->nCount && *DIONum >= dio->SubCount[*i];(*i)++) {
    *DIONum -= dio->SubCount[*i];
  }
  return (*i < dio->nCount);
}

void AggregateDIOSet(AggregateDIO *dio,int DIONum,DIOState State) {
  int i;

  if (!DIOSub(dio,&DIONum,&i)) return;
  dio->dio[i]->Set(dio->dio[i],DIONum,State);
}

DIOState AggregateDIOGet(AggregateDIO *dio,int DIONum) {
  int i;

  if (!DIOSub(dio,&DIONum,&i)) return INPUT;
  return dio->dio[i]->Get(dio->dio[i],DIONum);
}

void AggregateDIOSetAsync(AggregateDIO *dio,int DIONum,DIOState State) {
  int i;

  if (!DIOSub(dio,&DIONum,&i)) return;
  dio->dio[i]->SetAsync(dio->dio[i],DIONum,State);
}

DIOState AggregateDIOGetAsync(AggregateDIO *dio,int DIONum) {
  int i;

  //printf("%d\n",DIONum);
  if (!DIOSub(dio,&DIONum,&i)) return INPUT;
  //printf("%d:%d\n",i,DIONum);
  return dio->dio[i]->GetAsync(dio->dio[i],DIONum);
}

int AggregateDIOLock(AggregateDIO *dio,unsigned num,int flags) {
  unsigned j,num0=num;
  int ret;

  if (!DIOSub(dio,(int *)&num,&j)) return -1;
  if (dio->pin) {
    // shared:
    //   acquire read lock
    //   if pin not DIO
    //     acquire write lock
    //     set pin to DIO
    //     drop write lock
    // exclusive:
    //   acquire write lock
    //   set pin to DIO
    if (flags & SHARED) {
      ret = dio->pin->Lock(dio->pin,num0,flags);
      if (dio->pin->ModeGet(dio->pin,num0) != MODE_DIO) {
	ret = dio->pin->Lock(dio->pin,num0,flags & ~SHARED);
	if (ret < 0) {
	  dio->pin->Unlock(dio->pin,num0,flags); //assert
	  return ret;
	}
	dio->pin->ModeSet(dio->pin,num0,MODE_DIO);
	dio->pin->Unlock(dio->pin,num0,flags & ~SHARED);
      }
    } else {
      ret = dio->pin->Lock(dio->pin,num0,flags);
      if (ret < 0) return ret;
      dio->pin->ModeSet(dio->pin,num0,MODE_DIO);
    }
  }
  return ret;
}

int AggregateDIOUnlock(AggregateDIO *dio,unsigned num,int flags) {
  unsigned j,num0=num;

  if (!DIOSub(dio,(int *)&num,&j)) return -1;
  if (dio->pin) {
    return dio->pin->Unlock(dio->pin,num0,flags & SHARED);
  }
}

int AggregateDIOPreempt(AggregateDIO *dio) {
}

extern Time *TimeInit(int);

#define ASYNC_WAIT

void AggregateDIOWait(AggregateDIO *dio,int* match,int min,int max,
		     const int* h,const int* l) {
  int nh=ArrayLength(h),nl=ArrayLength(l);
  int i,j,matched,val;
  int h2[nh],l2[nl],dioh[nh],diol[nl];
  Time *t;
#ifndef ASYNC_WAIT
  int dioused[dio->nCount];

  for (i=0;i<dio->nCount;i++) {
    dioused[i] = 0;
  }
#endif

  t = TimeInit(1);
  if (!t) t = TimeInit(0);
  
  for (j=0;j<nh;j++) {
    h2[j] = h[j]; dioh[j] = 0;
    if (!DIOSub(dio,h2+j,dioh+j)) {
      dioh[j] = -1;
    }
#ifndef ASYNC_WAIT
    else {
      dioused[dioh[j]] = 1;
    }
#endif
  }
  for (j=0;j<nl;j++) {
    l2[j] = l[j]; diol[j] = 0;
    if (!DIOSub(dio,l2+j,diol+j)) {
      diol[j] = -1;
    }
#ifndef ASYNC_WAIT
    else {
      dioused[diol[j]] = 1;
    }
#endif
  }

  do {
    matched = 0;
#ifndef ASYNC_WAIT
    for (i=0;i<dio->nCount;i++) {
      if (dioused[i]) {
	dio->dio[i]->Refresh(dio->dio[i]);
      }
    }
#endif
    for (i=0;i<nh;i++) {
      if (dioh[i] == -1) continue;
#ifdef ASYNC_WAIT
      dio->dio[dioh[i]]->Lock(dio->dio[dioh[i]],0,SHARED);
      val = dio->dio[dioh[i]]->GetAsync(dio->dio[dioh[i]],h2[i]);
      dio->dio[dioh[i]]->Unlock(dio->dio[dioh[i]],0,SHARED);
#else
      val = dio->dio[dioh[i]]->Get(dio->dio[dioh[i]],h2[i]);
#endif
      if (val == HIGH || val == INPUT_HIGH) {
	if (match && matched < ArrayLength(match)) match[matched] = h[i];
	matched++;
      }
    }
    for (i=0;i<nl;i++) {
      if (diol[i] == -1) continue;
#ifdef ASYNC_WAIT
      dio->dio[diol[i]]->Lock(dio->dio[diol[i]],0,SHARED);
      val = dio->dio[diol[i]]->GetAsync(dio->dio[diol[i]],l2[i]);
      dio->dio[diol[i]]->Unlock(dio->dio[diol[i]],0,SHARED);
#else
      val = dio->dio[diol[i]]->Get(dio->dio[diol[i]],l2[i]);
#endif
      if (val == LOW || val == INPUT_LOW) {
	if (match && matched < ArrayLength(match)) match[matched] = l[i];
	matched++;
      }
    }
    if (matched < min || matched > max) {
      if (t) t->Wait(t,5000);
    }
  } while (matched < min || matched > max);
  if (match) ArraySizeAuto(match,matched);
}

unsigned AggregateDIOCount(AggregateDIO *dio) {
  unsigned ret = 0,i;

  for (i=0;i<dio->nCount;i++) {
    ret += dio->SubCount[i];
  }
  return ret;
}

DIOCaps AggregateDIOCapabilities(AggregateDIO *dio,unsigned num) {
  int i;

  if (!DIOSub(dio,&num,&i)) return DIO_NOT_PRESENT;
  return dio->dio[i]->Capabilities(dio->dio[i],num);
}

int AggregateDIOGetMulti(AggregateDIO *dio,char* bits,int offset) {
  int i,n,j,byte,tmp,max,q;
  max = dio->Count(dio) - offset;

  if (!bits || ArrayLength(bits) == 0) {
    tmp = 0;
    q = (max-offset > 32) ? 0 : 32-(max-offset);
    n = (max-offset > 32) ? 32 : max-offset;
    for (i=offset;i<n;i++) {
      tmp = (tmp << 1) + DIOValue(dio->Get(dio,i));
    }
    return tmp << q;
  }
  n=ArrayLength(bits)*8;
  dio->Refresh(dio);
  for (i=offset,j=0,byte=0;i<n;i++) {
    bits[byte] = (bits[byte] << 1) + DIOValue(dio->Get(dio,i));
    if (i == max) {
      bits[byte] <<= (7-j);
      break;
    }
    if (++j == 8) {
      j = 0;
      byte++;
    }
  }
  return n;
}

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
