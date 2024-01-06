output: main.o Gestion_Des_Processus.o
	gcc main.o Gestion_Des_Processus.o -o output

main.o: main.c
	gcc -c main.c

Gestion_Des_Processus.o: Gestion_Des_Processus.c Gestion_Des_Processus.h
	gcc -c Gestion_Des_Processus.c
