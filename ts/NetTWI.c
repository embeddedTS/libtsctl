#include "NetTWI.h"

static TWIAPI NetTWIAPI =  {
  .Init = (void *)NetTWIInit,
  .Fini = (void *)NetTWIFini,
  .Lock = (void *)NetTWILock,
  .Write = (void *)NetTWIWrite,
  .Read = (void *)NetTWIRead
};

void *NetTWIInit(NetTWI *twi,int socket,int inst,int mode,Packet *q,int *cmds){
  if (twi->InitStatus > 0) return twi;
  twi->API = &NetTWIAPI;

  twi->inst = inst;
  twi->socket = socket;
  twi->InitStatus = twi->socket >= 0 ? 1 : -1;
  twi->mode = mode;
  twi->q = q;
  twi->cmds = cmds;
  return twi;
}

void NetTWIFini(NetTWI *twi){
  if (twi->InitStatus > 0) twi->InitStatus = 0;
}

int NetTWIWrite(NetTWI *twi,int devadr,int adrslen,int adrs,int len,char *twibytes){
  if (twi->InitStatus < 0) return;
  PacketPushCmd(twi->q,NetTWI_Write,twi,NetTWIClass);
  PacketPush32(twi->q,devadr);
  PacketPush32(twi->q,adrslen);
  PacketPush32(twi->q,adrs);
  PacketPush32(twi->q,len);
  PacketPushBytes(twi->q,len,twibytes);
  return DoCmd(twi->q,twi,1);
}

int NetTWIRead(NetTWI *twi,int devadr,int adrslen,int adrs,int len,char *twibytes){
  int ret;
  if (twi->InitStatus < 0) return;
  PacketPushCmd(twi->q,NetTWI_Read,twi,NetTWIClass);
  PacketPush32(twi->q,devadr);
  PacketPush32(twi->q,adrslen);
  PacketPush32(twi->q,adrs);
  PacketPush32(twi->q,len);
  ret = DoCmd(twi->q,twi,1);
  if (ret > 0) {
    PacketPullBytes(twi->socket,len,twibytes);
  }
  return ret;
}

int NetTWILock(NetTWI *twi,int command,unsigned num,void *ptr){
  if (twi->InitStatus < 0) return -999;
  PacketPushCmd(twi->q,NetTWI_Lock,twi,NetTWIClass);
  PacketPush32(twi->q,command);
  PacketPush32(twi->q,num);
  return DoCmd(twi->q,twi,1);
}


/* Tests
# Lock
# Write
# Read tested (returns 55:02:xx:xx where xx:xx is proportional to voltage)
tsctl TWI m4500x9490:0 Read 7 1 0x40 4 
# the following won't work on the TS-4500
tsctl TWI m4500x8200:0 Read 0x49 1 7 2

The following two commands do essentially the same, except that their
output is formatted differently:
# ./product_ts4500/tsctl TWI m4500x9490:0 Read 7 1 0x40 4 
55:02:03:30 
# ./product_ts4500/ts8160ctl -hm4500x9490 --info  
avr_sw_rev=2   
voltage=7.35   
voltage_mv=7350
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
