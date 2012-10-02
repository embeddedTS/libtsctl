#ifndef __Packet_H
#define __Packet_H
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "nosig.h"

/*
  Combining socket Tx/Rx with packetizing a request/reply

  First we build up the packet by adding various data types to the packet
  such as 8,16, and 32-bit values.  Then we send the whole thing at once.

  When we receive, we pull off the data as we need it.  If this is inefficient,
  we could buffer the received packet.
 */

#define PacketMaxLen 512
typedef struct Packet {
  unsigned short len;
  char data[PacketMaxLen];
} Packet;

static inline void PacketInit(Packet *packet) {
  packet->len = 0;
}

static inline int PacketPush8(Packet *packet,unsigned char value) {
  if (packet->len + 1 >= PacketMaxLen) return -1;
  packet->data[packet->len++] = value;
  return 1;
}
static inline int PacketPush16(Packet *packet,unsigned short value) {
  if (packet->len + 2 >= PacketMaxLen) return -1;
  packet->data[packet->len++] = value >> 8;
  packet->data[packet->len++] = value & 0xFF;
  return 2;
}
static inline int PacketPush32(Packet *packet,unsigned value) {
  if (packet->len + 4 >= PacketMaxLen) return -1;
  packet->data[packet->len++] = (value >> 24) & 0xFF;
  packet->data[packet->len++] = (value >> 16) & 0xFF;
  packet->data[packet->len++] = (value >> 8) & 0xFF;
  packet->data[packet->len++] = value & 0xFF;
  return 4;
}
static inline int PacketPush64(Packet *packet,unsigned long long value) {
  if (packet->len + 8 >= PacketMaxLen) return -1;
  packet->data[packet->len++] = (value >> 56) & 0xFF;
  packet->data[packet->len++] = (value >> 48) & 0xFF;
  packet->data[packet->len++] = (value >> 40) & 0xFF;
  packet->data[packet->len++] = (value >> 32) & 0xFF;
  packet->data[packet->len++] = (value >> 24) & 0xFF;
  packet->data[packet->len++] = (value >> 16) & 0xFF;
  packet->data[packet->len++] = (value >> 8) & 0xFF;
  packet->data[packet->len++] = value & 0xFF;
  return 8;
}
static inline int PacketPushBytes(Packet *packet,unsigned char len,unsigned char *data) {
  if (packet->len + len >= PacketMaxLen) return -1;
  memcpy(packet->data+packet->len,data,len);
  packet->len += len;
  return len;
}
static inline void PacketRewind(Packet *packet,unsigned amt) {
  if (amt > packet->len) packet->len = 0;
  else packet->len -= amt;
}

static inline int PacketSend0(int socket,void *buf0,int len) {
  char *s = (char *)buf0;
  int ret,n=0;

  while (n < len) {
    errno=0;
    ret = NOSIG(send(socket,s+n,len-n,0));
    if (ret > 0) n += ret;
    // (n == 0 || n == -1 && errno == -EPIPE)
    if (n <= 0) { // won't get EAGAIN because we are not non-blocking
      return 0; // connection closed
    }
  }
  return n;
  // return NOSIG(send(socket,packet->data,packet->len,0));
}

static inline int PacketSend(Packet *packet,int socket) {
  return PacketSend0(socket,packet->data,packet->len);
}

static inline int PacketRecv(int socket,void *buf0,int len) {
  char *buf = buf0;
  int n=0,ret;
  while (n < len) {
    ret = NOSIG(recv(socket,buf+n,len-n,MSG_WAITALL));
    if (ret > 0) n += ret;
    if (ret <= 0) {
      //don't close here...
      //close(socket);
      return 0;
    }
  }
  return n;
}

static inline int PacketPullDummy(int socket,int *dummy) {
  *dummy = 1;
  return 1;
}

static inline int PacketPull8(int socket,unsigned char *ch) {
  return PacketRecv(socket,ch,1);
  //return NOSIG(recv(socket,ch,1,MSG_WAITALL));
}
static inline int PacketPull16(int socket,unsigned short *sh) {
  unsigned char buf[2];
  int ret;
  ret = PacketRecv(socket,buf,2);
  //ret = NOSIG(recv(socket,buf,2,MSG_WAITALL));
  *sh = 256 * buf[0] + buf[1];
  return ret;
}
static inline int PacketPull24(int socket,unsigned *sh) {
  unsigned char buf[3];
  int ret;
  ret = PacketRecv(socket,buf,3);
  //ret = NOSIG(recv(socket,buf,3,MSG_WAITALL));
  *sh = 256*256*buf[0] + 256 * buf[1] + buf[2];
  return ret;
}
static inline int PacketPull32(int socket,unsigned *i) {
  unsigned char buf[4];
  int ret;
  ret = PacketRecv(socket,buf,4);
  //ret = NOSIG(recv(socket,buf,4,MSG_WAITALL));
  *i = 256*65536 * buf[0] + 65536 * buf[1] + 256 * buf[2] + buf[3];
  return ret;
}
static inline int PacketPull64(int socket,unsigned long long *i) {
  unsigned char buf[8];
  int ret;
  ret = PacketRecv(socket,buf,8);
  //ret = NOSIG(recv(socket,buf,8,MSG_WAITALL));
  *i = 
    72057594037927936ULL * buf[0]
    + 281474976710656ULL * buf[1]
    + 1099511627776ULL * buf[2]
    + 4294967296ULL * buf[3]
    + 256*65536 * buf[4] 
    + 65536 * buf[5] 
    + 256 * buf[6] 
    + buf[7];
  return ret;
}

static inline int PacketPullBytes(int socket,unsigned char len,unsigned char *data) {
  int ret = PacketRecv(socket,data,len);
  // int ret =  NOSIG(recv(socket,data,len,MSG_WAITALL));
  return ret;
}
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
