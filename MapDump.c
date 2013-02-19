//#include "libtsctl.h"
#include "libtsctl0.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]) {
  System *sys;
  int i,j,m,n;
  char* name;

  sys = SystemInit(0);
  if (!sys) {
    printf("Error initializing System\n");
    return 1;
  }
  j = sys->MapLength(sys);
  for (i=0;i<j;i++) {
    name=sys->MapGet(sys,i,&n);
    printf("%s=%d\n",name,n);
    m=sys->MapLookup(sys,name);
    if (m!=n) {
      printf("%s=%d/%d error\n",n,m);
    }
  }
}
