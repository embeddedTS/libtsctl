-include Makefile.config
CC=$(TOOL_PREFIX)-gcc

LDFLAGS=-Wl,--rpath,/slib -Wl,-dynamic-linker,/slib/ld-uClibc.so.0 -Wl,-gc-sections -static -D$(BOARDSEL)=1
CFLAGS+=-fms-extensions -march=armv4 -ffunction-sections -fdata-sections -D$(BOARDSEL)=1

CFLAGS_tsctl_wrap=-I/usr/include/python2.5
LDFLAGS_CAN2=-lpthread
LDFLAGS_CANRx=-lpthread
CFLAGS_CANRx=-DTHREAD_USE_POSIX
LDFLAGS_canctl=-lpthread
#CFLAGS_tsctl=-DLOGGING
LDFLAGS_tsctl=-lpthread 
#-lefence
LDFLAGS_ptest=-lpthread

ifeq ($(DEBUG),)
CFLAGS+=-Os
else
CFLAGS+=-g
endif

BUILD_DIR:=$(BOARDSEL)

PRODUCTS = CAN2 CANTx CANDiag CANRx diotoggle spi8200 ts8160ctl DIOTest canctl tsctl spictl _tsctl.so

all: $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(PRODUCTS))

$(BUILD_DIR)/%: %.c
	@echo "Compiling $<"; $(CC) $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<)))) $< -o $@ $(LDFLAGS) $(LDFLAGS_$(lastword $(subst /, ,$(patsubst %.c,%,$<))))

%.o: %.c
	@echo "Compiling $<"; $(CC) -c $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.o,%,$@)))) $< -o  $@

$(BUILD_DIR)/tsctl_wrap.o: tsctl_wrap.c
	@echo "Compiling $<"; $(CC) -c $(CFLAGS) $(CFLAGS_tsctl_wrap) $< -o  $@

tsctl_wrap.c: tsctl.i
	swig -python tsctl.i

$(BUILD_DIR)/_tsctl.so: $(BUILD_DIR)/tsctl_wrap.o
	@echo "Compiling $<"; $(CC) -shared $(CFLAGS) $(CFLAGS_$(lastword $(subst /, ,$(patsubst %.o,%,$@)))) libtsctl.c $< -o  $@ $(LDFLAGS) $(LDFLAGS_$@)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(PRODUCTS) tsctl_wrap.* *~ *.py

.PHONY: clean copy release

$(BUILD_DIR):
	@mkdir -p $@


# These additional rules are for Technologic Systems internal use
# and will probably not be of much use to anyone else.

R=tsctl canctl spictl
FTP=/u/home/ftp/apps/tsctl
PKG=libtsctl-src
LATEST=$(PKG)-LATEST
BIN=/u/x/home/michael/tsctl/product_
BIN1=$(BIN)cavium
BIN2=$(BIN)noncavium

copy: .target
	@TARG=`cat .target`; for I in $(PRODUCTS); do if [ -e $$I ]; then cp $$I $(BIN)$$TARG/$$I; fi; done

strip:
	@for I in $R; do $(TOOL_PREFIX)strip $(BIN)cavium/$$I; done
	@for I in $R; do $(TOOL_PREFIX)strip $(BIN)noncavium/$$I; done

release:
	@for I in $R; do $(TOOL_PREFIX)strip $(BIN)cavium/$$I; done
	@for I in $R; do $(TOOL_PREFIX)strip $(BIN)noncavium/$$I; done
	@NOW=`date +%Y%m%d%H%M` && \
	for I in $R; do sudo cp $(BIN1)/$$I $(FTP)/$$I/$$I-cavium-$$NOW; done && \
	for I in $R; do sudo ln -sf $$I/$$I-cavium-$$NOW $(FTP)/$$I-cavium; done && \
	for I in $R; do sudo cp $(BIN2)/$$I $(FTP)/$$I/$$I-noncavium-$$NOW; done && \
	for I in $R; do sudo ln -sf $$I/$$I-noncavium-$$NOW $(FTP)/$$I-noncavium; done && \
	make clean && \
	cd .. && tar -chzf $(PKG)-$$NOW.tar.gz $(PKG)/ && \
	sudo cp $(PKG)-$$NOW.tar.gz $(FTP)/$(PKG)/ && \
	sudo ln -sf $(PKG)/$(PKG)-$$NOW.tar.gz $(FTP)/$(LATEST).tar.gz
