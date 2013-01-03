#ifndef LIBTSCTL_VERSION
#define LIBTSCTL_VERSION "0.93"
#endif
#ifndef LIBTSCTL_ORGANIZATION
#define LIBTSCTL_ORGANIZATION customer
#endif
#include "cpp.h"
#define LIBTSCTL_FULL_VERSION LIBTSCTL_VERSION "-" STRINGIFY(LIBTSCTL_ORGANIZATION)
#ifndef LocalSystem_c
#define LocalSystem_c
#include <sys/sysinfo.h> 
#include <assert.h>
#include <time.h>
#include "arch.h"
#include "LocalSystem.h"
#include "Thread.h"
#include "ts.h"
#include "shell.c"
#include "dioctlConfig.c"

int CompareNameValuePair0(const char *a,const char *b) {
  int ret = strncasecmp(a,b,ArrayElementSize(a)*ArrayLength(a));
  if (ret == 0 && (ArrayLength(a) != ArrayLength(b))) {
    return (ArrayLength(a) > ArrayLength(b)) ? 1 : -1;
  } else {
    return ret;
  }
}

int CompareNameValuePair1(const char *a,const char *b) {
  return strncasecmp(a,b,ArrayElementSize(a)*ArrayLength(a));
}

int CompareNameValuePair(const void *a1,const void *b1) {
  const NameValuePair *a = a1, *b = b1;

  int ret = strncasecmp(a->name,b->name,
			ArrayElementSize(a->name)*ArrayLength(a->name));
  if (ret == 0 && (ArrayLength(a->name) != ArrayLength(b->name))) {
    return (ArrayLength(a->name) > ArrayLength(b->name)) ? 1 : -1;
  } else {
    return ret;
  }
}

int CompareNVPP2(const void *a1,const void *b1) {
  const NameValuePair *a = a1, *b = b1;
  int strmatch = CompareNameValuePair1(b->name,a->name);
  //ArrayCompare1(b->name,a->name);

  //printf("1. %s vs. %s = %d (%d-%d)\n",b->name,a->name,strmatch,ArrayLength(b),ArrayLength(a));
  if (!strmatch) {
    return ArrayLength(a->name) - ArrayLength(b->name);
    return a->value - b->value;
  } else {
    return -strmatch;
  }
}

int CompareNVPP3(const void *a1,const void *b1) {
  const NameValuePair *a = a1, *b = b1;
  int strmatch = CompareNameValuePair1(b->name,a->name);
  //ArrayCompare1(b->name,a->name);

  //printf("2. %s vs. %s = %d (%d)\n",b->name,a->name,strmatch,b->value-a->value);
  if (!strmatch) {
    return ArrayLength(b->name) - ArrayLength(a->name);
    return a->value - b->value;
  } else {
    return -strmatch;
  }
}

int CompareNameValuePairPartial(const void *a1,const void *b1) {
  const NameValuePair *a = a1, *b = b1;
  int strmatch = CompareNameValuePair(b,a);
    //ArrayCompare1(b->name,a->name);

  //printf("2. %s vs. %s = %d (%d)\n",b->name,a->name,strmatch,b->value-a->value);
  if (!strmatch) {
    return a->value - b->value;
  } else {
    return -strmatch;
  }
}

void NameValuePairDump(NameValuePair *map) {
  int i,n;

  for (i=0;i<ArrayLength(map);i++) {
    printf("%d.%s=%d\n",i,map[i].name,map[i].value);
  }
}

ArrayAutoOfSize(char,emptystring,0);

static char* _MapLookupPartial(NameValuePair *map,const char* stem,
					  int value) {
  NameValuePair nvp;
  nvp.name = (char*)stem;
  nvp.value = value;
  unsigned i0,i = ArrayFindWith(map,&nvp,CompareNVPP2);
  unsigned i1 = ArrayFindWith(map,&nvp,CompareNVPP3);

  for (i0=i;i<=i1;i++) {
    if (map[i].value == value) {
      return ArrayRange(map[i].name,ArrayLength(stem),-1);
    }
  }
  return ArrayDup(emptystring); // ArrayAlloc(0,sizeof(char));
  /*
  unsigned index = ArrayFindWith(map,&nvp,CompareNameValuePairPartial);
  char *ret;
  //printf("%d:%s\n",index,map[index].name);
  //NameValuePairDump(map); exit(1);
  if (map[index].name && !ArrayCompare1(nvp.name,map[index].name)) {
    ret = ArrayRange(map[index].name,ArrayLength(stem),-1);
    //printf("%d-->%s\n",ArrayLength(stem),ret);
  } else {
    ret = ArrayDup(emptystring); // ArrayAlloc(0,sizeof(char));
  }
  return ret;
  */
}

