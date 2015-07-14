#ifndef _LLEX_H_
#define _LLEX_H_
#include "latino.h"
#include "lio.h"

#define FIRST_RESERVED 257

enum RESERVED {
    TK_SI = FIRST_RESERVED,
    TK_SINO,
    TK_FIN,
    TK_ELEGIR, /*260*/
    TK_CASO,
    TK_DEFECTO,
    TK_DESDE,
    TK_HASTA,
    TK_CUANDO,
    TK_SALTO,
    TK_MIENTRAS,
    TK_HACER,
    TK_ROMPER,
    TK_CONTINUAR, /*270*/
    TK_FUNCION,
    TK_RETORNO,
    TK_VERDADERO,
    TK_FALSO,
    TK_CLASE,
    TK_PROPIEDAD,
    TK_CONSTRUCTOR,
    TK_ESTA,
    /* data types */
    TK_CARACTER,
    TK_ENTERO, /*280*/
    TK_DECIMAL,
    TK_CADENA,
    TK_IDENT,
    TK_EOS
};

typedef union {
    lint r;
    lstring ts;
} semantic;

typedef struct token {
    lint token;
    semantic sem_info;
} token;

typedef struct lex_state {
    lint current; /* current character */
    lint linenumber; /* line counter */
    lint colnumber; /* column counter */
    lint pos; /* position in buffer */
    lint lastline; /* line of last token consumed */
    token currtoken; /* current token */
    token lookahead; /* look ahead token */
    lbuffer *inputfile; /* input stream */
} lex_state;

LAT_FUNC lex_state *lex_init();
LAT_FUNC void lex_next(lex_state *ls);
LAT_FUNC lint lex_lookahead(lex_state *ls);

#endif /*_LLEX_H_*/



