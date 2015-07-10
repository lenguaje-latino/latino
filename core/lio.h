#ifndef _LIO_H_
#define _LIO_H_

#include <stdio.h>
#include "latino.h"

#define EOS (-1)    /* end of stream */

#define buff_get_char(ls, pos) ((ls)->inputfile->buffer[pos])

typedef struct lbuffer {
    lstring buffer;
    lint size;
} lbuffer;

lstring read_file(lstring path);

#endif /*_LIO_H_*/
