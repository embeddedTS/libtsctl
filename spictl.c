#include "libtsctl.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "spictl-defbin.h"
#include "ts/opt.h"

//Stream protocol:
#define SPI_CMD_MASK            b1100_0000
#define SPI_CS			b00xx_xxxx
#define SPI_CS_AMASK            b0010_0000
# define SPI_CS_ASSERT  	bxx1x_xxxx
# define SPI_CS_DEASSERT	bxx0x_xxxx
#define SPI_CS_DOMASK           b0001_0000
# define SPI_CS_DOASSERT        bxxx1_0000
#define SPI_CS_EMASK1           b0000_1000
#define SPI_CS_EMASK2           b0000_0100
#define SPI_CS_CHEDGE           bxxxx_1xxx
#define SPI_CS_EDGE_POS         bxxxx_x1xx
#define SPI_CS_EDGE_NEG         bxxxx_x0xx
#define SPI_CS_NMASK            b0000_0011
# define SPI_CS_0               bxxxx_xx00
# define SPI_CS_1               bxxxx_xx01
# define SPI_CS_2               bxxxx_xx10
# define SPI_CS_3               bxxxx_xx11
#define SPI_READ		b01xx_xxxx
#define SPI_WRITE		b10xx_xxxx
#define SPI_READWRITE		b11xx_xxxx
# define SPI_SIZE_1             bxx00_0000
# define SPI_SIZE_2             bxx00_0001
# define SPI_SIZE_4             bxx00_0010
# define SPI_SIZE_8             bxx00_0011
# define SPI_SIZE_16            bxx00_0100
# define SPI_SIZE_512           bxx00_1001
# define SPI_SIZE_4096          bxx00_1100
#define SPI_SIZE_MASK           b0011_1111

struct instance_data {
  unsigned char *un;
  int bytes;
};
struct server_data {
};
// file.h =================================

inline int fileSetBlocking(int fd,int on) {
  return fcntl(fd, F_SETFL, on ? 0 : (FNDELAY | O_NONBLOCK)) != -1;
}
// mytime.h =================================

typedef long long xTime; // number of microseconds

static inline xTime TimeNow() {
  struct timeval tv;

  gettimeofday(&tv,0);
  return ((long long)tv.tv_sec)*1000000 + tv.tv_usec;
}

static inline xTime TimeUntil(xTime t) {
  return t - TimeNow();
}

static inline struct timeval TimeToTV(xTime t) {
  struct timeval tv;

  tv.tv_sec = t / 1000000LL;
  tv.tv_usec = t % 1000000LL;
  return tv;
}

static inline struct timeval TimeLeft(xTime t) {
  struct timeval tv;

  if (t < 0) {
    tv.tv_sec = tv.tv_usec = 0;
  } else {
    tv.tv_sec = t / 1000000LL;
    tv.tv_usec = t % 1000000LL;
  }
  return tv;
}

// file.c =================================

/*
  readt
    read bytes to <buf>
    returns when bytes read reaches <count>
    or when <ms> milliseconds have elapsed, whichever comes first
    returns the number of bytes read
  assumptions: file is open in non-blocking mode

  if <ms> is a null pointer, function will wait indefinitely

  TODO: 
  * if count is zero, wait <ms> or until data is ready, then return

  TEST ME:
  will we return immediately if read() would block? want NO
  will we return immediately if EOF and/or closed connection? want YES
*/
ssize_t readt(int fd, void *buf, size_t count, unsigned *ms) {
  fd_set readset;
  ssize_t rc,bytesRead = 0;
  struct timeval tv;
  xTime tStart,tNow,tTot = 0;

  tStart = tNow = TimeNow();
  if (ms) tTot = 1000LL * *ms; else tTot = 1;
  //fprintf(stderr,"start=%lld\n",tStart);
  while (bytesRead < count && tTot - tNow + tStart > 0) {
    //fprintf(stderr,"bytesRead=%d < count=%d, t=%lld > 0\n",bytesRead,count,tTot - tNow + tStart);
    FD_ZERO(&readset);
    FD_SET(fd,&readset);

    tv = TimeToTV(tTot - tNow + tStart);
    //fprintf(stderr,"waiting %d;%d\n",tv.tv_sec,tv.tv_usec);
    if (select(fd+1,&readset,0,0,&tv) > 0) {
      rc = read(fd,buf+bytesRead,count-bytesRead);
      //fprintf(stderr,"read=%d\n",rc);
      if (rc > 0) {
	bytesRead += rc;
      } else {
	break;
      }
    }
    if (ms) tNow = TimeNow();
  }
  if (ms) *ms = (tTot - tNow + tStart)/1000;
  //fprintf(stderr,"tTot=%lld, tNow=%lld, tStart=%lld\n",tTot,tNow,tStart);
  return bytesRead;
}


