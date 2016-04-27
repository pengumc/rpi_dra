all:dra.o

dra.o: src/dra.c
	gcc -c -o $@ -Wall -Iinclude $<