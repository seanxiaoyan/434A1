# Name: Xiaoyan Xu
# Student  Number: 11229743
# NSID: xix799

CC=gcc
CFLAGS=-g
CPPFLAGS= -std=gnu90 -Wall -pedantic

build: server client
server: server.o
	$(CC) -o server server.o
server.o: server.c
	$(CC) -o server.o -c $(CFLAGS) $(CPPFLAGS) server.c
client: client.o
	$(CC) -o client client.o
client.o: client.c
	$(CC) -o client.o -c $(CFLAGS) $(CPPFLAGS) client.c

.PHONY: clean
clean: 
	rm -f server.o client.o server client
