#ifndef _NODE_H_
#define _NODE_H_

typedef enum lat_node_ins {
	STATEMENT_LIST,
	BLOCK,
	IDENTIFIER,
	NS_VAR,
	GGET,
	GET,
	SET,
	GSET,
	CALL,
	FUNC_ARGS,
	CONST_INT,
	CONST_DOUBLE,
	CONST_STR,
	CONST_BOOL,
	CONST_LIST,
	LIST_BODY,
	IF,
	WHILE,
	FN,
	PARAM_LIST,
	RET,
	NS
} lat_node_ins;

typedef union lat_node_val {
	int ival;
	double dval;
	char strval[256];
} lat_node_val;

typedef struct lat_ast_node {
	lat_node_ins ins;
	struct lat_ast_node *arg1;
	struct lat_ast_node *arg2;
	lat_node_val val;
} lat_ast_node;

/*
typedef union YYSTYPE {
	int token;
	lat_ast_node *node;
} YYSTYPE;
*/

lat_node_val lat_null_value();
lat_node_val lat_int_value(int i);
lat_node_val lat_double_value(double d);
lat_node_val lat_str_value(char *s);

lat_ast_node *lat_make_node(lat_node_ins ins, lat_ast_node *arg1, lat_ast_node *arg2, lat_node_val val);

lat_ast_node *lat_const_integer_node(int i);
lat_ast_node *lat_double_integer_node(double d);
lat_ast_node *lat_const_string_node(char *s);
lat_ast_node *lat_const_bool_node(int i);
lat_ast_node *lat_identifier_node(char *name);

#endif
