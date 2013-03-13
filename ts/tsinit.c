#include "arch.h"
#include "cpp.h"

ArchInfo *ArchLast = &TEMPLATE(ARCH_LAST,_ArchInfo);

static int isInTest=0;

void ArchInit() {
  static int initialized = 0;
  ArchInfo *arch;
  int i;
  if (initialized) return;
  initialized = 1;
  startuptime = time(0);
  TEMPLATE(ARCH_LAST,_ArchListInit)(0);
  LogInit(0);
  arch = ArchFirst;
  while (arch) {
    arch->ArchInit();
    arch = arch->next;
  }
  dioctl_config_add(0);
}

#define CLASS_INC "classinit.h"
#define ALLOW_PIN_OVERRIDE
#include "classeach.h"

int startuptime;

// DIOCount is designed to be used before DIO is initialized
// it is used by the Pin object, which requires this information
// to determine how many locks to allocate
// we can probably require that the DIORaw Count function work even
// if we have not initialized the object.
unsigned DIOCount() {
  int n=0;
  unsigned num=0;
  DIORaw *dio = DIORawInit(n);
  while (dio) {
    num += dio->Count(dio);
    dio = DIORawInit(++n);
  }
  return num;
}

#ifdef __AggregateDIO_h
DIO *DIOInit0(AggregateDIO *DIO0) {
  static DIO *ret = 0;
  int i,j,total = 0;
  static DIO **pDIO = 0;
  DIO *dio = 0;
  static int *SubCount=0;
  int n = 0,offset;
  
  //if (ret) return ret;
  dio = DIOInit(1);
  while (dio) {
    total++;
    dio = DIOInit(total+1);
  }
  if (pDIO == 0) {
    pDIO = malloc(sizeof(DIO *) * total);
  } else {
    pDIO = realloc(pDIO,sizeof(DIO *) * total);
  }
  if (SubCount == 0) {
    SubCount = malloc(sizeof(int) * total);
  } else {
    SubCount = realloc(SubCount,sizeof(int) * total);
  }

  for (i=0;i<total;i++) {
    pDIO[i] = DIOInit(1+i);
  }
  return (ret=AggregateDIOInit(DIO0,total,PinInit(0),SubCount,pDIO));
}

// the old way won't work any more, because not every architecture defined
// need actually be used.
DIO *DIOInit0Old(AggregateDIO *DIO0) {
  int i,j,total = 0;
  DIO **pDIO;
  int n = 0,offset, *SubCount;
  ArchInfo *arch = ArchFirst;
    
  while (arch) {
    total += arch->Instances[ClassDIORaw];
    arch = arch->next;
  }
  pDIO = malloc(sizeof(DIO *) * total);
  SubCount = malloc(sizeof(int) * total);
  arch = ArchFirst;
  while (arch) {
    offset=arch->Instances[ClassDIO] - arch->Instances[ClassDIORaw];
    for (j=offset;j<arch->Instances[ClassDIO];j++) {
      pDIO[n] = arch->DIOInit(0,j);
      if (pDIO[n]) n++;
    }
    arch = arch->next;
  }
  return AggregateDIOInit(DIO0,total,PinInit(0),SubCount,pDIO);
}
#endif

#include "IPC.c"
#include "FPGA.c"
#include "peekpoke.c"
#include "ts.c"
#include "BaseBoard.c"
#include "opt.c"
//#include "libtsctlclient.c"
#include "Log.c"
#include "HashTable.c"

const char copyright[] 
__attribute__ ((weak)) 
  = "Copyright (c) Technologic Systems - " __DATE__ ; 
//const char hoststring[] __attribute__ ((weak)) = 
//  "CompileHost - $(shell uname -a)"; 
const char build[] 
__attribute__ ((weak)) 
  =  "$build: 0"; 
const char compiledate[] 
__attribute__ ((weak))
  = "$date: " __DATE__ " " __TIME__;
const char archstr[] 
__attribute__ ((weak)) 
  = ""; 

const int compiletime 
__attribute__ ((weak)) 
  = 0;