// sock.h =================================
typedef int (*service)(int,void *);
typedef struct _SC {
  int s; // server descriptor
  char *buf; // must be malloced
  int len,  // total size of buf
    used,   // current number of bytes in buf
    want;   // call service fcn when used >= want
  void *inst_data;
  char *wbuf;
  int wlen,wwr;
  fd_set *wfd;
  struct _SC *next; // for server use only
} SC;
typedef SC *(*SC_new)(int);
typedef int (*multi_service)(SC *,void *,SC *);

// sock.c =================================

int create_server_socket(int port) {
  int			rc;       /* system calls return value storage  */
  int			s;        /* socket descriptor                  */
  int			cs;       /* new connection's socket descriptor */
  struct sockaddr_in	sa;       /* Internet address struct            */
  int x = 1;

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    //perror("socket: allocation failed");
    return -1;
  }
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &x, 4);
  setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &x, 4);
  if (!fileSetBlocking(s,0)) {
    printf("ERROR: Unable to set server socket non-blocking (%m)!\n");
    NOSIG(close(s));
    return -1;
  }
  rc = bind(s, (struct sockaddr *)&sa, sizeof(sa));
  if (rc) {
    //perror("bind");
    return -1;
  }
  rc = listen(s, 5);
  if (rc) {
    //perror("listen");
    return -1;
  }  
  return s;
}

SC *SC_tail(SC *conn) {
  while (conn->next) conn = conn->next;
  return conn;
}

SC *SC_append(SC *head,SC *tail) {
  SC *last_tail;

  if (head == 0) {
    return tail;
  }
  last_tail = SC_tail(head);
  last_tail->next = tail;
  tail->next = 0; // just to be sure
  return head;
}

SC *SC_delete(SC *head,SC *e) {
  SC *cur = head, *ret;

  if (e == head) {
    ret = e->next;
    free(e->buf);
    return ret;
  }
  while (cur->next != e) {
    cur = cur->next;
  }
  cur->next = e->next;
  free(e->buf);
  return head;
}

// bwrite: buffered write
// write as much data as possible from the buffer
int bwrite(int fd,char *buf,int len,int *written) {
  int rc=0;

  if (len - *written > 0) {
    rc = write(fd,buf+*written,len - *written);
  }
  if (rc > 0) {
    *written += rc;
    return 1;
  } else {
    *written = len; // pretend we sent the rest
  }
  return 0;
}

// bread: buffered read
// returns false if an error occured (or EOF)
int bread(int fd,char *buf,int *len,int *used) {
  int rc=0;

  if (*len - *used > 0) {
    rc = read(fd,buf+*used,*len-*used);
  }
  if (rc >= 0) {
    if (rc != 0) {
      //printf("%d:read %d\n",fd,rc);
    } else {
      return 0; // end of file
    }
    *used += rc;
    return 1;
  } else {
    //perror("read:");
    return 0;
  }
}

int run_multi_server(int s,multi_service svc,SC_new newSC,void *data,SC *init) {
  fd_set             rfd;           /* set of open sockets                */
  fd_set             c_rfd;         /* set of sockets waiting to be read  */
  struct sockaddr_in csa;           /* client's address struct            */
  unsigned           size_csa;      /* size of client's address struct    */
  int running = 1;
  int dmax = s+1;
  int i,cs,rc;
  SC *head = init, *cur;

  FD_ZERO(&rfd);
  if (head && head->wfd) FD_ZERO(head->wfd);
  FD_SET(s,&rfd);
  cur = init;
  while (cur) {
    FD_SET(cur->s, &rfd); 
    if (cur->s + 1 > dmax) {
      dmax = cur->s + 1;
    }
    cur = cur->next;
  }
  size_csa = sizeof(csa);
  while (running) {
    do {
      c_rfd = rfd;
      rc = NOSIG(select(dmax, &c_rfd, head ? head->wfd : NULL, NULL, NULL));
    } while (rc == -1 && errno == EINTR);
    assert(rc != -1);
    if (FD_ISSET(s, &c_rfd)) {
      cs = NOSIG(accept(s, (struct sockaddr *)&csa, &size_csa));
      if (cs < 0) {
	continue;
      }
      FD_SET(cs, &rfd);
      if (cs + 1 > dmax) {
	dmax = cs + 1;
      }
      head = SC_append(head,newSC(cs));
      continue;
    }
    cur = head;
    while (cur) {
      if (cur->s && FD_ISSET(cur->s, &c_rfd)) {
	rc = bread(cur->s,cur->buf,&cur->len,&cur->used);
	if (rc == 0) {
	  //fprintf(stderr,"closing %d\n",cur->s);
	  NOSIG(close(cur->s));
	  FD_CLR(cur->s, &rfd);
	  head = SC_delete(head, cur);
	} else {
	  if (cur->used >= cur->want) {
	    running = svc(cur,data,head);
	  }
	}
      }
      if (head && head->wfd && cur->s && FD_ISSET(cur->s, head->wfd)) {
	bwrite(cur->s,cur->wbuf,cur->wlen,&cur->wwr);
	if (cur->wwr == cur->wlen) {
	  FD_CLR(cur->s,head->wfd);
	}
      }
      cur = cur->next;
    }
  }
}

