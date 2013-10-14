#ifndef __libtsctl_h
#define __libtsctl_h
#define FUNC(x) (*x)

typedef struct LockHolderInf LockHolderInf;
typedef struct ConnectionWaitInf ConnectionWaitInf;
typedef struct NameValuePair NameValuePair;
typedef struct System System;
struct LockHolderInf {
  int pid;
  int count;
};

struct ConnectionWaitInf {
  int pid;
  int wait;
};

struct NameValuePair {
  char *name;
  int value;
};

typedef enum SystemResult{
  SystemSuccess=1,SystemErrorNoSuchKey=-1,SystemErrorNoSuchCANInstance=-2
}SystemResult;

enum {
	NetSystem_ClassCount=0,
	NetSystem_InstanceCount=1,
	NetSystem_APICount=2,
	NetSystem_LockCount=3,
	NetSystem_LockHolderInfo=4,
	NetSystem_ConnWaitInfo=5,
	NetSystem_CANBusGet=6,
	NetSystem_BuildTime=7,
	NetSystem_ModelId=8,
	NetSystem_BaseBoardId=9,
	NetSystem_MapLength=10,
	NetSystem_MapGet=11,
	NetSystem_MapLookup=12,
	NetSystem_MapLookupPartial=13,
	NetSystem_MapAdd=14,
	NetSystem_MapDelete=15,
	NetSystem_Note=16,
	NetSystem_Version=17,
	NetSystem_UptimeServer=18,
	NetSystem_UptimeHost=19,
	NetSystem_FPGARevision=20,
	NetSystem_EchoNumber=21,
	XSystem_APICount=22
};
struct System {
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
};

#ifndef LIBTSCTL_VERSION
#define LIBTSCTL_VERSION "0.99+"
#endif
#ifndef LIBTSCTL_ORGANIZATION
#define LIBTSCTL_ORGANIZATION customer
#endif
#define LIBTSCTL_FULL_VERSION LIBTSCTL_VERSION "-" STRINGIFY(LIBTSCTL_ORGANIZATION)

typedef struct LocalSystem LocalSystem;
struct LocalSystem {
	void *FUNC(Init)(LocalSystem *me);
	void FUNC(Fini)(LocalSystem *me);
	int FUNC(ClassCount)(LocalSystem *me);
	int FUNC(InstanceCount)(LocalSystem *me,int ClassNumber);
	int FUNC(APICount)(LocalSystem *me,int ClassNumber);
	int FUNC(LockCount)(LocalSystem *me);
	LockHolderInf*FUNC(LockHolderInfo)(LocalSystem *me);
	ConnectionWaitInf*FUNC(ConnWaitInfo)(LocalSystem *me);
	SystemResult FUNC(CANBusGet)(LocalSystem *me,int CANInstance);
	unsigned FUNC(BuildTime)(LocalSystem *me);
	int FUNC(ModelId)(LocalSystem *me);
	int FUNC(BaseBoardId)(LocalSystem *me);
	int FUNC(MapLength)(LocalSystem *me);
	char *FUNC(MapGet)(LocalSystem *me,int MapIndex,int Value[1]);
	int FUNC(MapLookup)(LocalSystem *me,const char *String);
	char *FUNC(MapLookupPartial)(LocalSystem *me,const char *StringPrefix,int Value);
	SystemResult FUNC(MapAdd)(LocalSystem *me,const char *String,int Value);
	SystemResult FUNC(MapDelete)(LocalSystem *me,const char *String);
	char *FUNC(Note)(LocalSystem *me,const char *Message);
	char *FUNC(Version)(LocalSystem *me);
	unsigned FUNC(UptimeServer)(LocalSystem *me);
	unsigned FUNC(UptimeHost)(LocalSystem *me);
	int FUNC(FPGARevision)(LocalSystem *me);
	int FUNC(EchoNumber)(LocalSystem *me,int n);
	int InitStatus;
	unsigned maplock;
	NameValuePair *map;
};

