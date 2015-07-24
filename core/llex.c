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
    ls->colnumber  = 1;
    ls->pos  = 0;
    ls->lastline   = 1;
    ls->inputfile  = (lbuffer *) lmalloc(sizeof(lbuffer));
    ls->inputfile->buffer = NULL;
    ls->lookahead.token = TK_EOS;
    return ls;
}

static void next_char(lex_state *ls)
{
    ls->colnumber++;
    ls->pos++;
    if (ls->pos < ls->inputfile->size) {
        ls->current   = buff_get_char(ls, ls->pos);
        printf("(%i, %i) = %c\n", ls->linenumber, (ls->colnumber), ls->current);
    } else {
        ls->current = EOS;
    }
}

static char lookahead_char(lex_state *ls)
{
    long pos = ls->pos + 1;
    if (pos < ls->inputfile->size) {
        return ls->inputfile->buffer[pos];
    } else {
        return EOS;
    }
}

static void increment_line(lex_state *ls)
{
    ++ls->linenumber;
    ls->colnumber = 1;
    int old = ls->current;
    next_char(ls);
    if (is_new_line(ls) && ls->current != old) {
        next_char(ls);
    }
}

static lstring new_string(lex_state *ls)
{
    char word[LAT_MAXWORD];
    int i   = 0;
    do {
        word[i] = ls->current;
        next_char(ls);
        i++;
    } while (lisalnum(ls->current));
    word[i] = '\0';
    lstring ret = word;
    printf("new_string=%s\n", word);
    return ret;
}

static int is_reserved(lstring tk)
{
    unsigned int i;
    for (i = 0; i < NUM_RESERVERD; ++i) {
        if (strcmp(tk, keytab[i].key) == 0) {
            return keytab[i].value;
        }
    }
    return 0;
}

static lstring get_reserved_name(int tk){
    return keytab[tk].key;
}

static void lex_error(lex_state *ls, lstring msg, int token)
{
    printf("Error de sintaxis linea %d, columna %d: %s. TOKEN (%i)\n", ls->linenumber, ls->colnumber, msg, token);
}

static int read_string(lex_state *ls, int del, semantic *sem)
{
    next_char(ls);
    while (ls->current != del && ls->current != EOS) {
        switch (ls->current) {
        case EOS:
            lex_error(ls, "Cadena sin terminar", TK_EOS);
            return EOS;
            break;
        case '\n':
        case '\r':
            lex_error(ls, "Cadena sin terminar", TK_CADENA);
            increment_line(ls);
            break;
        case '\\': {
            int c;
            int i;
            next_char(ls);
            switch (ls->current) {
            case 'a':
                c = '\a';
                next_char(ls);
                break;
            case 'b':
                c = '\b';
                next_char(ls);
                break;
            case 'f':
                c = '\f';
                next_char(ls);
                break;
            case 'n':
                c = '\n';
                next_char(ls);
                break;
            case 'r':
                c = '\r';
                next_char(ls);
                break;
            case 't':
                c = '\t';
                next_char(ls);
                break;
            case 'v':
                c = '\v';
                next_char(ls);
                break;
            case 'x':
                next_char(ls);
                for (i = 0; i < 2; i++) {
                    if (!lisxdigit(ls->current))
                        lex_error(ls, "Secuencia de escape invalida", TK_CADENA);
                    next_char(ls);
                }
                break;
            case '\n':
            case '\r':
                lex_error(ls, "Cadena sin terminar", TK_CADENA);
                increment_line(ls);
                break;
            case '\\':
            case '\"':
            case '\'':
                c = ls->current;
                next_char(ls);
                break;
            default: {
                if (!lisdigit(ls->current)) {
                    lex_error(ls, "Secuencia de escape invalida", TK_CADENA);
                    next_char(ls);
                    break;
                }
                /* digital escape \ddd */
                for (i = 0; i < 3; i++) {
                    if (!lisodigit(ls->current))
                        lex_error(ls, "Secuencia de escape invalida", TK_CADENA);
                    next_char(ls);
                }
                break;
            }
            }
            break;
        }
        default:
            next_char(ls);
            break;
        }
    }
    return 0;
}