int run_server(int s,service svc,void *data) {
  unsigned size_csa; /* size of client's address struct    */
  struct sockaddr_in	csa;      /* client's address struct            */
  int cs,running = 1,n=0;

  while (running) {
    size_csa = sizeof(struct sockaddr_in);
    cs = NOSIG(accept(s, (struct sockaddr *)&csa, &size_csa));
    if (cs < 0) {
      continue;
    }
    n++;
    if (svc) {
      running = svc(cs,data);
    }
    NOSIG(close(cs));
  }
  return n;
}

int create_client_socket(char *host,int port) {
  int			rc;            /* system calls return value storage */
  int            	s;             /* socket descriptor */
  struct sockaddr_in	sa;            /* Internet address struct */
  struct hostent*     hen; 	       /* host-to-IP translation */

  hen = gethostbyname(host);
  if (!hen) {
    //perror("couldn't resolve host name");
    return -1;
  }

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  memcpy(&sa.sin_addr.s_addr, hen->h_addr_list[0], hen->h_length);
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    //perror("socket: allocation failed");
    return -1;
  }

  rc = connect(s, (struct sockaddr *)&sa, sizeof(sa));
  
  if (rc) {
    //perror("connect");
    return -1;
  }
  return s;
}
// end sock.c =============================

int server_service(SC *conn,void *data,SC *head);
SC *new_server_conn(int s);

SC *new_server_conn(int s) {
  SC *conn = malloc(sizeof(SC));

  conn->s = s;
  conn->buf = malloc(256);
  conn->len = 256;
  conn->used = 0;
  conn->want = 1;
  conn->inst_data = malloc(sizeof(struct instance_data));
  ((struct instance_data *)conn->inst_data)->un = 0;  ((struct instance_data *)conn->inst_data)->bytes = 0;
  conn->next = 0;
  conn->wbuf = 0;
  conn->wlen = 0;
  conn->wwr = 0;
  conn->wfd = 0;

  return conn;
}

extern unsigned char xbuf1[512];

#define CAVIUM_SPI_LUN(lun)			\
  LUN = lun
#define CAVIUM_SPI_SPEED(clk,edge)			\
  spi->ClockSet(spi,clk); spi->EdgeSet(spi,edge)
#define CAVIUM_SPI_READ(len1,retbuf,de_cs)	\
  {						\
    char *tmp = ArrayAlloc(len1,1);		\
    spi->Read(spi,de_cs?LUN+1:-LUN-1,tmp);	\
    memcpy(retbuf,tmp,len1);			\
    ArrayFree(tmp);				\
  }

#define CAVIUM_SPI_WRITE(len1,buf,de_cs)	\
  {						\
    char *tmp = ArrayAlloc(len1,1);		\
    memcpy(tmp,buf,len1);			\
    spi->Write(spi,de_cs?LUN+1:-LUN-1,tmp);		\
    ArrayFree(tmp);				\
  }
#define cavium_spi_readwrite(len1,wbuf,rbuf,de_cs) \
  {						   \
    char *r = ArrayAlloc(len1,1);		   \
    char *w = ArrayAlloc(len1,1);		   \
    memcpy(w,wbuf,len1);			   \
    spi->ReadWrite(spi,de_cs?LUN+1:-LUN-1,w,r);	   \
    memcpy(rbuf,r,len1);			   \
    ArrayFree(r);				   \
    ArrayFree(w);				   \
  }
#define CAVIUM_DISABLE_CS()

#define DEBUGMSG(msg,...)

#ifdef CLIENT_ONLY
unsigned char *interpret_spi_commandstream(int len,unsigned char *buf,int *n,int *did) {
  fprintf(stderr,"Direct SPI support not compiled into this executable!\n");
  exit(3);
}
#else
// takes: length of buffer, and buffer with command stream
// and pointer to integer to put the length of buffered returned
// and pointer to integer to put number of bytes we processed
// returns that buffer
/*
  interpretting a command stream
  1. we must look at the first byte to see what the command is
     and determine the length of the command
  2. if we don't have all the data for the command we cannot execute
     the command
  3. commands are length denoted strings
  4. if we can look ahead to the next command and see that is it a
     de-assertion, we can optimize.

  
 */
SPI *spi;
int LUN;

