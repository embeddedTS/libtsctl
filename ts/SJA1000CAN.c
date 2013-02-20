#ifndef SJA1000CAN_c
#define SJA1000CAN_c
#include <assert.h>
#include <fcntl.h>
#include <string.h> // memcpy
#include <netinet/in.h>
#include "SJA1000CAN.h"
#include "nosig.h"
#include "Log.h"

#define S11(x) ((char *)x)
static void BusOff(SJA1000CAN *can) {
  can->bus->Poke8(can->bus,0, 0x1); // Enter reset mode
  can->bus->Poke8(can->bus,31, 0x80); // Enable PeliCAN mode
  can->bus->Poke8(can->bus,4, 0xff); // All interrupts enabled
  can->bus->Poke8(can->bus,13, 96); // Error warning limit
  can->bus->Poke8(can->bus,14, 0); // Reset RX error counter to 0
  can->bus->Poke8(can->bus,15, 0); // Reset TX error counter to 0
}

__attribute__((always_inline)) 
static inline void BusOn(SJA1000CAN *can) {
  can->bus->Poke8(can->bus,0, 0); /* Enter operational mode */
}

/*
  determining the current baud rate from the bus timing registers

1. 2 * (REG6[5:0] + 1) * 1/24Mhz = clock period
   2 * (4+1) = 10 => 2.4 Mhz
   2 * (0+1) = 2 -> 12Mhz

2. bit period = ( 1 + REG7[6:4] + REG7[3:0] ) * clock period
   (1+6+15) = 22 => 109090  (need 24 for 100k)
   (1+2+7)  = 10 -> 1.2M (need 12 for 1M)
 */
unsigned get_baud(int btr0,int btr1) {
  int inv_clock_period = 2 * (1 + (btr0 & 0x3F));
  int tseg2 = (1 + (btr1 >> 4) & 7);
  int tseg1 = (1 + (btr1 & 15));
  int inv_bit_period = inv_clock_period * (1+tseg1+tseg2);
  return 24000000 / inv_bit_period;
}

static unsigned init_baud(int opt_baud,int *baudparms,
		      int *opt_btr0,int *opt_btr1) {
  int i;
  
  if (!baudparms) return;
  if (opt_baud < baudparms[0]) {
    //fprintf(stderr,"%d < %d, using %d baud\n",opt_baud,baudparms[0],baudparms[0]);
    opt_baud = baudparms[0];
  } else if (opt_baud > 1000000) {
    //fprintf(stderr,"%d > 1000000, using 1000000 baud\n",opt_baud);
    opt_baud = 1000000;
  } else {
    i = 0;
    while (baudparms[i]) {
      if (baudparms[i] >= opt_baud) {
	break;
      }
      i += 3;
    }
    if (i > 0) {
      if (baudparms[i] - opt_baud > opt_baud - baudparms[i-3]) {
	i -= 3; // pick a slightly slower baud rate if it is closer to target
      }
    }
    // assert(baudparms[i]);
    opt_baud = baudparms[i];
    *opt_btr0 = baudparms[i+1];
    *opt_btr1 = baudparms[i+2];
    //fprintf(stderr,"using %d baud\n",opt_baud);
  }
  return opt_baud;
}

int SJA1000CANDetect(SJA1000CAN *can) {
  int error=0;
  can->bus->Lock(can->bus,0,0);
  if (can->bus->BitGet8(can->bus,31,7) == 0) {
    // not in PeliCAN mode, safe to attempt a reset
    can->bus->BitSet8(can->bus,0,0);
    if (!can->bus->BitGet8(can->bus,0,0)) {
      // unable to enter reset mode, test failed
      error = -1; goto CANDetectDone;
    }
    can->bus->Poke8(can->bus,31, 0x80); // Enable PeliCAN mode
    can->bus->Poke8(can->bus,13, 99); // Error warning limit
    if (can->bus->Peek8(can->bus,13) != 99) {
      // unable to write error warning limit reg, test failed
      error = -2; goto CANDetectDone;
    }
    can->bus->Poke8(can->bus,13, 96);
    if (can->bus->Peek8(can->bus,13) != 96) {
      // unable to write error warning limit reg, test failed
      error = -3; goto CANDetectDone;
    }
    can->bus->BitClear8(can->bus,0,0);
    if (can->bus->BitGet8(can->bus,0,0)) {
      // unable to leave reset mode, test failed
      error = -4; goto CANDetectDone;
    }
    can->bus->Poke8(can->bus,13, 99); // Error warning limit
    if (can->bus->Peek8(can->bus,13) != 96) {
      // able to write error warning limit reg, test failed
      error = -5; goto CANDetectDone;
    }
  } else {
    // possibly in PeliCAN mode, not safe to attempt a reset
    if (0 && can->bus->Peek8(can->bus,3)) {
      /* commented out because this is not foolproof. we actually have a
	 potential race condition between clearing one interrupt condition
	 and receiving the next before we read again.
      if (can->bus->Peek8(can->bus,3)) {
	// bits set in Interrupt register not cleared on read, test failed
      printf("err6\n");
	goto CANDetectDone;
      } else {
	// bits set in Interrupt register cleared on read, test passed
      }
      */
    } else {
      // not interrupt bits set to test clear on read
      can->bus->Poke8(can->bus,4,0);
      if (can->bus->Peek8(can->bus,4) != 0) {
	// interrupt mask register not behaving as expected, test failed
	error = -7; goto CANDetectDone;
      }
      can->bus->Poke8(can->bus,4,0xFF);
      if (can->bus->Peek8(can->bus,4) != 0xFF) {
	// interrupt mask register not behaving as expected, test failed
	error = -8; goto CANDetectDone;
      }
      // interrupt mask register is read/write, test passed
    }
  }
CANDetectDone:
  can->bus->Unlock(can->bus,0,0);
  return error;
}

