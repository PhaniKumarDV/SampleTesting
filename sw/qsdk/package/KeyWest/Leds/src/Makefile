all: leds

LIBS += -luci -pthread

leds: Leds.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $<

clean:
	rm -f leds
