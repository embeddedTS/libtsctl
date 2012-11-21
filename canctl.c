#define THREAD_USE_POSIX
#include "libtsctl.h"
#include <asm/ioctls.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "ts/NetCANctl.c"
#include "ts/Net.c"

CAN *Net_CANctlInit(int inst,char *host,int mode){
  int socket = ClientSocketNew(host,7552+inst);
  if (socket < 0) return 0;
  NetCANctl *obj = malloc(sizeof(NetCANctl));
  memset(obj,0,sizeof(*obj));

  return NetCANctlInit(obj,socket);
}

struct opt_txdata {
  int opt_txdat;
  int txdat_len;
  unsigned char txdat[8];
};

static int parse_txdat(char *s, unsigned char *txdat) {
	unsigned int val, len;
	char *e;

	len = 0;
	while (*s) {
		val = strtoul(s, &e, 0);
		if (s == e) return -1;
		else if (ispunct(*e)) s = e + 1; 
		else s = e;
		*txdat++ = val;
		len++;
		if (len == 8) break;
	}

	return len;	
}

int OptionOctets(char *arg,void *target0,int opt) {
  struct opt_txdata *target = target0;

  target->opt_txdat = 0;
  target->txdat_len = parse_txdat(optarg, target->txdat);
  if (target->txdat_len == -1) {
    fprintf(stderr, "txdat parse error\n");
    return 0;
  }
  target->opt_txdat = 1;
  return 1;
}

void CANMessageTxInit(CANMessage *msg,unsigned id,int flags,
		      int length,unsigned char *data) {
  struct timeval tv;

  memset(msg,0,sizeof(*msg));
  msg->flags = flags;
  msg->id = id;
  gettimeofday(&tv,NULL);
  msg->t_sec = tv.tv_sec;
  msg->t_usec = tv.tv_usec;
  msg->length = length;
  if (length > 0) {
    memcpy(msg->data,data,length);
  }
}

static volatile int alarmed = 0;
CAN *CANTestRxObject = 0;
static void alarmsig(int x) {
  alarmed = 1;
  if (CANTestRxObject) {    
    CANTestRxObject->Abort(CANTestRxObject);
    usleep(100000);
  }
}

int CANTestRx(CAN *can,int verbose) {
  struct sigaction sa;
  struct timeval tv1, tv2;
  unsigned char tmp[16];
  unsigned skipped = 0;
  int idseq = -1, err = 1, i, j, k, n;
  int corrupts = 0, badlen = 0;
  struct sched_param sched;
  struct rusage ru1, ru2;
  CANMessage msg[1];

  CANTestRxObject = can;
  nice(-20);
  sched.sched_priority = 50;
  sched_setscheduler(0, SCHED_FIFO, &sched);
  
  sa.sa_handler = alarmsig;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGALRM, &sa, NULL);
  if (getenv("TS_PRODUCTION") == NULL) alarm(10);
  else alarm(2);
  gettimeofday(&tv1, NULL);
  getrusage(RUSAGE_SELF, &ru1);
  i = 0;
  while (!alarmed) {
    if ((can->Rx(can,msg)) <= 0) continue;
    for (j=0;j<1;j++) {
      if (msg[j].flags & FLAG_BUS_ERROR) printf("errormsg=\"*** bus error\"\n");
      if (msg[j].flags & FLAG_ERROR_PASSIVE) printf("errormsg=\"*** error passive\"\n");
      if (msg[j].flags & FLAG_DATA_OVERRUN) printf("errormsg=\"*** data overrun error\"\n");
      if (msg[j].flags & FLAG_ERROR_WARNING) printf("errormsg=\"*** error warning\"\n");
      if (msg[j].length) {
	i++;
	if (idseq == -1) {
	  err = 0;
	  idseq = msg[j].id;
	} else {
	  int nid = (idseq + 1) & 0x1fffffff;
	  if (msg[j].id != nid) {
	    if (skipped > 0) {
	      if (verbose) fprintf(stderr, 
		      "errormsg=\"skipped %d\"\n",msg[j].id-nid);
	      //		    "ID 0x%x != 0x%x\"\n",
	      //		    msg[j].id, nid);
	      skipped += (msg[j].id-nid);
	    } else skipped = 1;
	    err++;
	  }
	  if (msg[j].length > 8 || msg[j].length < 0) {
	    if (verbose) fprintf(stderr,"errormsg=\"bad length %d\"\n",msg[j].length);
	    badlen++;
	  } else  for (k = 0; k < msg[j].length; k++) 
	    if (msg[j].data[k] != (((msg[j].id<<3)+k+1)&0xff)) {
	      if (verbose) fprintf(stderr,
		      "errormsg=\""
		      "data[%d] 0x%x != 0x%x\"\n", 
		      k, msg[j].data[k], 
		      (((msg[j].id<<3)+k+1)&0xff));
	      corrupts++;
	    }
	  idseq = msg[j].id;
	}
      }
    }
  }
  /* count packets in i */
  getrusage(RUSAGE_SELF, &ru2);
  gettimeofday(&tv2, NULL);
  j = (tv2.tv_sec - tv1.tv_sec) * 1000;
  j += tv2.tv_usec / 1000 - tv1.tv_usec / 1000;
  printf("total_packets=%d\n",i);
  printf("skipped_packets=%d\n",skipped?skipped-1:skipped);
  printf("bad_length=%d\n",badlen);
  printf("packets_per_sec=%d\n", (i * 1000) / j);
  i = (ru2.ru_utime.tv_sec + ru2.ru_stime.tv_sec) * 1000;
  i += ru2.ru_utime.tv_usec / 1000 + ru2.ru_stime.tv_usec / 1000;
  i -= (ru1.ru_utime.tv_sec + ru1.ru_utime.tv_sec) * 1000;
  i -= ru1.ru_utime.tv_usec / 1000 + ru1.ru_stime.tv_usec / 1000;
  printf("cpu_utilization_pct=%d\n", i * 100 / j);
  printf("test_sequence_errors=%d\n", err);
  printf("test_corruption_errors=%d\n", corrupts);
  return 0;
}

