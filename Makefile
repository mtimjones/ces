CC=gcc
CFLAGS = -I.

DEPS = cestypes.h
OBJS = main.o entities.o systems.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ces: $(OBJS)
	gcc -g -o $@ $^ $(CFLAGS) -lncurses

clean:
	rm -f ces *.o
