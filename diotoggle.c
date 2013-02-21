#include <stdlib.h>
#include <stdio.h>
#include "libtsctl.c"

int main(int argc,char *argv[]) {
  DIO *dio;
  System *sys;
  int n,state;

  if (argc < 2) {
    printf("usage: %s <dio#>\n",argv[0]);
    return 1;
  }
  sys = SystemInit(0);
  dio = DIOInit(0);
  if (!dio) {
    printf("Error instantiating DIO 0\n");
    return 1;
  }
  n = atoi(argv[1]);
  if (n == 0 && argv[1][0] != '0') {
    n = sys->MapLookup(sys,ASCIIZ(argv[1]));
  }

  dio->Lock(dio,n,0);
  state = DIOValue(dio->GetAsync(dio,n));
  // DIOValue() converts INPUT_LOW to LOW and INPUT_HIGH to HIGH
  // for convenience, LOW=0 and HIGH=1
  printf("DIO %d was %s\n",n,state?"HIGH":"LOW");
  // Now toggle the DIO
  dio->SetAsync(dio,n,state?LOW:HIGH);
  // Now read back the new value
  state = DIOValue(dio->GetAsync(dio,n));
  dio->Unlock(dio,n,0);
  printf("DIO %d is now %s\n",n,state?"HIGH":"LOW");
  return 0;
}
