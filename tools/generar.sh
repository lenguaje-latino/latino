#!/bin/bash
#para generar el analizador lexico:
bison -d -olexico.c lexico.y
#genera: lexico.h lexico.c

#para generar el analizador sintactico:
flex -osintaxis.c sintaxis.l
#genera: sintaxis.c

#mover archivos
mv *.h ../include/
mv *.c ../src/

#compilar
cd ..
make
echo "terminado."
cd tools/
#generar el executable
#gcc sintaxis.c -o sintaxis

