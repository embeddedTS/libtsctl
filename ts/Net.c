#include <stdio.h>		/* Basic I/O routines          */
#include <sys/types.h>		/* standard system types       */
#include <netinet/in.h>		/* Internet address structures */
#include <sys/socket.h>		/* socket interface functions  */
#include <netdb.h>		/* host to IP resolution       */
#include <string.h>
#include <netinet/tcp.h>        // TCP_NODELAY
#include "Net.h"

int ClientSocketNew(char *host,int port) {
  int			rc;            /* system calls return value storage */
  int            	x,s;             /* socket descriptor */
  struct addrinfo *result,*rp;
  struct addrinfo hints;
  char service[8];

  sprintf(service,"%d",port);
  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  // next line commented out because when compiling for TS-4500 I get this:
  // error: `AI_NUMERICSERV' undeclared
  //hints.ai_flags = AI_NUMERICSERV;
  if (getaddrinfo(host,service,&hints,&result) < 0) {
    return -1;
  }
  for (rp=result; rp != NULL; rp = rp->ai_next) {
    s = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
    if (s < 0) continue;
    if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &x, 4) < 0) {
      perror("TCP_NO_DELAY");
    }
    if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1) break;
    close(s);
  }
  if (rp == NULL) return -1;
  freeaddrinfo(result);
  return s;
}

int DoCmd(Packet *req,Net *net,int block) {
  int ret=99,x,y;

  if (block || net->mode != NetModeQueued) {	
    if (PacketSend(req,net->socket) != req->len) {
      net->Fini(net);				
      return -1;					
    }							
    PacketInit(net->q);				
    if (block || net->mode == NetModeBlocking) {
      y = *net->cmds;
      while (*net->cmds) {				
	int dummy;					
	(*net->cmds)--;				
	if (PacketPull32(net->socket,&dummy) <= 0) {	
	  net->Fini(net);			
	  return -2;					
	}						
      }						
      if ((x=PacketPull32(net->socket,&ret)) <= 0) {	
	net->Fini(net);				
	return -2;					
      }						
    } else {						
      (*net->cmds)++;					
    }							
  }							
  return ret;						
}

int DoCmdBytes(Packet *req,Net *net,int block) {
  int ret=99;					
  
  if (block || net->mode != NetModeQueued) {	
    if (PacketSend(req,net->socket) != req->len) {
      net->Fini(net);				
      return -1;					
    }							
    PacketInit(net->q);			
    if (block || net->mode == NetModeBlocking) {
      while (*net->cmds) {			
	int dummy;				
	(*net->cmds)--;			
	if (PacketPull32(net->socket,&dummy) <= 0) {
	  net->Fini(net);		
	  return -2;				
	}					
      }					
      if (PacketPullDummy(net->socket,&ret) <= 0) {
	net->Fini(net);	
	return -2;		
      }			
    } else {			
      (*net->cmds)++;		
    }				
  }				
  return ret;			
}

#define DOCMD(x,y,z)							\
  int DoCmd##x(Packet *req,Net *net,int block) {			\
    z ret=99;								\
									\
    if (block || net->mode != NetModeQueued) {				\
      if (PacketSend(req,net->socket) != req->len) {			\
	net->Fini(net);						\
	return -1;							\
      }									\
      PacketInit(net->q);						\
      if (block || net->mode == NetModeBlocking) {			\
	while (*net->cmds) {						\
	  int dummy;							\
	  (*net->cmds)--;						\
	  if (PacketPull32(net->socket,&dummy) <= 0) {			\
	    net->Fini(net);					\
	    return -2;							\
	  }								\
	}								\
	if (PacketPull##y(net->socket,&ret) <= 0) {			\
	  net->Fini(net);						\
	  return -2;							\
	}								\
      } else {								\
	(*net->cmds)++;							\
      }									\
    }									\
    return ret;								\
  }

//DOCMD(Bytes,Dummy,int);
//DOCMD(,32,int);
DOCMD(8,8,unsigned char);
DOCMD(16,16,unsigned short);
DOCMD(64,64,unsigned long long);

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