void *LocalSystemInit(LocalSystem* ob);
void LocalSystemFini(LocalSystem* ob);
int LocalSystemClassCount(LocalSystem* ob);
int LocalSystemInstanceCount(LocalSystem* ob,int ClassNumber);
int LocalSystemAPICount(LocalSystem* ob,int ClassNumber);
int LocalSystemLockCount(LocalSystem* ob);
LockHolderInf *LocalSystemLockHolderInfo(LocalSystem* ob);
ConnectionWaitInf *LocalSystemConnWaitInfo(LocalSystem* ob);
SystemResult LocalSystemCANBusGet(LocalSystem* ob,int CANInstance);
unsigned LocalSystemBuildTime(LocalSystem* ob);
int LocalSystemModelId(LocalSystem* ob);
int LocalSystemBaseBoardId(LocalSystem* ob);
int LocalSystemMapLength(LocalSystem* ob);
char *LocalSystemMapGet(LocalSystem* ob,int MapIndex,int Value[1]);
int LocalSystemMapLookup(LocalSystem* ob,const char *String);
char *LocalSystemMapLookupPartial(LocalSystem* ob,const char *StringPrefix,int Value);
SystemResult LocalSystemMapAdd(LocalSystem* ob,const char *String,int Value);
SystemResult LocalSystemMapDelete(LocalSystem* ob,const char *String);
char *LocalSystemNote(LocalSystem* ob,const char *Message);
char *LocalSystemVersion(LocalSystem* ob);
unsigned LocalSystemUptimeServer(LocalSystem* ob);
unsigned LocalSystemUptimeHost(LocalSystem* ob);
int LocalSystemFPGARevision(LocalSystem* ob);
int LocalSystemEchoNumber(LocalSystem* ob,int n);

typedef struct Bus Bus;
enum {
	NetBus_Lock=0,
	NetBus_Unlock=1,
	NetBus_Preempt=2,
	NetBus_Peek8=3,
	NetBus_Poke8=4,
	NetBus_Peek16=5,
	NetBus_Poke16=6,
	NetBus_Peek32=7,
	NetBus_Poke32=8,
	NetBus_BitGet8=9,
	NetBus_BitAssign8=10,
	NetBus_BitSet8=11,
	NetBus_BitClear8=12,
	NetBus_BitGet16=13,
	NetBus_BitAssign16=14,
	NetBus_BitSet16=15,
	NetBus_BitClear16=16,
	NetBus_BitGet32=17,
	NetBus_BitAssign32=18,
	NetBus_BitSet32=19,
	NetBus_BitClear32=20,
	NetBus_PeekStream=21,
	NetBus_PokeStream=22,
	NetBus_Refresh=23,
	NetBus_Commit=24,
	NetBus_BitToggle8=25,
	NetBus_BitToggle16=26,
	NetBus_BitToggle32=27,
	NetBus_Assign8X=28,
	NetBus_Assign16X=29,
	NetBus_Assign32X=30,
	NetBus_BitsGet8=31,
	NetBus_BitsGet16=32,
	NetBus_BitsGet32=33,
	XBus_APICount=34
};
struct Bus {
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
};

typedef struct CANMessage CANMessage;
typedef struct CAN CAN;
struct CANMessage {
  unsigned flags;
  unsigned id;
  unsigned t_sec;
  unsigned t_usec;
  unsigned length;
  unsigned char data[8];
};

typedef enum CANEvent{
  CANEventBusError=128,CANEventArbLost=64,CANEventErrorPassive=32,CANEventWakeUp=16,CANEventDataOverrun=8,CANEventErrorWarning=4,CANEventTransmitDone=2,CANEventReceiveReady=1
}CANEvent;

typedef enum CANFlags{
  FLAG_BUS_ERROR=1,FLAG_ERROR_PASSIVE=2,FLAG_DATA_OVERRUN=4,FLAG_ERROR_WARNING=8,FLAG_RTR=16,FLAG_EXT_ID=32,FLAG_LOCAL=64,FLAG_CONTROL=128
}CANFlags;

typedef enum CANResult{
  CANErrorBusWarning=-6,CANErrorBusOff=-5,CANErrorFIFOUnexpectedlyEmpty=-4,CANErrorCannotTxControlMessage=-3,CANErrorAborted=-2,CANSuccess=1
}CANResult;

enum {
	NetCAN_Rx=0,
	NetCAN_Tx=1,
	NetCAN_BaudSet=2,
	NetCAN_BaudGet=3,
	NetCAN_Abort=4,
	NetCAN_RxMulti=5,
	XCAN_APICount=6
};
struct CAN {
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
};

typedef struct DIORaw DIORaw;
enum {
	NetDIORaw_Lock=0,
	NetDIORaw_Unlock=1,
	NetDIORaw_Preempt=2,
	NetDIORaw_DirSet=3,
	NetDIORaw_DataSet=4,
	NetDIORaw_DirGet=5,
	NetDIORaw_DataGet=6,
	NetDIORaw_Count=7,
	XDIORaw_APICount=8
};
struct DIORaw {
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
};

