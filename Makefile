CC=gcc
LD=$(CC)
CFLAGS =-Wall -pedantic -fsanitize=address -fsanitize=undefined

all: main

main: main.o
	$(LD) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
 
clean:
	rm -f *.o main