void CANMessagePrint(CANMessage *msg) {
  struct tm * tm;
  int i;

  if (msg->flags & FLAG_CONTROL) printf("*** control packet\n");
  if (msg->flags & FLAG_BUS_ERROR) printf("*** bus error\n");
  if (msg->flags & FLAG_ERROR_PASSIVE) printf("*** error passive\n");
  if (msg->flags & FLAG_DATA_OVERRUN) printf("*** data overrun error\n");
  if (msg->flags & FLAG_ERROR_WARNING) printf("*** error warning\n");
  tm = localtime((time_t *)&msg->t_sec);
  printf("%02d:%02d:%02d.%06d %c%c ", 
	 tm->tm_hour, tm->tm_min, tm->tm_sec,msg->t_usec, 
	 (msg->flags & FLAG_EXT_ID) ? 'E' : 'S', 
	 (msg->flags & FLAG_RTR)     ? 'R' : '.');
  if (msg->flags & FLAG_CONTROL) {
    printf("id=0x%08x ", msg->id);
    printf("cmd=%d ",msg->length);
    printf("dat=");
    for (i = 0; i < 8 ; i++) {
      printf("0x%02x", msg->data[i]);
      if (i != (msg->length - 1)) printf(":");
    }
  } else if (msg->length != 0) {
    printf("id=0x%08x ", msg->id);
    if (msg->length < 0 || msg->length > 8) {
      printf("bad length=%d\n",msg->length);
    } else {
      printf("dat=");
      for (i = 0; i < msg->length; i++) {
	printf("0x%02x", msg->data[i]);
	if (i != (msg->length - 1)) printf(":");
      }
    }
  }
  printf("\n");
}

