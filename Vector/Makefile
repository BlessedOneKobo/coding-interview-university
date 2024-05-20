CFLAGS=-Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -g -fsanitize=address -fno-omit-frame-pointer

all: main

main: main.c Vector.o

Vector.o: Vector.c Vector.h

clean:
	rm Vector.o main
