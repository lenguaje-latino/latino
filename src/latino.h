#ifndef LATINO_H
#define LATINO_H

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
extern int yyparse(void);
extern void yyerror(char*);

/*
 * ccalc.c
 */
extern void dump_row(void);
extern int get_next_char(char *b, int maxBuffer);
extern void begin_token(char*);
extern void print_error(char *s, ...);

/*
 * cmath.c
 */
typedef struct _variable {
  char    *name;
  double  value;
} variable;

extern double reduce_add(double, double, YYLTYPE*);
extern double reduce_sub(double, double, YYLTYPE*);
extern double reduce_mult(double, double, YYLTYPE*);
extern double reduce_div(double, double, YYLTYPE*);
extern double reduce_mod(double, double, YYLTYPE*);

extern variable *var_get(char*, YYLTYPE*);
extern void var_set_value(variable*, double);
extern double var_get_value(char*, YYLTYPE*);
extern void dump_variables(char *prefix);

#endif /* LATINO_H */
