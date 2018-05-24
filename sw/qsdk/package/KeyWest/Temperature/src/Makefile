CFLAGS?=-O2
CFLAGS+=
SFLAGS:=--std=gnu99
WFLAGS:=-Wall -Werror
LDFLAGS?=
BINARY:=temp-log


LIBS += -luci

all: $(BINARY)

$(BINARY): *.c
	$(CC) -I. $(CFLAGS) $(SFLAGS) $(WFLAGS) $(LDFLAGS) $(LIBS) -o $@ $+

clean:
	rm -f $(BINARY)
