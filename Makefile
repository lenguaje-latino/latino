#define el compilador C
CC=gcc

VPATH=src:../include

#define flags para el compilador
CFLAGS=-Wall -g

#define los directorios para las headers
INCLUDES = -Iinclude
SOURCE=$(exec_prefix)src/
BIN=$(exec_prefix)bin/

#define los archivos C
SRCS=$(SOURCE)lexico.c $(SOURCE)sintaxis.c

#define los objetos de los fuentes
OBJS=$(SRCS:.c=.o)

#define el archivo ejecutable
TARGET=sintaxis

#genera el comando de compilado
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(BIN)$(TARGET) $(INCLUDES) $(SRCS)

#limpia el directorio
clean:
		rm -f *.o
