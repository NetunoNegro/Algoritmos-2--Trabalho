# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Werror -Wextra -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = tpAlgII.o heap.o ordena.o

tpAlgII: tpAlgII.o heap.o ordena.o
	$(CC) -o tpAlgII tpAlgII.o heap.o ordena.o $(LDFLAGS)

fila.o: heap.c
	$(CC) -c $(CFLAGS) heap.c

tpAlgII.o: tpAlgII.c
	$(CC) -c $(CFLAGS) tpAlgII.c

clean:
	rm -f $(objects) tpAlgII
