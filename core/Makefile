TARGET = bin/latino
CFLAGS = -g -Wall -std=c11
MATH = -lm
LIBS = -I/usr/include
CC = gcc

all : $(TARGET)
.PHONY : all

latino.o :
	$(CC) $(CFLAGS) -c latino.c -o latino.o

lio.o :
	$(CC) $(CFLAGS) -c lio.c -o lio.o

llex.o :
	$(CC) $(CFLAGS) -c llex.c -o llex.o

lmem.o :
	$(CC) $(CFLAGS) -c lmem.c -o lmem.o

lparser.o :
	$(CC) $(CFLAGS) -c lparser.c -o lparser.o

main.o :
	$(CC) $(CFLAGS) -c main.c -o main.o

$(TARGET) : latino.o lio.o llex.o lparser.o lmem.o main.o
	mkdir -p "$$(dirname $(TARGET))"
	$(CC) $(CFLAGS) latino.o lio.o llex.o lparser.o lmem.o main.o -o $(TARGET) $(MATH) $(LIBS)

clean :
	rm -f *.o
.PHONY : clean
