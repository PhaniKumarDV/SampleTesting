CFLAGS?=-O2
CFLAGS+=
SFLAGS:=--std=gnu99
WFLAGS:=-Wall -Werror
LDFLAGS?=
BINARY:=Pkg2

all: $(BINARY)

$(BINARY): *.c
	$(CC) -I. $(CFLAGS) $(SFLAGS) $(WFLAGS) $(LDFLAGS) -o $@ $+

clean:
	rm -f $(BINARY)
