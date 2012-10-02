#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libtsctl.h"

#define AVR_ADDR        0x07      //AVR I2C address
#define TEMP_ADDR       0x49      //Temp Sensor I2C address
#define LED             0x04
#define SLEEP           0x08

int main(int argc,char *argv[]) {
  TWI *twi;
  System *sys;
  int i,sec,mask,ret,sleep_time,v,bb,err,model;
  ArrayAutoOfSize(char,buf,4);
  char *errmod=0;
  int OptInfo=0,OptIgnore=0,OptTemp=0,OptRetries=7,OptLED=-2;
  unsigned OptSeconds=0;
  char *host=0;

  struct option2 opts[] = {
    { 1, OptionString,   &host,  "<h>ost", "[host] sets the server host\n" },
    { 2, OptionUnsigned,  &OptInfo,    "<i>nfo", "     get input voltage and software revision" },
    { 1, OptionUnsigned, &OptSeconds, "<s>leep", "[n] sleep for the specified number of seconds (-1=forever)" },
    { 2, OptionUnsigned, &OptLED,     "<L>ED", "<0|1> set and/or get LED state" },
    { 0, OptionBoolean,  &OptIgnore,  "i<g>nore", "   ignore wake up jumper/signal during sleep" },
    { 0, OptionBoolean,  &OptTemp,    "<t>emp", "     TWI test to read temp sensor, if present" }, 
    { 0,0,0, "Technologic Systems TS-8160 Control Program\n", 
      "\nNote that sleep times will be rounded up to the granularity of sleep, which is\n"
      "8 seconds for sleeps under ~3 days and 2048 seconds for longer sleeps.  Actual\n"
      "sleep time will be +/- 10% the requested time due to low-power oscillator\n"
      "variation.\n"}
  };
  if (OptionsParse(argc,argv,opts) <= 0) {
    return 0;
  }
  if (host == 0) {
    host = "127.0.0.1";
  }
  sys = SystemInit(0);
  //twi = NetTWIInit1(0,host,NetModeBlocking);
  twi = TWIInit(0);
  if (!twi) {
    printf("error=\"No TWI present\"");
    return 1;
  }
  if (twi->InitStatus <= 0) {
    printf("error=\"Error %d initializing TWI\"\n",twi->InitStatus);
    return 1;
  }
  
  model = sys->ModelId(sys);
  if (model < 0 || (model & 0xF000) != 0x4000) {
    printf("error=\"%04X not a socket board\"\n",model);
    return 1;
  }
  bb = sys->BaseBoardId(sys); 
  if (bb != 0x8160) {
    printf("error=\"TS-8160 not detected (%04X)\"\n",bb);
    //return 1;
  }

  twi->Lock(twi,0,0);
  if (OptTemp) {
    int val;
  OptTempBegin:
    /*
    buf[0] = 7;
    TWI->Write(TEMP_ADDR,0,0,1,buf);
    TWI->Read(TEMP_ADDR,0,0,2,buf);
    */
    ArraySizeAuto(buf,2);
    ret = twi->Read(twi,TEMP_ADDR,1,0x07,buf);
    if (ret < 0) {
      printf("error=\"TWI Read error %d\"\n",ret);
      return 3;
    }

    if (buf[0] != 0x01 || buf[1] != 0x90) {
      if (OptRetries-- > 0) goto OptTempBegin;
      printf("tempSensor=0\n");
      printf("Temp Sensor sanity check failed, got ");
      printf("%02X %02X\n",buf[0],buf[1]);
      return 1;
    }
    usleep(150000);
    buf[0] = (0x4001 | (1 << 15)) >> 8;
    buf[1] = (0x4001 | (1 << 15)) & 0xFF;
    twi->Write(twi,TEMP_ADDR,1,0x01,buf);

    usleep(150000);
    buf[0] = 0x40;
    buf[1] = 0x01;
    twi->Write(twi,TEMP_ADDR,0,0,buf);
    usleep(150000);
    twi->Read(twi,TEMP_ADDR,1,0x00,buf);

    printf("tempSensor=1\n");

    val = (256*buf[0] + buf[1]) * 1000 / 128;
    printf("tempC=%d.%03d\n",val/1000,val%1000);
    val = val * 9 / 5 + 32000;
    printf("tempF=%d.%03d\n",val/1000,val%1000);
  }
  if (OptLED > -2) {
    ArraySizeAuto(buf,4);
    ret = twi->Read(twi,AVR_ADDR,1,0x80 | (OptLED>=0?1:0) | (OptLED>0?2:0),buf);
    if (ret < 0) {
      fprintf(stderr," error=\"TWI Read error %d\"\n",ret);
    } else {
      fprintf(stderr,"LED=%d\n",buf[3]);
    }
  }

  int ii=0,ij=0;
  if (OptInfo < 0) OptInfo = 1;
  while (OptInfo--) {  // get A/D reading
    if (OptInfo > 0) fprintf(stderr,"\r%d(%d) ",ii,ij);
    ii++;
  OptInfoBegin:
    ij++;
    ArraySizeAuto(buf,4);
    ret = twi->Read(twi,AVR_ADDR,1,0x40,buf);
    if (ret < 0) {
      if (OptRetries-- > 0) goto OptInfoBegin;
      fprintf(stderr," error=\"TWI Read error %d\"\n",ret);
      //return 3;
    }
    if (buf[0] != 0x55) {
      if (OptRetries-- > 0) goto OptInfoBegin;
      fprintf(stderr,"Sanity check failed: read back ");
      for (i=0;i<4;i++) {
	fprintf(stderr,"%02X ",buf[i]);
      }
      fprintf(stderr,"\n");
      //printf("\nerror=\"sanity check failed\"\n");
    } else {
      if (OptInfo == 0 || buf[1] != 2) {
	printf("avr_sw_rev=%d\n",buf[1]);
      }
      v = (unsigned)buf[2] * 256 + buf[3];
      v = v * 3690 / 4096;
      if (v < 300 || v > 4200) { // voltage way out of range, probably a TWI error, try again
	if (OptRetries-- > 0) goto OptInfoBegin;
      }
      // 1116 * REF / 4096 = 10.05
      if (OptInfo == 0 || v > 550 || v < 450) {
	printf("voltage=%d.%02d\n",v / 100,v % 100);
	printf("voltage_mv=%d\n",v*10);
      }
      // 0x7E4
      // if 0xFFF = 33V, then 8.05mV/tick
      // n * 33 / 4096
    }
  }
  if (OptSeconds) {
    sec = OptSeconds;
    if (OptIgnore) {
      mask = 0x80;
    } else {
      mask = 0;
    }
    if (sec < 0) {
      sleep_time = -1;
    } else if (sec < 262136 && ((sec % 2048) != 0)) {
      if (sec % 8 != 0) sec += (8 - sec % 8);
      sleep_time = sec / 8;
      fprintf(stderr,"Sleeping for %d seconds\n",sec);
    } else if (sec <= 67106816) {
      if (sec % 2048 != 0) sec += (2048 - sec % 2048);
      sleep_time = 0x8000 + sec / 2048;
      fprintf(stderr,"Sleeping for %d seconds\n",sec);
    } else {
      fprintf(stderr,"NOT sleeping.  Maximum sleep time is 67106816 seconds\n");
      return 3;
    }
    //printf("Mask=%02X\n",mask);
    fprintf(stderr,"Reset switch will %s\n",!(mask&0x80)?"wake up":"be ignored");
    buf[0] = SLEEP;
    buf[1] = (sleep_time & 0xFFFF)>>8;
    buf[2] = (sleep_time & 0xFF);
    buf[3] = (mask & 0xFF);
  OptSleepBegin:
    ArraySizeAuto(buf,4);
    ret = twi->Write(twi,AVR_ADDR,0,0,buf);
    if (ret < 0) {
      if (OptRetries-- > 0) goto OptSleepBegin;
      printf("error=\"TWI Write error %d\"\n",ret);
      return 3;
    }
    usleep(100000); // wait for power loss
    if (OptRetries-- > 0) goto OptSleepBegin; // we didn't sleep, try again
    twi->Fini(twi);
  }
}
/*
    We pass a 16-bit "sleep length" value to our sleep command.
    We can sleep from 
    1*8 to 32767*8 seconds (262136 seconds = 3 days 48 min 56 sec)
    in increments of 8 seconds by specifying the sleep time as
    "sleep length / 8".  The resulting value is between 1 and 0x7FFF, inclusive.
    
    To sleep longer than 262136 seconds we sleep in 2048 second increments.
    When the "sleep length" value passed is 0x8000 or larger, the sleep time
    is 262136 seconds plus "sleep length - 0x8000" times 2048. The yields a
    maximum sleep time of 0x7FFF * 2048 + 262136 = 67368952 seconds
    or 779 days 17 hours 35 min 52 seconds which is approximately
    2 years 1 month 18 days. update: we no longer subtract 0x8000

    A "sleep length" of -1 means to sleep forever, or (if enabled) until
    reset.

    We round the passed number of seconds up to the nearest 8 or 2048
    seconds.  If a negative value is passed we sleep forever (or until
    the jumper is used, if enabled, or until power is cycled.)  An
    attempt to sleep longer than the maximum length is an error and
    we will not sleep.
*/
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
