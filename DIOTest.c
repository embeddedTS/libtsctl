#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "libtsctl.c"


int Lookup(System *sys,char *str,...) {
  va_list ap;
  va_start(ap,str);
  int len,n;
  char dummy[1];

  len = vsnprintf(dummy,0,str,ap); 
  {
    char name[len];
    char* tmp;
    vsprintf(name,str,ap);  
    tmp = ASCIIZ(name);
    n = sys->MapLookup(sys,tmp);
    ArrayFree(tmp);
  }
  va_end(ap);
  return n;
}
 
void error(int output,int input,int driven,int read,int cn0,int pin0,int cn1,int pin1) {
  printf("DIO %d (CN%d_%d) driven %s, DIO (CN%d_%d) %d read back %s\n",
	 output,cn0,pin0,DIOValueString(driven),cn1,pin1,input,
	 DIOValueString(read));
}

void noerror(int output,int input,int driven,int read,int cn0,int pin0,int cn1,int pin1) {
  /*
  printf("DIO %d (CN%d_%d) driven %s, DIO (CN%d_%d) %d read back %s -- GOOD!\n",
	 output,cn0,pin0,DIOValueString(driven),cn1,pin1,input,
	 DIOValueString(read));
  */
}

// TO DO: sync versus async
int main(int argc,char *argv[]) {
  System *sys = SystemInit(0);
  DIO *dio = DIOInit(0);
  unsigned model,bb;
  char *cf,configfile[256+64],*str,*str2;
  int i,i2,j,maxconn,wires,*dionum,*dioval,*diocap,cn,pin,val,tested[256];
  int *cnn,*pinn;
  int passed=0,failed=0,tests,rc=0;

  // get model id and verify this is a board we can test
  model = sys->ModelId(sys);
  //printf("Model=%04X\n",model);
  if (model < 0 || (model & 0xF000) != 0x4000) {
    bb = model;
  } else {
    // get baseboard id
    bb = sys->BaseBoardId(sys);
    //printf("BaseBoard=%04X\n",bb);
  }
  // make sure we have a DIO object
  if (!dio) {
    fprintf(stderr,"No DIO 0 object\n");
    return 1;
  }
  if (dio->InitStatus <= 0) {
    fprintf(stderr,"Error %d initializing DIO 0\n",-dio->InitStatus);
    return 1;
  }
  // look up how the DIOs are connected on the base board
  maxconn = Lookup(sys,"attrib.%X.Wire.MaxConnections",bb);
  //printf("Max connections: %d\n",maxconn);
  wires = Lookup(sys,"attrib.%X.Wire.Count",bb);
  //printf("Wires: %d\n",wires);
  dionum = malloc(sizeof(int) * wires * maxconn);
  dioval = malloc(sizeof(int) * wires * maxconn);
  diocap = malloc(sizeof(int) * wires * maxconn);
  cnn = malloc(sizeof(int) * wires * maxconn);
  pinn = malloc(sizeof(int) * wires * maxconn);
  for (i=0;i<wires;i++) {
    for (j=0;j<maxconn;j++) {
      dionum[j+i*maxconn] = -1;
      cn = Lookup(sys,"attrib.%X.Wire.Connector.%d.%d",bb,i,j);
      if (cn >= 0) {
	pin = Lookup(sys,"attrib.%X.Wire.Pin.%d.%d",bb,i,j);
	cnn[j+i*maxconn] = cn;
	pinn[j+i*maxconn] = pin;
	char* name;
	name=sys->MapLookupPartial(sys,ASCIIZLocal("attrib.Connector.Name."),cn);
	if (ArrayLength(name) > 0) {
	  int drive = Lookup(sys,"attrib.%X.Wire.Drive.%d.%d",bb,i,j);
	  dionum[j+i*maxconn] = Lookup(sys,"%s%d",name,pin);
	  diocap[j+i*maxconn] = dio->Capabilities(dio,dionum[j+i*maxconn]) & drive;
	  //printf("#%d=%d [%d]\n",j+i*maxconn,dionum[j+i*maxconn],diocap[j+i*maxconn]);
	  //printf("wire %d, conn %d = %s%d = %d\n",
	  //       i,j,name,pin,dionum[j+i*maxconn]);
	}
      }      
    }
  }
  // lock all the DIOs to be tested
  for (i=0;i<wires*maxconn;i++) {
    if (dionum[i] >= 0) {
      dio->Lock(dio,dionum[i],0);
    }
  }
  // get current state of all DIOs
  for (i=0;i<wires*maxconn;i++) {
    if (dionum[i] >= 0) {
      dioval[i] = dio->GetAsync(dio,dionum[i]);
    }
  }
  // set all DIOs to inputs
  for (i=0;i<wires*maxconn;i++) {
    if (dionum[i] >= 0) {
      dio->SetAsync(dio,dionum[i],INPUT);
    }
  }
  // run the test in asynchronous mode
  for (j=0;j<wires;j++) {
    //printf("%d: %d %d %d\n",j,dionum[0+j*maxconn],
    //dionum[1+j*maxconn],dionum[2+j*maxconn]);
    for (i=0;i<maxconn;i++) {
      if (dionum[i+j*maxconn] == -1) continue;
      if (diocap[i+j*maxconn] & DIO_CAN_DRIVE_LOW) {
	// set DIO on wire i to output low
	dio->SetAsync(dio,dionum[i+j*maxconn],LOW);
	// check that other wires are low
	for (i2=0;i2<maxconn;i2++) {
	  if (dionum[i2+j*maxconn] >= 0
	      && (diocap[i2+j*maxconn] & DIO_CAN_INPUT)) {
	    val = dio->GetAsync(dio,dionum[i2+j*maxconn]);
	    if (val != ((i2==i)?LOW:INPUT_LOW)) {
	      error(dionum[i+j*maxconn],dionum[i2+j*maxconn],0,val,
		    cnn[i+j*maxconn],pinn[i+j*maxconn],
		    cnn[i2+j*maxconn],pinn[i2+j*maxconn]);
	      failed++;
	    } else {
	      noerror(dionum[i+j*maxconn],dionum[i2+j*maxconn],0,val,
		    cnn[i+j*maxconn],pinn[i+j*maxconn],
		    cnn[i2+j*maxconn],pinn[i2+j*maxconn]);
	      passed++;
	    }
	  }
	}
      }
      if (diocap[i+j*maxconn] & DIO_CAN_DRIVE_HIGH) {
	// set DIO on wire i to output high
	dio->SetAsync(dio,dionum[i+j*maxconn],HIGH);
	// check that other wires are high
	for (i2=0;i2<maxconn;i2++) {
	  if (dionum[i2+j*maxconn] >= 0
	      && (diocap[i2+j*maxconn] & DIO_CAN_INPUT)) {
	    val = dio->GetAsync(dio,dionum[i2+j*maxconn]);
	    if (val != ((i2==i)?HIGH:INPUT_HIGH)) {
	      error(dionum[i+j*maxconn],dionum[i2+j*maxconn],1,val,
		    cnn[i+j*maxconn],pinn[i+j*maxconn],
		    cnn[i2+j*maxconn],pinn[i2+j*maxconn]);
	      failed++;
	    } else {
	      noerror(dionum[i+j*maxconn],dionum[i2+j*maxconn],1,val,
		    cnn[i+j*maxconn],pinn[i+j*maxconn],
		    cnn[i2+j*maxconn],pinn[i2+j*maxconn]);
	      passed++;
	    }
	  }
	}
      }
      // set DIO on wire i to back to input
      dio->SetAsync(dio,dionum[i+j*maxconn],INPUT);
    }
  }
  // restore state of all DIOs
  for (i=0;i<wires*maxconn;i++) {
    if (dionum[i] >= 0) {
      dio->SetAsync(dio,dionum[i],dioval[i]);
    }
  }
  // unlock all the DIOs
  for (i=0;i<wires*maxconn;i++) {
    if (dionum[i] >= 0) {
      dio->Unlock(dio,dionum[i],0);
    }
  }
  switch ((model << 16) + bb) {
  case 0x42008200: tests = 186; break;
  case 0x45008200: tests = 188; break;
  case 0x47008200: tests = 180; break;
  case 0x48008200: tests = 174; break;
  
  case 0x42009490: tests = 238; break;
  case 0x45009490: tests = 172; break;
  case 0x47009490: tests = 202; break;
  case 0x48009490: tests = 168; break;

  case 0x42008100: tests = 104; break;

  case 0x42008160: tests = 104; break;
  case 0x45008160: tests = 104; break;
  case 0x47008160: tests = 104; break;
  case 0x48008160: tests = 104; break;

  case 0x48008390: tests = 24; break;

  case 0x47008900: tests = 104; break;
  case 0x48008900: tests = 104; break;

  default: tests = 0;
  }
  fprintf(stderr,"Test %04X-%04X (%d tests)\n",model,bb,tests);
  if (failed) {
    printf("failed=%d\n",failed);
    rc++;
  }
  if (tests != passed+failed) {
    printf("extra=%d\n",tests-passed-failed);
    rc++;
  }
  //printf("%d passed, %d failed\n",passed,failed);
  return rc;
}
