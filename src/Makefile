TARGET = ../bin/latino
CFLAGS = -g -Wall -std=c11 -ansi -pedantic
MATH = -lm
LIBS = -I/usr/include
CC = gcc

ifeq (Windows_NT,$(OS))
TARGET:=$(TARGET).exe
endif

TESTS=$(wildcard ejemplos/*.lat)

all : $(TARGET)

.PHONY : all

test : all
	$(TARGET) $(TESTS)

.PHONY : test

lbuffer.o : lbuffer.c
	$(CC) -g -c lbuffer.c -o lbuffer.o

llex.o : llex.c
	$(CC) -g -c llex.c -o llex.o

lmemory.o : lmemory.c
	$(CC) -g -c lmemory.c -o lmemory.o

latino.o : latino.c
	$(CC) -g -c latino.c -o latino.o

$(TARGET) : lbuffer.o llex.o lmemory.o latino.o
	mkdir -p "$$(dirname $(TARGET))"
	$(CC) $(CFLAGS) lbuffer.o llex.o lmemory.o latino.o -o $(TARGET) $(MATH) $(LIBS)

clean :
	rm -f *.o
.PHONY : clean
