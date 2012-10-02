#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
void *MemMap(off_t addr,int pages);
void MemUnmap(volatile void *ptr);

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
