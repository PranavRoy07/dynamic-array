CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

.PHONY: all build valgrind clean

all: build

build: main memory_demo

main: main.c dynamic_array.c dynamic_array.h
	$(CC) $(CFLAGS) main.c dynamic_array.c -o main

memory_demo: memory_demo.c
	$(CC) $(CFLAGS) memory_demo.c -o memory_demo

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

clean:
	rm -f main memory_demo