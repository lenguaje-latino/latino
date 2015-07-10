#include <string.h>
#include "lparser.h"
#include "llex.h"
#include "lio.h"

void lparser(lstring path){
    lex_state *ls = lex_init();
    ls->inputfile->buffer = read_file(path);
    ls->inputfile->size = strlen(ls->inputfile->buffer);
    ls->current          = buff_get_char(ls, 0);
    lbuffer *buff = ls->inputfile;
    printf("buffer is    = \n%s\n", buff->buffer);
    printf("buffer size  = \n%d\n", buff->size);
    //printf("first char = \n%c\n", (char) ls->inputfile[0]);
    lex_next(ls);
    lint c = ls->current;
    while(c!=EOS){
        lex_next(ls);
        c = ls->current;
    }
}