unsigned char *interpret_spi_commandstream(int len,unsigned char *buf,int *n,int *did) {
  unsigned char *next,*retbuf=0,*end,*buf0=buf;
  int retlen=0,lun,clk,edge;
  int de_cs,len1,pending=0;

  end = buf + len;
  if (did) *did = 0;
  lun = LUN;

  DEBUGMSG("interpretting %d bytes, buf=%p, end=%p\n",len,buf,end);
  while (len > 0) {
    DEBUGMSG("%d bytes left, buf[0]=%02X\n",len,buf[0]);
    switch ((buf[0] & SPI_CMD_MASK) >> 6) {
    case 0: // SPI_CS
      if (buf[0] & SPI_CS_AMASK) {
	next = buf + 3;
	if (next > end) { // insufficient length to hold args
	  DEBUGMSG("%p > %p + %d\n",next,buf,len1);
	  if (n) *n = retlen;
	  return retbuf;
	}
	if ((buf[0] & SPI_CS_DOMASK) == SPI_CS_DOASSERT) {
	  if (lun != (buf[0] & SPI_CS_NMASK)) {
	    lun = buf[0] & SPI_CS_NMASK;
	    DEBUGMSG("lun=%d\n",lun);
	    CAVIUM_SPI_LUN(lun);
	  }
	}
	clk = ((((unsigned)buf[1]) << 8) + buf[2]) * 2048;
	if ((buf[0] & SPI_CS_EMASK1) == SPI_CS_CHEDGE) {
	  if ((buf[0] & SPI_CS_EMASK2) == SPI_CS_EDGE_POS) {
	    edge = 1;
	  } else {
	    edge = -1;
	  }
	} else {
	  edge = 0;
	} 
	DEBUGMSG("clk=%d, edge=%d\n",clk,edge);
	if (clk || edge) {
	  CAVIUM_SPI_SPEED(clk,edge);
	}
	buf+=3;
	if (did) *did += 3;
	len-=3;

      } else {
	if (buf0 == buf) { // first command
	  DEBUGMSG("CMD 0 deassert (forced)\n",0);
	  CAVIUM_DISABLE_CS();
	} else {
	  DEBUGMSG("CMD 0 deassert\n",0);
	}
        buf++;
	if (did) *did += 1;
	len--;
      }
      break;
    case 1: // SPI_READ
      len1 = (1 << ((unsigned)buf[0] & SPI_SIZE_MASK));
      next = buf+1;
      de_cs = (len > 1) &&
	((next[0] & SPI_CMD_MASK) == 0) && ((next[0] & SPI_CS_AMASK) == 0);
      retbuf = realloc(retbuf,retlen+len1);
      DEBUGMSG("read %d to %p, de_cs=%d\n",len1,retbuf+retlen,de_cs);
      CAVIUM_SPI_READ(len1,retbuf+retlen,de_cs);
      retlen += len1;
      buf++;
      if (did) *did += 1;
      len--;
      break;
    case 2: // SPI_WRITE
      len1 = (1 << ((unsigned)buf[0] & SPI_SIZE_MASK));
      next = buf+len1+1;
      if (next > end) { // insufficient length to hold args
	DEBUGMSG("%p > %p + %d\n",next,buf,len1);
	if (n) *n = retlen;
	return retbuf;
      }
      de_cs = (next < end) &&
	((next[0] & SPI_CMD_MASK) == 0) && ((next[0] & SPI_CS_AMASK) == 0);
      DEBUGMSG("buf=%p,next=%p, len1=%d, len=%d\n",buf,next,len1,len);
#ifdef DEBUG
      //      if (de_cs == 0 && len1 > 1) {
      //	printf("COND1=%d\n",(next > buf + len1));
      //	printf("COND2=%d\n",(next[0] & SPI_CMD_MASK) == 0);
      //	printf("COND3=%d\n",(next[0] & SPI_CS_AMASK) == 0);
      //	printf("next[0]=%X, SPI_CS_AMASK=%X\n",next[0],SPI_CS_AMASK);
      //      }
      {
	int i;
	fprintf(stderr,"write %d, de_cs=%d\n",len1,de_cs);
	for (i=0;i<len1;i++) fprintf(stderr,"%02X ",buf[i+1]);
	fprintf(stderr,"\n");
      }
#endif
      CAVIUM_SPI_WRITE(len1,buf+1,de_cs);
      buf += (len1+1);
      if (did) *did += (len1 + 1);
      len -= (len1+1);
      break;
    case 3: // SPI_READWRITE
      len1 = (1 << ((unsigned)buf[0] & SPI_SIZE_MASK));
      next = buf+len1+1;
      if (next > end) { // insufficient length to hold args
	DEBUGMSG("%p > %p + %d\n",next,buf,len1);
	if (n) *n = retlen;
	return retbuf;
      }
      de_cs = (next < end) &&
	((next[0] & SPI_CMD_MASK) == 0) && ((next[0] & SPI_CS_AMASK) == 0);
      DEBUGMSG("buf=%p,next=%p, len1=%d\n",buf,next,len1);
      DEBUGMSG("readwrite %d\n",len1);
      retbuf = realloc(retbuf,retlen+len1);
      cavium_spi_readwrite(len1,buf+1,retbuf+retlen,de_cs);
      retlen += len1;
      buf += (len1+1);
      if (did) *did += (len1+1);
      len -= (len1+1);
      break;
    }
  }
  if (n) *n = retlen;
  return retbuf;
}
#endif
/*
  we don't know how many bytes we want before we get the data.
  give us the data whenever it arrives and either
  do each command as we get the complete data.
  if we don't have an assert or de-assert as the last command we get,
  then go ahead and assume to NOT de-assert
  
  if we have a partial command, ignore it, but set our buffer such that
  we haven't consumed it and will finish it later.

  since the buffer might not hold the packet, we need a way to indicate
  how much of the command we did NOT process, but the server must
  put that data away and then append additional data to it.

  how do we handle output as a server? interpret_spi_commandstream
  returns a buffer containing all the data to send to our socket.
 */
