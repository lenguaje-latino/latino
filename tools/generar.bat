@echo off
REM para generar el analizador lexico:
bison -d -olexico.c lexico.y
REM genera: lexico.h lexico.c

REM para generar el analizador sintactico:
flex -osintaxis.c sintaxis.l
REM genera: sintaxis.c

REM mover archivos
move *.h ..\include\
move *.c ..\src\

REM compilar
cd..
mingw32-make
cd tools\
echo "terminado."
REM generar el executable
REM gcc sintaxis.c -o sintaxis