NameValuePair* _MapConfigLineAssign(NameValuePair* map,char *name,
					   int value) {
  int connectorNum,connectorPin;
  char* tmp;
  char* tmp2;
  char* cname;

  //fprintf(stderr,"--> %s = %d\n",name,value);
  // automatic connector to connector name assignment
  if (2==sscanf(name,"attrib.Connector.%d.%d",
		&connectorNum,&connectorPin)) {
    tmp2 = ASCIIZ("attrib.Connector.Name.");
    cname = _MapLookupPartial(map,tmp2,connectorNum);
    //if (cname[0] != 0) printf("%s:%s\n",cname,tmp2);
    //printf("%s,%d,%d:%s\n",tmp2,connectorNum,connectorPin,cname);
    ArrayFree(tmp2);
    if (ArrayLength(cname) > 0) {
      tmp = strf("%s%d",cname,connectorPin);
      //fprintf(stderr,"--> 1. %s = %d\n",tmp,value);
      map = ArrayReplace(map,A(NameValuePair,Of(tmp,value)));//,
    }
    ArrayFree(cname);
  }
  //fprintf(stderr,"--> 2. %s=%d\n",name,value);
  map = ArrayReplace(map,A(NameValuePair,Of(ASCIIZ(name),value)));//,
  //CompareNameValuePairPartial);
  return map;
}

// parse str according to "name=value" and replace in map
// if value is a string, interpret as "name.value=1"
// returns 1 on success, or 0 on failure
static void MapConfigLineAssign(LocalSystem *sys,char *str) {
  char *str0 = str;
  char *name;
  char* tmp;
  unsigned value;
  static int lines=0; lines++;

  while (*str && *str != '=') str++;
  if (*str != '=') return;
  *str = 0;
  str++;
  value = strtoul(str,0,0);
  name = str0;
  if (value == 0 && str[0] != '0') {
    tmp = ASCIIZ(str);
    value = sys->MapLookup(sys,tmp);
    ArrayFree(tmp);
    //str[-1] = '.';
    //value = 1;
  }
  sys->map = _MapConfigLineAssign(sys->map,name,value);
}

void MapLoadFromFile(LocalSystem *sys,char *filename) {
  char buf[301],*str,*inst_str,*wc;
  int lines=0,n;
  FILE *f;

  f = fopen(filename,"r");
  if (!f) return;
  assert(ThreadLockW(sys->maplock,LOCK_SOD) > 0);
  while (!feof(f)) {
    buf[0] = 0;
    fgets(buf,300,f);
    if (buf[0] == 0) goto ConfigFileProcessEnd;
    str = buf;
    while (*str) str++;
    str--;
    while(str >= buf && (*str == '\n' || *str == '\r' || *str == ' ' || *str == '\t')) {
      *str = 0;
      str--;
    }
    lines++;
    if (buf[0] != '#') {
      MapConfigLineAssign(sys,buf);
    }
  }
 ConfigFileProcessEnd:
  assert(ThreadUnlockW(sys->maplock) > 0);
  fclose(f);
  return;
}

extern int startuptime;

void *LocalSystemInit(LocalSystem *sys) {
  if (sys->InitStatus > 0) return sys;

  sys->Init = (void *)LocalSystemInit;
  sys->Fini = (void *)LocalSystemFini;
  sys->ClassCount = (void *)LocalSystemClassCount;
  sys->InstanceCount = (void *)LocalSystemInstanceCount;
  sys->APICount = (void *)LocalSystemAPICount;
  sys->LockCount = (void *)LocalSystemLockCount;
  sys->LockHolderInfo = (void *)LocalSystemLockHolderInfo;
  sys->ConnWaitInfo = (void *)LocalSystemConnWaitInfo;
  sys->CANBusGet = (void *)LocalSystemCANBusGet;
  sys->BuildTime = (void *)LocalSystemBuildTime;
  sys->ModelId = (void *)LocalSystemModelId;
  sys->BaseBoardId = (void *)LocalSystemBaseBoardId;
  sys->MapLength = (void *)LocalSystemMapLength;
  sys->MapGet = (void *)LocalSystemMapGet;
  sys->MapLookup = (void *)LocalSystemMapLookup;
  sys->MapLookupPartial = (void *)LocalSystemMapLookupPartial;
  sys->MapAdd = (void *)LocalSystemMapAdd;
  sys->MapDelete = (void *)LocalSystemMapDelete;
  sys->Note = (void *)LocalSystemNote;
  sys->Version = (void *)LocalSystemVersion;
  sys->UptimeServer = (void *)LocalSystemUptimeServer;
  sys->UptimeHost = (void *)LocalSystemUptimeHost;
  sys->FPGARevision = (void *)LocalSystemFPGARevision;
  sys->EchoNumber = (void *)LocalSystemEchoNumber;

  sys->maplock = ThreadLockAllocate(1);
  sys->map = archmap; // ArrayAlloc(0,sizeof(NameValuePair));
  archmapptr = &sys->map;
  //ArraySort(sys->map,CompareNameValuePair);
  MapLoadFromFile(sys,"/etc/dioctl.config");
  sys->InitStatus = 1;
  return sys;
}

