#include <stdio.h>
#include <bzlib.h>
#include "Array.h"

int main(int argc,char *argv[]) {
  int doCompress = 1;

  if (argc < 2) {
    printf("Nothing to do!\n");
    return 1;
  }
  if (argc == 3) {
    doCompress = 0;
  }
  FILE *f = fopen(argv[1],"r");
  if (!f) {
    perror(argv[1]);
    return 1;
  }
  char* infile = ArrayAlloc(0,1);
  int ch;
  while (!feof(f)) {
    ch = fgetc(f);
    if (ch == EOF) break;
    ArraySize(infile,ArrayLength(infile)+1);
    infile[ArrayLength(infile)-1] = ch;
  }
  fclose(f);
  //printf("Read %d bytes\n",ArrayLength(infile));
  unsigned char* outfile = ArrayAlloc(ArrayLength(infile)*101/100+600,1);
  int len = ArrayLength(outfile);
  if (doCompress) {
    int ret = BZ2_bzBuffToBuffCompress(outfile,&len,
				       infile,ArrayLength(infile),9,0,30);
    if (ret != BZ_OK) {
      fprintf(stderr,"Error ");
      switch (ret) {
      case BZ_CONFIG_ERROR: fprintf(stderr,"BZ_CONFIG_ERROR\n"); break;
      case BZ_PARAM_ERROR: fprintf(stderr,"BZ_PARAM_ERROR\n"); break;
      case BZ_MEM_ERROR: fprintf(stderr,"BZ_MEM_ERROR\n"); break;
      case BZ_OUTBUFF_FULL: fprintf(stderr,"BZ_OUTBUFF_FULL\n"); break;
      default: fprintf(stderr,"UNKNOWN\n"); break;
      }
    }
  } else {
    memcpy(outfile,infile,len=ArrayLength(infile));
  }
  //printf("Out %d bytes\n",len);
  fprintf(stderr,"%s: %d/%d=%.3f\n",argv[1],ArrayLength(infile),len,(float)ArrayLength(infile)/len);

  printf("int Y");
  int i;
  for (i=0;argv[1][i];i++) {
    if (argv[1][i] == '.') {
      printf("_");
    } else {
      printf("%c",argv[1][i]);
    }
  }
  printf("_len=%d;\n",ArrayLength(infile));

  printf("int X");
  for (i=0;argv[1][i];i++) {
    if (argv[1][i] == '.') {
      printf("_");
    } else {
      printf("%c",argv[1][i]);
    }
  }
  printf("_len=%d;\n",len);

  printf("char X");
  for (i=0;argv[1][i];i++) {
    if (argv[1][i] == '.') {
      printf("_");
    } else {
      printf("%c",argv[1][i]);
    }
  }
  printf("[%d] = {",len);
  for (i=0;i<len;i++) {
    if (i % 8 == 0) printf("\n\t");
    printf("0x%02X",outfile[i]);
    if (i+1 < len) printf(",");
  }
  printf("\n};\n");
}
// gcc -o compress -I ../ts -lbz2 compress.c
// http://www.bzip.org/1.0.5/bzip2-manual-1.0.5.html#bzbufftobuffcompress
