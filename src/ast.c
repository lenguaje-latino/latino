/*
The MIT License (MIT)

Copyright (c) 2015 - Latino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <stdbool.h>
#include "latino.h"
#include "ast.h"
#include "vm.h"
#include "object.h"
#include "libmem.h"
#include "libstring.h"
#include "liblist.h"
#include "libio.h"

#define dbc(I, A, B, M) bcode[i++] = lat_bc(I, A, B, M)
#define pn(vm, N) i = nodo_analizar(vm, N, bcode, i)
#define fdbc(I, A, B, M) funcion_bcode[fi++] = lat_bc(I, A, B, M)
#define fpn(vm, N) fi = nodo_analizar(vm, N, funcion_bcode, fi)

ast *nodo_nuevo_operador(nodo_tipo nt, ast *l, ast *r)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    switch (nt)
    {
    case NODO_MAS_UNARIO:
    case NODO_SUMA:
    {
        a->l = nodo_nuevo_identificador("+", 1, 1);
    }
    break;
    case NODO_MENOS_UNARIO:
    case NODO_RESTA:
    {
        a->l = nodo_nuevo_identificador("-", 1, 1);
    }
    break;
    case NODO_MULTIPLICACION:
    {
        a->l = nodo_nuevo_identificador("*", 1, 1);
    }
    break;
    case NODO_DIVISION:
    {
        a->l = nodo_nuevo_identificador("/", 1, 1);
    }
    break;
    case NODO_MODULO:
    {
        a->l = nodo_nuevo_identificador("%", 1, 1);
    }
    break;
    case NODO_MAYOR_IGUAL:
    {
        a->l = nodo_nuevo_identificador(">=", 1, 1);
    }
    break;
    case NODO_MAYOR_QUE:
    {
        a->l = nodo_nuevo_identificador(">", 1, 1);
    }
    break;
    case NODO_MENOR_IGUAL:
    {
        a->l = nodo_nuevo_identificador("<=", 1, 1);
    }
    break;
    case NODO_MENOR_QUE:
    {
        a->l = nodo_nuevo_identificador("<", 1, 1);
    }
    break;
    case NODO_DESIGUALDAD:
    {
        a->l = nodo_nuevo_identificador("!=", 1, 1);
    }
    break;
    case NODO_IGUALDAD:
    {
        a->l = nodo_nuevo_identificador("==", 1, 1);
    }
    break;
    case NODO_NEGACION:
    {
        a->l = nodo_nuevo_identificador("!", 1, 1);
    }
    break;
    case NODO_Y:
    {
        a->l = nodo_nuevo_identificador("&&", 1, 1);
    }
    break;
    case NODO_O:
    {
        a->l = nodo_nuevo_identificador("||", 1, 1);
    }
    break;
    case NODO_CONCATENAR:
    {
        a->l = nodo_nuevo_identificador(".", 1, 1);
    }
    break;
    default:
        break;
    }
    if (nt == NODO_MENOS_UNARIO || nt == NODO_MAS_UNARIO)
    {
        a->r = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, nodo_nuevo_entero(0, 1, 1), l);
    }
    else if (nt == NODO_NEGACION)
    {
        a->r = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, l, NULL);
    }
    else
    {
        a->r = nodo_nuevo(NODO_FUNCION_ARGUMENTOS, l, r);
    }
    a->tipo = NODO_FUNCION_LLAMADA;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo(nodo_tipo nt, ast *l, ast *r)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = nt;
    a->l = l;
    a->r = r;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_entero(long i, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_ENTERO;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_ENTERO;
    val->v.i = i;
    a->valor = val;
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_decimal(double d, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_DECIMAL;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_DECIMAL;
    val->v.d = d;
    a->valor = val;
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_logico(int b, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_LOGICO;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_LOGICO;
    val->v.b = b;
    a->valor = val;
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_literal(char *c, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_LITERAL;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_LITERAL;
    a->valor = val;
    a->valor->v.c = __str_analizar(c, strlen(c));
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_cadena(const char *s, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_CADENA;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->v.s = __str_analizar(s, strlen(s));
    a->valor = val;
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_constante(char *s, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->v.s = __str_duplicar(s);
    a->valor = val;
    a->valor->es_constante = true;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_identificador(const char *s, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->v.s = __str_duplicar(s);
    a->valor = val;
    a->valor->es_constante = false;
    a->valor->num_linea = num_linea;
    a->valor->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_asignacion(ast *v, ast *s)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_ASIGNACION;
    a->l = v;
    a->r = s;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_asignacion_lista_elem(ast *exp, ast *id, ast *pos)
{
    nodo_lista_elem *a = (nodo_lista_elem*)__memoria_asignar(sizeof(nodo_lista_elem));
    a->tipo = NODO_LISTA_ASIGNAR_ELEMENTO;
    a->exp = exp;
    a->id = id;
    a->pos = pos;
    return (ast *)a;
}

ast *nodo_nuevo_asignacion_dicc_elem(ast *exp, ast *id, ast *llave)
{
    nodo_lista_elem *a = (nodo_lista_elem*)__memoria_asignar(sizeof(nodo_lista_elem));
    a->tipo = NODO_DICC_ASIGNAR_ELEMENTO;
    a->exp = exp;
    a->id = id;
    a->pos = llave;
    return (ast *)a;
}

ast *nodo_nuevo_si(ast *cond, ast *th, ast *el)
{
    nodo_si *a = (nodo_si*)__memoria_asignar(sizeof(nodo_si));
    a->tipo = NODO_SI;
    a->cond = cond;
    a->th = th;
    a->el = el;
    return (ast *)a;
}

ast *nodo_nuevo_mientras(ast *cond, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_MIENTRAS;
    a->l = cond;
    a->r = stmts;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_hacer(ast *cond, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_HACER;
    a->l = cond;
    a->r = stmts;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_BLOQUE;
    a->l = dec;
    a->r = nodo_nuevo_mientras(cond, nodo_nuevo(NODO_BLOQUE, stmts, inc));
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_funcion(ast *s, ast *syms, ast *func)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_ASIGNACION;
    a->l = nodo_nuevo(NODO_FUNCION_USUARIO, syms, func);
    a->r = s;
    a->valor = NULL;
    return a;
}

ast* nodo_nuevo_incluir(ast* ruta)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_INCLUIR;
    a->l = ruta;
    a->r = NULL;
    a->valor = NULL;
    return a;
}

void nodo_liberar(ast *a)
{
    if (a)
    {
        switch (a->tipo)
        {
        case NODO_BLOQUE:
        case NODO_LISTA_AGREGAR_ELEMENTO:
            if (a->r)
                nodo_liberar(a->r);
            if (a->l)
                nodo_liberar(a->l);
            break;
        default:
            if (a->tipo)
                __memoria_liberar(a->valor);
            __memoria_liberar(a);
            break;
        }
    }
}

ast* transformar_casos(ast* casos, ast* cond_izq){    
    if(casos == NULL){        
        return NULL;
    }        
    ast* caso = casos->l;        
    ast* cond = NULL;    
    if(caso->tipo == NODO_CASO){ 
        cond = nodo_nuevo_operador(NODO_IGUALDAD, cond_izq, caso->l);
    }    
    if(caso->tipo == NODO_DEFECTO){        
        cond = nodo_nuevo_operador(NODO_IGUALDAD, cond_izq, cond_izq);
    }       
    ast* nSi = nodo_nuevo_si(cond, caso->r, ((ast*)transformar_casos(casos->r, cond_izq)));    
    return nSi;
}

ast* transformar_elegir(ast* nodo_elegir){
    ast* cond_izq = nodo_elegir->l;
    ast* casos = nodo_elegir->r;
    ast* nSi = NULL;
    nSi = transformar_casos(casos, cond_izq);
    return nSi;
}

int nested = -1;
static int nodo_analizar(lat_vm *vm, ast *node, lat_bytecode *bcode, int i)
{
    int temp[8] = {0};
    lat_bytecode *funcion_bcode = NULL;
    int fi = 0;
    switch (node->tipo)
    {
    case NODO_INCLUIR:
    {
        //TODO: Incluir rutas con punto ej. incluir "lib.modulos.myModulo"
        char* archivo = node->l->valor->v.s;
        lat_objeto* mod = lat_cadena_nueva(vm, archivo);
        if (!__lista_existe_dato(vm->modulos, (void*)mod))
        {
            //encontrar el modulo en la ruta actual
            char dir_actual[MAX_PATH_LENGTH];
            getcwd(dir_actual, sizeof(dir_actual));
            strcat(dir_actual, PATH_SEP);
            strcat(dir_actual, archivo);
            if (!__str_termina_con(dir_actual, ".lat"))
            {
                strcat(dir_actual, ".lat");
            }
            if (__io_es_legible(dir_actual))
            {
                __lista_agregar(vm->modulos, mod);
                pn(vm, lat_analizar_archivo(dir_actual));
            }
            else
            {
                //sino existe buscar en el path_home de latino/lib
                char* latino_lib = getenv("LATINO_LIB");
                if (latino_lib != NULL)
                {
                    strcat(latino_lib, PATH_SEP);
                    strcat(latino_lib, archivo);
                    if (!__str_termina_con(latino_lib, ".lat"))
                    {
                        strcat(latino_lib, ".lat");
                    }
                    if (__io_es_legible(latino_lib))
                    {
                        __lista_agregar(vm->modulos, mod);
                        pn(vm, lat_analizar_archivo(latino_lib));
                    }
                }
            }
        }
    }
    break;
    case NODO_BLOQUE:
    {
        if (node->l)
        {
            //printf("procesando nodo_bloque->l\n");
            pn(vm, node->l);
        }
        if (node->r)
        {
            //printf("procesando nodo_bloque->r\n");
            pn(vm, node->r);
        }
    }
    break;
    case NODO_IDENTIFICADOR: /*GET: Obtiene el valor de la variable en la tabla de simbolos*/
    {
        dbc(OP_LOCALNS, 1, 0, NULL);
        lat_objeto *ret = lat_cadena_nueva(vm, node->valor->v.s);
        dbc(OP_STORESTR, 2, 0, ret);
        dbc(OP_GET, 2, 1, NULL);
        dbc(OP_MOV, 255, 2, NULL);
#if DEPURAR_AST
        printf("LOCALNS R1\n");
        printf("STORESTR R2 %s\n", ret->data.str);
        printf("GET R2 R1\n");
        printf("MOV R255 R2\n");
#endif
    }
    break;
    case NODO_ASIGNACION: /*SET: Asigna el valor de la variable en la tabla de simbolos*/
    {
        pn(vm, node->l);
        dbc(OP_PUSH, 255, 0, NULL);
#if DEPURAR_AST
        printf("PUSH R255 R0\n");
#endif
		    /*Nombre de la variable o funcion*/
        lat_objeto *ret = lat_cadena_nueva(vm, node->r->valor->v.s);
        if (ret->num_declared < 0)
        {
            ret->num_declared = 0;
        }
        ret->es_constante = node->r->valor->es_constante;
        ret->num_declared++;
        if (ret->es_constante && ret->num_declared > 1)
        {
            lat_error("Linea %d: %s", (node->r->valor->num_linea + 1),  "Intento de asignar un nuevo valor a una CONSTANTE ");
        }
    		//Si es una funcion contamos el numero de parametros que necesita
    		int num_params = 0;
    		if (node->l->tipo == NODO_FUNCION_USUARIO){
    			ast* tmp;
    			if (node->l->l->tipo == NODO_LISTA_PARAMETROS){
    				tmp = node->l->l;
    				while (tmp->r != NULL && tmp->r->tipo == NODO_LISTA_PARAMETROS){
    					tmp = tmp->r;
    					num_params++;
    				}
    				if (tmp->l->tipo){
    					num_params++;
    				}
    			}
    		}
    		ret->num_param = num_params;
        dbc(OP_LOCALNS, 1, 0, NULL);
        dbc(OP_POP, 255, 0, NULL);
        dbc(OP_SET, 255, 1, ret);
#if DEPURAR_AST
        printf("LOCALNS R1\n");
        printf("POP R255 R0\n");
        printf("SET R255 R1\n");        
#endif
    }
    break;
    case NODO_LITERAL:
    {
        lat_objeto *ret = lat_literal_nuevo(vm, node->valor->v.c);
        dbc(OP_STORELIT, 255, 0, ret);
#if DEPURAR_AST
        printf("STORELIT R255 %s\n", ret->data.str);
#endif
    }
    break;
    case NODO_ENTERO:
    {
        lat_objeto *ret = lat_entero_nuevo(vm, node->valor->v.i);
        dbc(OP_STOREINT, 255, 0, ret);
#if DEPURAR_AST
        printf("STOREINT R255 %ld\n", ret->data.i);
#endif
    }
    break;
    case NODO_DECIMAL:
    {
        lat_objeto *ret = lat_decimal_nuevo(vm, node->valor->v.d);
        dbc(OP_STOREDOUBLE, 255, 0, ret);
#if DEPURAR_AST
        printf("OP_STOREDOUBLE R255 %.14g\n", ret->data.d);
#endif
    }
    break;
    case NODO_CADENA:
    {
        lat_objeto *ret = lat_cadena_nueva(vm, node->valor->v.s);
        dbc(OP_STORESTR, 255, 0, ret);
#if DEPURAR_AST
        printf("STORESTR R255 %s\n", ret->data.str);
#endif
    }
    break;
    case NODO_LOGICO:
    {
        lat_objeto *ret = (node->valor->v.b == true) ? vm->objeto_verdadero : vm->objeto_falso;
        dbc(OP_STOREBOOL, 255, 0, ret);
#if DEPURAR_AST
        printf("STOREBOOL R255 %i\n", ret->data.b);
#endif
    }
    break;
    case NODO_SI:
    {
        nodo_si *nIf = ((nodo_si *)node);
        pn(vm, nIf->cond);
        dbc(OP_MOV, 2, 255, NULL);
        dbc(OP_MOV, 3, 255, NULL);
        dbc(OP_NOT, 2, 0, NULL);
        temp[0] = i;
        dbc(OP_NOP, 0, 0, NULL);
#if DEPURAR_AST
        printf("MOV R2 R255\n");
        printf("MOV R3 R255\n");
        printf("NOT\n");
        printf("NOP\n");
#endif
        pn(vm, nIf->th);
        bcode[temp[0]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEPURAR_AST
        printf("JMPIF R%i R2\n", i);
#endif
        if (nIf->el)
        {
            temp[1] = i;
            dbc(OP_NOP, 0, 0, NULL);
            pn(vm, nIf->el);
            bcode[temp[1]] = lat_bc(OP_JMPIF, i, 3, NULL);
#if DEPURAR_AST
            printf("NOP\n");
            printf("JMPIF R%i R3\n", i);
#endif
        }
    }
    break;
    case NODO_ELEGIR:
    {        
        /*transformar nodo elegir en nodos si*/
        ast* nSi = transformar_elegir(node);
        pn(vm, nSi);
    }
    break;
    case NODO_MIENTRAS:
    {
        temp[0] = i;
        pn(vm, node->l);
        dbc(OP_MOV, 2, 255, NULL);
        dbc(OP_NOT, 2, 0, NULL);
        temp[1] = i;
        dbc(OP_NOP, 0, 0, NULL);
#if DEPURAR_AST
        printf("MOV R2 R255\n");
        printf("NOT R2 R0\n");
        printf("NOP\n");
#endif
        pn(vm, node->r);
        dbc(OP_JMP, temp[0], 0, NULL);
        bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEPURAR_AST
        printf("JMP R%i\n", temp[0]);
        printf("JMPIF R%i R2\n", i);
#endif
    }
    break;
    case NODO_HACER:
    {
        pn(vm, node->r);
        temp[0] = i;
        pn(vm, node->l);
        dbc(OP_MOV, 2, 255, NULL);
        dbc(OP_NOT, 2, 0, NULL);
        temp[1] = i;
        dbc(OP_NOP, 0, 0, NULL);
#if DEPURAR_AST
        printf("MOV R2 R255\n");
        printf("NOT R2 R0\n");
        printf("NOP\n");
#endif
        pn(vm, node->r);
        dbc(OP_JMP, temp[0], 0, NULL);
        bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEPURAR_AST
        printf("JMP R%i\n", temp[0]);
        printf("JMPIF R%i R2\n", i);
#endif
    }
    break;
    case NODO_FUNCION_LLAMADA:
    {
        if (node->r)
        {
                pn(vm, node->r);
        }
        pn(vm, node->l);
        dbc(OP_CALL, 255, 0, NULL);
#if DEPURAR_AST
        printf("CALL R255\n");
#endif
    }
    break;
    case NODO_RETORNO:
    {
        pn(vm, node->l);
        dbc(OP_END, 0, 0, NULL);
#if DEPURAR_AST
        printf("END R255\n");
#endif
    }
    break;
    case NODO_FUNCION_ARGUMENTOS:
    {
/*#if DEPURAR_AST
            printf(">>INICIO NODO_FUNCION_ARGUMENTOS\n");
#endif*/
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_PUSH, 255, 0, NULL);
#if DEPURAR_AST
            printf("PUSH R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            //Soporte para recursion NODO_FUNCION_LLAMADA
            if (node->r->valor || node->r->tipo == NODO_FUNCION_LLAMADA)
            {
                dbc(OP_PUSH, 255, 0, NULL);
#if DEPURAR_AST
                printf("PUSH R255\n");
#endif
            }
        }
/*#if DEPURAR_AST
            printf("<<FIN NODO_FUNCION_ARGUMENTOS\n");
#endif*/
    }
    break;
    case NODO_LISTA_PARAMETROS:
    {
/*#if DEPURAR_AST
            printf(">>INICIO NODO_LISTA_PARAMETROS\n");
#endif*/
        if (node->l)
        {
            dbc(OP_LOCALNS, 1, 0, NULL);
            dbc(OP_POP, 2, 0, NULL);
            lat_objeto *ret = lat_clonar_objeto(vm, lat_cadena_nueva(vm, node->l->valor->v.s));
            dbc(OP_SET, 2, 1, ret);
#if DEPURAR_AST
            printf("LOCALNS R1\n");
            printf("POP R2\n");
            printf("SET R2 R1 %s\n", ret->data.str);
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
        }
/*#if DEPURAR_AST
            printf("<<FIN NODO_LISTA_PARAMETROS\n");
#endif*/
    }
    break;
    case NODO_FUNCION_USUARIO:
    {
        funcion_bcode = (lat_bytecode *)__memoria_asignar(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
        fi = 0;
        /* procesar lista de argumentos */
        if (node->l)
        {
            fpn(vm, node->l);
        }
        /* procesar instrucciones */
        fpn(vm, node->r);
        dbc(OP_FN, 255, 0, funcion_bcode);
#if DEPURAR_AST
        printf("FN R255\n");
#endif
        funcion_bcode = NULL;
        fi = 0;
    }
    break;
    case NODO_LISTA:
    {
        nested++;
        dbc(OP_STORELIST, nested, 0, NULL);
#if DEPURAR_AST
        printf("STORELIST R%i\n", nested);
#endif
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 255, nested, NULL);
#if DEPURAR_AST
            printf("MOV R255 R%i\n", nested);
#endif
        }
        nested--;
    }
    break;
    case NODO_LISTA_AGREGAR_ELEMENTO:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_PUSHLIST, nested, 255, NULL);
