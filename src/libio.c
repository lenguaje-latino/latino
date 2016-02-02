#include <stdio.h>
#include <string.h>
#include "libio.h"
#include "vm.h"

void lat_read(lat_vm *vm){
  char str[254];
  fgets(str, 254, stdin);
  int i = strlen(str) - 1;
  if (str[i] == '\n')
    str[i] = '\0';
  vm->regs[255] = lat_str(vm, parse_string(str, strlen(str)));
}
void lat_write(lat_vm *vm){

}
void lat_readfile(lat_vm *vm){

}
void lat_writefile(lat_vm *vm){

}
