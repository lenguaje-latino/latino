/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include "libio.h"
#include "vm.h"

void lat_leer(lat_vm *vm){
  char str[254];
  fgets(str, 254, stdin);
  int i = strlen(str) - 1;
  if (str[i] == '\n')
    str[i] = '\0';

  //obtiene decimal
  char *ptr;
  double ret;
  ret =strtod(str, &ptr);
  if(strcmp(ptr, "") == 0){
    vm->regs[255] = lat_decimal_nuevo(vm, ret);
  }else{
    vm->regs[255] = lat_cadena_nueva(vm, parse_string(str, strlen(str)));
  }
}
void lat_leer_archivo(lat_vm *vm){
  lat_objeto* o = lat_desapilar(vm);

  if(o->type == T_STR || o->type == T_LIT){
    FILE *fp;
    char *buf;
    fp = fopen(lat_obtener_cadena(o), "r");
    if (fp == NULL) {
      lat_registrar_error("No se pudo abrir el archivo\n");
    }
    fseek(fp, 0, SEEK_END);
    int fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = calloc(fsize, 1);
    size_t newSize = fread(buf, sizeof(char), fsize, fp);
    if (buf == NULL) {
      printf("No se pudo asignar %d bytes de memoria\n", fsize);
    }
    buf[newSize] = '\0';
    vm->regs[255] = lat_cadena_nueva(vm, buf);
  }else{
    lat_registrar_error("No se pudo abrir el archivo\n");
  }
}

void lat_escribir_archivo(lat_vm *vm){
  lat_objeto* s = lat_desapilar(vm);
  lat_objeto* o = lat_desapilar(vm);
  if(o->type == T_STR || o->type == T_LIT){
    FILE* fp;
    fp = fopen(lat_obtener_cadena(o), "w");
    const char* cad = lat_obtener_cadena(s);
    size_t lon = strlen(cad);
    fwrite(cad, 1 , lon , fp);
    fclose(fp);
  }else{
    lat_registrar_error("No se pudo escribir en el archivo\n");
  }
}
