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
