all: gps

LIBS += -luci

gps: gpsinfo.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

clean:
	rm -f gps
