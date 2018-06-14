
all: sify_events 

sify_events: sify_events.o 
	$(CC) $(LDFLAGS) $(LDFLAGS)$^ -o $@ -lm
sify_events.o: sify_events.c	

clean:
	rm -f sify_events.o 

