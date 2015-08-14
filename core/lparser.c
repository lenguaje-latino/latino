#include <stdlib.h>
#include <string.h>

#include "lparser.h"
#include "llex.h"
#include "lmem.h"
#include "lio.h"

int lparser(lstring path)
{
    lex_state *ls = lex_init();
    ls->inputfile->buffer = read_file(path);
    if (!ls->inputfile->buffer) {
        return EXIT_FAILURE;
    }
    ls->inputfile->size = strlen(ls->inputfile->buffer);
    /*read first char*/
    ls->current = buff_get_char(ls, 0);
    lbuffer *buff = ls->inputfile;
    printf("buffer is: \n%s\n", buff->buffer);
    printf("buffer size  = %ld\n", buff->size);
    /*printf("(%i, %i) => %c\n", ls->linenumber, (ls->colnumber), ls->current);*/
    /*read first token*/
    lex_next(ls);
    int tk = ls->currtoken.token;
    while (tk != TK_EOS) {
        lex_next(ls);
        tk = ls->currtoken.token;
    }
    /*test lookahead*/
    /*tk = lex_lookahead(ls);*/
    /*printf("lookahead token = %i\n", tk);*/
    lex_destroy(ls);
    return EXIT_SUCCESS;
}