unsigned _SJA1000CANBaudSet(SJA1000CAN *can,unsigned opt_baud,int force,int *changed) {
  int new_baud;
  int BTR0,BTR1;

  can->bus->Lock(can->bus,0,0);
  BTR0 = can->bus->Peek8(can->bus,6);
  BTR1 = can->bus->Peek8(can->bus,7);
  can->baud = get_baud(BTR0,BTR1);

  //fprintf(stderr,"new baud=%d, old baud=%d\n",opt_baud,can->baud);
  can->baud = opt_baud;
  new_baud = init_baud(can->baud,can->baudparms,&BTR0,&BTR1);


  if (can->bus->BitGet8(can->bus,0,1) // in reset
      || can->bus->BitGet8(can->bus,2,7) // error warning
      || can->bus->BitGet8(can->bus,2,6)) { // Bus Off
    BusOff(can);
    BusOn(can);
  }

  BusOn(can);
  if (BTR0 == can->bus->Peek8(can->bus,6)
      && BTR1 == can->bus->Peek8(can->bus,7)) {
    can->bus->Unlock(can->bus,0,0);
    *changed = 0;
    return can->baud;
  }
  *changed = 1;

  if (force || (can->bus->Peek8(can->bus,31) & 0x80) == 0
      || can->bus->Peek8(can->bus,2) & 0xC0 ) {

    //fprintf(stderr,"Re-initializing CAN\n");
    BusOff(can);

    // 0x00, 0x27 = 1Mbps
    // 0x04, 0x6F = 100kbps
    // 0x2F, 0x7F = 10kbps
    can->baud = new_baud;

    can->bus->Poke8(can->bus,6, BTR0);
    can->bus->Poke8(can->bus,7, BTR1);
    can->txto = 150000000/can->baud; // us
    if (can->txto > 300) can->txto=0;

    can->bus->Poke8(can->bus,20, 0xff); // Acceptance mask disabled (all packets rx'ed)
    can->bus->Poke8(can->bus,21, 0xff);
    can->bus->Poke8(can->bus,22, 0xff);
    can->bus->Poke8(can->bus,23, 0xff);
    
    can->bus->Peek8(can->bus,3); /* Clear pending interrupts */

    BusOn(can);
    /*
    if (baud) {
      can->BaudSet(can,baud);
    }
    */
  } else {
    can->bus->Poke8(can->bus,4, 0xff); // All interrupts enabled, in case it got disabled
  }
  can->bus->Unlock(can->bus,0,0);
  return can->baud;
}

unsigned SJA1000CANBaudSet(SJA1000CAN *can,unsigned opt_baud) {
  int dummy;
  return _SJA1000CANBaudSet(can,opt_baud,1,&dummy);
}


unsigned SJA1000CANBaudGet(SJA1000CAN *can) {
  int BTR0, BTR1;

  can->bus->Lock(can->bus,0,0);
  BTR0 = can->bus->Peek8(can->bus,6);
  BTR1 = can->bus->Peek8(can->bus,7);
  can->bus->Unlock(can->bus,0,0);

  return (can->baud = get_baud(BTR0,BTR1));
}

void SJA1000CANAbort(SJA1000CAN *can) {
  can->doabort = 1;
}

void *SJA1000CANInit(SJA1000CAN *can,void *bus,void *pin,void *time) {
  int dummy;

  can->Init = (void *)SJA1000CANInit;
  can->Fini = (void *)SJA1000CANFini;
  can->Rx = (void *)SJA1000CANRx;
  can->Tx = (void *)SJA1000CANTx;
  can->BaudSet = (void *)SJA1000CANBaudSet;
  can->BaudGet = (void *)SJA1000CANBaudGet;
  can->Abort = (void *)SJA1000CANAbort;
  can->RxMulti = (void *)SJA1000CANRxMulti;

  can->doabort = 0;
  can->bus = bus;
  can->pin = pin;
  can->time = time;
  dummy = SJA1000CANDetect(can);
  if (dummy < 0) {
    can->InitStatus = dummy;
    return 0;
  }
  //if (can->InitStatus > 0) return can;
  if (can->bus->InitStatus < 0
      ||can->pin->InitStatus < 0) {
    can->Fini(can);
    can->InitStatus = -1;
    return can;
  }
  can->status = 0;
  can->pin->Lock(can->pin,can->CAN_TX,0);
  can->pin->ModeSet(can->pin,can->CAN_TX,MODE_CAN);
  can->pin->Unlock(can->pin,can->CAN_TX,0);

  can->pin->Lock(can->pin,can->CAN_RX,0);
  can->pin->ModeSet(can->pin,can->CAN_RX,MODE_CAN);
  can->pin->Unlock(can->pin,can->CAN_RX,0);
  _SJA1000CANBaudSet(can,can->baud,0,&dummy);
  //can->BaudSet(can,can->baud);
  can->txrdy = 1;
  return can;
}

