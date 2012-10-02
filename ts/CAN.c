#include "CAN.h"

#if 0
/*
  who locks the Bus used by CAN, if any?
  ideally this function should probably do this.
  there isn't any real need to keep CAN locked outside of this call,
  although we should prevent a CAN object from simultaneously being
  (re)entered.

  one way of viewing this is that we need underscore functions which
  assume the lock is already acquired, and those without acquire the
  lock as then call the underscore version.
 */
int CANTxRx(TSCANFeature *CAN,
	    CANMessage *tx,unsigned *txlen,
	    CANMessage *rx,unsigned *rxlen,
	    int autoRecoverBusOff) {
  int rxcount=0;
  int status0,status;
  int ack = CANStatusAll & ~(autoRecoverBusOff ? 0 : CANStatusErrorBusOff);

  status0 = status = CAN->Status(CAN,ack);
  while (*rxlen > 0 && status & CANStatusRxReady) {
      CAN->Rx(CAN,rx+rxcount);
      (*rxlen)--;
      rxcount++;
      status = CAN->Status(CAN,ack);
  }
  //fprintf(stderr,"tx=%p txlen=%d status0=%X\n",tx,*txlen,status0);
  if (tx && *txlen && status & CANStatusTxReady) {
    CAN->Tx(CAN,tx);
    (*txlen)--;
    //status = CAN->Status(CAN,ack);
  }
  return (status0 & CANStatusErrorMask) | (status & CANStatusReadyMask);
}
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
