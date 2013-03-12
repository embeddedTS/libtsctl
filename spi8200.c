#include "libtsctl.h"
#include <stdlib.h>
#include <stdio.h>
#include "Array.h"

int main(int argc,char *argv[]) {
  SPI *spi;
  ArrayAuto(char,buf1,ARR(0x04,0x00));
  ArrayAuto(char,wbuf,ARR(0x08, 0x00, 0x14, 0x00, 0x18, 0x00, 0x24, 0x00, 0x28,
			  0x00, 0x34, 0x00, 0x38, 0x00));
  ArrayAutoOfSize(char,rbuf,14);
  float full[] = { 7.5, 5.0, 3.125, 3.125, 5, 2.5, 5.0 };
  float expect[] = { 5.0, 3.3, 1.0, 1.5, 3.3, 1.8, 3.3 };
  int use[] = { 1,1,1,1,1,1,1 };
  float error,actual;
  int vals[] = { 0x0a6e, 0x0a76, 0x0d35, 0x0629, 0x0a78, 0x0baa, 0x0a70, 0 };
  //char rbuf[14];
  unsigned short *got = (short *)rbuf;
  int i,bb,model,passed=1;
  System *sys = SystemInit(0);

  bb = sys->BaseBoardId(sys);
  if (bb != 0x8200) {
    printf("This program requires a TS-8200 base board.\n");
    printf("Base board detected was %04X\n",bb);
    return 1;
  }

  model = sys->ModelId(sys);
  switch (model) {
  case 0x4500:
    expect[2] = 2.5;
    use[3] = use[4] = 0;
    break;
  case 0x4700:
    use[2] = use[3] = 0;
    break;
  case 0x4800:
    use[2] = 0;
    expect[3] = 2.775;
    expect[4] = 1.8;
    break;
  }

  spi = SPIInit(0);
  i=spi->Lock(spi,0,0);
  if (i <= 0) { printf("Error %d on Lock\n",i); return 1; }
  i=spi->ClockSet(spi,2000000);
  if (i <= 0) { printf("Error %d on ClockSet\n",i); return 1; }
  i=spi->EdgeSet(spi,-2); // was 1
  if (i <= 0) { printf("Error %d on EdgeSet\n",i); return 1; }
  i=spi->Write(spi,3,buf1);
  if (i <= 0) { printf("Error %d on Write\n",i); return 1; }
  i=spi->ReadWrite(spi,3,wbuf,rbuf);
  if (i <= 0) { printf("Error %d on ReadWrite\n",i); return 1; }
  i=spi->Unlock(spi,0,0);
  if (i <= 0) { printf("Error %d on Unlock\n",i); }
  //for (i=0;i<14;i++) printf("%02X ",rbuf[i]);
  printf("actual/expected\n");
  for (i=0;i<7;i++) {
    if (!use[i]) continue;
    actual = full[i]*ntohs(got[i])/4096.0;
    //error = 100.0*(expect[i]-actual)/actual;
    error = 100.0 * actual / expect[i];
    if (model == 0x4200 && i == 5) {
      if (error < 90 || error > 130) passed = 0;
    } else {
      if (error < 90 || error > 110) passed = 0;
    }
    printf("%d. %1.3f / %1.3fV (%1.1f%%)\n",i,
	   actual, expect[i],error);
	   //error>0.0?error:-error,
	   //error>=0.0?"low":"high");
  }
  return (passed == 1) ? 0 : 1;
}