void SJA1000CANFini(SJA1000CAN *can){
  can->bus->Fini(can->bus);
  can->pin->Fini(can->pin);
  if (can->InitStatus > 0) can->InitStatus = 0;
}

CANResult SJA1000CANRxMulti(SJA1000CAN *can,CANMessage* buf,int min) {
  int n=0;
  int ret,rdy;

  if (min > ArrayLength(buf)) min = ArrayLength(buf);
  while (min-- > 0) {
    ret = SJA1000CANRx(can,buf+(n++));
    if (ret < 0) goto SJA1000CANRxMultiDone;
  }
  while (n < ArrayLength(buf)) {
    can->bus->Lock(can->bus,0,0);
    rdy = can->bus->Peek8(can->bus,2) & 0x01;
    can->bus->Unlock(can->bus,0,0);
    if (!rdy) goto SJA1000CANRxMultiDone;
    ret = SJA1000CANRx(can,buf+(n++));
    if (ret < 0) goto SJA1000CANRxMultiDone;
  }
 SJA1000CANRxMultiDone:
  if (ret >= 0) {
    ret = n;
  }
  ArraySizeAuto(buf,n);
  return ret;
}

CANResult SJA1000CANRx(SJA1000CAN *can,CANMessage msg[0]){
  unsigned char d[16];
  unsigned char check[10];
  int i,j=0,n,ret=0,timeout;
  //static int lastid=-1;
  LogEnter("%p,id=%d,len=%d\n",can,msg->id,msg->length);

  can->bus->Lock(can->bus,0,0);
  //gettimeofday(&msg->timestamp,NULL);
  // block until CAN message ready
  timeout = 100;
  while (!can->doabort) {
    j=can->bus->Peek8(can->bus,2);
    
    if ((j & 0x01)==1) break;
    if (j & 0xC0) {
      can->bus->Unlock(can->bus,0,0);
      ArraySizeAuto(msg->data,0);
      msg->flags = (j & 0x80 ? FLAG_BUS_ERROR : 0) +
	(j & 0x40 ? FLAG_ERROR_WARNING : 0);
      msg->id = 0;
      return (j & 0x80) ? CANErrorBusOff : CANErrorBusWarning;
    }
    if (--timeout == 0) {
      can->bus->Preempt(can->bus);
      timeout = 1000;
    }
  }
  if (can->doabort) {
    can->doabort = 0;
    can->bus->Unlock(can->bus,0,0);
    ArraySizeAuto(msg->data,0);
    msg->flags = 0;
    msg->id = 0;
    LogReturn("%d\n",CANErrorAborted);
  }
  memset(msg,0,sizeof(CANMessage));
  n = can->bus->Peek8(can->bus,29);
  ret = (n>0) ? CANSuccess : CANErrorFIFOUnexpectedlyEmpty;
  if (ret < 0) {
    Log(LOG_CAN,"j=%02X, n=%d\n",j,n);
  }
  if (n > 128) n &= 0x7F;
  if (n) { // j & 0x1
    ArrayAuto(char,t1,ARR(0,0));

    unsigned short t;
    unsigned len;
    
    can->bus->PeekStream(can->bus,16,1,t1);
    t = *((short *)t1);
    //t = (t << 8) + (t >> 8); ???
    msg->length = t & 0x0F;
    if (t & 0x80) msg->flags |= FLAG_EXT_ID;
    if (t & 0x40) msg->flags |= FLAG_RTR;

    d[0] = t & 0xff; // flags+len; 0x80=EXT,0x40=RTR
    d[1] = t >> 8;   // ??
    /* standard or extended frame */
    if (d[0] & 0x80) len = 3; else len = 1;
    
    if (!(d[0] & 0x40)) /* Not RTR packet? */
      len += ((d[0] & 0xf) > 8) ? 8 : (d[0] & 0xf);
    ArrayAutoOfSize(char,d1,16);
    ArraySizeAuto(d1,len);

    can->bus->PeekStream(can->bus,18, 1, d1); // data
    
    if (t & 0x80) {
      msg->id = d[1] << 21;
      msg->id |= d1[0] << 13;
      msg->id |= d1[1] << 5;
      msg->id |= d1[2] >> 3;
      for (i=0;i<8;i++) { msg->data[i] = d1[i+3]; } 
    } else {
      msg->id = d[1] << 21;
      msg->id |= (d1[0] & 0xe0) << 13;
      msg->id = msg->id >> 18;
      for (i=0;i<8;i++) { msg->data[i] = d1[i+1]; } 
     }

    can->bus->Poke8(can->bus,1, 0x4); // Release receive buffer
  }
  if (j & 0x80) msg->flags |= FLAG_BUS_ERROR;
  if (j & 0x40) msg->flags |= FLAG_ERROR_WARNING;
  if (j & 0x2) {
    msg->flags |= FLAG_DATA_OVERRUN;
    can->bus->Poke8(can->bus,1, 0x8); // clear data overrun (here???)
  }
  can->bus->Unlock(can->bus,0,0);
  LogReturn("%d\n",ret);
}