int canctl(int argc,char *argv[]) {
  int OptInst;
  unsigned OptAdrs=-1,OptBaud=0,OptPeek=-1,OptPoke=-1,OptTxId=0,OptRTR=0;
  unsigned OptServer=-1,OptDump=0,OptBTR0=-1,OptBTR1=-1;
  unsigned OptTxTest=0,OptRxTest=0,OptExt=1,OptVerbose=0;
  int OptClient=-1;
  unsigned OptGoody=0;
  struct opt_txdata OptTxD = { .opt_txdat = 0 };
  CAN *can = 0;
  Bus *bus = 0;

  // for backwards compatibility, we really should do the following:
  // if can or bus are 0, it means we haven't defined them yet. defer the action
  // until they are defined.
  // but, note that we can't do this for txId or txrTr, because we can't infer
  // whether or not the user meant to specify them first or not.

  void CANPrep() {
    if (!can) can = CANInit(0);
    if (!can) {
      fprintf(stderr,"CAN not detected\n");
      exit(3);
    }
  }
  void BusPrep() {
    if (!bus) {
      int canbus;
      System *sys = SystemInit(0);
      canbus = sys->CANBusGet(sys,0);
      bus = BusInit(canbus);
    }
  }

  int DoBaud(char *arg,void *target0,int opt) {
    CANPrep();
    OptionUnsigned(arg,target0,opt);
    can->BaudSet(can,OptBaud);
    return 1;
  }

  int DoPeek8(char *arg,void *target0,int opt) {
    BusPrep();
    OptionUnsigned(arg,target0,opt);
    if (OptPeek == -1) OptPeek = OptAdrs;
    if (OptPeek > 255) {
      fprintf(stderr,"Warning: Ignoring peek out of range address 0x%02X\n",OptPeek);
    } else {
      int peekval;
      bus->Lock(bus,0,0);
      peekval = bus->Peek8(bus,OptPeek);
      bus->Unlock(bus,0,0);
      printf("[%d]=0x%02X\n",OptPeek,peekval);
    }
    return 1;
  }

  int DoPoke8(char *arg,void *target0,int opt) {
    BusPrep();
    OptionUnsigned(arg,target0,opt);
    if (OptAdrs > 255) {
      fprintf(stderr,"Warning: Ignoring poke out of range address 0x%02X\n",OptAdrs);
    } else {
      bus->Lock(bus,0,0);
      bus->Poke8(bus, OptAdrs, OptPoke);
      bus->Unlock(bus,0,0);
    }
    return 1;
  }


  int DoRTR(char *arg,void *target0,int opt) {
    CANMessage msg;

    CANPrep();
    ArrayAutoOfSize(char,nomsg,0);
    can->Tx(can,(OptExt?FLAG_EXT_ID:0)|FLAG_RTR,OptTxId,nomsg);
    return 1;
  }

  int DoTx(char *arg,void *target0,int opt) {
    CANMessage msg;

    CANPrep();
    OptionOctets(arg,target0,opt);
    //fprintf(stderr,"dbug:%X %X %X\n",OptExt,OptRTR,(OptExt?FLAG_EXT_ID:0)|(OptRTR?FLAG_RTR:0));
    ArrayAutoOfSize(char,data,8);
    ArraySizeAuto(data,OptTxD.txdat_len);
    memcpy(data,OptTxD.txdat,OptTxD.txdat_len);
    can->Tx(can,(OptExt?FLAG_EXT_ID:0)|(OptRTR?FLAG_RTR:0),OptTxId,data);
    return 1;
  }

  volatile int gotSigInt = 0;
  void SigInt(int signal) {
    gotSigInt = 1;
    if (can) {    
      can->Abort(can);
    }
  }

  // note: we can't currently perform bus operations on remote servers
  // it is possible, just add a call to Net_BusInit. But, this will require
  // that the server be running the tsctl server in addition to the canctl
  // server, and there is no way to guarantee this.
  int DoServer(char *arg,void *target0,int opt) {
    CANPort *ci = malloc(sizeof(CANPort));
    int retries = 10;
    CAN *old = can;
    OptionUnsigned(arg,target0,opt);
    if (OptServer == -1) OptServer = 0;

    ThreadInit();
    ci->can = CANInit(OptServer);
    if (!ci->can) {
      fprintf(stderr,"CAN not detected\n");
      exit(3);
    }
    ci->port = 7552+OptServer;
    if (!ci->can) {
      fprintf(stderr,"failed to get CAN instance %d\n",OptServer);
      return 0;
    }
    ThreadNew("canctl server",0,CANStart,0,ci,0);

    do {
      can = Net_CANctlInit(0,"localhost",0);
      if (can) 	return 1;
      usleep(100000);
    } while (--retries > 0);
    fprintf(stderr,"Failed to start server for CAN instance %d\n",OptServer);
    return 1;
  }

  int DoEnd(char *arg,void *target0,int opt) {
    OptServer = -1;
    can->Fini(can);
    can = 0;
    return 1;
  }

  int DoClient(char *arg,void *target0,int opt) {
    int (*tmp)(char *,int) = OptionHostSocketCreate;

    int createclient(char *host,int port) {
      if (can) {
	can->Fini(can);
      }
      can = Net_CANctlInit(0,"localhost",0);
      if (!can) fprintf(stderr,"Failed to connect to server %s:%d\n",host,port);
      return (can != 0);
    }

    OptionHostSocketCreate = createclient;
    OptionHost(arg,target0,opt);
    OptionHostSocketCreate = tmp;
    return 1;
  }

  int sigcap=0;

  void SigPrep() {
    gotSigInt = 0;
    if (!sigcap) {
      if (SignalCapture(SIGINT,SigInt) < 0) {
	fprintf(stderr,"signal %d capture error:%m\n",SIGINT);
      }
      if (SignalCapture(SIGTERM,SigInt) < 0) {
	fprintf(stderr,"signal %d capture error:%m\n",SIGTERM);
      }
      if (SignalCapture(SIGHUP,SigInt) < 0) {
	fprintf(stderr,"signal %d capture error:%m\n",SIGHUP);
      }
      sigcap = 1;
    }
  }

  int DoDump(char *arg,void *target0,int opt) {
    CANMessage msg;
    int ret;

    SigPrep();
    CANPrep();
    printf("Dumping\n");
    while (!gotSigInt) {
      if ((ret =can->Rx(can,&msg)) <= 0) {
	fprintf(stderr,"Rx error %d\n",ret);
	return 1;
      } else {
	CANMessagePrint(&msg);
      }
    }
    printf("done\n");
  }

  int DoTxTest(char *arg,void *target0,int opt) {
    int i,j,ret;
    ArrayAutoOfSize(char,data,8);
    SigPrep();
    CANPrep();
    for (i=0;!gotSigInt;i++) {
      for (j=0;j<8;j++) data[j] = (i << 3) + j + 1;
      if ((ret=can->Tx(can,(OptExt ? FLAG_EXT_ID : 0),i,data)) < 0) {
	fprintf(stderr,"Tx error %d\n",ret);
	break;
      }
    }
  }

  int DoRxTest(char *arg,void *target0,int opt) {
    CANMessage msg;
    SigPrep();
    CANPrep();
    CANTestRx(can,OptVerbose);
  }

  int DoBTR0(char *arg,void *target0,int opt) {
    OptionUnsigned(arg,target0,opt);
    BusPrep();
    bus->Lock(bus,0,0);
    bus->Poke8(bus,0, 0x1); // Enter reset mode
    bus->Poke8(bus,6, OptBTR0);
    bus->Poke8(bus,0, 0); // Leave reset mode
    bus->Unlock(bus,0,0);
    return 1;
  }

  int DoBTR1(char *arg,void *target0,int opt) {
    OptionUnsigned(arg,target0,opt);
    BusPrep();
    bus->Lock(bus,0,0);
    bus->Poke8(bus,0, 0x1); // Enter reset mode
    bus->Poke8(bus,6, OptBTR1);
    bus->Poke8(bus,0, 0); // Leave reset mode
    bus->Unlock(bus,0,0);
    return 1;
  }

  int DoStressTest(char *arg,void *target0,int opt) {
    int i,j,k;
    fprintf(stderr,"Beginning CAN stress test\n");
    BusPrep();
    bus->Lock(bus,0,0);
    bus->Poke8(bus,0,1);
    for (i=17;i<24;i++) {
      bus->Poke8(bus,i,i);
    }
    for (j=0;j<100000000;j++) {
      for (i=17;i<24;i++) {
	if ((k=bus->Peek8(bus,i)) != i) {
	  fprintf(stderr,"%d:%d\n",k,bus->Peek8(bus,i));
	}
      }
      if (j % 100 == 0) bus->Preempt(bus);
    }
    bus->Unlock(bus,0,0);
  }

  struct option2 opts[] = {
    { 1, OptionUnsigned,&OptAdrs  ,"<a>ddress" , "ADR        CAN register address for write" },
    { 1, DoBaud        ,&OptBaud  ,"<b>aud" , "BAUD          CAN baud rate (7500 to 1000000)" },
    { 2, DoPeek8       ,&OptPeek  ,"peek8<R>" , "ADR         CAN register read" },
    { 1, DoPoke8       ,&OptPoke  ,"poke8<W>" , "VAL         CAN register write" },
    { 1, OptionUnsigned,&OptTxId  ,"tx<i>d" , "ID            CAN TX packet ID" },
    { 0, DoRTR         ,&OptRTR   ,"txr<T>r" , "             TX RTR packet" },
    { 1, DoTx          ,&OptTxD   ,"tx<d>at" , "DAT          TX packet with data DAT" },
    { 2, DoServer      ,&OptServer,"<s>erver" , "=<port>     Daemonize, run as server (default port=7552+instance)" },
    { 0, DoEnd         ,&OptServer,"<e>nd" , "               End server operation" },
    { 0, DoDump        ,&OptDump  ,"<D>ump" , "              Receive and print all CAN packets" },
    { 1, DoBTR0        ,&OptBTR0  ,"btr<0>" , "BTR0          SJA1000 BTR0 bus timing reg val" },
    { 1, DoBTR1        ,&OptBTR1  ,"btr<1>" , "BTR1          SJA1000 BTR1 bus timing reg val" },
    { 0, DoTxTest      ,&OptTxTest,"<t>xtest" , "            Send TX test pattern (until CTRL+C pressed)" },
    { 0, DoRxTest      ,&OptRxTest,"<r>xtest" , "            Do RX test" },
    { 2, DoClient      ,&OptClient,"<p>ort" , "<host><:port> Talk to canctl server" },
    { 1, OptionUnsigned ,&OptInst ,"<I>nstance" , "ADR       CAN instance (0,1,etc.)" },
    { 0, OptionBoolean ,&OptExt   ,"<E>xt" , "               Send extended frame (default)" },
    { 0, OptionBoolean0,&OptExt   ,"<S>td" , "               Send standard frame (not extended)" },
    //{ 0, OptionBoolean ,&OptRecover,"reco<v>er","             Automatically recover from bus-off" },
    { 0, OptionBoolean ,&OptVerbose,"<V>erbose" , "           verbose error messages during rxtest" },
    { 0, DoStressTest  ,&OptGoody ,"<G>oody" , "            Run CAN bus stress test" },
    { 0,0,0,"Technologic Systems CAN controller manipulation.\n","" }
  };

  OptionsParse(argc,argv,opts);
  if (OptServer != -1) {
    if (can) {
      can->Fini(can);
    }
    printf("canctl server running\n");
    // following line commented out due to apparent bug in uclibc!!!
    //daemon(1,0);
    while(1) sleep(1);
  }
  return 0;
}

