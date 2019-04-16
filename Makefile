CC = gcc
CFLAGS = -Wall -Wfatal-errors -ansi
LDFLAGS = -lMLV
OBJ = main.o plateau.o bit.o ascii.o graphique.o


projet: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	make clean


main.o: main.c plateau.h bit.h ascii.h graphique.h

plateau.o: plateau.c plateau.h

bit.o: bit.c bit.h plateau.h

ascii.o: ascii.c ascii.h plateau.h bit.h

graphique.o: graphique.c graphique.h plateau.h bit.h ascii.h


%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.gch