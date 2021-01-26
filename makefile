# Name: Xiaoyan Xu
# Student  Number: 11229743
# NSID: xix799

CC=gcc
CFLAGS=-g
CPPFLAGS= -std=gnu90 -Wall -pedantic

build: server client proxytcp
server: server.o
	$(CC) -o server server.o
server.o: server.c
	$(CC) -o server.o -c $(CFLAGS) $(CPPFLAGS) server.c
client: client.o
	$(CC) -o client client.o
client.o: client.c
	$(CC) -o client.o -c $(CFLAGS) $(CPPFLAGS) client.c
proxytcp: proxytcp.o
	$(CC) -o proxytcp proxytcp.o
proxytcp.o: proxytcp.c
	$(CC) -o proxytcp.o -c $(CFLAGS) $(CPPFLAGS) proxytcp.c

.PHONY: clean
clean: 
	rm -f server.o client.o proxytcp.o server client proxytcp
