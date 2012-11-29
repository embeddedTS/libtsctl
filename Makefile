-include Makefile.config
CC=$(TOOL_PREFIX)gcc

CFLAGS+=-march=armv4 -ffunction-sections -fdata-sections -D$(BOARDSEL)=1
LDFLAGS+=-D$(BOARDSEL)=1

CFLAGS_tsctl_wrap=-I/usr/include/python2.5
LDFLAGS_CAN2=-lpthread
LDFLAGS_CANRx=-lpthread
CFLAGS_CANRx=-DTHREAD_USE_POSIX
LDFLAGS_canctl=-lpthread
#CFLAGS_tsctl=-DLOGGING
LDFLAGS_tsctl=-lpthread -lreadline
#-lefence
LDFLAGS_ptest=-lpthread

ifeq ($(DEBUG),)
CFLAGS+=-Os
else
CFLAGS+=-g
endif

BUILD_DIR:=$(BOARDSEL)

PRODUCTS ?= CAN2 CANTx CANDiag CANRx diotoggle spi8200 ts8160ctl DIOTest canctl tsctl spictl 

all: $(PRODUCTS)

%: %.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<"; $(CC) $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<)))) $< $(LDFLAGS) $(LDFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<)))) -o $(BUILD_DIR)/$@ 

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(PRODUCTS) tsctl_wrap.* *~ *.py

.PHONY: clean copy release



