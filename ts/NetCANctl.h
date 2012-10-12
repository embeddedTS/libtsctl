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
	int FUNC(Rx)(NetCANctl *me,CANMessage [1]);
	int FUNC(Tx)(NetCANctl *me,unsigned flags,unsigned id,const char *data);
	unsigned FUNC(BaudSet)(NetCANctl *me,unsigned opt_baud);
	unsigned FUNC(BaudGet)(NetCANctl *me);
	void FUNC(Abort)(NetCANctl *me);
	int FUNC(RxMulti)(NetCANctl *me,CANMessage *,int min);
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
int NetCANctlRx(NetCANctl* ob,CANMessage [1]);
int NetCANctlTx(NetCANctl* ob,unsigned flags,unsigned id,const char *data);
unsigned NetCANctlBaudSet(NetCANctl* ob,unsigned opt_baud);
unsigned NetCANctlBaudGet(NetCANctl* ob);
void NetCANctlAbort(NetCANctl* ob);
int NetCANctlRxMulti(NetCANctl* ob,CANMessage *,int min);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