int main(int argc,char *argv[]) {
  return canctl(argc,argv);
}

/*
  This sample code implements the classic "canctl" client/server application
  using the latest libtsctl API, thereby providing canctl support for all
  platforms supposed by libtsctl.

  This version provides enhancements over the original version while remaining
  backwards compatible.  

  First, command line options are interpreted as they are encountered in the 
  order given.  This makes it possible to perform several different commands, 
  even to different servers.  For example, the following command will send
  two CAN messages, the first using standard framing and the second using
  extended framing.  It will then connect to the canctl server on the
  host "remote" and send an extended frame via that host:
    canctl -S -d 1:2:3 -E -d 4:5:6 --port=remote -d 7:8:9

  In interpretting commands, the most current options are always used.  So
  for example, the latest port option is used to determine which server to
  talk to.  And if a CAN ID is specified, all subsequent "txdat" options will
  send a message with that ID until a new one is specified.

  Actions which run indefinitely can be terminated with CTRL+C or by sending
  a SIGINT to canctl.  This will cause any additional command line arguments
  to then be interpreted.

  By default, canctl talks directly to the local CAN hardware.  If it is
  desired to set up a localhost canctl server and talk to it instead, use
  the --server option.  The --end option is used to cancel operation of the
  server if it is not desired to keep the server running when finished
  processing command line options.

  Do not specify the --server option more than once for a given CAN instance, 
  as this will cause unpredictable behavior.

  Direct CAN Bus operations (peek, poke, RTR) are currently only supported 
  directly on the hardware.  It is possible to implement these remotely,
  but it would only work if the remote server also supports the tsctl
  protocol, which is implemented separately.
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
