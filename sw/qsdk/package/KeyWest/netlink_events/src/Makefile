all: netlinkevents

LIBS += -luci

netlinkupdate: netlinkevents.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

clean:
	rm -f netlinkevents