int server_service(SC *conn,void *data,SC *head) {
  int retlen,did,cmdlen;
  unsigned char *ret,*cmd;
  struct instance_data *inst = conn->inst_data;

  if (inst->un) { // already have pending data, add to it
    DEBUGMSG("+%d\n",conn->used);
    cmd = inst->un = realloc(inst->un,inst->bytes + conn->used);
    memcpy(inst->un+inst->bytes,conn->buf,conn->used);
    cmdlen = (inst->bytes += conn->used);
  } else { // all new data
    DEBUGMSG("=%d\n",conn->used);
    cmd = conn->buf;
    cmdlen = conn->used;
  }
  ret = interpret_spi_commandstream(cmdlen,cmd,&retlen,&did);
  if (retlen > 0) {
    DEBUGMSG("returning %d\n",retlen);
    write(conn->s,ret,retlen);
    free(ret);
  }
  if (did < inst->bytes) {
    if (inst->bytes != conn->used) {
      // we already copied the bytes to the instance buffer
      // get rid of the bytes we already sent
      DEBUGMSG("+=%d\n",inst->bytes-did);
      memmove(inst->un,inst->un + did,inst->bytes - did);
      inst->bytes -= did;
    } else {
      // instance buffer is empty, so copy to it
      DEBUGMSG("==%d\n",inst->bytes-did);
      inst->un = malloc(inst->bytes - did);
      memcpy(inst->un,conn->buf + did,inst->bytes - did);
      inst->bytes -= did;
    }
  } else {
    if (inst->un) free(inst->un);
    inst->un = 0;
    inst->bytes = 0;
  }
  conn->used = 0;
  return 1;
}

int bufsize = 0,bufn = 0, expected=0;
char *buf = 0;
int server = -1;
int ext,clk,edge,lun;

void buf_largen(unsigned by) {
  if (bufn + by >= bufsize) {
    if (bufsize * 2 < bufn + by) {
      bufsize = bufn + by;
    } else {
      bufsize *= 2;
    }
    buf = realloc(buf,bufsize);
  }
}

void spi_start(char *ip,int port) {
  server = create_client_socket(ip,port);
}

void spi_init() {
  if (buf) {
    free(buf);
    buf = 0;
  }
  bufsize = bufn = expected = 0;
}

// clock=0 means to use existing clock
// edge>0 means use positive edge, edge<0 means use negative edge, 0=unchanged
// cs<0 means to use existing cs
int spi_assert_cs_config(int cs,int clock,int edge) {
  unsigned char edgelogic;
  buf_largen(2);
  if (cs > 3) return 0;
  if (clock > 2048*65535) return 0;
  edgelogic = (edge == 0) ? 0 
    : SPI_CS_CHEDGE | (edge>0 ? SPI_CS_EDGE_POS : SPI_CS_EDGE_NEG);
  buf[bufn++] = SPI_CS|SPI_CS_ASSERT|edgelogic|((cs>=0)?(cs|SPI_CS_DOASSERT):0);
  clock /= 2048;
  DEBUGMSG("--clock=%d\n",clock);
  buf[bufn++] = clock >> 8;
  buf[bufn++] = clock & 0xFF;
  return 1;
}

int spi_assert_cs(int cs) {
  return spi_assert_cs_config(cs,0,0);
}

void spi_write(unsigned char value) {
  buf_largen(2);
  buf[bufn++] = SPI_WRITE|SPI_SIZE_1;
  buf[bufn++] = value;
}

void spi_readwrite(unsigned char value) {
  buf_largen(2);
  buf[bufn++] = SPI_READWRITE|SPI_SIZE_1;
  buf[bufn++] = value;
  expected++;
}

void spi_readwrite2(unsigned char val1,unsigned char val2) {
  buf_largen(2);
  buf[bufn++] = SPI_READWRITE|SPI_SIZE_2;
  buf[bufn++] = val1;
  buf[bufn++] = val2;
  expected += 2;
}

