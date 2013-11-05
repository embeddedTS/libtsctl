#define THREAD_USE_POSIX
#include "NetTsctl.h"
#include <stdlib.h>
#include <stdio.h>

static inline const char *DIOValueString(DIOState state) { 
  switch(state) {                                          
  case INPUT_LOW: return "InputLow";                       
  case INPUT_HIGH: return "InputHigh";                     
  case INPUT: return "Input";                              
  case LOW: return "Low";                                  
  case HIGH: return "High";                                
  default: return "Invalid";                               
  }                                                        
}                                                          

static inline DIOState DIOValue(DIOState state) {
  switch (state) {                               
  case INPUT_LOW:                                
  case LOW:                                      
    return LOW;                                  
  case INPUT_HIGH:                               
  case HIGH:                                     
    return HIGH;                                 
  default: return LOW;                           
  }                                              
}

int main(int argc,char *argv[]) {
  DIO *dio;
  System *sys;
  Time *t;
  int socket;
  int i,j,n,m,RED_LED;
  char* name;
  unsigned t0,t1,tot=0;
  DIOState val;
  tsctl *conn;

  if (argv < 2) {
    printf("usage: %s <host>\n",argv[0]);
    return 1;
  }
  conn = TsctlClient(argv[1],NetModeBlocking);
  if (!conn) {
    perror("socket:");
    return 1;
  }
  dio = NetDIOInit(conn,0);
  if (!dio) {
    printf("Error initializing DIO\n");
    return 1;
  }
  t = NetTimeInit(conn,0);
  if (!t) {
    printf("Error initializing Time\n");
    return 1;
  }
  sys = NetSystemInit(conn,0);
  if (!sys) {
    printf("Error initializing System\n");
    return 1;
  }
  if (!setjmp(conn->exception)) {
    t0 = t->Tick(t);
    for (i=0;i<1000;i++) {
      t1 = t->Tick(t);
      if (t1 > t0) {
	tot += (t1-t0);
      } else {
	tot += (0xFFFFFFFF - t0) + t1;
      }
      t0 = t1;
    }
    printf("%uus avg round trip time\n",tot/i);
    printf("Model ID=%02X\n",sys->ModelId(sys));
    printf("BaseBoard ID=%02X\n",sys->BaseBoardId(sys));
    RED_LED = sys->MapLookup(sys,ASCIIZ("RED_LED"));
    val = dio->GetAsync(dio,RED_LED);
    printf("RED_LED=%s\n",DIOValueString(val));
    for (i=0;i<100;i++) {
      dio->SetAsync(dio,RED_LED,HIGH);
      dio->SetAsync(dio,RED_LED,LOW);
    }
    j = sys->MapLength(sys);
    for (i=0;i<j;i++) {
      name=sys->MapGet(sys,i,&n);
      //printf("%d:%s=%d\n",i,name,n);
      /*
      m=sys->MapLookup(sys,name);
      if (m!=n) {
	printf("%s=%d/%d error\n",n,m);
      }
      */
    }
  } else {
    printf("exception\n");
  }
}
