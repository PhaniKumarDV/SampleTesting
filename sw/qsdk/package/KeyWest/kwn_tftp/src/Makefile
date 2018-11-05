
all: kwn_tftp

kwn_tftp: kwn_tftp.o
	$(CC) $(LDFLAGS) $(LDFLAGS)$^ -o $@ -lm
kwn_tftp.o: kwn_tftp.c

clean:
	rm -f kwn_tftp.o