void spi_readstream(int bytes) {
  int n,i,j;

  expected += bytes;
  while (bytes) {
    i = n = (bytes > 4096) ? 4096 : bytes;
    j = 1;
    while (i) {
      if (i & 1) {
	buf_largen(1);
	buf[bufn++] = SPI_READ|(j-1);
      }
      i >>= 1;
      j++;
    }
    bytes -= n;
  }
}

void spi_writestream(unsigned bytes,unsigned char *buf1) {
  int n,i,j;
  unsigned ii;

  while (bytes) {
    i = n = (bytes > 8191) ? 8191 : bytes;
    j = 1;
    while (i) {
      if (i & 1) {
	buf_largen(1+bytes);
	buf[bufn++] = SPI_WRITE|(j-1);
	for (ii=0;ii<(1<<(j-1));ii++) {
	  buf[bufn++] = *buf1++;
	}
      }
      i >>= 1;
      j++;
    }
    bytes -= n;
  }
}

void spi_deassert_cs(int cs) {
  buf_largen(1);
  buf[bufn++] = SPI_CS|SPI_CS_DEASSERT|SPI_CS_3;
}

unsigned char *spi_execute(int *n) {
  char *buf1;
  unsigned ms = 1000;
  int got;

  if (server>0) {
    DEBUGMSG("execute writing %d\n",bufn);
    *n = write(server,buf,bufn);
    // what if this assert fails regularly?
    // if it fails, we should actually handle the condition, not die!
    if (*n != bufn) {
      fprintf(stderr,"wrote %d of %d (%m,%d)EFAULT=%d\n",*n,bufn,errno,EFAULT);
    }
    assert(*n == bufn);
    buf1 = malloc(expected);
    got = readt(server,buf1,expected,&ms);
    DEBUGMSG("read %d of %d\n",got,expected);
    *n = got;
    assert(got == expected);
    return buf1;
  } else {
    return interpret_spi_commandstream(bufn,buf,n,0);
  }
  /* TODO: Executes/flushes all enqueued ops (sends stream via socket) */
}

void spi_stop() {
  /* Close connection */
  if (server > 0) {
    NOSIG(close(server));
    server = -1;
  }
}

void spi_flash_wait() {
  char *buf=0;
  do {
    if (buf) free(buf);
    usleep(100000);
    spi_init();
    spi_assert_cs(1);
    spi_write(0x05); // read status register
    spi_readstream(2);
    spi_deassert_cs(1);
    buf = spi_execute(0);
  } while ((buf[1] & 1) == 1);
}

// for 9448 SPI flash, must be 8k (16 sector) boundary
void spi_sector_erase(unsigned int sector) {
  char buf[5];

  spi_init();
  //  spi_assert_cs(1);
  buf[0] = 0x06; // write-enable
  buf[1] =  0x20; // sector erase
  buf[2] = (sector >> 16) & 0xFF;
  buf[3] = (sector >> 8) & 0xFF;
  buf[4] = sector & 0xFF;
  spi_writestream(1,buf);
  spi_deassert_cs(1);
  spi_assert_cs(1);
  spi_writestream(4,buf+1);
  spi_deassert_cs(1);

  spi_execute(0);
  spi_flash_wait();
}

void spi_flash_write(unsigned int adr,unsigned int len,unsigned char *dat) {
  char buf[5];
  if (len == 0) return;
  spi_init();
  spi_assert_cs(1);
  buf[0] = 0x06; // write-enable
  buf[1] = 0x02;
  buf[2] = (adr >> 16) & 0xFF;
  buf[3] = (adr >> 8) & 0xFF;
  buf[4] = adr & 0xFF;
  spi_writestream(1,buf);
  spi_deassert_cs(1);
  spi_assert_cs(1);
  spi_writestream(4,buf+1);
  spi_writestream(len,dat);
  spi_deassert_cs(1);
  spi_execute(0);
  spi_flash_wait();
}

unsigned char *spi_flash_read(unsigned int adr,unsigned int len) {
  char buf[5];
  if (len == 0) return;
  spi_init();
  spi_assert_cs(1);
  buf[0] = 0x0B;
  buf[1] = (adr >> 16) & 0xFF;
  buf[2] = (adr >> 8) & 0xFF;
  buf[3] = adr & 0xFF;
  buf[4] = 0;
  spi_writestream(5,buf);
  spi_readstream(len);
  spi_deassert_cs(1);
  return spi_execute(0);
}

// chip erase
void spi_chip_erase(void) {
  spi_init();
  spi_assert_cs(1);
  spi_write(0x60);
  spi_deassert_cs(1);
  spi_execute(0);
  spi_flash_wait();
}

