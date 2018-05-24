
ifndef CC
   CC = gcc
endif

ifndef BLUETOPIA_PATH
   BLUETOPIA_PATH = ../../../Bluetopia
endif

INCLDDIRS = -I../../include                        \
	    -I../../include/client                      \
	    -I$(BLUETOPIA_PATH)/include                 \
	    -I$(BLUETOPIA_PATH)/profiles/GATT/include

ifndef SYSTEMLIBS
   SYSTEMLIBS = -lpthread -lm
endif

CFLAGS = -Wall $(DEFS) $(INCLDDIRS) $(GLOBINCLDDIRS) -O2 -fno-strict-aliasing $(GLOBCFLAGS)

LDFLAGS = -L../../lib/client $(GLOBLDFLAGS)

LDLIBS = -lSS1BTPM $(SYSTEMLIBS) $(GLOBLDLIBS)

OBJS = LinuxFTPM_CLT.o

.PHONY:
all: LinuxFTPM_CLT

LinuxFTPM_CLT: $(OBJS)

.PHONY: clean veryclean realclean
clean veryclean realclean:
	-rm -f *.o
	-rm -f *~
	-rm -f LinuxFTPM_CLT

