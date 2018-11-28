
all: kwn_ipaddr

kwn_ipaddr: kwn_ipaddr.o
	$(CC) $(LDFLAGS) $(LDFLAGS)$^ -o $@ -lm
kwn_ipaddr.o: kwn_ipaddr.c

clean:
	rm -f kwn_ipaddr.o

