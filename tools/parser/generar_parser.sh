#!/bin/bash

# genera analizador lexico
flex latlex.l

# genera analizador sintactico
bison -y latparse.y

# copia archivo *.c y *.h a src
cp *.c ../../src
cp *.h ../../src

# borra archivos *.c y *.h generados
rm *.c
rm *.h