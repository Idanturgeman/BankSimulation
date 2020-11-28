all: main

main: main.o myBank.o
		gcc main.o myBank.o -o main

main.o: main.c myBank.h
		gcc -Wall -c main.c

myBank.o: myBank.c
		gcc -Wall -c myBank.c

.PHONY: all clean

clean:
		rm -f *.o main