typedef struct DIO DIO;
typedef enum DIOState{
  INPUT_LOW=-3,INPUT_HIGH=-2,INPUT=-1,LOW=0,HIGH=1
}DIOState;

typedef enum DIOCaps{
  DIO_NOT_PRESENT=0,DIO_CAN_INPUT=1,DIO_CAN_DRIVE_HIGH=2,DIO_HIGH_SIDE=3,DIO_CAN_DRIVE_LOW=4,DIO_LOW_SIDE=5,DIO_OUTPUT_ONLY=6,DIO_NORMAL=7
}DIOCaps;

enum {
	NetDIO_Lock=0,
	NetDIO_Unlock=1,
	NetDIO_Preempt=2,
	NetDIO_Refresh=3,
	NetDIO_Commit=4,
	NetDIO_Set=5,
	NetDIO_Get=6,
	NetDIO_SetAsync=7,
	NetDIO_GetAsync=8,
	NetDIO_Wait=9,
	NetDIO_Count=10,
	NetDIO_Capabilities=11,
	NetDIO_GetMulti=12,
	XDIO_APICount=13
};
struct DIO {
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
};

typedef struct Pin Pin;
typedef enum PinMode{
  MODE_DIO=0,MODE_CAN=1,MODE_SPI=2,MODE_ADC=3,MODE_TWI=4,MODE_UART=5,MODE_TS=6,MODE_BUS=7,MODE_PWM=8,MODE_CLK=9,MODE_UNKNOWN=-1
}PinMode;

typedef enum PinResult{
  PinSuccess=1,PinErrorModeInvalid=-13
}PinResult;

enum {
	NetPin_Lock=0,
	NetPin_Unlock=1,
	NetPin_Preempt=2,
	NetPin_ModeGet=3,
	NetPin_ModeSet=4,
	XPin_APICount=5
};
struct Pin {
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
};

typedef struct Time Time;
typedef enum TimeResult{
  TimeoutOccurred=1,TimeoutDidNotOccur=0
}TimeResult;

enum {
	NetTime_Wait=0,
	NetTime_Delay=1,
	NetTime_Tick=2,
	NetTime_usElapsed=3,
	NetTime_usFuture=4,
	NetTime_TimeoutQ=5,
	NetTime_TPS=6,
	XTime_APICount=7
};
struct Time {
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
};

typedef struct TWI TWI;
typedef enum TWIMode{
  TWIModeSlave=0,TWIModeMaster=1
}TWIMode;

typedef enum TWIResult{
  TWISuccess=1,TWIErrorPortInvalid=-1,TWIErrorModeUnsupported=-2,TWIErrorBaudUnconstrained=-3,TWIErrorHardware=-4,TWIErrorHandle=-5,TWIErrorWriteNAck=-6,TWIErrorDataNAck=-7,TWIErrorReadNack=-8,TWIErrorSDALow=-9,TWIErrorSCLLow=-10,TWIErrorAdrsLen=-11,TWIErrorTimeout=-12,TWIErrorOverrun=-13,TWIErrorArbLost=-14,TWIErrorUnknown=-999,TWIErrorOpInvalid=-15
}TWIResult;

typedef enum TWIOps{
  TWIOpWrite=0,TWIOpRead=1
}TWIOps;

