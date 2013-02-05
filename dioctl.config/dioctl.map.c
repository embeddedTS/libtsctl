#include <stdio.h>

/*
  autogenerate C array to map compressed values to dictionary or literal
  values.

  The following values map to sequential dictionary values:
  1-45, 58-63, 127-255
  All other values map directly to the corresponding ASCII value.

  The map is a 256 element integer array.  If the element value is -1,
  then it indicates that the literal character is to be used.  Otherwise,
  it is the index in the dictionary to be used.
 */

int main() {
  int i,n = 0;
  int diodict[256];

  printf("int diodict[256] = {\n");
  printf("\t-1,\n"); diodict[0] = -1;
  for (i=1;i<=45;i++) {
    diodict[i] = n; printf("\t%d,\n",n++);
  }
  for (;i<58;i++) {
    diodict[i] = -1; printf("\t-1,\n");
  }

  for (;i<=63;i++) {
    diodict[i] = n; printf("\t%d,\n",n++);
  }
  for (;i<127;i++) {
    diodict[i] = -1; printf("\t-1,\n");
  }
  for (i=127;i<=255;i++) {
    diodict[i] = n; printf("\t%d,\n",n++);
  }
  printf("};\n");

  printf("int dioeict[256] = {\n");
  for (i=1;i<=45;i++) {
    printf("\t%d,\n",i);
  }
  for (i=58;i<=63;i++) {
    printf("\t%d,\n",i);
  }
  for (i=127;i<=255;i++) {
    printf("\t%d,\n",i);
  }
  printf("};\n");

}
