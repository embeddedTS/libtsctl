#include "NetBus.h"

void *NetBusInit(tsctl *conn,int instance) {
  NetBus *ret = malloc(sizeof(NetBus));
  ret->instance = instance;
  ret->conn = conn;
  ret->in = ret->out = conn->st;
  ret->InitStatus = 1;
  ret->Init = (void *)NetBusInit;
  ret->Fini = (void *)NetBusFini;
  ret->Lock = (void *)NetBusLock;
  ret->Unlock = (void *)NetBusUnlock;
  ret->Preempt = (void *)NetBusPreempt;
  ret->Peek8 = (void *)NetBusPeek8;
  ret->Poke8 = (void *)NetBusPoke8;
  ret->Peek16 = (void *)NetBusPeek16;
  ret->Poke16 = (void *)NetBusPoke16;
  ret->Peek32 = (void *)NetBusPeek32;
  ret->Poke32 = (void *)NetBusPoke32;
  ret->BitGet8 = (void *)NetBusBitGet8;
  ret->BitAssign8 = (void *)NetBusBitAssign8;
  ret->BitSet8 = (void *)NetBusBitSet8;
  ret->BitClear8 = (void *)NetBusBitClear8;
  ret->BitGet16 = (void *)NetBusBitGet16;
  ret->BitAssign16 = (void *)NetBusBitAssign16;
  ret->BitSet16 = (void *)NetBusBitSet16;
  ret->BitClear16 = (void *)NetBusBitClear16;
  ret->BitGet32 = (void *)NetBusBitGet32;
  ret->BitAssign32 = (void *)NetBusBitAssign32;
  ret->BitSet32 = (void *)NetBusBitSet32;
  ret->BitClear32 = (void *)NetBusBitClear32;
  ret->PeekStream = (void *)NetBusPeekStream;
  ret->PokeStream = (void *)NetBusPokeStream;
  ret->Refresh = (void *)NetBusRefresh;
  ret->Commit = (void *)NetBusCommit;
  ret->BitToggle8 = (void *)NetBusBitToggle8;
  ret->BitToggle16 = (void *)NetBusBitToggle16;
  ret->BitToggle32 = (void *)NetBusBitToggle32;
  ret->Assign8X = (void *)NetBusAssign8X;
  ret->Assign16X = (void *)NetBusAssign16X;
  ret->Assign32X = (void *)NetBusAssign32X;
  ret->BitsGet8 = (void *)NetBusBitsGet8;
  ret->BitsGet16 = (void *)NetBusBitsGet16;
  ret->BitsGet32 = (void *)NetBusBitsGet32;
  return ret;
}

void *NetBusFini(NetBus *ob) {
  ob->InitStatus = 0;
}

int32 NetBusLock(NetBus *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x00);
  WriteUInt32LE(ob->out,num);
  WriteInt32LE(ob->out,flags);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetBusUnlock(NetBus *ob,uint32 num,int32 flags) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x01);
  WriteUInt32LE(ob->out,num);
  WriteInt32LE(ob->out,flags);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetBusPreempt(NetBus *ob) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x02);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x02) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint8 NetBusPeek8(NetBus *ob,int32 Address) {
  Stream *out = ob->out;
  int ret_len;
  uint8 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x03);
  WriteInt32LE(ob->out,Address);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,3);
  ret = ReadUInt8LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusPoke8(NetBus *ob,int32 Address,uint8 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x04);
  WriteInt32LE(ob->out,Address);
  WriteUInt8LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x04) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

uint16 NetBusPeek16(NetBus *ob,int32 Address) {
  Stream *out = ob->out;
  int ret_len;
  uint16 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x05);
  WriteInt32LE(ob->out,Address);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x05) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,3);
  ret = ReadUInt16LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusPoke16(NetBus *ob,int32 Address,uint16 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x06);
  WriteInt32LE(ob->out,Address);
  WriteUInt16LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x06) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

uint32 NetBusPeek32(NetBus *ob,int32 Address) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x07);
  WriteInt32LE(ob->out,Address);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x07) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusPoke32(NetBus *ob,int32 Address,uint32 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x08);
  WriteInt32LE(ob->out,Address);
  WriteUInt32LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x08) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

int32 NetBusBitGet8(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x09);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x09) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusBitAssign8(NetBus *ob,int32 Address,int32 BitNumber,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0A);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  WriteInt32LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitSet8(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0B);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitClear8(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0C);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