void LocalSystemFini(LocalSystem *sys) {
}

int LocalSystemClassCount(LocalSystem *sys) {
  return ClassesCount;
}

int LocalSystemInstanceCount(LocalSystem *sys,int class) {
  int i,n=0;
  ArchInfo *arch = ArchFirst;

  if (class < 0 || class >= ClassesCount) return 0;
  while (arch) {
    if (arch->ArchInit() > 0) {
      n += arch->Instances[class];
    }
    arch = arch->next;
  }
  return n;  
}

int LocalSystemAPICount(LocalSystem *sys,int class) {
  switch (class) {                             
  case ClassSystem:
    return XSystem_APICount;
  case ClassBus:
    return XBus_APICount;
  case ClassTime:
    return XTime_APICount;
  case ClassPin:
    return XPin_APICount;
  case ClassDIORaw:
    return XDIORaw_APICount;
  case ClassDIO:
    return XDIO_APICount;
  case ClassTWI:
    return XTWI_APICount;
  case ClassCAN:
    return XCAN_APICount;
  case ClassSPI:                        
    return XSPI_APICount;
  default:                                 
    return 0;
  }
}

int LocalSystemLockCount(LocalSystem *sys) {
  return ThreadMutexCount();
}

LockHolderInf *LocalSystemLockHolderInfo(LocalSystem *sys) {
  return 0;
}

ConnectionWaitInf *LocalSystemConnWaitInfo(LocalSystem *sys) {
  // TO DO: implement this using Thread module
  // but, thread module does not expose this information, so add that!
  /*
  ThreadData *cur;
  int conns=0,n=0,i=max;

  pthread_mutex_lock(&watchlock);
  cur = head_thread;
  while (cur) {
    conns++;
    cur = cur->next;
  }
  if (conns > i) conns = i;
  cur = head_thread;
  while (cur && i--) {
    info[n].pid = cur->pid;
    info[n++].wait = cur->wait;
    cur = cur->next;
  }
  pthread_mutex_unlock(&watchlock);
  return conns;
  */
  return 0;
}

SystemResult LocalSystemCANBusGet(LocalSystem *sys,int CANInst) {
  if (CANInst >= LocalSystemInstanceCount(sys,ClassCAN)) {
    return SystemErrorNoSuchCANInstance;
  } else {
    ArchInfo *arch = ArchFirst;
    while (arch) {
      if (arch->Instances[ClassCAN] > CANInst) {
	return arch->CANBusNum[CANInst];
      }
      CANInst -= arch->Instances[ClassCAN];
      arch = arch->next;
    }
    // BUG: what if CAN instance is not in a primary architecture?
  }
  return SystemErrorNoSuchCANInstance; // should not reach here!
}

extern const char build[];
extern const char archstr[];
extern const char compiledate[];

static time_t tFromDateTime(char const *time) { 
  char s_month[5],timestr[10];
  int month, day, year;
  struct tm t = {0};
  static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

  sscanf(time, "%s %d %d %s", s_month, &day, &year, timestr);

  timestr[2] = timestr[5] = 0;

  month = (strstr(month_names, s_month)-month_names)/3;

  t.tm_mon = month-1;
  t.tm_mday = day;
  t.tm_year = year - 1900;
  t.tm_isdst = -1;
  t.tm_hour = atoi(timestr); 
  t.tm_min = atoi(timestr+3); 
  t.tm_sec = atoi(timestr+6); 
  return mktime(&t);
}

unsigned LocalSystemBuildTime(LocalSystem* ob) {
  return tFromDateTime(compiledate+7);
}

unsigned LocalSystemUptimeServer(LocalSystem* ob) {
  return time(0) - startuptime;
}

unsigned LocalSystemUptimeHost(LocalSystem* ob) {
  struct sysinfo info;
  sysinfo(&info);
  return info.uptime;
}

char *LocalSystemVersion(LocalSystem* ob) {
  return ASCIIZ(LIBTSCTL_FULL_VERSION);
}

