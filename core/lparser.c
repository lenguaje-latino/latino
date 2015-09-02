#include <stdlib.h>
#include <string.h>

#include "latino.h"
#include "lparser.h"
#include "llex.h"
#include "lmem.h"
#include "lio.h"

static void stat_list(lex_state *ls);

static void parser_error(lex_state *ls, lstring msg)
{
    printf("Error gramatical linea %d, columna %d: %s.\n", ls->linenumber, ls->colnumber, msg);
}

static void parse_multiplication(lex_state *ls){

}

static void parse_addition(lex_state *ls){

}

static void subexpresion(lex_state *ls){
    printf("%s\n", "parsing sub expresion...");
}

static void expresion(lex_state *ls){
    printf("%s\n", "parsing expresion...");
    subexpresion(ls);
}

static void if_stat(lex_state *ls){
    /*if_stat -> SI ( cond ) block {SINO_SI ( cond ) block } [SINO block] FIN */
    printf("%s\n", "if");
    lex_next(ls); /*skip SI keyword*/
    if (ls->currtoken.token == '(')
    {
        expresion(ls);
        stat_list(ls);
    }else{
        parser_error(ls, "sentencia SI mal formada se esperaba (");
    }
}

static void while_stat(lex_state *ls){

}

static void fun_stat(lex_state *ls){

}

static void statement(lex_state *ls){
    switch (ls->currtoken.token) {
        case TK_SI:
            if_stat(ls);
            break;
        case TK_DESDE:
            while_stat(ls);
            break;
        case TK_FUNCION:
            fun_stat(ls);
            break;
        default:
            lex_next(ls);
            break;
    }
}

static void stat_list(lex_state *ls){
    while(ls->currtoken.token != TK_EOS){
        statement(ls);
    }
}

int parser_init(lstring path)
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
    printf("buffer size  = %ld\n", buff->size);
    printf("buffer is: \n%s\n", buff->buffer);
    lparser(ls);
    lex_destroy(ls);
    return OK;
}

int lparser(lex_state *ls){
    /*read first token*/
    lex_next(ls);
    stat_list(ls);
    return 0;
}
