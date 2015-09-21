#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "latino.h"
#include "ast.h"
#include "utils.h"

latValue *evalNodeAdd(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    switch (left->t) {
    case VALUE_BOOL:
        if (right->t == VALUE_STRING) {
            result->t = VALUE_STRING;
            result->v.s = concat(bool2str(left->v.b), right->v.s);
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t == VALUE_INT) {
            result->t = VALUE_INT;
            result->v.i  = left->v.i + right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.i + right->v.d;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.i + right->v.c;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->t   = VALUE_STRING;
            result->v.s = concat(int2str(left->v.i), right->v.s);
            return result;
        }
        break;
    case VALUE_DOUBLE:
        if (right->t == VALUE_INT) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d + right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d + right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->t   = VALUE_STRING;
            result->v.s = concat(int2str(left->v.d), right->v.s);
            return result;
        }
        break;
    case VALUE_CHAR:
        if (right->t == VALUE_INT) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.c + right->v.i;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.c + right->v.c;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->t   = VALUE_STRING;
            result->v.s = concat(char2str(left->v.c), right->v.s);
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t == VALUE_BOOL) {
            result->t = VALUE_STRING;
            result->v.s = concat(left->v.s, bool2str(right->v.b));
            return result;
        }
        if (right->t == VALUE_INT) {
            result->t = VALUE_STRING;
            result->v.s  = concat(left->v.s, int2str(right->v.i));
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_STRING;
            result->v.s  = concat(left->v.s, double2str(right->v.d));
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->t = VALUE_STRING;
            result->v.s  = concat(left->v.s, char2str(right->v.c));
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->t   = VALUE_STRING;
            result->v.s = concat(left->v.s, right->v.s);
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("+ tipos incompatibles");
    return result;
}

latValue *evalNodeSub(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    switch (left->t) {
    case VALUE_INT:
        if (right->t == VALUE_INT) {
            result->t = VALUE_INT;
            result->v.i  = left->v.i - right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.i - right->v.d;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.i - right->v.c;
            return result;
        }
        break;
    case VALUE_DOUBLE:
        if (right->t == VALUE_INT) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d - right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d - right->v.d;
            return result;
        }
        break;
    case VALUE_CHAR:
        if (right->t == VALUE_INT) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.c - right->v.i;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->t = VALUE_CHAR;
            result->v.c  = left->v.c - right->v.c;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("- tipos incompatibles");
    return result;
}