void LocalSystemBuildInfo(LocalSystem *sys,BuildInf inf[1]) {
  char *str;
  unsigned buildNumber = strtoul(build+7,&str,10);

  inf[0].buildNumber = buildNumber;
  inf[0].buildTime = tFromDateTime(compiledate+7);
  inf[0].hostname = ASCIIZ(str+1);
  inf[0].arch = ASCIIZ((char *)archstr+1);
}

int LocalSystemModelId(LocalSystem *sys) {
  return TSModelGet();
}

int BaseBoardIdGet();
int LocalSystemBaseBoardId(LocalSystem *sys) {
  static int bbid = 0;

  if (bbid) return bbid;
  ThreadEnterBlock();
  bbid = BaseBoardIdGet();
  ThreadLeaveBlock();
  return bbid;
}

int LocalSystemMapLength(LocalSystem *sys) {
  assert(ThreadLockR(sys->maplock,LOCK_SOD) > 0);
  unsigned len = ArrayLength(sys->map);
  assert(ThreadUnlockR(sys->maplock) > 0);
  return len;
}

char* LocalSystemMapGet(LocalSystem *sys,int n,int val[1]) {
  assert(ThreadLockR(sys->maplock,LOCK_SOD) > 0);
  unsigned len = ArrayLength(sys->map);
  char* ret;
  if (n < 0 || n >= len) {
    ret = ArrayAlloc(0,sizeof(char));
  } else {
    ret = ArrayDup(sys->map[n].name);
    val[0] = sys->map[n].value;
  }
  assert(ThreadUnlockR(sys->maplock) > 0);
  return ret;
}

int LocalSystemMapLookup(LocalSystem *sys,const char* key) {
  NameValuePair nvp;
  nvp.name = (char *)key;
  int ignoresharp=0;
  if (key[ArrayLength(key)-1] == '#') {
    ignoresharp = 1;
    ArraySizeAuto((char*)key,ArrayLength(key)-1);
  }
  assert(ThreadLockR(sys->maplock,LOCK_SOD) > 0);
  unsigned index = ArrayFind(sys->map,&nvp);
  int ret;
  if (sys->map[index].name && !CompareNameValuePair0(sys->map[index].name,nvp.name)) {
    //printf("%s=%d\n",sys->map[index].name,sys->map[index].value);
    ret = sys->map[index].value;
  } else {
    ret = -1;
  }
  assert(ThreadUnlockR(sys->maplock) > 0);
  if (ignoresharp) {
    ArraySizeAuto((char*)key,ArrayLength(key)+1);
  }
  return ret;
}

char* LocalSystemMapLookupPartial(LocalSystem *sys,const char* stem,int value) {
  assert(ThreadLockR(sys->maplock,LOCK_SOD) > 0);
  char* ret = _MapLookupPartial(sys->map,(char *)stem,value);
  assert(ThreadUnlockR(sys->maplock) > 0);
  return ret;
}

SystemResult LocalSystemMapAdd(LocalSystem *sys,const char* key,int value) {
  assert(ThreadLockW(sys->maplock,LOCK_SOD) > 0);
  sys->map = ArrayReplace(sys->map,
			  A(NameValuePair,Of((char *)ArrayDup(key),value)));
  //,
  //			      CompareNameValuePairPartial);
  assert(ThreadUnlockW(sys->maplock) > 0);
  return SystemSuccess;
}

int LocalSystemMapDelete(LocalSystem *sys,const char* key) {
  assert(ThreadLockW(sys->maplock,LOCK_SOD) > 0);
  unsigned index = ArrayFind(sys->map,A(NameValuePair,Of((char *)key,0)));
  int ret = SystemErrorNoSuchKey;
  if (index < ArrayLength(sys->map) 
      && !ArrayCompare(sys->map[index].name,(char *)key)) {
    ArrayFree(sys->map[index].name);
    sys->map = ArrayDelete(sys->map,index,1);
    ret = SystemSuccess;
  }
  //sys->map = ArrayFindDelete(sys->map,NameValuePair,Of((char *)key,0));
  assert(ThreadUnlockW(sys->maplock) > 0);
  return ret;
}

char* LocalSystemNote(LocalSystem* ob,const char* msg) {
  return ArrayDup(msg);
}

Bus *BusInit(int);
int LocalSystemFPGARevision(LocalSystem* ob) {
  int model = ob->ModelId(ob),ret;
  Bus *bus = BusInit(0);

  bus->Lock(bus,0,0);
  if (model == 0x4500) {
    ret = bus->BitsGet16(bus,0x62,3,0);
  } else {
    ret = bus->BitsGet16(bus,0x2,3,0);
  }
  bus->Unlock(bus,0,0);
  return ret;
}

int LocalSystemEchoNumber(LocalSystem* ob,int n) {
  return n;
}

#endif
