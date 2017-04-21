#Makefile for client.c, client_functions.c, server.c, server_functions.c

CC = gcc -g

all: client server

client:		client.c client_functions.c
	$(CC) -c client_functions.c
	$(CC) -c client.c
	$(CC) -o client client_functions.o client.o
server:		server_functions.c server.c
	$(CC) -c server.c
	$(CC) -c server_functions.c
	$(CC) -o server server.functions.o server.o

clean:
	rm client server
