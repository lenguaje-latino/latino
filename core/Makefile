TARGET = latino
CFLAGS = -g -Wall -std=c11
MATH = -lm
LIBS = -I/usr/include
CC = gcc

all : $(TARGET)
.PHONY : all

latino.o : latino.c
	$(CC) $(CFLAGS) -c latino.c -o latino.o

lio.o : lio.c
	$(CC) $(CFLAGS) -c lio.c -o lio.o

llex.o : llex.c
	$(CC) $(CFLAGS) -c llex.c -o llex.o

lmem.o : lmem.c
	$(CC) $(CFLAGS) -c lmem.c -o lmem.o

lparser.o : lparser.c
	$(CC) $(CFLAGS) -c lparser.c -o lparser.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

$(TARGET) : latino.o lio.o llex.o lparser.o lmem.o main.o
	mkdir -p "$$(dirname $(TARGET))"
	$(CC) $(CFLAGS) latino.o lio.o llex.o lparser.o lmem.o main.o -o $(TARGET) $(MATH) $(LIBS)

clean :
	rm -f *.o
.PHONY : clean
