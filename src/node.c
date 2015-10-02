#include "node.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include "utils.h"

lat_node_val NULL_VALUE = {0};

lat_node_val lat_null_value()
{
    return NULL_VALUE;
}

lat_node_val lat_int_value(int i)
{
    lat_node_val r;
    r.ival = i;
    return r;
}

lat_node_val lat_double_value(double d)
{
    lat_node_val r;
    r.dval = d;
    return r;
}

lat_node_val lat_str_value(char *s)
{
    lat_node_val r;
    if (s != NULL) {
        memset((void *) r.strval, 0x0, 256);
        memcpy(r.strval, s, strlen(s));
    }
    return r;
}

lat_ast_node *lat_make_node(lat_node_ins ins, lat_ast_node *arg1, lat_ast_node *arg2, lat_node_val val)
{
    lat_ast_node *r;
    if ((r = (lat_ast_node *) malloc(sizeof(lat_ast_node)))) {
        r->ins = ins;
        r->arg1 = arg1;
        r->arg2 = arg2;
        r->val = val;
        return r;
    }
    log_err("malloc failure in make_node");
    exit(1);
}

lat_ast_node *lat_const_integer_node(int i)
{
    return lat_make_node(CONST_INT, NULL, NULL, lat_int_value(i));
}

lat_ast_node *lat_const_double_node(double d)
{
    return lat_make_node(CONST_DOUBLE, NULL, NULL, lat_double_value(d));
}

lat_ast_node *lat_const_string_node(char *s)
{
    return lat_make_node(CONST_STR, NULL, NULL, lat_str_value(s));
}

lat_ast_node *lat_const_bool_node(int i)
{
    return lat_make_node(CONST_BOOL, NULL, NULL, lat_int_value(i));
}

lat_ast_node *lat_identifier_node(char *name)
{
    return lat_make_node(IDENTIFIER, NULL, NULL, lat_str_value(name));
}
