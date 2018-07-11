all: cfgupdate

LIBS += -luci

cfgupdate: cfgupdateinfo.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

clean:
	rm -f cfgupdate