// read device id
void spi_read_device_id(unsigned *manufacturer, unsigned *devid) {
  unsigned char *result;
  spi_init();
  spi_assert_cs(1);
  spi_write(0x9F);
  spi_readstream(4);
  spi_deassert_cs(1);
  result = spi_execute(0);
  assert(result);
  if (manufacturer) *manufacturer = result[1];
  if (devid) *devid = (((unsigned)result[0]) << 8) + result[3];
}
/*
void spi_clock(unsigned freq,int edge) {
  spi_init();
  spi_assert_cs_config(1,freq,edge);
  spi_execute(0);
}
*/
int init_cavium();

int opt_int(char *arg,int *target,int opt) {
  if (!arg) {
    *target = 7575;
  } else {
    *target = atoi(arg);
  }
  return 1;
}

char *parse_hex_octets(char *buf,int *n) {
  char *ret,*s;
  int i,len = strlen(buf),count=0;
  *n = 0;
  for (i=0;i<len;i++) {
    if (buf[i] == ':') {
      count++;
    }
  }
  ret = malloc(2+count);
  while (buf) {
    s = strchr(buf,':');
    if (s) {
      *s++ = 0;
    }
    ret[n[0]] = strtoul(buf,0,16);
    n[0]++;
    buf = s;
  }
  return ret;
}

int opt_spiseq(char *arg,unsigned *target,int opt) {
  char *buf;
  int i,n;

  target[0]++;
  switch(opt) {
  case 'p':
    if (OptionHost(arg,&i,opt)) {
      if (server != -1) {
	unsigned char *buf = spi_execute(&i);
	write(1,buf,i);
	NOSIG(close(server));
      }
      server = i;
    }
    break;
  case 'l':
    spi_assert_cs(atoi(arg));
    break;
  case 'r':
    spi_readstream(atoi(arg));
    break;
  case 'w':
    buf = parse_hex_octets(arg,&n);
    spi_writestream(n,buf);
    break;
  case 'd':
    buf = parse_hex_octets(arg,&n);
    for (i=0;i<n-1;i+=2) {
      spi_readwrite2(buf[i],buf[i+1]);
    }
    if (i < n) {
      spi_readwrite(buf[i]);
    }
    break;
  case 'c':
    i = atoi(arg);

    // this is a hack to get around the fact that we can only request
    // frequencies that are multiples of 2048 via our packet protocol
    // technically this means that we might get a slightly higher
    // frequency than we requested.  but if we don't do this, we can't
    // hit 75MHz, since we have a remainder and will get dropped to
    // 37.5MHz
    if (i % 2048 > 0) {
      i += 2048;
    }
    spi_assert_cs_config(-1,i,0);
    break;
  case 'e':
    spi_assert_cs_config(-1,0,atoi(arg));
    break;
  }
  return 1;
}

 /*
 * This function records a PID so that ts7500ctl --loadfpga will send
 * a SIGHUP to the PID after FPGA reconfiguration.
 *
 * Predefined slots:
 *  0 - sdctl NBD service
 *  1 - nand NBD service
 *  2 - SPI flash NBD service
 *  3 - xuartctl --server service
 *  4 - canctl --server service
 *  5 - dmxctl --server service
 *  6 - spictl --server service
 *  7 - reserved
 *  8 - reserved
 *  >= 9 is invalid
 *
 * Before calling, application should setup or ignore the SIGHUP signal. 
 * e.g. signal(SIGHUP, SIG_IGN);
 */
record_daemon_pid(int slot) {
  key_t shmkey;
  int shmid;
  unsigned int *sbus_shm;
  
  shmkey = 0x75000000;
  shmid = shmget(shmkey, 0x1000, IPC_CREAT);
  assert(shmid != -1);
  sbus_shm = shmat(shmid, NULL, 0);
  sbus_shm += (slot * 32);
  sbus_shm[0] = getpid();

  shmdt(sbus_shm);
  return 0;
}

int gotHUP = 0;

void do_hup() {
  gotHUP = 1;
}

typedef OptionFunction opt_func;
#define opt_bool OptionBoolean

