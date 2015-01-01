#Makefile k sestaveni proramu graph.exe pro unixove systemy
CC=gcc #kompilator
CFLAGS=-c -Wall #volby kompilatoru
LDFLAGS=-lm -o#volby linkeru, linkovani knihovny math a nastaveni jmena vystupu
OUT=graph.exe #vystup
RMV=del #prikaz na smazani
OBJ=main.o zapisovac.o charToken.o zasobnik.o shuntyard.o compute.o #soubory k linkovani

#pravidla
all: program clean

program: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(OUT)

main.o: main.c charToken.h shuntyard.h compute.h zapisovac.h
	$(CC) $(CFLAGS) main.c

zapisovac.o: zapisovac.c
	$(CC) $(CFLAGS) zapisovac.c

charToken.o: charToken.c
	$(CC) $(CFLAGS) charToken.c
	
zasobnik.o: zasobnik.c
	$(CC) $(CFLAGS) zasobnik.c
	
shuntyard.o: shuntyard.c
	$(CC) $(CFLAGS) shuntyard.c
	
compute.o: compute.c
	$(CC) $(CFLAGS) compute.c
	
clean:
	$(RMV) *.o