#ifndef LATINO_H
#define LATINO_H 1

#define LATINO_HUGE 1

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include "parse.h"

/*
 * global variable
 */
extern int debug;

/*
 * lex & parse
 */
extern int yylex(void);

extern void dump_row(void);
extern int get_next_char(char *b, int maxBuffer);
extern void begin_token(char*);
extern void print_error(char *s, ...);

void yyerror(char *s, ...);
/* interface to the lexer */
extern int yylineno;    /* from lexer */

#endif /* LATINO_H */