CANResult SJA1000CANTx(SJA1000CAN *can,unsigned flags,unsigned id,const char* data){
  int len = ArrayLength(data) > 8 ? 8 : ArrayLength(data);
  ArrayAutoOfSize(unsigned char,buf,13);
  unsigned char *b = buf;
  int i,j,timeout=1000;

  can->bus->Lock(can->bus,0,0);
  // block until CAN is ready to accept another message or an error occurs
  while (!can->doabort) {
    j=can->bus->Peek8(can->bus,2);
    
    if (j & 0xC0) {
      can->bus->Unlock(can->bus,0,0);
      return (j & 0x80) ? CANErrorBusOff : CANErrorBusWarning;
    }
    if ((j & 0x04)==4) break;
    if (--timeout == 0) {
      can->bus->Preempt(can->bus);
      timeout = 1000;
    }
  }
  /*
  while  (!can->doabort && ((i=can->bus->Peek8(can->bus,2)) & 0x04)==0) {
    if (--timeout == 0) {
      can->bus->Preempt(can->bus);
      timeout = 1000;
    }  
  }
  */
  if (can->doabort) {
    can->doabort = 0;
    return CANErrorAborted;
  }
  if (flags & FLAG_CONTROL) return CANErrorCannotTxControlMessage;

  *b++ = ((flags&FLAG_RTR)?0x40:0)+((flags&FLAG_EXT_ID)?0x80:0)+len;

  if (flags & FLAG_EXT_ID) {
    id <<= 3;
    *b++ = (id >> 24);
    *b++ = (id >> 16);
    *b++ = (id >> 8);
    *b++ = (id & 0xff);
  } else {
    *b++ = (id >> 3);
    *b++ = (id << 5);
  }
  while (len--) *b++ = *data++;
  ArraySizeAuto(buf,b-buf);
  can->bus->PokeStream(can->bus,16, 1,buf);
  can->bus->Poke8(can->bus,1, 0x1); /* TX command */
  can->bus->Unlock(can->bus,0,0);
  return CANSuccess;
}

//#define DEBUG1

#ifdef DEBUG1
struct debuglog {
  unsigned time;
  int line;
};

struct debuglog Q[2048];
int qlen;

void dump() {
  int i;
  
  for (i=0;i<qlen;i++) {
    fprintf(stderr,"%4d:%d:%llu\n",i,Q[i].line,
	    (i==0)?0:Q[i].time-Q[i-1].time);
  }
  qlen = 0;
}
void queue(int line) {
  if (qlen >= 500) dump();
  Q[qlen].time = SystemTimeTick(0);
  Q[qlen++].line = line;
}
#define ___ queue(__LINE__);
#else
#ifdef DEBUG2

__attribute__((always_inline)) 
static inline void queue(int line) { 
  fprintf(stderr,"%d ",line); 
}
__attribute__((always_inline)) 
static inline void dump() { }
#define ___ queue(__LINE__);
#else
__attribute__((always_inline)) 
static inline void queue(int line) { }
__attribute__((always_inline)) 
static inline void dump() { }
#define ___
#endif
#endif

#define CAN_BusOff 0x80
#define CAN_TxRdy 0x04
#define CAN_RxRdy 0x01
#define CAN_RxQLen 32

// High Performance CAN
// Requires:
// 1. List of socket connections 
//    One connection must already be established when CANMain is called.
//    We select on the listen socket so a new connection cannot be
//    accepted until we make it to select(), so under heavy
//    load when we don't have time to process new connections anyway,
//    we won't be wasting time trying to accept the connection!
// 2. For each connection, we need a socket receive queue
//    The size of this queue should be large enough that we can get
//    a lot of messages in a single read() if they are available to
//    reduce the amortized cost of the system call, but not enough that
//    we underflow the transmitter.
//    Although 50 messages should fit in a 1500 byte packet,
//    32 messages is probably the most to avoid starving CAN Tx.
//    Unless we have a partial message read, we empty the buffer before
//    we refill it.  For a partial read, we copy the partial message to
//    the beginning of the buffer so we can again try for a max sized read.
// 3. For each connection, we need a socket transmit buffer large enough
//    to hold a partial message.  When we can't send all a message, we
//    write the failed part.
// X. When we get into a bus off condition we close all connections, and
//    delay accepting any new connections until all connections have been
//    closed.  When the first connection is opened when bus off we 
//    re-initialize CAN.
// Y. Errors are reported on CAN message reception.  We mark the error
//    flags in the message written to the socket.

