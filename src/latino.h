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
#include "lex.yy.c"

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
extern void DumpRow(void);
extern int GetNextChar(char *b, int maxBuffer);
extern void BeginToken(char*);
extern void PrintError(char *s, ...);

/*
 * cmath.c
 */
typedef struct _Variable {
  char    *name;
  double  value;
} Variable;

extern double ReduceAdd(double, double, YYLTYPE*);
extern double ReduceSub(double, double, YYLTYPE*);
extern double ReduceMult(double, double, YYLTYPE*);
extern double ReduceDiv(double, double, YYLTYPE*);

extern Variable *VarGet(char*, YYLTYPE*);
extern void VarSetValue(Variable*, double);
extern double VarGetValue(char*, YYLTYPE*);
extern void DumpVariables(char *prefix);

#endif /* LATINO_H */
