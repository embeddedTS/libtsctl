CC=/home/michael/Development/ts/tools/arm-uclibc-3.4.6/bin/arm-linux-gcc
LDFLAGS=-Wl,--rpath,/slib -Wl,-dynamic-linker,/slib/ld-uClibc.so.0 -Os -static
LDFLAGS+=-L/home/michael/Development/ts/tools/arm-uclibc-3.4.6/lib
CFLAGS+=-g

CANTx: CANTx.c

CANRx: CANRx.c

#CAN2: CAN2.c -lpthread
CAN2: CAN2.c /home/michael/Development/ts/tools/arm-uclibc-3.4.6/lib/libpthread.a