/*
CAN Message queue
1. reading from a socket, we try to read several messages at once.
   if the last message being read isn't completed, we deal with it separately
2. when writing to a socket, we try to write several messages at once.
   if the last message being written isn't completed, we deal with it separately
3. when reading and writing CAN, only a single message at a time goes
   we always read and write complete messages from/to CAN
4. We only read from CAN when our receive Q is empty, and then we send out
   the packets in the queue all at once, thus emptying the queue immediately.
5. We only read from a socket when the transmit Q is empty
   We read as many packets as we can from one socket, and continue to the next
   if we don't have anything to send
   
   Tx/Rx nomenclature is always with respect to CAN
   
   head/tail nomenclature:
   head of the line is where you come out
   tail of the line is where you go in
   
   struct CANConn {
     int socket;
     unsigned char txq[sizeof(CANMessage)];
     unsigned txtail; // init=0
     unsigned char rxq[sizeof(CANMessage)];
     unsigned rxtail; // init=0
   };
   #define BUFLEN sizeof(CANMessage)*32
   struct CANData {
     // Transmit Queue:
     unsigned char txq[BUFLEN];
     unsigned txhead,txtail;
     // Receive Queue:
     unsigned char rxq[BUFLEN];
     unsigned rxtail;
     // Connections:
     CANConn *conn;
     unsigned maxconn,nconn,txc; // init=?,1,0
     // txc is the next connection to read from
     fd_set r1,r2,w1;
     // r1 contains listen, irq
        // must be initialized. by caller?
     // r2 contains listen, irq, and all CANConn sockets
        // must also be initialized (by caller?) but when we accept
	// new connections we must add the socket and when a connection
	// dies we must remove it.
     int fdmax;
     int irqfd;
  };
   
   closed connection:
   we want to detect a closed connection when we try to read from it
   that way, we don't prematurely detect it when writing and close the
   connection when there might still be more data we can read from it.
   since we always eventually read all connections in round-robin fashion
   when CAN is ready to transmit, and CAN should always continue transmitting
   unless it gets into a bus off state, we should detect a closed connection
   fairly quickly by reading out all the remaining data from it.  if we do
   not, it is not a big deal because we aren't in a state to care anyway.
   
   sockets must be non-blocking
   
   we don't yet have a way of pushing out partial rx data if no additional
   data is received.
*/
/*
   we must add code if transmit is empty to listen on all sockets
   is this a problem?  if transmit is not empty, then after we send the
   last message in the transmit queue, we will try to read again. if
   we fail that, then transmit is empty, so no, it is not a problem.

   should never wait if RxRdy is true
*/
void wait(SJA1000CAN *can,int socketwait,int txwait,int rxwait) {
  unsigned char intmask = 0xFD,ints;
  fd_set fdr,fdw;
  CANData *d = &can->D;
  int dummy,i,n,rc;
  struct timeval tv,*tvp=0;
  LogEnter("%p,%d,%d,%d\n",can,socketwait,txwait,rxwait);

  // we need a flag to tell us if we wait for transmit
  fdw = d->w1;
  if (socketwait) {
    fdr = d->r2; //read set includes IRQ, listen, and all sockets
  } else {
    fdr = d->r1; //read set includes IRQ, listen
    intmask |= 2; // unmask CAN Tx Rdy interrupt
  }
  can->bus->Poke8(can->bus,4,intmask);
  dummy = can->bus->Peek8(can->bus,2);
  if (((dummy & CAN_TxRdy) && txwait)
      ||((dummy & CAN_RxRdy) && rxwait)) {
    // check if we lost the race between unmasking interrupts and the
    // interrupt condition occurs.  if we lost the race, the interrupt
    // won't happen, so go ahead and return for there is something to
    // do; we don't need to wait...
    LogReturn("\n");
  }
  // write set must be modified as needed elsewhere
  can->bus->Unlock(can->bus,0,0);
  if (socketwait && txwait) fprintf(stderr,"warn: socketwait and txwait both set\n");
  //#if 0
  //  if (txwait) {
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //tvp = &tv;
    //  }
    //#endif
  while (1) {
    NOSIG(rc=select(d->fdmax+1,&fdr,&fdw,0,tvp));
    if (rc > 0) break;
    can->bus->Lock(can->bus,0,0);
    ints = can->bus->Peek8(can->bus,3);
    can->bus->Unlock(can->bus,0,0);
    if (ints) break;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
  } 
  can->bus->Lock(can->bus,0,0);
#if 0
  if (rc == 0) {
    can->bus->Poke8(can->bus,1,2);
  }
#endif
  int debug = can->bus->Peek8(can->bus,4);
  can->bus->Poke8(can->bus,4,0);
  ints = can->bus->Peek8(can->bus,3);
  // note: do something with this "ints". check for errors
  
  if (ints) { // || FD_ISSET(d->irqfd,&fdr)) {
    // we don't use FD_ISSET(d->irqfd) in case an interrupt
    // occurrs after select returns but before we mask them
    /*
    if (!ints) {
      Log(LOG_CAN,"INT UNKNOWN\n");
    }
    */
    Log(LOG_CAN,"ints=%d(%d)\n",ints,debug);
    if (FD_ISSET(d->irqfd,&fdr)) {
      read(d->irqfd,&dummy,4); //read IRQ fd to acknowledge with OS
    } else {
      fprintf(stderr,"Uh-oh! IRQ descriptor was not ready!\n");
      // Why exactly did select() return anyway???
    }
    //can->bus->Poke8(can->bus,4,0);
  }
  // if listen descriptor is ready, accept a new connection
  if (FD_ISSET(d->listen,&fdr)) {
    // if we want to accept new connections outside of wait,
    // we can set the listen socket non-blocking, then poll
    // it during pre-emption.  
    // this block can be factored into a separate function
    // to facilitate that
    struct sockaddr_in csa;
    unsigned size_csa = sizeof(csa);
    int s;
    if ((s=accept(d->listen, (struct sockaddr *)&csa, &size_csa)) >= 0) {
      //fprintf(stderr,"accept %d\n",s);
      if (d->nconn == d->maxconn) {
	close(s); // no more slots left
      } else {
	fcntl(s, F_SETFL, (O_NDELAY | O_NONBLOCK));
	d->conn[d->nconn].socket = s;
	d->conn[d->nconn].txtail = 0;
	d->conn[d->nconn].rxtail = 0;
	FD_SET(s,&d->r2);
	if (s > d->fdmax) d->fdmax = s;
	d->nconn++;
      }
    }
  }
  // check if any of the socket write descriptors unblocked
  // for any found, try to write its partial buffer
  for (i=0;i<d->nconn;i++) {
    CANConn *c = d->conn + i;
    if (c->rxtail) {
      n = write(c->socket,c->rxq,c->rxtail);
      if (n > 0) c->rxtail -= n;
      if (c->rxtail == 0) {
	FD_CLR(c->socket,&d->w1);
      }
    }
  }
  LogReturn("\n");
}


