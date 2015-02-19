#include "latino.h"
#include <math.h>

/*
 * local variables
 */
#define MAXVARS 1000
static variable vars[MAXVARS];
static int nVars=0;

/*--------------------------------------------------------------------
 * reduce_add
 *
 * add two numbers
 *------------------------------------------------------------------*/
extern
double reduce_add(double a, double b, YYLTYPE *bloc) {
    return a + b;
}
/*--------------------------------------------------------------------
 * reduce_sub
 *
 * sub two numbers
 *------------------------------------------------------------------*/
extern
double reduce_sub(double a, double b, YYLTYPE *bloc) {
    return a - b;
}
/*--------------------------------------------------------------------
 * reduce_mult
 *
 * multiply two numbers
 *------------------------------------------------------------------*/
extern
double reduce_mult(double a, double b, YYLTYPE *bloc) {
    return a * b;
}
/*--------------------------------------------------------------------
 * reduce_div
 *
 * divide two numbers, check for zero
 *------------------------------------------------------------------*/
extern
double reduce_div(double a, double b, YYLTYPE *bloc) {
    if (  b == 0  ) {
        print_error("division by zero! Line %d:c%d to %d:c%d",
                    bloc->first_line, bloc->first_column,
                    bloc->last_line, bloc->last_column);
        return FLT_MAX;
    }
    return a / b;
}
/*--------------------------------------------------------------------
 * reduce_mod
 *
 * divide two numbers and return remainder check for zero
 *------------------------------------------------------------------*/
extern
double reduce_mod(double a, double b, YYLTYPE *bloc) {
    if (  b == 0  ) {
        print_error("division by zero! Line %d:c%d to %d:c%d",
                    bloc->first_line, bloc->first_column,
                    bloc->last_line, bloc->last_column);
        return FLT_MAX;
    }
    return fmod(a, b);
}
/*--------------------------------------------------------------------
 * find_var
 *
 * simple search for a variable
 *------------------------------------------------------------------*/
static
variable *find_var(char *varname) {
    int i;
    if (  varname == NULL  )
        return NULL;
    for (i=0; i<nVars; i++)
        if (  strcmp(vars[i].name, varname) == 0  )
            return vars+i;
    return NULL;
}
/*--------------------------------------------------------------------
 * add_var
 *
 * simple search for a variable
 *------------------------------------------------------------------*/
static
variable *add_var(char *varname) {

    if (  varname == NULL  )
        return NULL;
    if (  nVars >= MAXVARS  ) {
        print_error("maximum number (%d) of variables reached", MAXVARS);
        return NULL;
    }
    vars[nVars].value = 0;
    vars[nVars].name = malloc(strlen(varname)+1);
    if (  vars[nVars].name == NULL  ) {
        print_error("internal error creating variable '%s'", varname);
        return NULL;
    }
    strcpy(vars[nVars].name, varname);
    nVars += 1;

    return vars+nVars-1;
}
/*--------------------------------------------------------------------
 * var_get
 *
 * gets a variable for reference, create if necessary
 *------------------------------------------------------------------*/
extern
variable *var_get(char *varname, YYLTYPE *bloc) {
    variable *var;

    if (  debug  )
        printf("get var %s\n", varname);
    var = find_var(varname);
    if (  var == NULL  )
        var = add_var(varname);
    return var;
}
/*--------------------------------------------------------------------
 * var_set_value
 *
 * sets a varible to a value
 *------------------------------------------------------------------*/
extern
void var_set_value(variable *var, double value) {
    if (  var == NULL  )
        return;
    if (  debug  )
        printf("set var %s to %lf\n", var->name, value);
    var->value = value;
}
/*--------------------------------------------------------------------
 * var_get_value
 *
 * get the contents of a variable
 *------------------------------------------------------------------*/
extern
double var_get_value(char *varname, YYLTYPE *bloc) {
    variable *var = NULL;

    var = find_var(varname);
    if (  var == NULL  ) {
        print_error("reference to unknown variable '%s'", varname);
        var = add_var(varname);
        if (  var == NULL  )
            return 0;
    }
    if (  debug  )
        printf("get var %s => %lf\n", var->name, var->value);
    return var->value;
}
/*--------------------------------------------------------------------
 * dump_variables
 *
 * get the contents of a variable
 *------------------------------------------------------------------*/
extern
void dump_variables(char *prefix) {
    int i;

    printf("%s Name------------------ Value----------\n", prefix);
    for (i=0; i<nVars; i++)
        printf("%s '%-20.20s' %g\n", prefix,
               vars[i].name, vars[i].value);
    return;
}