int32 NetBusBitGet16(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0D);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0D) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusBitAssign16(NetBus *ob,int32 Address,int32 BitNumber,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0E);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  WriteInt32LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0E) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitSet16(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x0F);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x0F) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitClear16(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x10);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x10) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

int32 NetBusBitGet32(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x11);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x11) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

void NetBusBitAssign32(NetBus *ob,int32 Address,int32 BitNumber,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x12);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  WriteInt32LE(ob->out,Value);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x12) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitSet32(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x13);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusBitClear32(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x14);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x14) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusPeekStream(NetBus *ob,int32 address,int32 direction,int8* dest) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x15);
  WriteInt32LE(ob->out,address);
  WriteInt32LE(ob->out,direction);
  WriteInt32LE(ob->out,ArrayLength(dest));
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x15) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x50) longjmp(ob->conn->exception,3);
  if (ReadInt32LE(ob->in)!=ArrayLength(dest)) longjmp(ob->conn->exception,5);
  {
    int i;
    for(i=0;i<ArrayLength(dest);i++) {
      dest[i] = ReadInt8LE(out);
    }
  }
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusPokeStream(NetBus *ob,int32 address,int32 direction,const int8* data) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x16);
  WriteInt32LE(ob->out,address);
  WriteInt32LE(ob->out,direction);
  int i;
  WriteInt32LE(ob->out,ArrayLength(data));
  for (i=0;i<ArrayLength(data);i++) {
    WriteInt8LE(ob->out,data[i]);
  }
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x16) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusRefresh(NetBus *ob) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x17);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x17) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

void NetBusCommit(NetBus *ob,int32 ForceAll) {
  Stream *out = ob->out;
  int ret_len;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x18);
  WriteInt32LE(ob->out,ForceAll);
  if (ob->conn->mode > 0) ob->conn->count++;
  if (ob->conn->mode < 2)  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) return;
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x18) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
} 

int32 NetBusBitToggle8(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x19);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x19) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetBusBitToggle16(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1A);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1A) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

int32 NetBusBitToggle32(NetBus *ob,int32 Address,int32 BitNumber) {
  Stream *out = ob->out;
  int ret_len;
  int32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1B);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitNumber);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1B) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x13) longjmp(ob->conn->exception,3);
  ret = ReadInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint8 NetBusAssign8X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  uint8 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1C);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  WriteInt32LE(ob->out,Value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1C) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,3);
  ret = ReadUInt8LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint16 NetBusAssign16X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  uint16 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1D);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  WriteInt32LE(ob->out,Value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1D) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,3);
  ret = ReadUInt16LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetBusAssign32X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1E);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  WriteInt32LE(ob->out,Value);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1E) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint8 NetBusBitsGet8(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB) {
  Stream *out = ob->out;
  int ret_len;
  uint8 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x1F);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x1F) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x00) longjmp(ob->conn->exception,3);
  ret = ReadUInt8LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint16 NetBusBitsGet16(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB) {
  Stream *out = ob->out;
  int ret_len;
  uint16 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x20);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x20) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x01) longjmp(ob->conn->exception,3);
  ret = ReadUInt16LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

uint32 NetBusBitsGet32(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB) {
  Stream *out = ob->out;
  int ret_len;
  uint32 ret;
  WriteInt16LE(ob->out,0x0001);
  WriteInt8LE(ob->out,ob->instance);
  WriteInt8LE(ob->out,0x21);
  WriteInt32LE(ob->out,Address);
  WriteInt32LE(ob->out,BitMSB);
  WriteInt32LE(ob->out,BitLSB);
  ob->out->Flush(ob->out);
  if (ob->conn->mode > 0) {
    while (ob->conn->count) {
      ob->conn->count--;
      ReadInt32LE(ob->in);
    }
  }
  if (ReadInt16LE(ob->in) != 0x0001) longjmp(ob->conn->exception,1);
  if (ReadInt8LE(ob->in) != 0x21) longjmp(ob->conn->exception,2);
  if (ReadInt8LE(ob->in) != 0x03) longjmp(ob->conn->exception,3);
  ret = ReadUInt32LE(out);
  if (ReadInt8LE(ob->in) != 0x80) longjmp(ob->conn->exception,2);
  return ret;
} 