static int read_char(lex_state *ls, int del, semantic *sem)
{
    next_char(ls);
    while (ls->current != del && ls->current != EOS) {
        switch (ls->current) {
        case EOS:
            lex_error(ls, "Caracter sin terminar", TK_EOS);
            return EOS;
            break;
        case '\n':
        case '\r':
            lex_error(ls, "Caracter sin terminar", TK_CARACTER);
            increment_line(ls);
            break;
        case '\\': {
            int c;
            int i;
            next_char(ls);
            switch (ls->current) {
            case 'a':
                c = '\a';
                next_char(ls);
                break;
            case 'b':
                c = '\b';
                next_char(ls);
                break;
            case 'f':
                c = '\f';
                next_char(ls);
                break;
            case 'n':
                c = '\n';
                next_char(ls);
                break;
            case 'r':
                c = '\r';
                next_char(ls);
                break;
            case 't':
                c = '\t';
                next_char(ls);
                break;
            case 'v':
                c = '\v';
                next_char(ls);
                break;
            case 'x':
                next_char(ls);
                for (i = 0; i < 2; i++) {
                    if (!lisxdigit(ls->current))
                        lex_error(ls, "Secuencia de escape invalida", TK_CARACTER);
                    next_char(ls);
                }
                break;
            case '\n':
            case '\r':
                lex_error(ls, "Cadena sin terminar", TK_CARACTER);
                increment_line(ls);
                break;
            case '\\':
            case '\"':
            case '\'':
                c = ls->current;
                next_char(ls);
                break;
            default: {
                if (!lisdigit(ls->current)) {
                    lex_error(ls, "Secuencia de escape invalida", TK_CARACTER);
                    next_char(ls);
                    break;
                }
                /* digital escape \ddd */
                for (i = 0; i < 3; i++) {
                    if (!lisodigit(ls->current))
                        lex_error(ls, "Secuencia de escape invalida", TK_CARACTER);
                    next_char(ls);
                }
                break;
            }
            }
            break;
        }
        default: {
            next_char(ls);
            break;
        }
        }
    }
    return 0;
}

static int read_number(lex_state *ls, semantic *sem)
{
    int ret = TK_ENTERO;
    int has_point = 0;
    int c;
    /* 105 return TK_ENTERO */
    /* 3.1416 return TK_DECIMAL */
    /* 3.14.16 return TK_DECIMAL TK_DOT TK_ENTERO */
    for (;;) {
        c = lookahead_char(ls);
        if (lisdigit(c) && has_point == 0) {
            next_char(ls);
            continue;
        }
        if (c == '.' && has_point == 0) {
            has_point++;
            next_char(ls);
            continue;
        }
        if (lisdigit(c) && has_point == 1) {
            next_char(ls);
            continue;
        }
        break;
    }
    if (has_point)
        ret = TK_DECIMAL;
    return ret;
}

static int llex(lex_state *ls, semantic *sem)
{
    int ret;
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
        case '"': {
            ret = read_string(ls, ls->current, sem);
            if (ret != EOS)
                next_char(ls);
            return TK_CADENA;
        }
        case '\'': {
            ret = read_char(ls, ls->current, sem);
            if (ret != EOS)
                next_char(ls);
            return TK_CARACTER;
        }
        case '=': {
            next_char(ls);
            if (ls->current != '=') return '=';
            else {
                next_char(ls);
                return TK_IGUALDAD;
            }
        }
        case '!': {
            next_char(ls);
            if (ls->current != '=') return '!';
            else {
                next_char(ls);
                return TK_DIFERENTE;
            }
        }
        case '<': {
            next_char(ls);
            if (ls->current != '=') return '<';
            else {
                next_char(ls);
                return TK_MENOR_IGUAL;
            }
        }
        case '>': {
            next_char(ls);
            if (ls->current != '=') return '>';
            else {
                next_char(ls);
                return TK_MAYOR_IGUAL;
            }
        }
        case '&': {
            next_char(ls);
            if (ls->current != '&') return '&';
            else {
                next_char(ls);
                return TK_Y_LOGICO;
            }
        }
        case '|': {
            next_char(ls);
            if (ls->current != '|') return '|';
            else {
                next_char(ls);
                return TK_O_LOGICO;
            }
        }
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            ret = read_number(ls, sem);
            next_char(ls);
            return ret;
        }
        default: {
            if (lisalpha(ls->current)) {
                lstring tk = new_string(ls);
                /* is reserved word? */
                int reserved = is_reserved(tk);
                if (reserved) {
                    return reserved;
                } else {
                    return TK_IDENT;
                }
            } else {
                int c = ls->current;
                next_char(ls);
                return c;
            }
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

LAT_FUNC int lex_lookahead(lex_state *ls)
{
    lex_state *ls_tmp = lmalloc(sizeof(lex_state));
    memcpy(ls_tmp, ls, sizeof(lex_state));
    ls_tmp->lookahead.token = llex(ls_tmp, &ls_tmp->lookahead.sem_info);
    lfree(ls_tmp);
    return ls_tmp->lookahead.token;
}

