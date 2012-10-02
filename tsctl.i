%module tsctl
%{

#include "ts/libtsctl.h"

%}

%typemap(in,numinputs=0) void *me "$1=NULL;"
%typemap(check) void *me {
  $1 = arg1;
}

%include "swiggy.h"
%include "ts/System.h"
%include "ts/Bus.h"
%include "ts/CAN.h"
%include "ts/DIORaw.h"
%include "ts/DIO.h"
%include "ts/Pin.h"
%include "ts/Time.h"
%include "ts/TWI.h"
%include "ts/SPI.h"
%include "ts/AIO.h"
%include "ts/Log.h"
%include "ts/ts.h"
System *SystemInit(int inst);
Time *TimeInit(int inst);
Bus *BusInit(int inst);
Pin *PinInit(int inst);
CAN *CANInit(int inst);
DIORaw *DIORawInit(int inst);
DIO *DIOInit(int inst);
TWI *TWIInit(int inst);
SPI *SPIInit(int inst);
AIO *AIOInit(int inst);