latValue *evalNodeMult(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    switch (left->t) {
    case VALUE_INT:
        if (right->t == VALUE_INT) {
            result->t = VALUE_INT;
            result->v.i  = left->v.i * right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.i * right->v.d;
            return result;
        }
        break;
    case VALUE_DOUBLE:
        if (right->t == VALUE_INT) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d * right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            result->v.d  = left->v.d * right->v.d;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("* tipos incompatibles");
    return result;
}

latValue *evalNodeDiv(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    switch (left->t) {
    case VALUE_INT:
        if (right->t == VALUE_INT) {
            result->t = VALUE_INT;
            if (right->v.i == 0) {
                yyerror("/ division por cero");
            } else {
                result->v.i  = left->v.i / right->v.i;
            }
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            if (right->v.d == 0) {
                yyerror("/ division por cero");
            } else {
                result->v.d  = left->v.i / right->v.d;
            }
            return result;
        }
        break;
    case VALUE_DOUBLE:
        if (right->t == VALUE_INT) {
            result->t = VALUE_DOUBLE;
            if (right->v.i == 0) {
                yyerror("/ division por cero");
            } else {
                result->v.d  = left->v.d / right->v.i;
            }
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->t = VALUE_DOUBLE;
            if (right->v.d == 0) {
                yyerror("/ division por cero");
            } else {
                result->v.d  = left->v.d / right->v.d;
            }
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("/ tipos incompatibles");
    return result;
}

latValue *evalNodeMod(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    switch (left->t) {
    case VALUE_INT:
        if (right->t == VALUE_INT) {
            result->t = VALUE_INT;
            if (right->v.i == 0) {
                yyerror("\% division por cero");
            } else {
                result->v.i  = left->v.i % right->v.i;
            }
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("\% tipos incompatibles");
    return result;
}

latValue *evalNodeMinus(latValue *left)
{
    latValue *result = malloc(sizeof(latValue));
    if (left->t == VALUE_INT) {
        result->t = VALUE_INT;
        result->v.i = - (left->v.i);
        return result;
    }
    if (left->t == VALUE_DOUBLE) {
        result->t = VALUE_DOUBLE;
        result->v.d  = - (left->v.d);
        return result;
    }
    yyerror("- tipos incompatible");
    return result;
}

latValue *evalNodeAnd(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    if (left->t == VALUE_BOOL && right->t == VALUE_BOOL) {
        result->t = VALUE_BOOL;
        result->v.b = left->v.b && right->v.b;
        return result;
    }
    yyerror("&& tipos incompatible");
    return result;
}

latValue *evalNodeOr(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    if (left->t == VALUE_BOOL && right->t == VALUE_BOOL) {
        result->t = VALUE_BOOL;
        result->v.b = left->v.b || right->v.b;
        return result;
    }
    yyerror("|| tipos incompatible");
    return result;
}

latValue *evalNodeNeg(latValue *left)
{
    latValue *result = malloc(sizeof(latValue));
    if (left->t == VALUE_BOOL) {
        result->t = VALUE_BOOL;
        result->v.b = !(left->v.b);
        return result;
    }
    yyerror("! tipos incompatible");
    return result;
}

latValue *evalNodeGt(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_CHAR:
        if (right->t == VALUE_INT) {
            result->v.b = left->v.c > right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) > 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.i > right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i > right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.i > right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) > 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE :
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i > right->v.d;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.d > right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) > 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t == VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) > 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) > 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) > 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) > 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *evalNodeLt(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_CHAR:
        if (right->t == VALUE_INT) {
            result->v.b = left->v.c < right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) < 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.i < right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i < right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.i < right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) < 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE :
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i < right->v.d;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.d < right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) < 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t == VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) < 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) < 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) < 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) < 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *evalNodeNeq(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_BOOL:
        if (right->t == VALUE_BOOL) {
            result->v.b = left->v.b != right->v.b;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.b != right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(bool2str(left->v.b), right->v.s) != 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_CHAR:
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.c == right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.c != right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) != 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t == VALUE_BOOL) {
            result->v.b = left->v.i != right->v.b;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.i != right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i != right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.i != right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) != 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE:
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i != right->v.d;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.d != right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) != 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t == VALUE_BOOL) {
            result->v.b = strcmp(left->v.s, bool2str(right->v.b)) != 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) != 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) != 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) != 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) != 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *evalNodeEq(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_BOOL:
        if (right->t == VALUE_BOOL) {
            result->v.b = left->v.b == right->v.b;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.b == right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(bool2str(left->v.b), right->v.s) == 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_CHAR:
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.c == right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.c == right->v.i;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) == 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t == VALUE_BOOL) {
            result->v.b = left->v.i == right->v.b;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b = left->v.i == right->v.c;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i == right->v.i;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.i == right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) == 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE :
        if (right->t == VALUE_INT) {
            result->v.b = left->v.i == right->v.d;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b = left->v.d == right->v.d;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) == 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t == VALUE_BOOL) {
            result->v.b = strcmp(left->v.s, bool2str(right->v.b)) == 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) == 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) == 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) == 0 ? 1 : 0;
            return result;
        }
        if (right->t == VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) == 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *evalNodeGe(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_CHAR:
        if (right->t >= VALUE_INT) {
            result->v.b = left->v.c >= right->v.i;
            return result;
        }
        if (right->t >= VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) >= 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t >= VALUE_CHAR) {
            result->v.b = left->v.i >= right->v.c;
            return result;
        }
        if (right->t >= VALUE_INT) {
            result->v.b = left->v.i >= right->v.i;
            return result;
        }
        if (right->t >= VALUE_DOUBLE) {
            result->v.b = left->v.i >= right->v.d;
            return result;
        }
        if (right->t >= VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) >= 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE :
        if (right->t >= VALUE_INT) {
            result->v.b = left->v.i >= right->v.d;
            return result;
        }
        if (right->t >= VALUE_DOUBLE) {
            result->v.b = left->v.d >= right->v.d;
            return result;
        }
        if (right->t >= VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) >= 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t >= VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) >= 0 ? 1 : 0;
            return result;
        }
        if (right->t >= VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) >= 0 ? 1 : 0;
            return result;
        }
        if (right->t >= VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) >= 0 ? 1 : 0;
            return result;
        }
        if (right->t >= VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) >= 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *evalNodeLe(latValue *left, latValue *right)
{
    latValue *result = malloc(sizeof(latValue));
    result->t = VALUE_BOOL;
    switch (left->t) {
    case VALUE_CHAR:
        if (right->t <= VALUE_INT) {
            result->v.b = left->v.c <= right->v.i;
            return result;
        }
        if (right->t <= VALUE_STRING) {
            result->v.b = strcmp(char2str(left->v.c), right->v.s) <= 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_INT:
        if (right->t <= VALUE_CHAR) {
            result->v.b = left->v.i <= right->v.c;
            return result;
        }
        if (right->t <= VALUE_INT) {
            result->v.b = left->v.i <= right->v.i;
            return result;
        }
        if (right->t <= VALUE_DOUBLE) {
            result->v.b = left->v.i <= right->v.d;
            return result;
        }
        if (right->t <= VALUE_STRING) {
            result->v.b = strcmp(int2str(left->v.i), right->v.s) <= 0 ?  1 : 0;
            return result;
        }
        break;
    case VALUE_DOUBLE :
        if (right->t <= VALUE_INT) {
            result->v.b = left->v.i <= right->v.d;
            return result;
        }
        if (right->t <= VALUE_DOUBLE) {
            result->v.b = left->v.d <= right->v.d;
            return result;
        }
        if (right->t <= VALUE_STRING) {
            result->v.b = strcmp(double2str(left->v.d), right->v.s) <= 0 ? 1 : 0;
            return result;
        }
        break;
    case VALUE_STRING:
        if (right->t <= VALUE_INT) {
            result->v.b  = strcmp(left->v.s, int2str(right->v.i)) <= 0 ? 1 : 0;
            return result;
        }
        if (right->t <= VALUE_DOUBLE) {
            result->v.b  = strcmp(left->v.s, double2str(right->v.d)) <= 0 ? 1 : 0;
            return result;
        }
        if (right->t <= VALUE_CHAR) {
            result->v.b  = strcmp(left->v.s, char2str(right->v.c)) <= 0 ? 1 : 0;
            return result;
        }
        if (right->t <= VALUE_STRING) {
            result->v.b = strcmp(left->v.s, right->v.s) <= 0 ? 1 : 0;
            return result;
        }
        break;
    default:
        break;
    }
    yyerror("> tipos incompatibles");
    return result;
}

latValue *val;
latValue *val1;
jmp_buf eval_fun;

/* evaluar ast */
latValue *eval(ast *a)
{
    double v;
    if (!a) {
        yyerror("eval es nulo\n");
        return val;
    }
    switch (a->nodetype) {
    /* constant */
    case NODE_BOOLEAN:
    case NODE_CHAR:
    case NODE_DECIMAL:
    case NODE_STRING:
    case NODE_INT:
        return ((node *)a)->value;
        break;
    /* name reference */
    case NODE_SYMBOL: {
        if (((symref *)a)->s->value == NULL) {
            yyerror("variable sin definir");
        } else {
            return ((symref *)a)->s->value;
        }
    }
    break;
    /* assignment */
    case NODE_ASSIGMENT: {
        ((symAsgn *)a)->s->value = eval(((symAsgn *)a)->v);
        return ((symAsgn *)a)->s->value;
    }
    break;
    case NODE_UNARY_MINUS:
        return evalNodeMinus(eval(a->l));
        break;
    /* expressions */
    case NODE_ADD:
        return evalNodeAdd(eval(a->l), eval(a->r));
        break;
    case NODE_SUB:
        return evalNodeSub(eval(a->l), eval(a->r));
        break;
    case NODE_MULT:
        return evalNodeMult(eval(a->l), eval(a->r));
        break;
    case NODE_DIV:
        return evalNodeDiv(eval(a->l), eval(a->r));
        break;
    case NODE_MOD:
        return evalNodeMod(eval(a->l), eval(a->r));
        break;
    case NODE_AND:
        return evalNodeAnd(eval(a->l), eval(a->r));
        break;
    case NODE_OR:
        return evalNodeOr(eval(a->l), eval(a->r));
        break;
    case NODE_NEG:
        return evalNodeNeg(eval(a->l));
        break;
    /* comparisons */
    case NODE_GT:
        return evalNodeGt(eval(a->l), eval(a->r));
        break;
    case NODE_LT:
        return evalNodeLt(eval(a->l), eval(a->r));
        break;
    case NODE_NEQ:
        return evalNodeNeq(eval(a->l), eval(a->r));
        break;
    case NODE_EQ:
        return evalNodeEq(eval(a->l), eval(a->r));
        break;
    case NODE_GE:
        return evalNodeGe(eval(a->l), eval(a->r));
        break;
    case NODE_LE:
        return evalNodeLe(eval(a->l), eval(a->r));
        break;
    /* control flow */
    /* if/else */
    /* null expressions allowed in the grammar, so check for them */
    case NODE_IF: {
        if ((eval(((flow *)a)->cond))->v.b != 0) {
            if (((flow *)a)->tl) {
                eval(((flow *)a)->tl);
            }
        } else {
            if (((flow *)a)->el) {
                eval(((flow *)a)->el);
            }
        }
        return val;
    }
    break;
    /* while */
    case NODE_WHILE:
        while ((eval(((flow *)a)->cond))->v.b != 0) {
            eval(((flow *)a)->tl);
        }
        return val;
        break;
    /* do */
    case NODE_DO:
        do {
            eval(((flow *)a)->tl);
        } while ((eval(((flow *)a)->cond))->v.b != 0);
        return val;
        break;
    case NODE_SWITCH:
        val = eval(((flow *)a)->cond);
        ((flow *)(((flow *)a)->tl))->cond = ((flow *)a)->cond;
        /* evaluar los casos */
        val = eval(((flow *)a)->tl);
        /* si ningun caso se evaluo */
        if (!val->v.b) {
            /* evaluar default si existe */
            if ((((flow *)a)->el)) {
                val = eval(((flow *)a)->el);
            }
        }
        return val;
        break;
    case NODE_CASES:
        val = eval(((flow *)a)->cond);
        /* pasa la condicion a los nodos hijos */
        ((flow *)(((flow *)a)->tl))->cond = ((flow *)a)->cond;
        ((flow *)(((flow *)a)->el))->cond = ((flow *)a)->cond;
        /* evaluar caso */
        val = eval(((flow *)a)->el);
        if (!val->v.b) {
            /* evaluar otros casos */
            val = eval(((flow *)a)->tl);
        }
        return val;
        break;
    case NODE_CASE:
        val = eval(((flow *)a)->cond);
        /* evaluar valor del caso */
        val1 = eval(((flow *)a)->tl);
        /*si el caso es igual a la condicion */
        if ((evalNodeEq(val, val1))->v.b) {
            /* evaluar bloque de codigo */
            eval(((flow *)a)->el);
            val1->v.b = 1;
        } else {
            val1->v.b = 0;
        }
        return val1;
        break;
    case NODE_DEFAULT:
        eval(((flow *)a)->tl);
        break;
    /* list of statements */
    case NODE_FROM:
        if ((eval(((nodeFor *)a)->begin))->t == VALUE_INT && (eval(((nodeFor *)a)->end))->t == VALUE_INT) {
            int old_begin = (eval(((nodeFor *)a)->begin))->v.i;
            int begin = (eval(((nodeFor *)a)->begin))->v.i;
            int end   = (eval(((nodeFor *)a)->end))->v.i;
            int step = 1;
            if (((nodeFor *)a)->step != NULL) {
                step = (eval(((nodeFor *)a)->step))->v.i;
            }
            if (begin < end) {
                while (begin < end) {
                    eval(((nodeFor *)a)->stmts);
                    (eval(((nodeFor *)a)->begin))->v.i += step;
                    begin += step;
                }
            }
            if (begin > end) {
                while (begin > end) {
                    eval(((nodeFor *)a)->stmts);
                    (eval(((nodeFor *)a)->begin))->v.i -= step;
                    begin -= step;
                }
            }
            //restore begin value
            (eval(((nodeFor *)a)->begin))->v.i = old_begin;
        }
        return val;
        break;
    case NODE_BLOCK: {
        if (a->r) {
            if (a->l) {
                eval(a->l);
            }
            eval(a->r);
        } else {
            if (a->l) {
                eval(a->l);
            }
        }
        return val;
    }
    break;
    case NODE_RETURN: {
        if (a->l) {
            val = eval(a->l);
            longjmp(eval_fun, 1);
        }
        return val;
    }
    break;
    case NODE_BUILTIN_FUNCTION:
        v = callBuiltin((fnCall *)a);
        break;
    case NODE_USER_FUNCTION: {
        val = callUser((ufnCall *)a);
        return val;
    }
    break;
    case NODE_LIST_SYMBOLS:
        if (a->l) {
            val = eval(a->l);
        }
        return val;
        break;
    default:
        printf("nodo incorrecto %i\n", a->nodetype);
        break;
    }
    return val;
}

void imprimir(latValue *val)
{
    if (val != NULL) {
        switch (val->t) {
        case VALUE_BOOL:
            printf("%s\n", bool2str(val->v.b));
            break;
        case VALUE_INT:
            printf("%ld\n", val->v.i);
            break;
        case VALUE_CHAR:
            printf("%c\n", val->v.c);
            break;
        case VALUE_DOUBLE:
            printf("%g\n", val->v.d);
            break;
        case VALUE_STRING:
            printf("%s\n", val->v.s);
            break;
        case VALUE_NULL:
            printf("%s\n", "nulo");
            break;
        }
    }
}

latValue *callUser(ufnCall *f)
{
    struct symbol *fn = f->s; /* function name */
    symList *sl; /* dummy arguments */
    ast *args = f->l; /* actual arguments */
    latValue **oldval;
    latValue **newval; /* saved arg values */
    int nargs = 0;
    int i;
    if (!fn->func) {
        yyerror("llamada a funcion indefinida\n");
        return val;
    }
    /* count the arguments */
    sl = fn->syms;
    if (sl) {
        for (nargs = 0; sl; sl = sl->next) {
            nargs++;
        }
    }
    /* prepare to save them */
    oldval = malloc(nargs * sizeof(latValue));
    newval = malloc(nargs * sizeof(latValue));
    if (!oldval || !newval) {
        yyerror("sin espacio en %s", fn->name);
        return val;
    }
    /* evaluate the arguments */
    for (i = 0; i < nargs; i++) {
        if (!args) {
            yyerror("muy pocos argumentos en llamada a funcion");
            free(oldval);
            free(newval);
            return val;
        }
        if (args->nodetype == NODE_LIST_SYMBOLS) { /* if this is a list node */
            newval[i] = eval(args->l);
            args = args->r;
        } else { /* if it's the end of the list */
            /*newval[i] = eval(args);*/
            newval[i] = eval(args->l);
            args = NULL;
        }
    }
    /* save old values of dummies, assign new ones */
    sl = fn->syms;
    for (i = 0; i < nargs; i++) {
        struct symbol *s = sl->sym;
        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl->next;
    }
    free(newval);
    /* evaluate the function */
    if (fn->func) {
        if (!setjmp(eval_fun)) {
            val = eval(fn->func);
            /*printf("***!setjmp->%i\n", val->v.i);*/
        } else {
            /* put the real values of the dummies back */
            sl = fn->syms;
            for (i = 0; i < nargs; i++) {
                struct symbol *s = sl->sym;
                s->value = oldval[i];
                sl = sl->next;
            }
            free(oldval);
            return val;
        }
    }
    return val;
}
