# Name: Xiaoyan Xu
# Student  Number: 11229743
# NSID: xix799

CC=gcc
CFLAGS=-g
CPPFLAGS= -std=gnu90 -Wall -pedantic

build: servertcp clienttcp proxytcp
servertcp: servertcp.o
	$(CC) -o servertcp servertcp.o
servertcp.o: servertcp.c
	$(CC) -o servertcp.o -c $(CFLAGS) $(CPPFLAGS) servertcp.c
clienttcp: clienttcp.o
	$(CC) -o clienttcp clienttcp.o
clienttcp.o: clienttcp.c
	$(CC) -o clienttcp.o -c $(CFLAGS) $(CPPFLAGS) clienttcp.c
proxytcp: proxytcp.o
	$(CC) -o proxytcp proxytcp.o
proxytcp.o: proxytcp.c
	$(CC) -o proxytcp.o -c $(CFLAGS) $(CPPFLAGS) proxytcp.c

.PHONY: clean
clean: 
	rm -f servertcp.o clienttcp.o proxytcp.o servertcp clienttcp proxytcp
