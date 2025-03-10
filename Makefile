CC=gcc
LD=$(CC)
CFLAGS =-std=gnu99 -Wall -pedantic -fsanitize=address -fsanitize=undefined -g
SOURCE=src

all: main

main: $(SOURCE)/main.o display.o conversion.o game.o terminal.o deque.o gameData.o
	$(LD) $(CFLAGS) -o $@ $^

%.o: $(SOURCE)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<
 
run:
	@./main $(word 2, $(MAKECMDGOALS)) $(word 3, $(MAKECMDGOALS))
 
clean:
	rm -f src/*.o main
