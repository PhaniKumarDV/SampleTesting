all: socketevent

LIBS += -luci

socketevent: socketevent.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

clean:
	rm -f socketevent
