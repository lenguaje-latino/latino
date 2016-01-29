#ifndef _LIBIO_H_
#define _LIBIO_H_

#include <stdio.h>
#include "vm.h"

void lat_read(lat_vm *vm);
void lat_write(lat_vm *vm);
void lat_readfile(lat_vm *vm);
void lat_writefile(lat_vm *vm);

#endif /* ifndef _LIBIO_H_ */