// returns the next message buffer in the CAN receive queue
// and assumes it will be filled with a CAN message
// don't call if fullRxQ() returned true!
// CAN -> RxQ
CANMessage *pushRxQ(SJA1000CAN *can) {
	CANData *d = &can->D;
	CANMessage *ret;
	if (d->rxtail >= BUFLEN) return 0;
	ret = (CANMessage *)(d->rxq + d->rxtail);
	d->rxtail += sizeof(CANMessage);
	return ret;
}

// returns the next CAN message in the CAN transmit queue
// and assumes it will be sent to CAN
// TxQ -> CAN
CANMessage *pullTxQ(SJA1000CAN *can) {
	CANData *d = &can->D;
	CANMessage *ret = (CANMessage *)(d->txq + d->txhead);
	d->txhead += sizeof(CANMessage);
	if (d->txhead > BUFLEN) { 
	  fprintf(stderr,"ACK\n");
	}
	return ret;
}

// close the socket for the given connection
// and shift the last connection (if there is one) down into its slot
// to eliminate the gap
void closeSocket(SJA1000CAN *can,unsigned nconn) {
	CANData *d = &can->D;
	//fprintf(stderr,"closeSocket(%d)\n",d->conn[nconn].socket);
	close(d->conn[nconn].socket);
	FD_CLR(d->conn[nconn].socket,&d->r2);
	d->conn[nconn].socket = -1;
	if (nconn+1 < d->nconn) {
		// slightly more efficient might be to only copy the parts
		// of the txq and rxq that are used
		d->conn[nconn] = d->conn[d->nconn-1];
	}
	d->nconn--;
}

__attribute__((always_inline)) 
static inline int emptyTxQ(SJA1000CAN *can) {
	// we really should reset txhead and txtail back to 0 when we 
	// run out of data
	return can->D.txhead == can->D.txtail;
}

// not used yet, but it should be!!!
__attribute__((always_inline)) 
static inline int fullRxQ(SJA1000CAN *can) {
	return can->D.rxtail == BUFLEN;
}

__attribute__((always_inline)) 
static inline int emptyRxQ(SJA1000CAN *can) {
	return can->D.rxtail == 0;
}

// RxQ -> all sockets
void dumpRxQToAllSockets(SJA1000CAN *can) {
	CANData *d = &can->D;
	CANConn *c;
	int i,n,part;
	
	for (i=0;i<d->nconn;i++) {
		c = d->conn + i;
		// do we have partial data from previous rx to send?
		if (c->rxtail) {
			n = write(c->socket,c->rxq,c->rxtail);
			if (n > 0) {
				c->rxtail -= n;
				if (n > 0) continue;
			}
		}
		n = write(c->socket,d->rxq,d->rxtail);
		// if we sent a partial msg, store the rest for later
		if (n > 0) {
		  part = n % sizeof(CANMessage);
		  if (part) {
		    c->rxtail = sizeof(CANMessage) - part;
		    memcpy(c->rxq,d->rxq+n,c->rxtail);
		    FD_SET(c->socket,&d->w1);
		    if (c->socket > d->fdmax) {
		      d->fdmax = c->socket;
		    }
		  }
		}
	}
	d->rxtail = 0; // Q sent, now purge it
}

// next socket with data -> TxQ
void readSocketsToTxQ(SJA1000CAN *can) {
	CANData *d = &can->D;
	CANConn *c;
	int txc0, i, part;
	
	d->txhead = d->txtail = 0; // assume empty on entry
	txc0 = d->txc;
	do {
		c = d->conn + d->txc;
		if (c->txtail) {
			// socket has partial msg stored for it
			// move the partial message to the TxQ
			memcpy(d->txq,c->txq,c->txtail);
			d->txtail = c->txtail;
			c->txtail = 0;
		}
		// read as much data from the socket as possible
		i = read(c->socket,d->txq+d->txtail,BUFLEN-d->txtail);
		if (i == 0 || i<0 && errno==-EPIPE) { // connection closed
		        d->txtail = 0;
			closeSocket(can,d->txc);
			// don't advance to the next connection, because
			// closing the socket will replace the current
			// connection slot with the next one. however if
			// this was the last connection, we now must
			// roll back over to the beginning
			if (!d->nconn) return;
			if (d->txc >= d->nconn) d->txc = 0;
			continue;
		} else {
			// go ahead and advance the next connection to read from
			// as we don't use d->txc again until the end of the
			// loop and we might return before that
			if (++d->txc >= d->nconn) d->txc = 0;
		}
		if (i < 0 && d->txtail) {
		  c->txtail = d->txtail;
		  d->txtail = 0;
		} else if (i > 0) { // can't be ==
			d->txtail += i;
			part = d->txtail % sizeof(CANMessage);
			if (part) {
				// move partial to tx buffer for socket
			  // technically we could probably get by only
			  // copying the additional data back to the
			  // partial buffer!
				memcpy(c->txq,d->txq+d->txtail-part,part);
				c->txtail = part;
				d->txtail -= part;
			}
			if (d->txtail > 0) {
				return;
			}
		}
	} while (d->txc != txc0);
}

