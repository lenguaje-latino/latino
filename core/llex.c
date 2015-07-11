#include <stdlib.h>
#include <string.h>
#include "llex.h"
#include "lmem.h"
#include "lio.h"

struct keyword {
    lstring key;
    enum RESERVED value;
};

struct keyword keytab[] = {
    { "si", TK_SI },
    { "sino", TK_SINO },
    { "fin", TK_FIN },
    { "elegir", TK_ELEGIR },
    { "caso", TK_CASO },
    { "defecto", TK_DEFECTO },
    { "desde", TK_DESDE },
    { "hasta", TK_HASTA },
    { "cuando", TK_CUANDO },
    { "salto", TK_SALTO },
    { "mientras", TK_MIENTRAS },
    { "hacer", TK_HACER },
    { "romper", TK_ROMPER },
    { "continuar", TK_CONTINUAR },
    { "funcion", TK_FUNCION },
    { "retorno", TK_RETORNO },
    { "verdadero", TK_VERDADERO },
    { "falso", TK_FALSO },
    { "clase", TK_CLASE },
    { "propiedad", TK_PROPIEDAD },
    { "constructor", TK_CONSTRUCTOR },
    { "esta", TK_ESTA }
};

#define is_new_line(ls) (ls->current == '\n' || ls->current == '\r')

#define NUM_RESERVERD (sizeof(keytab) / sizeof(struct keyword))

LAT_FUNC lex_state *lex_init()
{
    lex_state *ls  = (lex_state *) lmalloc(sizeof(lex_state));
    ls->linenumber = 1;
    ls->colnumber  = 0;
    ls->lastline   = 1;
    ls->inputfile  = (lbuffer *) lmalloc(sizeof(lbuffer));
    ls->inputfile->buffer = NULL;
    ls->lookahead.token = TK_EOS;
    return ls;
}

static void next_char(lex_state *ls)
{
    ls->colnumber++;
    if (ls->colnumber < ls->inputfile->size) {
        ls->current   = ls->inputfile->buffer[ls->colnumber - 1];
        printf("(%i, %i) = %c\n", ls->linenumber, (ls->colnumber - 1), ls->current);
    } else {
        ls->current = EOS;
    }
}

static void increment_line(lex_state *ls)
{
    lint old = ls->current;
    next_char(ls);
    if (is_new_line(ls) && ls->current != old) {
        next_char(ls);
    }
    ++ls->linenumber;
}

static lstring new_string(lex_state *ls)
{
    lchar word[LAT_MAXWORD];
    int i   = 0;
    do {
        word[i] = ls->current;
        i++;
        next_char(ls);
    } while (lisalnum(ls->current) && i < LAT_MAXWORD);
    word[i] = '\0';
    printf("word=%s\n", word);
    lstring ret = word;
    return ret;
}

static lint is_reserved(lstring tk)
{
    unsigned int i;
    for (i = 0; i < NUM_RESERVERD; ++i) {
        if (strcmp(tk, keytab[i].key) == 0) {
            return keytab[i].value;
        }
    }
    return 0;
}

static lint llex(lex_state *ls, semantic *sem)
{
    for (;;) {
        switch (ls->current) {
        case '\n':
        case '\r': {
            increment_line(ls);
            break;
        }
        case ' ':
        case '\f':
        case '\t':
        case '\v': {  /* spaces */
            next_char(ls);
            break;
        }
        case '#': { /* comments */
            while (!is_new_line(ls) && ls->current != EOS)
                next_char(ls);
            break;
        }
        case EOS: {
            return TK_EOS;
        }
        case '"':{
             //read_string(ls, ls->current, sem_info);
             return TK_CADENA;
         }
        default: {
            if (lisalpha(ls->current)) {
                lstring tk = new_string(ls);
                /* is reserved word? */
                lint reserved = is_reserved(tk);
                if (reserved) {
                    return reserved;
                } else {
                    return TK_IDENT;
                }
            } else {
                lint c = ls->current;
                next_char(ls);
                return c;
            }
            break;
        }
        }
    }
}

LAT_FUNC void lex_next(lex_state *ls)
{
    ls->lastline = ls->linenumber;
    if (ls->lookahead.token != TK_EOS) {
        ls->currtoken       = ls->lookahead;
        ls->lookahead.token = TK_EOS;
    } else {
        ls->currtoken.token = llex(ls, &ls->currtoken.sem_info);
        printf("token=%i\n", ls->currtoken.token);
    }
}

LAT_FUNC lint lex_lookahead(lex_state *ls)
{
    lint col            = ls->colnumber;
    ls->lookahead.token = llex(ls, &ls->lookahead.sem_info);
    ls->colnumber       = col;
    return ls->lookahead.token;
}
