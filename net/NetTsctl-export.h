#ifndef __NetTsctl_h
#define __NetTsctl_h
#include "libtsctl.h"

#include <setjmp.h>
#include "Stream.h"

enum {
  NetModeBlocking=0, // all calls block until server returns completion
  NetModeNonBlocking=1, // calls to functions return void return immediately
  NetModeQueued=2 // we don't send commands to server until 
  // function returning non-void is called.
  // caller is responsible for making sure it doesn't queue too many
  // commands (and run out of transmit buffer space)
};

typedef struct tsctl tsctl;
struct tsctl {
  jmp_buf exception;
  struct Stream *st;
  int mode,count;
};
tsctl *TsctlClient(char *host,int mode);
tsctl *TsctlClient2(Stream *st,int mode);

enum {
	NetSystemClass = 0,
	NetBusClass = 1,
	NetTimeClass = 2,
	NetPinClass = 3,
	NetDIORawClass = 4,
	NetDIOClass = 5,
	NetTWIClass = 6,
	NetCANClass = 7,
	NetSPIClass = 8,
	NetAIOClass = 9,
	NetEDIOClass = 10,
	NetModeClass = 11,
	Net_ClassCount=12
};

typedef struct NetAIO NetAIO;

struct NetAIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  AIOType FUNC(Type)(void *me);
  VoltageRange*FUNC(VoltageRangeList)(void *me);
  int FUNC(PrecisionList)(void *me);
  PeriodRange*FUNC(PeriodRangeList)(void *me);
  int *FUNC(TriggerList)(void *me);
  int FUNC(Channels)(void *me);
  void FUNC(Reset)(void *me);
  int FUNC(ChannelEnable)(void *me,int ch,int flag);
  unsigned FUNC(ChannelSamplePeriod)(void *me,int ch,unsigned ns);
  int FUNC(ChannelPrecision)(void *me,int ch,int prec);
  int FUNC(ChannelVoltageRange)(void *me,int ch,float low,float high);
  int FUNC(Configuration)(void *me,float *low,float *high,int *prec,int *t,int *trigger,int itrig[1]);
  int FUNC(ConfigureTest)(void *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
  int FUNC(Configure)(void *me,const float *low,const float *high,const int *prec,const int *rate,const int *trigger,int itrig);
  int FUNC(ITrig)(void *me,int itrig);
  int FUNC(Get)(void *me,int channel);
  int FUNC(Put)(void *me,int channel,int value);
  int FUNC(Ready)(void *me,int channel);
  int FUNC(Gets8)(void *me,char *buf);
  int FUNC(Gets16)(void *me,short *buf);
  int FUNC(Gets32)(void *me,int *buf);
  int FUNC(Puts8)(void *me,const char *buf);
  int FUNC(Puts16)(void *me,const short *buf);
  int FUNC(Puts32)(void *me,const int *buf);
  int FUNC(Readys8)(void *me,const char *buf);
  int FUNC(Readys16)(void *me,const short *buf);
  int FUNC(Readys32)(void *me,const int *buf);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetAIOInit(tsctl *,int instance);
void *NetAIOFini(NetAIO *);
int32 NetAIOLock(NetAIO *ob,uint32 num,int32 flags);
int32 NetAIOUnlock(NetAIO *ob,uint32 num,int32 flags);
int32 NetAIOPreempt(NetAIO *ob);
AIOType NetAIOType(NetAIO *ob);
VoltageRange* NetAIOVoltageRangeList(NetAIO *ob);
int32 NetAIOPrecisionList(NetAIO *ob);
PeriodRange* NetAIOPeriodRangeList(NetAIO *ob);
int32* NetAIOTriggerList(NetAIO *ob);
int32 NetAIOChannels(NetAIO *ob);
void NetAIOReset(NetAIO *ob);
int32 NetAIOChannelEnable(NetAIO *ob,int32 ch,int32 flag);
uint32 NetAIOChannelSamplePeriod(NetAIO *ob,int32 ch,uint32 ns);
int32 NetAIOChannelPrecision(NetAIO *ob,int32 ch,int32 prec);
int32 NetAIOChannelVoltageRange(NetAIO *ob,int32 ch,real32 low,real32 high);
int32 NetAIOConfiguration(NetAIO *ob,real32* low,real32* high,int32* prec,int32* t,int32* trigger,int32 itrig[1]);
int32 NetAIOConfigureTest(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig);
int32 NetAIOConfigure(NetAIO *ob,const real32* low,const real32* high,const int32* prec,const int32* rate,const int32* trigger,int32 itrig);
int32 NetAIOITrig(NetAIO *ob,int32 itrig);
int32 NetAIOGet(NetAIO *ob,int32 channel);
int32 NetAIOPut(NetAIO *ob,int32 channel,int32 value);
int32 NetAIOReady(NetAIO *ob,int32 channel);
int32 NetAIOGets8(NetAIO *ob,int8* buf);
int32 NetAIOGets16(NetAIO *ob,int16* buf);
int32 NetAIOGets32(NetAIO *ob,int32* buf);
int32 NetAIOPuts8(NetAIO *ob,const int8* buf);
int32 NetAIOPuts16(NetAIO *ob,const int16* buf);
int32 NetAIOPuts32(NetAIO *ob,const int32* buf);
int32 NetAIOReadys8(NetAIO *ob,const int8* buf);
int32 NetAIOReadys16(NetAIO *ob,const int16* buf);
int32 NetAIOReadys32(NetAIO *ob,const int32* buf);

typedef struct NetBus NetBus;

struct NetBus {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  unsigned char FUNC(Peek8)(void *me,int Address);
  void FUNC(Poke8)(void *me,int Address,unsigned char Value);
  unsigned short FUNC(Peek16)(void *me,int Address);
  void FUNC(Poke16)(void *me,int Address,unsigned short Value);
  unsigned FUNC(Peek32)(void *me,int Address);
  void FUNC(Poke32)(void *me,int Address,unsigned Value);
  int FUNC(BitGet8)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign8)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet8)(void *me,int Address,int BitNumber);
  void FUNC(BitClear8)(void *me,int Address,int BitNumber);
  int FUNC(BitGet16)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign16)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet16)(void *me,int Address,int BitNumber);
  void FUNC(BitClear16)(void *me,int Address,int BitNumber);
  int FUNC(BitGet32)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign32)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet32)(void *me,int Address,int BitNumber);
  void FUNC(BitClear32)(void *me,int Address,int BitNumber);
  void FUNC(PeekStream)(void *me,int address,int direction,char *dest);
  void FUNC(PokeStream)(void *me,int address,int direction,const char *data);
  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int ForceAll);
  int FUNC(BitToggle8)(void *me,int Address,int BitNumber);
  int FUNC(BitToggle16)(void *me,int Address,int BitNumber);
  int FUNC(BitToggle32)(void *me,int Address,int BitNumber);
  unsigned char FUNC(Assign8X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned short FUNC(Assign16X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned FUNC(Assign32X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned char FUNC(BitsGet8)(void *me,int Address,int BitMSB,int BitLSB);
  unsigned short FUNC(BitsGet16)(void *me,int Address,int BitMSB,int BitLSB);
  unsigned FUNC(BitsGet32)(void *me,int Address,int BitMSB,int BitLSB);
  int InitStatus;
  unsigned LockBase;
  int deferlockW;
  int deferlockR;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetBusInit(tsctl *,int instance);
void *NetBusFini(NetBus *);
int32 NetBusLock(NetBus *ob,uint32 num,int32 flags);
int32 NetBusUnlock(NetBus *ob,uint32 num,int32 flags);
int32 NetBusPreempt(NetBus *ob);
uint8 NetBusPeek8(NetBus *ob,int32 Address);
void NetBusPoke8(NetBus *ob,int32 Address,uint8 Value);
uint16 NetBusPeek16(NetBus *ob,int32 Address);
void NetBusPoke16(NetBus *ob,int32 Address,uint16 Value);
uint32 NetBusPeek32(NetBus *ob,int32 Address);
void NetBusPoke32(NetBus *ob,int32 Address,uint32 Value);
int32 NetBusBitGet8(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign8(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet8(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear8(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitGet16(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign16(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet16(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear16(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitGet32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign32(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusPeekStream(NetBus *ob,int32 address,int32 direction,int8* dest);
void NetBusPokeStream(NetBus *ob,int32 address,int32 direction,const int8* data);
void NetBusRefresh(NetBus *ob);
void NetBusCommit(NetBus *ob,int32 ForceAll);
int32 NetBusBitToggle8(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitToggle16(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitToggle32(NetBus *ob,int32 Address,int32 BitNumber);
uint8 NetBusAssign8X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint16 NetBusAssign16X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint32 NetBusAssign32X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint8 NetBusBitsGet8(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);
uint16 NetBusBitsGet16(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);
uint32 NetBusBitsGet32(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);

typedef struct NetCAN NetCAN;

struct NetCAN {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  CANResult FUNC(Rx)(void *me,CANMessage message[1]);
  CANResult FUNC(Tx)(void *me,unsigned flags,unsigned id,const char *data);
  unsigned FUNC(BaudSet)(void *me,unsigned opt_baud);
  unsigned FUNC(BaudGet)(void *me);
  void FUNC(Abort)(void *me);
  CANResult FUNC(RxMulti)(void *me,CANMessage *msg,int min);
  int InitStatus;
  unsigned LockBase;
  int deferlock;
  int irq;
  int CAN_TX;
  int CAN_RX;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetCANInit(tsctl *,int instance);
void *NetCANFini(NetCAN *);
CANResult NetCANRx(NetCAN *ob,CANMessage message[1]);
CANResult NetCANTx(NetCAN *ob,uint32 flags,uint32 id,const int8* data);
uint32 NetCANBaudSet(NetCAN *ob,uint32 opt_baud);
uint32 NetCANBaudGet(NetCAN *ob);
void NetCANAbort(NetCAN *ob);
CANResult NetCANRxMulti(NetCAN *ob,CANMessage* msg,int32 min);

typedef struct NetDIO NetDIO;

struct NetDIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int ForceAll);
  void FUNC(Set)(void *me,int DIONum,DIOState State);
  DIOState FUNC(Get)(void *me,int DIONum);
  void FUNC(SetAsync)(void *me,int DIONum,DIOState State);
  DIOState FUNC(GetAsync)(void *me,int DIONum);
  void FUNC(Wait)(void *me,int *match,int min,int max,const int *nh,const int *nl);
  unsigned FUNC(Count)(void *me);
  DIOCaps FUNC(Capabilities)(void *me,unsigned num);
  int FUNC(GetMulti)(void *me,char *state,int offset);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetDIOInit(tsctl *,int instance);
void *NetDIOFini(NetDIO *);
int32 NetDIOLock(NetDIO *ob,uint32 num,int32 flags);
int32 NetDIOUnlock(NetDIO *ob,uint32 num,int32 flags);
int32 NetDIOPreempt(NetDIO *ob);
void NetDIORefresh(NetDIO *ob);
void NetDIOCommit(NetDIO *ob,int32 ForceAll);
void NetDIOSet(NetDIO *ob,int32 DIONum,DIOState State);
DIOState NetDIOGet(NetDIO *ob,int32 DIONum);
void NetDIOSetAsync(NetDIO *ob,int32 DIONum,DIOState State);
DIOState NetDIOGetAsync(NetDIO *ob,int32 DIONum);
void NetDIOWait(NetDIO *ob,int32* match,int32 min,int32 max,const int32* nh,const int32* nl);
uint32 NetDIOCount(NetDIO *ob);
DIOCaps NetDIOCapabilities(NetDIO *ob,uint32 num);
int32 NetDIOGetMulti(NetDIO *ob,int8* state,int32 offset);

typedef struct NetDIORaw NetDIORaw;

struct NetDIORaw {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(DirSet)(void *me,int num,int asOutput);
  void FUNC(DataSet)(void *me,int num,int asHigh);
  int FUNC(DirGet)(void *me,int num);
  int FUNC(DataGet)(void *me,int num);
  unsigned FUNC(Count)(void *me);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetDIORawInit(tsctl *,int instance);
void *NetDIORawFini(NetDIORaw *);
int32 NetDIORawLock(NetDIORaw *ob,uint32 num,int32 flags);
int32 NetDIORawUnlock(NetDIORaw *ob,uint32 num,int32 flags);
int32 NetDIORawPreempt(NetDIORaw *ob);
void NetDIORawDirSet(NetDIORaw *ob,int32 num,int32 asOutput);
void NetDIORawDataSet(NetDIORaw *ob,int32 num,int32 asHigh);
int32 NetDIORawDirGet(NetDIORaw *ob,int32 num);
int32 NetDIORawDataGet(NetDIORaw *ob,int32 num);
uint32 NetDIORawCount(NetDIORaw *ob);

typedef struct NetEDIO NetEDIO;

struct NetEDIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  int *FUNC(QueryFunction)(void *me,EDIOType type);
  int FUNC(PWM)(void *me,int num,unsigned periodHigh,unsigned periodLow);
  int FUNC(QueryPWM)(void *me,int num,unsigned periodHigh[1],unsigned periodLow[1]);
  int FUNC(PWMfd)(void *me,int num,unsigned freq,unsigned DC);
  int FUNC(QueryPWMfd)(void *me,int num,unsigned freq[1],unsigned DC[1]);
  int FUNC(QuadratureCount)(void *me,int num);
  unsigned long long FUNC(EdgeCount)(void *me,int num,int edge);
  int FUNC(Glitched)(void *me,int num);
  int FUNC(HBridge)(void *me,int num,HBState state);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetEDIOInit(tsctl *,int instance);
void *NetEDIOFini(NetEDIO *);
int32 NetEDIOLock(NetEDIO *ob,uint32 num,int32 flags);
int32 NetEDIOUnlock(NetEDIO *ob,uint32 num,int32 flags);
int32 NetEDIOPreempt(NetEDIO *ob);
int32* NetEDIOQueryFunction(NetEDIO *ob,EDIOType type);
int32 NetEDIOPWM(NetEDIO *ob,int32 num,uint32 periodHigh,uint32 periodLow);
int32 NetEDIOQueryPWM(NetEDIO *ob,int32 num,uint32 periodHigh[1],uint32 periodLow[1]);
int32 NetEDIOPWMfd(NetEDIO *ob,int32 num,uint32 freq,uint32 DC);
int32 NetEDIOQueryPWMfd(NetEDIO *ob,int32 num,uint32 freq[1],uint32 DC[1]);
int32 NetEDIOQuadratureCount(NetEDIO *ob,int32 num);
uint32 NetEDIOEdgeCount(NetEDIO *ob,int32 num,int32 edge);
int32 NetEDIOGlitched(NetEDIO *ob,int32 num);
int32 NetEDIOHBridge(NetEDIO *ob,int32 num,HBState state);

typedef struct NetPin NetPin;

struct NetPin {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  PinMode FUNC(ModeGet)(void *me,int PinNumber);
  PinResult FUNC(ModeSet)(void *me,int PinNumber,PinMode Mode);
  int InitStatus;
  unsigned LockBase;
  int deferlock;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetPinInit(tsctl *,int instance);
void *NetPinFini(NetPin *);
int32 NetPinLock(NetPin *ob,uint32 num,int32 flags);
int32 NetPinUnlock(NetPin *ob,uint32 num,int32 flags);
int32 NetPinPreempt(NetPin *ob);
PinMode NetPinModeGet(NetPin *ob,int32 PinNumber);
PinResult NetPinModeSet(NetPin *ob,int32 PinNumber,PinMode Mode);

typedef struct NetSPI NetSPI;

struct NetSPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  SPIResult FUNC(Write)(void *me,int adrs,const unsigned char *buf);
  SPIResult FUNC(Read)(void *me,int adrs,unsigned char *buf);
  SPIResult FUNC(ReadWrite)(void *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
  SPIResult FUNC(ClockSet)(void *me,unsigned hz);
  SPIResult FUNC(EdgeSet)(void *me,int posedge);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetSPIInit(tsctl *,int instance);
void *NetSPIFini(NetSPI *);
int32 NetSPILock(NetSPI *ob,uint32 num,int32 flags);
int32 NetSPIUnlock(NetSPI *ob,uint32 num,int32 flags);
int32 NetSPIPreempt(NetSPI *ob);
SPIResult NetSPIWrite(NetSPI *ob,int32 adrs,const uint8* buf);
SPIResult NetSPIRead(NetSPI *ob,int32 adrs,uint8* buf);
SPIResult NetSPIReadWrite(NetSPI *ob,int32 adrs,const uint8* wbuf,uint8* rbuf);
SPIResult NetSPIClockSet(NetSPI *ob,uint32 hz);
SPIResult NetSPIEdgeSet(NetSPI *ob,int32 posedge);

typedef struct NetSystem NetSystem;

struct NetSystem {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(ClassCount)(void *me);
  int FUNC(InstanceCount)(void *me,int ClassNumber);
  int FUNC(APICount)(void *me,int ClassNumber);
  int FUNC(LockCount)(void *me);
  LockHolderInf*FUNC(LockHolderInfo)(void *me);
  ConnectionWaitInf*FUNC(ConnWaitInfo)(void *me);
  SystemResult FUNC(CANBusGet)(void *me,int CANInstance);
  unsigned FUNC(BuildTime)(void *me);
  int FUNC(ModelId)(void *me);
  int FUNC(BaseBoardId)(void *me);
  int FUNC(MapLength)(void *me);
  char *FUNC(MapGet)(void *me,int MapIndex,int Value[1]);
  int FUNC(MapLookup)(void *me,const char *String);
  char *FUNC(MapLookupPartial)(void *me,const char *StringPrefix,int Value);
  SystemResult FUNC(MapAdd)(void *me,const char *String,int Value);
  SystemResult FUNC(MapDelete)(void *me,const char *String);
  char *FUNC(Note)(void *me,const char *Message);
  char *FUNC(Version)(void *me);
  unsigned FUNC(UptimeServer)(void *me);
  unsigned FUNC(UptimeHost)(void *me);
  int FUNC(FPGARevision)(void *me);
  int FUNC(EchoNumber)(void *me,int n);
  int InitStatus;
  unsigned maplock;
  NameValuePair *map;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetSystemInit(tsctl *,int instance);
void *NetSystemFini(NetSystem *);
int32 NetSystemClassCount(NetSystem *ob);
int32 NetSystemInstanceCount(NetSystem *ob,int32 ClassNumber);
int32 NetSystemAPICount(NetSystem *ob,int32 ClassNumber);
int32 NetSystemLockCount(NetSystem *ob);
LockHolderInf* NetSystemLockHolderInfo(NetSystem *ob);
ConnectionWaitInf* NetSystemConnWaitInfo(NetSystem *ob);
SystemResult NetSystemCANBusGet(NetSystem *ob,int32 CANInstance);
uint32 NetSystemBuildTime(NetSystem *ob);
int32 NetSystemModelId(NetSystem *ob);
int32 NetSystemBaseBoardId(NetSystem *ob);
int32 NetSystemMapLength(NetSystem *ob);
int8* NetSystemMapGet(NetSystem *ob,int32 MapIndex,int32 Value[1]);
int32 NetSystemMapLookup(NetSystem *ob,const int8* String);
int8* NetSystemMapLookupPartial(NetSystem *ob,const int8* StringPrefix,int32 Value);
SystemResult NetSystemMapAdd(NetSystem *ob,const int8* String,int32 Value);
SystemResult NetSystemMapDelete(NetSystem *ob,const int8* String);
int8* NetSystemNote(NetSystem *ob,const int8* Message);
int8* NetSystemVersion(NetSystem *ob);
uint32 NetSystemUptimeServer(NetSystem *ob);
uint32 NetSystemUptimeHost(NetSystem *ob);
int32 NetSystemFPGARevision(NetSystem *ob);
int32 NetSystemEchoNumber(NetSystem *ob,int32 n);

typedef struct NetTime NetTime;

struct NetTime {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  unsigned FUNC(Wait)(void *me,unsigned microseconds);
  void FUNC(Delay)(void *me,unsigned microseconds);
  unsigned FUNC(Tick)(void *me);
  unsigned FUNC(usElapsed)(void *me,unsigned start);
  unsigned FUNC(usFuture)(void *me,unsigned start,unsigned microseconds);
  TimeResult FUNC(TimeoutQ)(void *me,unsigned start,unsigned end);
  unsigned FUNC(TPS)(void *me);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetTimeInit(tsctl *,int instance);
void *NetTimeFini(NetTime *);
uint32 NetTimeWait(NetTime *ob,uint32 microseconds);
void NetTimeDelay(NetTime *ob,uint32 microseconds);
uint32 NetTimeTick(NetTime *ob);
uint32 NetTimeusElapsed(NetTime *ob,uint32 start);
uint32 NetTimeusFuture(NetTime *ob,uint32 start,uint32 microseconds);
TimeResult NetTimeTimeoutQ(NetTime *ob,uint32 start,uint32 end);
uint32 NetTimeTPS(NetTime *ob);


typedef struct NetTWI NetTWI;

struct NetTWI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  TWIResult FUNC(Write)(void *me,int devadr,int adrslen,int adrs,const char *bytes);
  TWIResult FUNC(Read)(void *me,int devadr,int adrslen,int adrs,char *bytes);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetTWIInit(tsctl *,int instance);
void *NetTWIFini(NetTWI *);
int32 NetTWILock(NetTWI *ob,uint32 num,int32 flags);
int32 NetTWIUnlock(NetTWI *ob,uint32 num,int32 flags);
int32 NetTWIPreempt(NetTWI *ob);
TWIResult NetTWIWrite(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,const int8* bytes);
TWIResult NetTWIRead(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,int8* bytes);

#endif