static int process_command(SJA1000CAN *can,CANMessage *msg) {
  if (msg->length == 1) {
    int changed;
    //can->baud = ((unsigned *)msg->data)[0];
    can->bus->Unlock(can->bus,0,0);
    _SJA1000CANBaudSet(can,((unsigned *)msg->data)[0],1,&changed);
    can->bus->Lock(can->bus,0,0);
    return 0;
  }
  if (msg->length == 77) { // NO-OP
    return 0;
  }
  if (msg->length == 666) { // terminate server
    return 6;
  }
  return 0;
}

static void CANMainPreInit(SJA1000CAN *can,int listen,int irqfd,int s) {
  // reset CAN if needed
  can->Init(can,can->bus,can->pin,can->time); 
  can->D.nconn = 1;
  can->D.conn[0].socket = s;
  can->D.conn[0].txtail = 0;
  can->D.conn[0].rxtail = 0;
  can->D.listen = listen;
  can->D.irqfd = irqfd;
  fcntl(s, F_SETFL, (O_NDELAY | O_NONBLOCK));
  FD_ZERO(&can->D.r1);
  FD_SET(irqfd,&can->D.r1);
  can->D.fdmax = irqfd;
  FD_SET(listen,&can->D.r1);
  if (listen > can->D.fdmax) can->D.fdmax = listen;
  can->D.r2 = can->D.r1;
  FD_SET(s,&can->D.r2);
  if (s > can->D.fdmax) can->D.fdmax = s;
  FD_ZERO(&can->D.w1);
}

int CANMain(void *can0,int listen,int irqfd,int s) {
  SJA1000CAN *can = can0;
  int CANStatus;
  unsigned start1,end1,start2,end2;
  CANMessage *msg;
  int i=0,socketwait,ret=1,tmp;
  int txwait,rxwait;
  LogEnter("%p,%d,%d,%d\n",can0,listen,irqfd,s);

  Log(LOG_CAN,"CANMain entered\n");
  can->pin->Lock(can->pin,can->CAN_TX,0);
  can->pin->Lock(can->pin,can->CAN_RX,0);
  Log(LOG_CAN,"CAN Pins locked\n");
  can->pin->ModeSet(can->pin,can->CAN_RX,MODE_CAN);
  can->pin->ModeSet(can->pin,can->CAN_TX,MODE_CAN);
  Log(LOG_CAN,"CAN Pins %d, %d set to CAN\n",can->CAN_RX,can->CAN_TX);

  start1 = start2 = end1 = can->time->Tick(can->time);
  end2 = can->time->usFuture(can->time,start1,10000);
  CANMainPreInit(can,listen,irqfd,s);
  can->bus->Lock(can->bus,0,0); 

  
  while (1) {
    ___ CANStatus = can->bus->Peek8(can->bus,2);
    socketwait = txwait = rxwait = 0;
    if (CANStatus & CAN_BusOff) {
    terminate_connections:
      for (i=0;i<can->D.nconn;i++) {
	//fprintf(stderr,"close(%d)\n",can->D.conn[i].socket);
	close(can->D.conn[i].socket);
	can->D.conn[i].socket = -1;
      }
      //___ fprintf(stderr,"\nBusOff\n");
      goto escape_hatch;
    }
    if (CANStatus & CAN_TxRdy) {
      if (emptyTxQ(can)) {
        readSocketsToTxQ(can);
      }
      ___ while (!emptyTxQ(can)) {
	msg = pullTxQ(can);
	if ((msg->flags & FLAG_CONTROL) == 0) goto label0;
	else if ((tmp = process_command(can,msg)) > 0) {
	  ret = tmp;
	  goto terminate_connections;
	}
      }
      // emptyTxQ(can), since we fell out of the loop
      socketwait = 1;
      if (!can->D.nconn) { // no open sockets remain
      escape_hatch:
	can->bus->Unlock(can->bus,0,0);
	dump();
	can->pin->Unlock(can->pin,can->CAN_TX,0);
	can->pin->Unlock(can->pin,can->CAN_RX,0);
	LogReturn("%d\n",ret);
      }
      goto label1;
    label0:
      Log(LOG_CAN,"Tx\n"); {
	ArrayAutoOfSize(unsigned char,buf,8);
	memcpy(buf,msg->data,msg->length);
	ArraySizeAuto(buf,msg->length);
	can->bus->Unlock(can->bus,0,0);
	___ can->Tx(can,msg->flags,msg->id,buf);
	can->bus->Lock(can->bus,0,0); 
      }
      txwait = 1;
      start1 = can->time->Tick(can->time);
      if (can->txto) {
	end1 = can->time->usFuture(can->time,start1,can->txto);
      } else end1=start1;
      CANStatus = can->bus->Peek8(can->bus,2);
    } else {
      txwait = 1;
    }
    label1:
    while ((CANStatus & CAN_RxRdy) && (msg=pushRxQ(can))) {
      i++;
      can->bus->Unlock(can->bus,0,0);
      can->Rx(can,msg);
      can->bus->Lock(can->bus,0,0); 
      Log(LOG_CAN,"Rx %X\n",msg->id);
      CANStatus = can->bus->Peek8(can->bus,2);
    }
    rxwait = !(CANStatus & CAN_RxRdy);
    if (!emptyRxQ(can)) {
      //___ fprintf(stderr,"CCC %d\n",i); goto escape_hatch; // <RE?> N
      ___ dumpRxQToAllSockets(can); 
    } else if (can->time->TimeoutQ(can->time,start2,end2)) {
      can->bus->Preempt(can->bus);
      start2 = can->time->Tick(can->time);
      end2 = can->time->usFuture(can->time,start2,10000);
    } else if (can->time->TimeoutQ(can->time,start1,end1)) {
      //___ fprintf(stderr,"DDD\n"); goto escape_hatch; // <RR?> Y, timeout no
      wait(can,socketwait,txwait,rxwait);
    } 
  }
}

