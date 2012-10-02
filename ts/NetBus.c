#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "NetBus.h"


static BusAPI NetBusAPI = {
  .Init = (void *)NetBusInit,
  .Fini = (void *)NetBusFini,
  .Lock = (void *)NetBusLock,
  .Peek8 = (void *)NetBusPeek8,
  .Poke8 = (void *)NetBusPoke8,
  .Peek16 = (void *)NetBusPeek16,
  .Poke16 = (void *)NetBusPoke16,
  .Peek32 = (void *)NetBusPeek32,
  .Poke32 = (void *)NetBusPoke32,
  .BitGet8 = (void *)NetBusBitGet8,
  .BitAssign8 = (void *)NetBusBitAssign8,
  .BitSet8 = (void *)NetBusBitSet8,
  .BitClear8 = (void *)NetBusBitClear8,
  .BitGet16 = (void *)NetBusBitGet16,
  .BitAssign16 = (void *)NetBusBitAssign16,
  .BitSet16 = (void *)NetBusBitSet16,
  .BitClear16 = (void *)NetBusBitClear16,
  .BitGet32 = (void *)NetBusBitGet32,
  .BitAssign32 = (void *)NetBusBitAssign32,
  .BitSet32 = (void *)NetBusBitSet32,
  .BitClear32 = (void *)NetBusBitClear32,
  .PeekStream = (void *)NetBusPeekStream,
  .PokeStream = (void *)NetBusPokeStream,
  .Refresh = (void *)NetBusRefresh,
  .Commit = (void *)NetBusCommit,
  .BitToggle8 = (void *)NetBusBitToggle8,
  .BitToggle16 = (void *)NetBusBitToggle16,
  .BitToggle32 = (void *)NetBusBitToggle32,
  .Assign8X = (void *)NetBusAssign8X,
  .Assign16X = (void *)NetBusAssign16X,
  .Assign32X = (void *)NetBusAssign32X,
  .BitsGet8 = (void *)NetBusBitsGet8,
  .BitsGet16 = (void *)NetBusBitsGet16,
  .BitsGet32 = (void *)NetBusBitsGet32
};


void *NetBusInit(NetBus *bus,int socket,int inst,int mode,Packet *q,int *cmds) {
  if (bus->InitStatus > 0) return bus;
  bus->API = &NetBusAPI;
  
  bus->inst = inst;
  bus->socket = socket;
  bus->InitStatus = bus->socket >= 0 ? 1 : -1;
  bus->mode = mode;
  bus->q = q;
  bus->cmds = cmds;
  return bus;
}

void NetBusFini(NetBus *bus) {
  //shutdown(bus->socket,0);
  close(bus->socket);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

// 
int NetBusLock(NetBus *bus,int command,unsigned num) {
  if (bus->InitStatus < 0) return -999;
  PacketPushCmd(bus->q,NetBus_Lock,bus,NetBusClass);
  PacketPush32(bus->q,command);
  PacketPush32(bus->q,num);
  return DoCmd(bus->q,bus,1);
}

unsigned char NetBusPeek8(NetBus *bus,int adrs) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Peek8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  return DoCmd8(bus->q,bus,1);
}

void NetBusPoke8(NetBus *bus,int adrs,unsigned char val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_Poke8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush8(bus->q,val);
  DoCmd(bus->q,bus,0);
}

unsigned short NetBusPeek16(NetBus *bus,int adrs) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Peek16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  return DoCmd16(bus->q,bus,1);
}

void NetBusPoke16(NetBus *bus,int adrs,unsigned short val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_Poke16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush16(bus->q,val);
  DoCmd(bus->q,bus,0);
}

unsigned NetBusPeek32(NetBus *bus,int adrs) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Peek32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  return DoCmd(bus->q,bus,1);
}

void NetBusPoke32(NetBus *bus,int adrs,unsigned val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_Poke32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,val);
  DoCmd(bus->q,bus,0);
}

int NetBusBitGet8(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitGet8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}

void NetBusBitAssign8(NetBus *bus,int adrs,int bit,int val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitAssign8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  PacketPush32(bus->q,val);
  DoCmd(bus->q,bus,0);
}

