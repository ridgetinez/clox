CC=gcc
FLAGS=-Wall -Werror
DEPS = chunk.h memory.h common.h debug.h value.h vm.h scanner.h compiler.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

clox: main.o chunk.o debug.o value.o memory.o vm.o scanner.o compiler.o
	$(CC) -o $@ $^ $(FLAGS)

clean: 
	rm -rf *.o clox
.PHONY: clean