int main(int argc, char **argv) {
  unsigned opt_bytes=512;
  int opt_read=-1,opt_write=-1, opt_doseq = 0, opt_holdcs=0 , opt_lun=0;
  int opt_server = 0, opt_client = -1, opt_verbose = 0;
  int opt_ce = 0, opt_se = -1;
  int manu=-1, dev=-1, bytes, total=0;
  unsigned char buf[512],*rbuf;

  struct option2 opts[] = {
    { 1, (opt_func)opt_spiseq,&opt_doseq  ,"<c>lock", "frequency    SPI clock frequency" },
    { 1, (opt_func)opt_spiseq,&opt_doseq  ,"<e>dge", "value         set clock edge (positive for > 0, negative for < 0)" },
    /*
    { 0, (opt_func)opt_bool  ,&opt_ce     ,"erasec<h>ip", "         erase entire flash chip" },
    { 1, (opt_func)opt_long  ,&opt_se     ,"erasesec<t>or", "sector erase specified 8k sector on flash chip" },
    { 1, (opt_func)opt_long  ,&opt_write  ,"<W>rite", "adrs         read stdin and write to flash starting at byte adrs" },
    { 1, (opt_func)opt_long  ,&opt_read   ,"<R>ead", "adrs          read flash starting at byte adrs and write to stdout" },
    { 1, (opt_func)opt_long  ,&opt_bytes  ,"<b>ytes", "count        number of bytes to read (default is 512)" },
    { 0, (opt_func)opt_bool  ,&opt_verbose,"<v>erbose", "           output what we are doing to stderr" },
    */
    { 1, (opt_func)opt_spiseq ,&opt_doseq ,"<w>ritestream", "data   write colon delimited hex octets to SPI" },
    { 1, (opt_func)opt_spiseq ,&opt_doseq ,"rea<d>write", "data     write colon delimited hex octets to SPI while reading to stdout" },
    { 1, (opt_func)opt_spiseq ,&opt_doseq ,"<r>eadstream", "bytes   read specified number of bytes from SPI to stdout" },
    { 0, (opt_func)opt_bool  ,&opt_holdcs ,"h<o>ldcs", "            don't de-assert CS# when done" },
    { 1, (opt_func)opt_spiseq,&opt_doseq  ,"<l>un", "id             Talk to specified chip number" },
    { 2, (opt_func)opt_int   ,&opt_server ,"<s>erver", "<port>      Daemonize and run as server listening on port" },
    { 1, (opt_func)opt_spiseq,&opt_client ,"<p>ort", "<host><:port> Talk to spictl server" },
    { 0,0,0,"Technologic Systems SPI controller manipulation.\n\nGeneral options:\n",
      "hex octets are hexadecimal bytes. for example,\n"
      "this command reads 32 bytes of CS#1 SPI flash from address 8192:\n"
      "./spictl -l 1 -w 0B:00:20:00:00 -r 32\n"
      /*
	TS-4500 + TS-8200
        ./spictl -e 1 -c 2000000 -l 0 -w 04:00 -d 08:00:14:00:18:00:24:00:28:00:34:00:38:00 -r 2 | hexdump -C
	should return something close to this:
	6e 0a 76 0a 35 0d 29 06  78 0a aa 0b 70 0a 00 00
       */
    }
  };
#ifndef CLIENT_ONLY
  spi = SPIInit(0);
#endif
  spi_init();

  OptionHostPortDefault = 7552;
  OptionsParse(argc,argv,opts);

  if (opt_doseq > 0) {
    if (!opt_holdcs) {
      spi_deassert_cs(0);
    }
    rbuf = spi_execute(&bytes);
    write(1,rbuf,bytes);
  }
  /*
  if (opt_ce) {
    if (opt_verbose) {
      fprintf(stderr,"Erasing SPI flash chip\n");
    }
    spi_chip_erase();
  }
  if (opt_se >= 0) {
    if (opt_verbose) {
      fprintf(stderr,"Erasing SPI flash sector %d\n",opt_se);
    }
    spi_sector_erase(opt_se);
  }
  if (opt_write >= 0) {
    if (opt_verbose) {
      fprintf(stderr,"Writing SPI flash from address %d\n",opt_write);
    }
    total = 0;
    do {
      bytes = read(0,buf,512);
      if (bytes > 0) {
	total += bytes;
	spi_flash_write(opt_write,bytes,buf);
	opt_write += bytes;
      }
    } while (bytes > 0);
    if (opt_verbose) {
      fprintf(stderr,"%d bytes written\n",total);
    }
  }

  if (opt_read >= 0) {
    if (opt_verbose) {
      fprintf(stderr,"Reading SPI flash from address %d for %d bytes\n",opt_read,opt_bytes);
    }
    while (opt_bytes > 0) {
      bytes = opt_bytes > 4096 ? 4096 : opt_bytes;
      rbuf = spi_flash_read(opt_read,bytes);
      write(1,rbuf,bytes);
      opt_bytes -= bytes;
      opt_read += bytes;
    }
  }
  */
  if (opt_server) {
#ifdef CLIENT_ONLY
    fprintf(stderr,"Error: no server support in this binary\n");
#else
    struct sigaction sa;
    int s;
    struct server_data sd;

    sa.sa_handler = do_hup;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGHUP, &sa, NULL);
    signal(SIGPIPE,SIG_IGN);

    s = create_server_socket(opt_server);
    if (s < 0) {
      perror("create_server_socket:");
      return 3;
    }
    daemon(1,0);
    record_daemon_pid(6);

    DEBUGMSG(stderr,"Waiting for SPI EXT\n");
    while (!ext) {
      while (!gotHUP) {
	usleep(100000);
      }
      gotHUP = 0;
      //cavium_spi_getparms(&ext,&clk,&edge,&lun);
      //ext = cavium_spi_detect_extsup();
    }
    return run_multi_server(s,server_service,new_server_conn,&sd,0);
#endif
  }

}

