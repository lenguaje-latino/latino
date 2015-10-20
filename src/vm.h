#ifndef _VM_H_
#define _VM_H_

typedef	struct lat_vm lat_vm;

#include "utils.h"
#include "object.h"

#define DEBUG_VM 0

typedef enum lat_ins {
	OP_END,
	OP_NOP,
	OP_PUSH,
	OP_POP,
	OP_GET,
	OP_SET,
	OP_STORECHAR,
	OP_STOREINT,
	OP_STOREDOUBLE,
	OP_STORESTR,
	OP_STOREBOOL,
	OP_STORELIST,
	OP_PUSHLIST,
	OP_POPLIST,
	OP_MOV,
	OP_GLOBALNS,
	OP_LOCALNS,
	OP_FN,
	OP_NS,
	OP_ENDNS,
	OP_JMP,
	OP_JMPIF,
	OP_CALL,
	OP_NOT,
} lat_ins;

/*

TODO:Remove
static char* ins_str[] = {
	"END", "NOP", "PUSH", "POP", "GET", "SET", 
	"STORE_CHAR", "STORE_INT", "STORE_DOUBLE", 
	"STORE_STR", "STORE_BOOL", "STORE_LIST", 
	"PUSH_LIST", "POP_LIST", "MOV", "GLOBAL_NS", 
	"LOCAL_NS", "FN", "NS", "END_NS", "JMP", 
	"JMP_IF", "CALL", "NOT"
};

char * getOpIns(enum lat_ins ins);
*/

typedef struct lat_bytecode {
	lat_ins ins;
	int a;
	int b;
	void *meta;
} lat_bytecode;

typedef struct lat_function {
	lat_bytecode *bcode;
	//lat_object *closure;
} lat_function;

struct lat_vm {
	list_node *stack;
	list_node *all_objects;
	lat_object *regs[256];
	lat_object *ctx_stack[256];
	int ctx_stack_pointer;
};

lat_vm *lat_make_vm();

void lat_push_stack(lat_vm *vm, lat_object *o);
lat_object *lat_pop_stack(lat_vm *vm);

void lat_push_list(lat_object *list, lat_object *o);
lat_object *lat_pop_list(lat_object *list);

void lat_push_ctx(lat_vm *vm);
void lat_pop_ctx(lat_vm *vm);

void lat_push_predefined_ctx(lat_vm *vm, lat_object *ctx);
lat_object *lat_pop_predefined_ctx(lat_vm *vm);

lat_object *lat_get_current_ctx(lat_vm *vm);

void lat_gc_add_object(lat_vm *vm, lat_object *o);
void lat_gc(lat_vm *vm);

lat_object *lat_define_function(lat_vm *vm, lat_bytecode *inslist);
lat_object *lat_define_c_function(lat_vm *vm, void(*function)(lat_vm *vm));

void lat_nth_list(lat_vm *vm);
void lat_print_list(lat_vm *vm, list_node *l);
void lat_print(lat_vm *vm);
void lat_clone(lat_vm *vm);
void lat_cons(lat_vm *vm);
void lat_add(lat_vm *vm);
void lat_sub(lat_vm *vm);
void lat_mul(lat_vm *vm);
void lat_div(lat_vm *vm);
void lat_mod(lat_vm *vm);
void lat_neq(lat_vm *vm);
void lat_eq(lat_vm *vm);
void lat_lt(lat_vm *vm);
void lat_lte(lat_vm *vm);
void lat_gt(lat_vm *vm);
void lat_gte(lat_vm *vm);

lat_object *lat_not(lat_vm *vm, lat_object *o);
lat_bytecode lat_bc(lat_ins i, int a, int b, void *meta);
void lat_call_func(lat_vm *vm, lat_object *func);

#endif // !_VM_H_
