#include "NetCAN.h"

void *NetCANInit(tsctl *conn,int instance) {
  NetCAN *ret = malloc(sizeof(NetCAN));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetCANInit;
  ret->Fini = (void *)NetCANFini;
  ret->Rx = (void *)NetCANRx;
  ret->Tx = (void *)NetCANTx;
  ret->BaudSet = (void *)NetCANBaudSet;
  ret->BaudGet = (void *)NetCANBaudGet;
  ret->Abort = (void *)NetCANAbort;
  ret->RxMulti = (void *)NetCANRxMulti;
  return ret;
}

void *NetCANFini(NetCAN *ob) {
  ob->InitStatus = 0;
}

CANResult NetCANRx(NetCAN *ob,CANMessage message[1]) {
  Stream *out = ob->out;
  int ret_len;
  CANResult ret;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0xCB) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x74) longjmp(ob->conn->exception,3);
  ReadInt32LE(out);
  {
    int i;
    for(i=0;i<1;i++) {
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      message[i].flags = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      message[i].id = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      message[i].t_sec = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      message[i].t_usec = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      message[i].length = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x40) longjmp(ob->conn->exception,3);
      ReadInt32LE(out);
      {
        int k;
        for(k=0;k<8;k++) {
          message[i].data[i] = ReadUInt8LE(out);
        }
      }
    }
  }
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

CANResult NetCANTx(NetCAN *ob,uint32 flags,uint32 id,const int8* data) {
  Stream *out = ob->out;
  int ret_len;
  CANResult ret;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  WriteUInt32LE(ob->out,flags);
  WriteUInt32LE(ob->out,id);
  int i;
  WriteInt32LE(ob->out,ArrayLength(data));
  for (i=0;i<ArrayLength(data);i++) {
    WriteInt8LE(ob->out,data[i]);
  }
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0xCB) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetCANBaudSet(NetCAN *ob,uint32 opt_baud) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  WriteUInt32LE(ob->out,opt_baud);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetCANBaudGet(NetCAN *ob) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetCANAbort(NetCAN *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

CANResult NetCANRxMulti(NetCAN *ob,CANMessage* msg,int32 min) {
  Stream *out = ob->out;
  int ret_len;
  CANResult ret;
  WriteInt16LE(ob->out,0x0007);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteInt32LE(ob->out,ArrayLength(msg));
  WriteInt32LE(ob->out,min);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0007) longjmp(ob->conn->exception,1);
  if (ReadUInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadUInt8LE(ob->in) != 0xCB) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadUInt8LE(ob->in) != 0x74) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(msg)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(msg);i++) {
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      msg[i].flags = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      msg[i].id = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      msg[i].t_sec = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      msg[i].t_usec = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
      msg[i].length = ReadUInt32LE(out);
      if (ReadUInt8LE(ob->in) != 0x40) longjmp(ob->conn->exception,3);
      ReadInt32LE(out);
      {
        int k;
        for(k=0;k<8;k++) {
          msg[i].data[i] = ReadUInt8LE(out);
        }
      }
    }
  }
  if (ReadUInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