#if DEPURAR_AST
            printf("PUSHLIST R%i R255\n", nested);
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
        }
    }
    break;
    case NODO_LISTA_ASIGNAR_ELEMENTO:
    {
        nodo_lista_elem *elem = ((nodo_lista_elem *)node);
        if (elem->exp)
        {
            pn(vm, elem->exp);
            dbc(OP_MOV, 3, 255, NULL);
#if DEPURAR_AST
            printf("MOV R3 R255\n");
#endif
        }
        if (elem->id)
        {
            pn(vm, elem->pos);
            dbc(OP_MOV, 4, 255, NULL);
#if DEPURAR_AST
            printf("MOV R4 R255\n");
#endif
            pn(vm, elem->id);
            dbc(OP_LISTSETITEM, 255, 3, (void *)4);
#if DEPURAR_AST
            printf("LISTSETITEM R255 R3\n");
#endif
        }
    }
    break;
    case NODO_LISTA_OBTENER_ELEMENTO:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 3, 255, NULL);
#if DEPURAR_AST
            printf("MOV R3 R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_LISTGETITEM, 255, 3, NULL);
#if DEPURAR_AST
            printf("LISTGETITEM R55 R3\n");
#endif
        }
    }
    break;
    case NODO_DICCIONARIO:
    {
        nested++;
        dbc(OP_STOREDICT, nested, 0, NULL);
#if DEPURAR_AST
        printf("STOREDICT R%i\n", nested);
#endif
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 255, nested, NULL);
#if DEPURAR_AST
            printf("MOV R255 R%i\n", nested);
