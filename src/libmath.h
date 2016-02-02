#ifndef _LIBMATH_H_
#define _LIBMATH_H_

#include <math.h>
#include "vm.h"

void lat_acos(lat_vm* vm);
void lat_asin(lat_vm* vm);
void lat_atan(lat_vm* vm);
void lat_atan2(lat_vm* vm);
void lat_cos(lat_vm* vm);
void lat_cosh(lat_vm* vm);
void lat_sin(lat_vm* vm);
void lat_sinh(lat_vm* vm);
void lat_tan(lat_vm* vm);
void lat_tanh(lat_vm* vm);
void lat_exp(lat_vm* vm);
//void lat_frexp(lat_vm *vm);
//void lat_ldexp(lat_vm* vm);
void lat_log(lat_vm* vm);
void lat_log10(lat_vm* vm);
//void lat_modf(lat_vm *vm);
void lat_pow(lat_vm* vm);
void lat_sqrt(lat_vm* vm);
void lat_ceil(lat_vm* vm);
void lat_fabs(lat_vm* vm);
void lat_floor(lat_vm* vm);
void lat_fmod(lat_vm* vm);

#endif /* ifndef _LIBMATH_H_ */
