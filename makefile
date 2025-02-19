CFLAGS=-std=c17 -pedantic -Wall

Prog: arbre.o cellule.o file.o Main.o
	gcc -o main Main.o arbre.o cellule.o file.o

Main.o:
	gcc $(CFLAGS) -c -o Main.o Main.c

arbre.o:
	gcc $(CFLAGS) -c -o arbre.o arbre.c

cellule.o:
	gcc $(CFLAGS) -c -o cellule.o cellule.c

file.o:
	gcc $(CFLAGS) -c -o file.o file.c

clean:
	rm -f *.o