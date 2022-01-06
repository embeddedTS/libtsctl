#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>

static int fd = -1;
static int UseCount = 0;

void *MemMap(off_t addr,int pages) {
  off_t page;
  unsigned char *start;

  if (fd == -1)
    fd = open("/dev/mem", O_RDWR|O_SYNC);
  if (fd == -1) {
    //perror("open(/dev/mem):");
    return 0;
  }
  page = addr & 0xfffff000;
  if (page & 0xfff) pages++;
  while ((unsigned)(page + pages * getpagesize() - 1) < (unsigned)page) {
    pages--;
  }
  start = mmap(0, pages * getpagesize(), PROT_READ|PROT_WRITE, MAP_SHARED, fd, page);
  if (start == MAP_FAILED) {
    //perror("mmap:");
    return 0;
  }
  UseCount++;
  start = start + (addr & 0xfff);
  return start;
}

void MemUnmap(volatile void *ptr) {
  munmap((void *)ptr,getpagesize());
  UseCount--;
  if (UseCount == 0) {
    close(fd);
    fd = -1;
  }
}
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
