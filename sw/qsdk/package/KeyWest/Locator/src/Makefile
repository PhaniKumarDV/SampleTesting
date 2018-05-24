PREFIX?=/usr
CC?=gcc
CFLAGS=
EXTRA_CFLAGS=
INCLUDES=
LIBS=
FILES_LOCATOR= \
	locator.o \
	sys_tools.o \
	cfg_lib.o

FILES_DISCOVER= \
	discover.o \
	sys_tools.o \
	cfg_lib.o

all: locator discover

locator: $(FILES_LOCATOR)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(FILES_LOCATOR) $(LIBS) -o $@
	@echo "make $@ finished on `date`"

discover: $(FILES_DISCOVER)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(FILES_DISCOVER) $(LIBS) -o $@
	@echo "make $@ finished on `date`"
	
%.o:	%.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $(INCLUDES) -D_GNU_SOURCE -c $<

clean: clean_locator clean_discover

clean_locator:
	rm -f *.o locator

clean_discover:
	rm -f *.o discover

install: locator discover
	install locator $(PREFIX)/sbin
	install default.script $(PREFIX)/share/locator
	install discover $(PREFIX)/sbin
	install default.script $(PREFIX)/share/discover
