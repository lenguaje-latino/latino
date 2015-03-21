YACC = bison -y
LEX = flex
TARGET = bin/latino
CFLAGS = -g -Wall
MATH = -lm
LIBS = -I/usr/include
CC = gcc

#ifeq (Windows_NT,$(OS))
#TARGET:=$(TARGET).exe
#endif

TESTS=$(wildcard ejemplos/*.lat)

all : $(TARGET)

.PHONY : all

test : all
	$(TARGET) $(TESTS)

.PHONY : test

src/parse.c : src/parse.y
	$(YACC) -osrc/parse.c src/parse.y

src/lex.c : src/lex.l
	$(LEX) -osrc/lex.c -i src/lex.l

src/parse.o : src/parse.c
	$(CC) -g -c src/parse.c -o src/parse.o

src/latino.o : src/latino.c src/latino.h src/structs.h
	$(CC) -g -c src/latino.c -o src/latino.o

src/eval.o : src/eval.c src/latino.h src/structs.h
	$(CC) -g -c src/eval.c -o src/eval.o

src/lex.o : src/lex.c
	$(CC) -g -c src/lex.c -o src/lex.o

$(TARGET) : src/parse.o src/latino.o src/lex.o src/eval.o
	mkdir -p "$$(dirname $(TARGET))"
	$(CC) $(CFLAGS) src/parse.o src/latino.o src/lex.o src/eval.o -o $(TARGET) $(MATH) $(LIBS)

clean :
	rm -f src/lex.c
	rm -f src/parse.h
	rm -f src/parse.c
	rm -f src/*.o
.PHONY : clean