enum {
	NetTWI_Lock=0,
	NetTWI_Unlock=1,
	NetTWI_Preempt=2,
	NetTWI_Write=3,
	NetTWI_Read=4,
	XTWI_APICount=5
};
struct TWI {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	TWIResult FUNC(Write)(void *me,int devadr,int adrslen,int adrs,const char *bytes);
	TWIResult FUNC(Read)(void *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
};

typedef struct SPI SPI;
typedef enum SPIResult{
  SPISuccess=1,SPIErrorTimeout=-9,SPIErrorInvalidAddress=-10,SPIErrorInvalidEdge=-11,SPIErrorInvalidHz=-12
}SPIResult;

enum {
	NetSPI_Lock=0,
	NetSPI_Unlock=1,
	NetSPI_Preempt=2,
	NetSPI_Write=3,
	NetSPI_Read=4,
	NetSPI_ReadWrite=5,
	NetSPI_ClockSet=6,
	NetSPI_EdgeSet=7,
	XSPI_APICount=8
};
struct SPI {
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
};

typedef struct VoltageSubRange VoltageSubRange;
typedef struct VoltageRange VoltageRange;
typedef struct ActualVoltageRange ActualVoltageRange;
typedef struct PeriodRange PeriodRange;
typedef struct AIO AIO;
struct VoltageSubRange {
  float start;
  float step;
  unsigned count;
};

struct VoltageRange {
  VoltageSubRange low;
  VoltageSubRange high;
};

struct ActualVoltageRange {
  float low;
  float high;
};

struct PeriodRange {
  unsigned start;
  unsigned step;
  unsigned count;
};

typedef enum AIOType{
  AIO_ADC=1,AIO_DAC=2
}AIOType;

enum {
	NetAIO_Lock=0,
	NetAIO_Unlock=1,
	NetAIO_Preempt=2,
	NetAIO_Type=3,
	NetAIO_VoltageRangeList=4,
	NetAIO_PrecisionList=5,
	NetAIO_PeriodRangeList=6,
	NetAIO_TriggerList=7,
	NetAIO_Channels=8,
	NetAIO_Reset=9,
	NetAIO_ChannelEnable=10,
	NetAIO_ChannelSamplePeriod=11,
	NetAIO_ChannelPrecision=12,
	NetAIO_ChannelVoltageRange=13,
	NetAIO_Configuration=14,
	NetAIO_ConfigureTest=15,
	NetAIO_Configure=16,
	NetAIO_ITrig=17,
	NetAIO_Get=18,
	NetAIO_Put=19,
	NetAIO_Ready=20,
	NetAIO_Gets8=21,
	NetAIO_Gets16=22,
	NetAIO_Gets32=23,
	NetAIO_Puts8=24,
	NetAIO_Puts16=25,
	NetAIO_Puts32=26,
	NetAIO_Readys8=27,
	NetAIO_Readys16=28,
	NetAIO_Readys32=29,
	XAIO_APICount=30
};
struct AIO {
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
};

typedef struct EDIO EDIO;
typedef enum EDIOType{
  EDIO_PWM=1,EDIO_QUADRATURE=2,EDIO_EDGECOUNT=3,EDIO_GLITCHED=4
}EDIOType;

typedef enum HBState{
  HB_LEFT=1,HB_RIGHT=2,HB_FREE_RUNNING=3,HB_BRAKING=4
}HBState;

enum {
	NetEDIO_Lock=0,
	NetEDIO_Unlock=1,
	NetEDIO_Preempt=2,
	NetEDIO_QueryFunction=3,
	NetEDIO_PWM=4,
	NetEDIO_QueryPWM=5,
	NetEDIO_PWMfd=6,
	NetEDIO_QueryPWMfd=7,
	NetEDIO_QuadratureCount=8,
	NetEDIO_EdgeCount=9,
	NetEDIO_Glitched=10,
	NetEDIO_HBridge=11,
	XEDIO_APICount=12
};
struct EDIO {
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
};

typedef enum TS_CPU {
  CPU_UNKNOWN=0,CPU_EP9302, CPU_CAVIUM, CPU_ATMEL, CPU_X86, CPU_FREESCALE,
  CPU_MARVELL_PXA168, CPU_MARVELL_MV88F5182, CPU_CUSTOM, CPU_7400_7670
} TS_CPU;

TS_CPU TSCPUGet(void);
const char *TSArchGet();
int TSModelGet();

typedef struct Thread Thread;

enum {
  LOCK_TRY, LOCK_FOD, LOCK_SOD
};

typedef void *(*ThreadFunction)(void *);
typedef void (*ThreadDestructor)(void *);

struct Thread {
  // public, R/W
  void *data;
  // public, RO
  char *name; int instance;
  int pid;
  int socket;
  ThreadFunction f;
};

int ThreadInit();
void ThreadFini(void *);
Thread *ThreadNew(char *name,int inst,ThreadFunction func,int socket,
		  void *data,ThreadDestructor destor);
int ThreadEnterBlock();
int ThreadLeaveBlock();
unsigned ThreadMutexAllocate(int);
unsigned ThreadLockAllocate(int);
unsigned ThreadMutexCount();
unsigned ThreadLockCount();
int ThreadMutexLock(unsigned num,int mode);
int ThreadMutexUnlock(unsigned num);
void ThreadUnlockAll(Thread *);
int ThreadWait(int (*f)(int),unsigned num,int mode);
int ThreadSignalIf(int (*f)(int),unsigned num);
int ThreadLockW(unsigned num,int mode);
int ThreadLockR(unsigned num,int mode);
int ThreadUnlockW(unsigned num);
int ThreadUnlockR(unsigned num);
Thread *ThreadLockHolder(unsigned num);
Thread *ThreadMutexHolder(unsigned num);

// AIO
#define AIO_PR(start,step,count) ((PeriodRange){start,step,count});
#define AIO_VR(lowstart,lowstep,lowcount,highstart,highstep,highcount) ((VoltageRange){(VoltageSubRange){lowstart,lowstep,lowcount},(VoltageSubRange){highstart,highstep,highcount}})
#define AIO_HZ(hz) ((int)(1000000000/hz))

// CAN
/*
  Raw Packet Format:

  UINT8    flags:
               control information present (reserved for future use)
               message originates from this node (unused)
               message has extended ID
               remote transmission request (RTR)
               error warning
               data overrun
               error passive
               bus error
  UINT32   id
  UINT32   timestamp_seconds
  UINT32   timestamp_microseconds
  UINT8    bytes
  UINT8[8] data
 */
#include <sys/time.h>
#include <sys/select.h>
/*
  Statistics:
  Tx count
  Rx count
  overruns
  other error counters
 */
typedef struct CANPort {
  CAN *can;
  int port;
} CANPort;


// DIO
__attribute__((always_inline)) 
static inline DIOState DIOValue(DIOState state) {
  switch (state) {
  case INPUT_LOW:
  case LOW:
    return LOW;
  case INPUT_HIGH:
  case HIGH:
    return HIGH;
  default: return LOW;
  }
}

__attribute__((always_inline)) 
static inline const char *DIOValueString(DIOState state) {
  switch(state) {
  case INPUT_LOW: return "InputLow";
  case INPUT_HIGH: return "InputHigh";
  case INPUT: return "Input";
  case LOW: return "Low";
  case HIGH: return "High";
  default: return "Invalid";
  }
}

// Pin
__attribute__((always_inline)) 
static inline const char *PinModeString(PinMode mode) {
  switch (mode) {
  case MODE_DIO: return "DIO";
  case MODE_CAN: return "CAN";
  case MODE_SPI: return "SPI";
  case MODE_ADC: return "ADC";
  case MODE_TWI: return "TWI";
  case MODE_UART: return "UART";
  case MODE_TS: return "TS";
  case MODE_UNKNOWN: return "UNKNOWN";
  default: return "ILLEGAL";
  }
}

// LocalSystem
extern const char copyright[] __attribute__ ((weak)) ;
extern const char build[] __attribute__ ((weak)) ;
extern const char compiledate[] __attribute__ ((weak));
extern const char archstr[] __attribute__ ((weak)) ;
extern const int compiletime __attribute__ ((weak)) ;

// MMapBus
void *MMapBusInit2(void *,void *mem,int Pages);

// SJA1000CAN
#define BUFLEN sizeof(CANMessage)*32
void *CANStart(void *arg);
void CANStop();

// ts81x0Pin
void ts81x0PinPostInit(void *,int CAN_TX1,int CAN_TX2,int CAN_RX1,int CAN_RX2);

enum {
  ClassSystem = 0,
  ClassBus = 1,
  ClassTime = 2,
  ClassPin = 3,
  ClassDIORaw = 4,
  ClassDIO = 5,
  ClassTWI = 6,
  ClassCAN = 7,
  ClassSPI = 8,
  ClassAIO = 9,
  ClassEDIO = 10
};
typedef enum {
  ArchTypeNone = -1,
  ArchTypeCPU = 0,
  ArchTypeTSSocketBB = 1,
  ArchTypePC104 = 2
} ArchType;

#define ClassesCount (ClassEDIO+1)

#ifdef __cplusplus
extern "C" {
#endif
  System *SystemInit(int inst);
  Time *TimeInit(int inst);
  Bus *BusInit(int inst);
  Pin *PinInit(int inst);
  CAN *CANInit(int inst);
  DIORaw *DIORawInit(int inst);
  DIO *DIOInit(int inst);
  TWI *TWIInit(int inst);
  SPI *SPIInit(int inst);
  AIO *AIOInit(int inst);
  EDIO *EDIOInit(int inst);
#ifdef __cplusplus
}
#endif
#endif