static int SJA1000CANRunning = 0;

void CANStop() {
  SJA1000CANRunning = 0;
}

#include "socket.c"

void *CANStart(void *arg) {
  Thread *th = arg;
  CANPort *ci = th->data;
  int i;
  int listen,irqfd,s,tmp;
  struct sockaddr_in csa;
  unsigned size_csa = sizeof(csa);

  {
    char tmp[80];
    sprintf(tmp,"/proc/irq/%d/irq",ci->can->irq);
    irqfd = open(tmp,O_RDONLY|O_SYNC);
  }
  if (irqfd < 0) return 0;
  SJA1000CANRunning = 1;
  listen = ServerSocketNew((int)(ci->port));
  fcntl(listen,F_SETFL,fcntl(listen,F_GETFL,0)&~O_NONBLOCK);

  //fprintf(stderr,"CAN listen=%d, ci=%p,CAN=%p\n",listen,ci,ci->can);
  while (SJA1000CANRunning) {
    if ((s=accept(listen, (struct sockaddr *)&csa, &size_csa)) >= 0) {
      //fprintf(stderr,"accept %d, ci=%p,CAN=%p\n",s,ci,ci->can);
      //fprintf(stderr,"Entering CANMain (%d)\n",s);
      //log9(LOG_CAN,"cans[%d]->D.nconn=%d ",inst,((SJA1000CAN *)cans[inst])->D.nconn);
      //for (i=0;i<((SJA1000CAN *)cans[inst])->D.nconn;i++) {
      //log9(LOG_CAN,"[%d]",((SJA1000CAN *)cans[inst])->D.conn[i].socket);
      //}
      //log9(LOG_CAN,"\n");
      tmp = CANMain(ci->can,listen,irqfd,s);
      //fprintf(stderr,"CANMain returned %d\n",tmp);
      if (tmp == 6) break;
    }
  }
}

/*
  mods necessary to support multiple sockets:

  1. When checking if there is Rx Q data available, we need to first
  maintain a circular index to the current socket under consideration.
  Whenever there is data in this Rx Q, we leave the index alone.  When
  we can't read any data, we advance to the next index.  We keep track
  of our original index so we know if we have tried them all.  However
  we must advance the index one extra so that we have a round-robin
  scheme of checking for packets.
  2. Seems like we should be able to maintain a single flag to tell us
  whether or not to block on reading our sockets.  We need to try to do 
  a non-blocking read on all sockets until we have at least one message 
  in one Rx queue, or exhaust them all.  The former results in NTR=0, 
  the latter in NTR=1.
  3. We don't start receiving into the packet Q if there are already
  complete messages in it.  We can only send one message at a time,
  so we need to keep track of the next message to send.  If only a
  partial message is left to send, we must copy it to the beginning
  and then try to read more.
  4. baud/size threshold
  The amount of time to send the message is approximately:
  (7+data bytes) * 8 * bit time
  We need to calculate the bit time whenever the baud rate is set,
  and store its value in microseconds.  For instance, 1MBps has a
  1us bit time, so message time is 56 - 120us.
  5. We have a single transmit queue.  When we go to send it, we step
  through each socket starting at the beginning.  We first check if
  there is any prior partial data left to send and if so, we try to
  send it first. 
  If that is cleared out, then we try to send the entire transmit queue, 
  and if we aren't able to send it all and we sent part of a message we 
  store the rest of the message in the partial buffer.
  While trying to send we must set a flag whenever we find a connection
  that is still open.  This is cleared before we start.  This flag
  determines whether or not we return if NTR is clear.

  6. We need to optimize our FDSET/FDCLR operations. One way to do this
  is to maintain two static sets.  The first only contains the IRQ and
  the second contains the the IRQ and all open sockets.  We only touch
  the second set to set or clear flags when connections are accepted or
  closed. 
  7. We also need to maintain a write descriptor list, as otherwise
  if we send part of a packet and no further packets are received we
  would never get around to sending.  however we also need to try to
  send our partial directly in response to the select; there is no
  path otherwise if we don't receive anything from CAN.  we can FDSET
  the static write set when we wind up copying into the partial buffer,
  and FDCLR when we finish writing out the partial.

 */

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
