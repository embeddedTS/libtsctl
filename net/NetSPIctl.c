#include "NetSPIctl.h"
#include "Packet.h"

static SPIAPI NetSPIctlAPI =  {
  .Init = (void *)NetSPIctlInit,
  .Fini = (void *)NetSPIctlFini,
  .Lock = (void *)NetSPIctlLock,
  .Write = (void *)NetSPIctlWrite,
  .Read = (void *)NetSPIctlRead,
  .ReadWrite = (void *)NetSPIctlReadWrite,
  .ClockSet = (void *)NetSPIctlClockSet,
  .EdgeSet = (void *)NetSPIctlEdgeSet
};

void *NetSPIctlInit(NetSPIctl *spi,int socket,int inst){
  if (spi->InitStatus > 0) return spi;
  spi->API = &NetSPIctlAPI;

  spi->inst = inst;
  spi->socket = socket;
  spi->InitStatus = spi->socket >= 0 ? 1 : -1;
  spi->edge = EDGE_DO_NOTHING;
  return spi;
}

void NetSPIctlFini(NetSPIctl *spi){
  if (spi->InitStatus > 0) spi->InitStatus = 0;
}

int NetSPIctlLock(NetSPIctl *spi,int command,unsigned num){
  if (spi->InitStatus < 0) return -999;
  return 1; // NO-OP
}


static inline unsigned char NetSPIctlOpcodeCS(int do_assert,int do_edge,int csn) {
  unsigned char ret = csn & 3;

  if (do_assert != CS_DO_NOTHING) {
    ret |= (1 << 4);
    if (do_assert == CS_DO_ASSERT) {
      ret |= (1 << 5);
    }
  }
  if (do_edge != EDGE_DO_NOTHING) {
    ret |= (1 << 3);
    if (do_edge == EDGE_DO_POS) {
      ret |= (1 << 2);
    }
  }
  return ret;
}

static inline unsigned char NetSPIctlOpcode(int cmd,int lenlog2) {
  unsigned char ret = (cmd << 6) + lenlog2;
  return ret;
}

static int NetSPIctlRW(NetSPIctl *spi,int cmd,int adrs,unsigned char *wbuf,
		unsigned char *rbuf,int len) {
  int i,bit=0,n=1,ret,de_cs=1,pl=3,len0=len;
  unsigned char pktbuf[32+len];

  if (adrs < 0) {
    adrs = -adrs;
    de_cs = 0;
  }
  adrs--;

  //  printf("debug: %d ",len); for (i=0;i<len;i++) printf("%02X ",wbuf[i]); printf("\n");

  pktbuf[0] = NetSPIctlOpcodeCS(CS_DO_ASSERT,spi->edge,adrs);
  pktbuf[1] = pktbuf[2] = 0;
  if (spi->InitStatus < 0) return -99;
  // actual lengths possible are 2^n, where 0<=n<=12
  if (len > 4096) return -3; // too long

  while (len > 0) {
    if (len & 1) {
      pktbuf[pl++] = NetSPIctlOpcode(cmd,bit);
      if (cmd & SPICMD_WRITE) {
	for (i=0;i<n;i++) {
	  pktbuf[pl++] = *(wbuf++);
	}
      }
    }
    bit++;
    len >>= 1;
    n <<= 1;
  }
  if (de_cs) {
    pktbuf[pl++] = NetSPIctlOpcodeCS(CS_DO_DEASSERT,EDGE_DO_NOTHING,adrs);
    pktbuf[pl++] = 0;
    pktbuf[pl++] = 0;
  }
  //printf("debug: %d ",pl); for (i=0;i<pl;i++) printf("%02X ",pktbuf[i]); printf("\n");
  ret = PacketSend0(spi->socket,pktbuf,pl);
  if (ret < 0) return -100+ret;
  spi->edge = EDGE_DO_NOTHING;
  if (cmd & SPICMD_READ) {
    ret = PacketPullBytes(spi->socket,len0,rbuf);
  }
  return ret;
}

int NetSPIctlWrite(NetSPIctl *spi,int adrs,unsigned char *buf,int len) {
  return NetSPIctlRW(spi,SPICMD_WRITE,adrs,buf,0,len);
}

int NetSPIctlRead(NetSPIctl *spi,int adrs,unsigned char *buf,int len) {
  return NetSPIctlRW(spi,SPICMD_READ,adrs,0,buf,len);
}

int NetSPIctlReadWrite(NetSPIctl *spi,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len) {
  return NetSPIctlRW(spi,SPICMD_READWRITE,adrs,wbuf,rbuf,len);
}

int NetSPIctlClockSet(NetSPIctl *spi,unsigned hz) {
  char pktbuf[3];
  int ret;

  pktbuf[0] = NetSPIctlOpcodeCS(CS_DO_NOTHING,spi->edge,0);
  spi->edge = EDGE_DO_NOTHING;
  if (hz % 2048) {
    hz = 1 + hz / 2048;
  } else {
    hz = hz / 2048;
  }
  pktbuf[1] = hz >> 8;
  pktbuf[2] = hz & 0xFF;
  ret = PacketSend0(spi->socket,pktbuf,3);
  if (ret != 3) return -100+ret;
  return 1;
}

int NetSPIctlEdgeSet(NetSPIctl *spi,int posedge) {
  spi->edge = posedge? EDGE_DO_POS : EDGE_DO_NEG;
}

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
