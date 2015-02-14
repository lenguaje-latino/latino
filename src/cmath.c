#include "latino.h"
#include <math.h>

/*
 * local variables
 */
#define MAXVARS 1000
static Variable vars[MAXVARS];
static int nVars=0;

/*--------------------------------------------------------------------
 * ReduceAdd
 *
 * add two numbers
 *------------------------------------------------------------------*/
extern
double ReduceAdd(double a, double b, YYLTYPE *bloc) {
  return a + b;
}
/*--------------------------------------------------------------------
 * ReduceSub
 *
 * sub two numbers
 *------------------------------------------------------------------*/
extern
double ReduceSub(double a, double b, YYLTYPE *bloc) {
  return a - b;
}
/*--------------------------------------------------------------------
 * ReduceMult
 *
 * multiply two numbers
 *------------------------------------------------------------------*/
extern
double ReduceMult(double a, double b, YYLTYPE *bloc) {
  return a * b;
}
/*--------------------------------------------------------------------
 * ReduceDiv
 *
 * divide two numbers, check for zero
 *------------------------------------------------------------------*/
extern
double ReduceDiv(double a, double b, YYLTYPE *bloc) {
  if (  b == 0  ) {
// simple error-message
/*
    printf("division by zero!\n");
*/
// complex error-meessage
/*
    PrintError("division by zero!");
*/

// complex error-printing
/* */
    PrintError("division by zero! Line %d:c%d to %d:c%d",
                        bloc->first_line, bloc->first_column,
                        bloc->last_line, bloc->last_column);
/* */
    return FLT_MAX;
  }
  return a / b;
}
/*--------------------------------------------------------------------
 * ReduceMod
 *
 * divide two numbers and return remainder check for zero
 *------------------------------------------------------------------*/
extern
double ReduceMod(double a, double b, YYLTYPE *bloc) {
  if (  b == 0  ) {
// simple error-message
/*
    printf("division by zero!\n");
*/
// complex error-meessage
/*
    PrintError("division by zero!");
*/

// complex error-printing
/* */
    PrintError("division by zero! Line %d:c%d to %d:c%d",
                        bloc->first_line, bloc->first_column,
                        bloc->last_line, bloc->last_column);
/* */
    return FLT_MAX;
  }
  return fmod(a, b);
}
/*--------------------------------------------------------------------
 * findVar
 *
 * simple search for a variable
 *------------------------------------------------------------------*/
static
Variable *findVar(char *varname) {
  int i;
  if (  varname == NULL  )
    return NULL;
  for (i=0; i<nVars; i++)
    if (  strcmp(vars[i].name, varname) == 0  )
      return vars+i;
  return NULL;
}
/*--------------------------------------------------------------------
 * addVar
 *
 * simple search for a variable
 *------------------------------------------------------------------*/
static
Variable *addVar(char *varname) {

  if (  varname == NULL  )
    return NULL;
  if (  nVars >= MAXVARS  ) {
    PrintError("maximum number (%d) of variables reached", MAXVARS);
    return NULL;
  }
  vars[nVars].value = 0;
  vars[nVars].name = malloc(strlen(varname)+1);
  if (  vars[nVars].name == NULL  ) {
    PrintError("internal error creating variable '%s'", varname);
    return NULL;
  }
  strcpy(vars[nVars].name, varname);
  nVars += 1;

  return vars+nVars-1;
}
/*--------------------------------------------------------------------
 * VarGet
 *
 * gets a variable for reference, create if necessary
 *------------------------------------------------------------------*/
extern
Variable *VarGet(char *varname, YYLTYPE *bloc) {
  Variable *var;

  if (  debug  )
    printf("get var %s\n", varname);
  var = findVar(varname);
  if (  var == NULL  )
    var = addVar(varname);
  return var;
}
/*--------------------------------------------------------------------
 * VarSetValue
 *
 * sets a varible to a value
 *------------------------------------------------------------------*/
extern
void VarSetValue(Variable *var, double value) {
  if (  var == NULL  )
    return;
  if (  debug  )
    printf("set var %s to %lf\n", var->name, value);
  var->value = value;
}
/*--------------------------------------------------------------------
 * VarGetValue
 *
 * get the contents of a variable
 *------------------------------------------------------------------*/
extern
double VarGetValue(char *varname, YYLTYPE *bloc) {
  Variable *var = NULL;

  var = findVar(varname);
  if (  var == NULL  ) {
    PrintError("reference to unknown variable '%s'", varname);
    var = addVar(varname);
    if (  var == NULL  )
      return 0;
  }
  if (  debug  )
    printf("get var %s => %lf\n", var->name, var->value);
  return var->value;
}
/*--------------------------------------------------------------------
 * DumpVariables
 *
 * get the contents of a variable
 *------------------------------------------------------------------*/
extern
void DumpVariables(char *prefix) {
  int i;

  printf("%s Name------------------ Value----------\n", prefix);
  for (i=0; i<nVars; i++)
    printf("%s '%-20.20s' %g\n", prefix,
                        vars[i].name, vars[i].value);
  return;
}