#endif
        }
        nested--;
    }
    break;
    case NODO_DICC_AGREGAR_ELEMENTO:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_PUSHDICT, nested, 255, NULL);
#if DEPURAR_AST
            printf("PUSHDICT R%i R255\n", nested);
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
        }
    }
    break;
    case NODO_DICC_ELEMENTO:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_PUSH, 255, 0, NULL);
#if DEPURAR_AST
            printf("PUSH R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_PUSH, 255, 0, NULL);
#if DEPURAR_AST
            printf("PUSH R255\n");
#endif
        }
        dbc(OP_PUSHDICTELEM, 0, 0, NULL);
#if DEPURAR_AST
        printf("OP_PUSHDICTELEM\n");
#endif
    }
    break;
    case NODO_DICC_ASIGNAR_ELEMENTO:
    {
        nodo_dicc_elem *elem = ((nodo_dicc_elem *)node);
        if (elem->exp)
        {
            pn(vm, elem->exp);
            dbc(OP_MOV, 3, 255, NULL);
#if DEPURAR_AST
            printf("MOV R3 R255\n");
#endif
        }
        if (elem->id)
        {
            pn(vm, elem->llave);
            dbc(OP_MOV, 4, 255, NULL);
#if DEPURAR_AST
            printf("MOV R4 R255\n");
#endif
            pn(vm, elem->id);
            dbc(OP_DICTSETITEM, 255, 3, (void*)4);
#if DEPURAR_AST
            printf("DICTITEM R255 R3\n");
#endif
        }
    }
    break;
    case NODO_DICC_OBTENER_ELEMENTO:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 3, 255, NULL);
#if DEPURAR_AST
            printf("MOV R3 R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_DICTGETITEM, 255, 3, NULL);
#if DEPURAR_AST
            printf("DICTGETITEM R255 R3\n");
#endif
        }
    }
    break;    
    default:
        printf("nodo_tipo:%i\n", node->tipo);
        return 0;
    }
    // printf("i = %i\n", i);
    return i;
}

lat_objeto *nodo_analizar_arbol(lat_vm *vm, ast *tree)
{
    lat_bytecode *bcode = (lat_bytecode *)__memoria_asignar(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    int i = nodo_analizar(vm, tree, bcode, 0);
    dbc(OP_END, 0, 0, NULL);
    nodo_liberar(tree);
    return lat_definir_funcion(vm, bcode);
}
