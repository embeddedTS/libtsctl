#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
void *MemMap(off_t addr,int pages);
void MemUnmap(volatile void *ptr);

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
