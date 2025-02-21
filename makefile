CFLAGS=-std=c17 -pedantic -Wall

Prog: Main.o
	gcc -o dm dm.o

Main.o:
	gcc $(CFLAGS) -c -o dm.o dm.c

clean:
	rm -f *.o