# Makefile for C-version of StupidZip
#CC=g++
CC=gcc
CFLAGS=-c -Wall -O2

all: szmake

szmake: sz.o
	$(CC) sz.o -o sz
	rm sz.o

sz.o: sz.c
	$(CC) $(CFLAGS) sz.c

.PHONY: clean

clean:
	rm -f *.o sz