void NetBusBitSet8(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitSet8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

void NetBusBitClear8(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitClear8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

int NetBusBitGet16(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitGet16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}

void NetBusBitAssign16(NetBus *bus,int adrs,int bit,int val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitAssign16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  PacketPush32(bus->q,val);
  DoCmd(bus->q,bus,0);
}

void NetBusBitSet16(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitSet16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

void NetBusBitClear16(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitClear16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

int NetBusBitGet32(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitGet32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}

void NetBusBitAssign32(NetBus *bus,int adrs,int bit,int val) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitAssign32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  PacketPush32(bus->q,val);
  DoCmd(bus->q,bus,0);
}

void NetBusBitSet32(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitSet32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

void NetBusBitClear32(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitClear32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  DoCmd(bus->q,bus,0);
}

void NetBusPeekStream(NetBus *bus,int adr,int dir,char *buf,int len) {
  int l,o=0;

  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_PeekStream,bus,NetBusClass);

  while (len > 0) {
    if (len > 256) {
      l = 256;
      len -= 256;
    } else {
      l = len;
      len = 0;
    }
    PacketPush32(bus->q,adr);
    PacketPush32(bus->q,dir);
    PacketPush8(bus->q,l);
    DoCmdBytes(bus->q,bus,1);
    PacketPullBytes(bus->socket,l,buf+o);
    o += l;
    adr += l;
    PacketRewind(bus->q,9);
  }
}

void NetBusPokeStream(NetBus *bus,int adr,int dir,char *buf,int len) {
  int l,o=0;

  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_PokeStream,bus,NetBusClass);

  while (len > 0) {
    if (len > 256) {
      l = 256;
      len -= 256;
    } else {
      l = len;
      len = 0;
    }
    PacketPush32(bus->q,adr);
    PacketPush32(bus->q,dir);
    PacketPush8(bus->q,l);
    PacketPushBytes(bus->q,l,buf+o);
    DoCmd(bus->q,bus,0);
    o += l;
    adr += l;
    PacketRewind(bus->q,9+l);
  }
}

void NetBusRefresh(NetBus *bus) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_Refresh,bus,NetBusClass);
  DoCmd(bus->q,bus,0);
}

void NetBusCommit(NetBus *bus,int forceall) {
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_Commit,bus,NetBusClass);
  PacketPush32(bus->q,forceall);
  DoCmd(bus->q,bus,0);
}

int NetBusBitToggle8(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitToggle8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}

int NetBusBitToggle16(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitToggle16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}

int NetBusBitToggle32(NetBus *bus,int adrs,int bit) {
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitToggle32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit);
  return DoCmd(bus->q,bus,1);
}
unsigned char NetBusAssign8X(NetBus *bus,int adrs,int bit1,int bit0,int val){
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Assign8X,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  PacketPush32(bus->q,val);
  return DoCmd8(bus->q,bus,1);
}

unsigned short NetBusAssign16X(NetBus *bus,int adrs,int bit1,int bit0,int val){
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Assign16X,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  PacketPush32(bus->q,val);
  return DoCmd16(bus->q,bus,1);
}

unsigned NetBusAssign32X(NetBus *bus,int adrs,int bit1,int bit0,int val){
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_Assign32X,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  PacketPush32(bus->q,val);
  return DoCmd(bus->q,bus,1);
}

unsigned char NetBusBitsGet8(NetBus *bus,int adrs,int bit1,int bit0){
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitsGet8,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  return DoCmd8(bus->q,bus,1);
}

unsigned short NetBusBitsGet16(NetBus *bus,int adrs,int bit1,int bit0){
  if (bus->InitStatus < 0) return 0;
  PacketPushCmd(bus->q,NetBus_BitsGet16,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  return DoCmd16(bus->q,bus,1);
}

unsigned NetBusBitsGet32(NetBus *bus,int adrs,int bit1,int bit0){
  if (bus->InitStatus < 0) return;
  PacketPushCmd(bus->q,NetBus_BitsGet32,bus,NetBusClass);
  PacketPush32(bus->q,adrs);
  PacketPush32(bus->q,bit1);
  PacketPush32(bus->q,bit0);
  return DoCmd(bus->q,bus,1);
}


/* Tests:
# Lock tested implicitly in Bus
# Peek8
tsctl Bus m4500x8200:5 Peek8 0
# Poke8
# Peek16 tested (returns 0x4500)
tsctl Bus m4500x8200:0 Peek16 0x60
# => 0x4500
# Poke16 tested (turns on Red LED, other bits unchanged from boot values)
tsctl Bus m4500x8200:0 Poke16 0x62 0xD002
# Peek32
# Poke32
# BitGet8
# BitAssign8
# BitSet8
# BitClear8
# BitGet16 tested (after boot returns 1)
tsctl Bus m4500x8200:0 BitGet16 0x62 15
# BitAssign16
# BitSet16 tested (turns on green LED)
tsctl Bus m4500x8200:0 BitSet16 0x62 15
# BitClear16 tested (turns off green LED)
tsctl Bus m4500x8200:0 BitClear16 0x62 15
# BitGet32
# BitAssign32
# BitSet32
# BitClear32
# PeekStream
# PokeStream
# Refresh
# Commit tested (simultaneously turns green LED off and red LED on)
tsctl Bus m4500x8200:1 BitClear16 -99 15
tsctl Bus m4500x8200:1 BitSet16 -99 14
tsctl Bus m4500x8200:1 Commit 0
# BitToggle8
# BitToggle16 tested (toggles green LED)
tsctl Bus m4500x8200:0 BitToggle16 0x62 15
# BitToggle32

 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
