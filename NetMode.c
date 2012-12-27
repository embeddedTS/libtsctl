#include "NetMode.h"

void *NetModeInit(tsctl *conn,int instance) {
  NetMode *ret = malloc(sizeof(NetMode));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetModeInit;
  ret->Fini = (void *)NetModeFini;
  ret->JSON = (void *)NetModeJSON;
  ret->Assign = (void *)NetModeAssign;
  ret->NoAssign = (void *)NetModeNoAssign;
  ret->Hex = (void *)NetModeHex;
  ret->Dec = (void *)NetModeDec;
  ret->Oct = (void *)NetModeOct;
  ret->AStr = (void *)NetModeAStr;
  ret->AHex = (void *)NetModeAHex;
  ret->ADec = (void *)NetModeADec;
  ret->AOct = (void *)NetModeAOct;
  ret->ABinOct = (void *)NetModeABinOct;
  ret->ABinHex = (void *)NetModeABinHex;
  ret->ABinUni = (void *)NetModeABinUni;
  return ret;
}

void *NetModeFini(NetMode *ob) {
  ob->InitStatus = 0;
}

void NetModeJSON(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeAssign(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeNoAssign(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeHex(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeDec(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeOct(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeAStr(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeAHex(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeADec(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeAOct(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeABinOct(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeABinHex(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetModeABinUni(NetMode *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x000B);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0C);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x000B) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

