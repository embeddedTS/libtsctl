#include <stdio.h>
#include "libtsctl.h"
#include "Array.h"

int _BaseBoardIdGet() {
  int adrs[3],inbit,extrabit;
  int saveCN2_6,saveCN2_8,saveCN1_98,saveCN1_83,saveCN1_85;
  int i,value=0,tmp;
  System *sys = SystemInit(0);
  DIO *dio = DIOInit(0);

  if (!dio) return 0;
  adrs[0] = sys->MapLookup(sys,ASCIIZLocal("CN2_6"));
  if (adrs[0] < 0) return 0;
  adrs[1] = sys->MapLookup(sys,ASCIIZLocal("CN2_8"));
  if (adrs[1] < 0) return 0;
  adrs[2] = sys->MapLookup(sys,ASCIIZLocal("CN1_98"));
  if (adrs[2] < 0) return 0;
  inbit = sys->MapLookup(sys,ASCIIZLocal("CN1_83"));
  if (inbit < 0) return 0;
  extrabit = sys->MapLookup(sys,ASCIIZLocal("CN1_85"));
  if (extrabit < 0) return 0;
  dio->Lock(dio,adrs[0],0);
  dio->Lock(dio,adrs[1],0);
  dio->Lock(dio,adrs[2],0);
  dio->Lock(dio,inbit,0);
  dio->Lock(dio,extrabit,0);
  saveCN2_6 = dio->GetAsync(dio,adrs[0]);
  saveCN2_8 = dio->GetAsync(dio,adrs[1]);
  saveCN1_98 = dio->GetAsync(dio,adrs[2]);
  saveCN1_83 = dio->GetAsync(dio,inbit);
  saveCN1_85 = dio->GetAsync(dio,extrabit);
  dio->SetAsync(dio,inbit,INPUT);
  dio->SetAsync(dio,extrabit,INPUT);
  for (i=7;i>=0;i--) {
    dio->SetAsync(dio,adrs[0],i&1?LOW:HIGH);
    dio->SetAsync(dio,adrs[1],i&2?LOW:HIGH);
    dio->SetAsync(dio,adrs[2],i&4?HIGH:LOW);
    if ((tmp=dio->GetAsync(dio,adrs[0])) != ((i&1)?LOW:HIGH)) {
      //printf("adrs[0] wrote %s, read back %s\n",
      //       DIOValueString((i&1)?LOW:HIGH),DIOValueString(tmp));
    }
    if ((tmp=dio->GetAsync(dio,adrs[1])) != ((i&2)?LOW:HIGH)) {
      //printf("adrs[1] wrote %s, read back %s\n",
      //       DIOValueString((i&2)?LOW:HIGH),DIOValueString(tmp));
    }
    if ((tmp=dio->GetAsync(dio,adrs[2])) != ((i&4)?HIGH:LOW)) {
      //printf("adrs[2] wrote %s, read back %s\n",
      //       DIOValueString((i&4)?HIGH:LOW),DIOValueString(tmp));
    }
    value <<= 1;
    tmp = dio->GetAsync(dio,inbit);
    tmp = dio->GetAsync(dio,inbit);
    value |= (3+tmp);
  }
  dio->SetAsync(dio,adrs[0],saveCN2_6);
  dio->SetAsync(dio,adrs[1],saveCN2_8);
  dio->SetAsync(dio,adrs[2],saveCN1_98);
  dio->SetAsync(dio,inbit,saveCN1_83);
  dio->SetAsync(dio,extrabit,saveCN1_85);
  dio->Unlock(dio,adrs[0],0);
  dio->Unlock(dio,adrs[1],0);
  dio->Unlock(dio,adrs[2],0);
  dio->Unlock(dio,inbit,0);
  dio->Unlock(dio,extrabit,0);
  //fprintf(stderr,"%X\n",value);
  //value = value & 0x3F;
  // TO DO: look up value in Map
  switch (value & 0x3F) {
  case 0x01: return 0x8395;
  case 0x02: return 0x8390;
  case 0x03: return 0x8510;
  case 0x04: return 0x8500;
  case 0x05: return 0x8400;
  case 0x06: return 0x8160;
  case 0x07: return 0x8100;
  case 0x08: return 0x8820;
  case 0x0A: return 0x8900;
  case 0x0B: return 0x8290;
  case 0x0C: return 0xF16;
  case 0x0D: return 0x8700;
  case 0x0E: return 0x8280;
  case 0x0F: return 0x8380;
  case 0x10: return 0xA20; // TS-AN20
  case 0x30: return 0x9490;
  case 0x38: return 0xC0DE;
  case 0x3A: return 0x1EC2011;
  case 0x3B: return 0xDDC3;
  case 0x3C: return 0x1111;
  case 0x3D: return 0x3044;
  case 0x3E: return 0x1EC2010;
  case 0x00: case 0x3F: return 0x8200;
  default:
    return value & 0x3F;
  }
}

typedef struct {
  unsigned baseboardid;
} tsctlpage;

int BaseBoardIdGet() {
  tsctlpage *page = SharedMemoryGet(0x75015001,4096,0);
  int ret;

  if (!page || !page->baseboardid) {
    ret = _BaseBoardIdGet();
    if (page) page->baseboardid = ret;
  } else ret=page->baseboardid;
  return ret;
}

int BaseBoardMuxBusSupport() {
  int bb = BaseBoardIdGet();
  if ((bb & 0xFF00) == 0x8100) return 1;
  if (bb == 0x8900) return 1;
  if (bb == 0x8820) return 1;
  return 0;
}
