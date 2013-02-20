#include "libtsctl.h"
#include <iostream>
using namespace std;

int main(int argc,char *argv[]) {
  System *sys;
  int i,j,m,n;
  char* name;

  sys = SystemInit(0);
  if (!sys) {
    cerr << "Error initializing System\n";
    return 1;
  }
  j = sys->MapLength(sys);
  for (i=0;i<j;i++) {
    name=sys->MapGet(sys,i,&n);
    cout << name << "=" << n << "\n";
    m=sys->MapLookup(sys,name);
    if (m!=n) {
      cerr << name << "=" << n << "/" << m << " error\n";
    }
  }
}
