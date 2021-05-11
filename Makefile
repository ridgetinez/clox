CC=gcc
FLAGS=-Wall -Werror
DEPS = chunk.h memory.h common.h debug.h value.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

clox: main.o chunk.o debug.o value.o memory.o
	$(CC) -o $@ $^ $(FLAGS)

clean: 
	rm -rf *.o clox
.PHONY: clean