#ifndef __NetCANctl_h
#define __NetCANctl_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct NetCANctl NetCANctl;
struct NetCANctl {
	void *FUNC(Init)(NetCANctl *me,int socket);
	void FUNC(Fini)(NetCANctl *me);
	CANResult FUNC(Rx)(NetCANctl *me,CANMessage message[1]);
	CANResult FUNC(Tx)(NetCANctl *me,unsigned flags,unsigned id,const char *data);
	unsigned FUNC(BaudSet)(NetCANctl *me,unsigned opt_baud);
	unsigned FUNC(BaudGet)(NetCANctl *me);
	void FUNC(Abort)(NetCANctl *me);
	CANResult FUNC(RxMulti)(NetCANctl *me,CANMessage *msg,int min);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int irq;
	int CAN_TX;
	int CAN_RX;
	int socket;
};

void *NetCANctlInit(NetCANctl* ob,int socket);
void NetCANctlFini(NetCANctl* ob);
CANResult NetCANctlRx(NetCANctl* ob,CANMessage message[1]);
CANResult NetCANctlTx(NetCANctl* ob,unsigned flags,unsigned id,const char *data);
unsigned NetCANctlBaudSet(NetCANctl* ob,unsigned opt_baud);
unsigned NetCANctlBaudGet(NetCANctl* ob);
void NetCANctlAbort(NetCANctl* ob);
CANResult NetCANctlRxMulti(NetCANctl* ob,CANMessage *msg,int min);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
