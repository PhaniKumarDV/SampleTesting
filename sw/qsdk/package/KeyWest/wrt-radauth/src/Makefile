
all: wrt-radauth

wrt-radauth: wrt-radauth.o md5.o wireless.o radius.o
	$(CC) $(LDFLAGS) $(LDFLAGS)$^ -o $@


wrt-radauth.o: wrt-radauth.c radius.h wireless.h wrt-radauth.h

radius-client.o: radius-client.c radius.h

md5.o: md5.c md5.h

radius.o: radius.c radius.h common.h

wireless.o: wireless.c wireless.h common.h wrt-radauth.h

clean:
	rm -f wrt-radauth md5.o wrt-radauth.o wireless.o radius.o radius-client.o radius-client

dist:
	cd ..; rm -f wrt-radauth-0.1.tar.gz; tar -c -v --exclude=wrt-radauth/CVS -z -f wrt-radauth-0.1.tar.gz wrt-radauth/

.PHONY: all clean dist
