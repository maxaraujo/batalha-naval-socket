all:	servidor	cliente
servidor:	servidor.o	tabuleiro.o
	gcc	servidor.o	tabuleiro.o	-o	servidor

cliente:	cliente.o	tabuleiro.o
	gcc	cliente.o	tabuleiro.o	-o	cliente

servidor.o:	servidor.c
	gcc	-c	servidor.c

cliente.o:	cliente.c
	gcc	-c	cliente.c

tabuleiro.o:	tabuleiro.c	tabuleiro.h
	gcc	-c	tabuleiro.c

clean:
	rm *.o