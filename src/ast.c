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
#include <math.h>
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

ast *nodo_nuevo(nodo_tipo nt, ast *l, ast *r)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = nt;
    a->izq = l;
    a->der = r;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_logico(int b, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->tipo = VALOR_LOGICO;
    val->val.logico = b;
    a->valor = val;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_numerico(double d, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->tipo = VALOR_NUMERICO;
    val->val.numerico = d;
    a->valor = val;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_cadena(const char *s, int num_linea, int num_columna)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_VALOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->tipo = VALOR_CADENA;
    //val->val.cadena = __str_analizar(s, strlen(s));
    val->val.cadena = __str_duplicar(s);
    a->valor = val;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_identificador(const char *s, int num_linea, int num_columna, bool es_constante)
{    
    //printf("nodo_nuevo_identificador (%i, %i): %s, \n", num_linea, num_columna, s);
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor *val = (nodo_valor*)__memoria_asignar(sizeof(nodo_valor));
    val->tipo = VALOR_CADENA;
    val->val.cadena = __str_duplicar(s);
    val->es_constante = es_constante;
    a->valor = val;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast *nodo_nuevo_asignacion(ast *val, ast *sim)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_ASIGNACION;
    a->izq = val;
    a->der = sim;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_asignacion_lista_elem(ast *exp, ast *id, ast *pos)
{
    nodo_lista_elem *a = (nodo_lista_elem*)__memoria_asignar(sizeof(nodo_lista_elem));
    a->tipo = NODO_LISTA_ASIGNAR_ELEMENTO;
    a->expresion = exp;
    a->identificador = id;
    a->posicion = pos;
    return (ast *)a;
}

ast *nodo_nuevo_asignacion_dicc_elem(ast *exp, ast *id, ast *llave)
{
    nodo_lista_elem *a = (nodo_lista_elem*)__memoria_asignar(sizeof(nodo_lista_elem));
    a->tipo = NODO_DICC_ASIGNAR_ELEMENTO;
    a->expresion = exp;
    a->identificador = id;
    a->posicion = llave;
    return (ast *)a;
}

ast *nodo_nuevo_si(ast *cond, ast *th, ast *el)
{
    nodo_si *a = (nodo_si*)__memoria_asignar(sizeof(nodo_si));
    a->tipo = NODO_SI;
    a->condicion = cond;
    a->entonces = th;
    a->_sino = el;
    return (ast *)a;
}

ast *nodo_nuevo_mientras(ast *cond, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_MIENTRAS;
    a->izq = cond;
    a->der = stmts;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_hacer(ast *cond, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_HACER;
    a->izq = cond;
    a->der = stmts;
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_desde(ast *dec, ast *cond, ast *inc, ast *stmts)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_BLOQUE;
    a->izq = dec;
    a->der = nodo_nuevo_mientras(cond, nodo_nuevo(NODO_BLOQUE, stmts, inc));
    a->valor = NULL;
    return a;
}

ast *nodo_nuevo_funcion(ast *nombre, ast *parametros, ast *sentencias)
{
    nodo_funcion *a = (nodo_funcion*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_FUNCION_USUARIO;
    a->nombre = nombre;
    a->parametros = parametros;
    a->sentencias = sentencias;
    return (ast*)a;
}

ast* nodo_nuevo_incluir(ast* ruta)
{
    ast *a = (ast*)__memoria_asignar(sizeof(ast));
    a->tipo = NODO_INCLUIR;
    a->izq = ruta;
    a->der = NULL;
    a->valor = NULL;
    return a;
}

ast* nodo_reducir_constantes(nodo_tipo nt, ast* lhs, ast* rhs){
    //le dejamos el trabajo a la maquina virtual :)
    return nodo_nuevo(nt, lhs, rhs);
}

void nodo_liberar(ast *a)
{
    if (a)
    {
        switch (a->tipo)
        {
        case NODO_SI:
        {
            nodo_si* nsi = (nodo_si*) a;
            nodo_liberar(nsi->condicion);
            nodo_liberar(nsi->entonces);
            if (nsi->_sino)
                nodo_liberar(nsi->_sino);
            break;
        }
        case NODO_FUNCION_USUARIO:{
            nodo_funcion* fun = (nodo_funcion*) a;
            if(fun->parametros)
                nodo_liberar(fun->parametros);
            if(fun->sentencias)
                nodo_liberar(fun->sentencias);
            nodo_liberar(fun->nombre);
            break;
        }
        case NODO_LISTA_ASIGNAR_ELEMENTO:
        {
            nodo_lista_elem* nelem = (nodo_lista_elem*)a;
            nodo_liberar(nelem->expresion);
            nodo_liberar(nelem->identificador);
            nodo_liberar(nelem->posicion);
            break;
        }
        case NODO_DICC_ASIGNAR_ELEMENTO:
        {
            nodo_dicc_elem* nelem = (nodo_dicc_elem*)a;
            nodo_liberar(nelem->expresion);
            nodo_liberar(nelem->identificador);
            nodo_liberar(nelem->llave);
            break;
        }
        case NODO_IDENTIFICADOR:
        case NODO_VALOR:
            if(a->valor->tipo == VALOR_CADENA){
            __memoria_liberar(a->valor->val.cadena);
            }
            __memoria_liberar(a->valor);
        break;
        default:
            nodo_liberar(a->izq);
            nodo_liberar(a->der);
        }
        __memoria_liberar(a);
    }
}

ast* __transformar_casos(ast* casos, ast* cond_izq)
{
    if(casos == NULL)
    {
        return NULL;
    }
    ast* caso = casos->izq;
    ast* cond = NULL;
    if(caso->tipo == NODO_CASO)
    {
        cond = nodo_nuevo(NODO_IGUALDAD, cond_izq, caso->izq);
    }
    if(caso->tipo == NODO_DEFECTO)
    {
        cond = nodo_nuevo(NODO_IGUALDAD, cond_izq, cond_izq);
    }
    ast* nSi = nodo_nuevo_si(cond, caso->der, ((ast*)__transformar_casos(casos->der, cond_izq)));
    return nSi;
}

static ast* __transformar_elegir(ast* nodo_elegir)
{
    ast* cond_izq = nodo_elegir->izq;
    ast* casos = nodo_elegir->der;
    ast* nSi = NULL;
    nSi = __transformar_casos(casos, cond_izq);
    return nSi;
}

static int __contar_num_parargs(ast* node, nodo_tipo nt){
    ast* tmp;
    int num_params = 0;
    if(node){
        if (node->tipo == nt)
        {
            tmp = node;
            while (tmp->der != NULL && tmp->der->tipo == nt)
            {
                tmp = tmp->der;
                num_params++;
            }
            if (tmp->izq->tipo)
            {
                num_params++;
            }
        }
    }
    return num_params;
}

static int nodo_analizar(lat_mv *vm, ast *node, lat_bytecode *bcode, int i)
{
    int temp[4] = {0};
    lat_bytecode *funcion_bcode = NULL;
    int fi = 0;
    switch (node->tipo)
    {
    case NODO_INCLUIR:
    {
        //TODO: Incluir rutas con punto ej. incluir "lib.modulos.myModulo"
        char* archivo = node->izq->valor->val.cadena;
        lat_objeto* mod = lat_cadena_nueva(vm, archivo);
        lista *modulos = __lista(vm->modulos);
        int status;
        if (!__lista_contiene_valor(modulos, (void*)mod))
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
                __lista_apilar(modulos, mod);
                pn(vm, lat_analizar_archivo(dir_actual, &status));
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
                        __lista_apilar(modulos, mod);
                        pn(vm, lat_analizar_archivo(latino_lib, &status));
                    }
                }
            }
        }
    }
    break;
    case NODO_BLOQUE:
    {
        if (node->izq){
            pn(vm, node->izq);
        }
        if (node->der){
            pn(vm, node->der);
        }
    }
    break;
    case NODO_IDENTIFICADOR: /*GET: Obtiene el valor de la variable en la tabla de simbolos*/
    {
        lat_objeto *o = lat_cadena_nueva(vm, node->valor->val.cadena);
        o->num_linea = node->num_linea;
        o->num_columna = node->num_columna;
        o->es_constante = node->valor->es_constante;
        dbc(LOAD_NAME, 0, 0, o);
    }
    break;
    case NODO_ASIGNACION: /*SET: Asigna el valor de la variable en la tabla de simbolos*/
    {
        pn(vm, node->izq);
        lat_objeto *o = lat_cadena_nueva(vm, node->der->valor->val.cadena);
        o->num_linea = node->der->num_linea;
        o->num_columna = node->der->num_columna;        
        o->es_constante = node->der->valor->es_constante;
        dbc(STORE_NAME, 0, 0, o);
    }
    break;
    case NODO_VALOR:
    {
        lat_objeto *o = NULL;
        if(node->valor->tipo == VALOR_LOGICO)
            o = (node->valor->val.logico == true) ? vm->objeto_verdadero : vm->objeto_falso;
        if(node->valor->tipo == VALOR_NUMERICO)
            o = lat_numerico_nuevo(vm, node->valor->val.numerico);
        if(node->valor->tipo == VALOR_CADENA)
            o = lat_cadena_nueva(vm, node->valor->val.cadena);
        o->num_linea = node->num_linea;
        o->num_columna = node->num_columna;
        dbc(LOAD_CONST, 0, 0, o);
    }
    break;
    case NODO_MAS_UNARIO:
    {
        pn(vm, node->izq);
    }
    break;
    case NODO_MENOS_UNARIO:
    {
        pn(vm, node->izq);
        dbc(UNARY_MINUS, 0, 0, NULL);
    }
    break;
    case NODO_INC:
    {
        lat_objeto *o = lat_cadena_nueva(vm, node->izq->valor->val.cadena);
        o->num_linea = node->num_linea;
        o->num_columna = node->num_columna;
        o->es_constante = node->izq->valor->es_constante;
        dbc(INC, 0, 0, o);
    }
    break;
    case NODO_DEC:
    {        
        lat_objeto *o = lat_cadena_nueva(vm, node->izq->valor->val.cadena);
        o->num_linea = node->num_linea;
        o->num_columna = node->num_columna;
        o->es_constante = node->izq->valor->es_constante;
        dbc(DEC, 0, 0, o);
    }
    break;
    case NODO_SUMA:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_ADD, 0, 0, NULL);
    }
    break;
    case NODO_RESTA:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_SUB, 0, 0, NULL);
    }
    break;
    case NODO_MULTIPLICACION:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_MUL, 0, 0, NULL);
    }
    break;
    case NODO_DIVISION:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_DIV, 0, 0, NULL);
    }
    break;
    case NODO_MODULO:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_MOD, 0, 0, NULL);
    }
    break;
    case NODO_MAYOR_QUE:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_GT, 0, 0, NULL);
    }
    break;
    case NODO_MAYOR_IGUAL:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_GE, 0, 0, NULL);
    }
    break;
    case NODO_MENOR_QUE:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_LT, 0, 0, NULL);
    }
    break;
    case NODO_MENOR_IGUAL:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_LE, 0, 0, NULL);
    }
    break;
    case NODO_IGUALDAD:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_EQ, 0, 0, NULL);
    }
    break;
    case NODO_DESIGUALDAD:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_NEQ, 0, 0, NULL);
    }
    break;
    case NODO_Y:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_AND, 0, 0, NULL);
    }
    break;
    case NODO_O:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(OP_OR, 0, 0, NULL);
    }
    break;
    case NODO_NO:
    {
        pn(vm, node->izq);
        dbc(OP_NOT, 0, 0, NULL);
    }
    break;
    case NODO_CONCATENAR:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(CONCAT, 0, 0, NULL);
    }
    break;
    case NODO_SI:
    {
        nodo_si *nIf = ((nodo_si *)node);
        pn(vm, nIf->condicion);
        temp[0] = i;
        dbc(NOP, 0, 0, NULL);
        pn(vm, nIf->entonces);
        temp[1] = i;
        dbc(NOP, 0, 0, NULL);
        temp[2] = i;
        if(nIf->_sino){
            pn(vm, nIf->_sino);
        }
        temp[3] = i;
        bcode[temp[0]] = lat_bc(POP_JUMP_IF_FALSE, (temp[2]-1), 0, NULL);
        bcode[temp[1]] = lat_bc(JUMP_ABSOLUTE, (temp[3]-1), 0, NULL);
    }
    break;
    case NODO_ELEGIR:
    {
        //transformar nodo elegir en nodos si
        ast* nSi = __transformar_elegir(node);
        pn(vm, nSi);
    }
    break;
    case NODO_MIENTRAS:
    {
        dbc(SETUP_LOOP, 0, 0, NULL);
        temp[0] = i;
        pn(vm, node->izq);
        temp[1] = i;
        dbc(NOP, 0, 0, NULL);
        pn(vm, node->der);
        dbc(JUMP_ABSOLUTE, (temp[0] -1), 0, NULL);
        dbc(POP_BLOCK, 0, 0, NULL);
        bcode[temp[1]] = lat_bc(POP_JUMP_IF_FALSE, (i-1), 0, NULL);
    }
    break;
    case NODO_HACER:
    {
        dbc(SETUP_LOOP, 0, 0, NULL);
        temp[0] = i;
        pn(vm, node->der);
        pn(vm, node->izq);
        temp[1] = i;
        dbc(NOP, 0, 0, NULL);
        dbc(POP_BLOCK, 0, 0, NULL);
        bcode[temp[1]] = lat_bc(POP_JUMP_IF_TRUE, (temp[0]-1), 0, NULL);
    }
    break;
    case NODO_FUNCION_LLAMADA:
    {
        //argumentos
        if (node->der)
        {
            pn(vm, node->der);
        }
        //nombre funcion
        pn(vm, node->izq);        
        int num_args = __contar_num_parargs(node->der, NODO_FUNCION_ARGUMENTOS);
        if(node->izq->tipo == NODO_ATRIBUTO){
            num_args++;
        }
        dbc(CALL_FUNCTION, num_args, 0, NULL);
    }
    break;
    case NODO_RETORNO:
    {
        pn(vm, node->izq);
        dbc(RETURN_VALUE, 0, 0, NULL);
    }
    break;
    case NODO_FUNCION_ARGUMENTOS:
    {
        if (node->izq)
        {
            pn(vm, node->izq);
        }
        if (node->der)
        {
            pn(vm, node->der);
            if (node->der->valor || node->der->tipo == NODO_FUNCION_LLAMADA)
            {
                //se agrega para soporte recursivo
                int num_args = __contar_num_parargs(node->der->izq, NODO_FUNCION_ARGUMENTOS);
                dbc(CALL_FUNCTION, num_args, 0, NULL);
            }
        }        
    }
    break;
    case NODO_ATRIBUTO:{
        //pn(vm, node->der);        
        pn(vm, node->izq);
        lat_objeto *o = lat_cadena_nueva(vm, node->der->valor->val.cadena);
        o->num_linea = node->der->num_linea;
        o->num_columna = node->der->num_columna;
        o->es_constante = node->der->valor->es_constante;
        dbc(LOAD_ATTR, 0, 0, o);
    }
    break;
    case NODO_FUNCION_PARAMETROS:
    {           
        if (node->izq)
        {
            lat_objeto *o = lat_cadena_nueva(vm, node->izq->valor->val.cadena);
            dbc(STORE_NAME, 0, 0, o);
        }        
        if (node->der)
        {
            pn(vm, node->der);
        }
    }
    break;
    case NODO_FUNCION_USUARIO:
    {
        nodo_funcion *fun = (nodo_funcion*)node;
        funcion_bcode = (lat_bytecode *)__memoria_asignar(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
        fi = 0;
        // procesar lista de parametros
        if (fun->parametros)
        {
            fpn(vm, fun->parametros);
        }
        // procesar instrucciones
        fpn(vm, fun->sentencias);
        fdbc(RETURN_VALUE, 0, 0, NULL);
        funcion_bcode = __memoria_reasignar(funcion_bcode, sizeof(lat_bytecode) * (fi+1));
        dbc(MAKE_FUNCTION, 0, 0, (void*)funcion_bcode);
        funcion_bcode = NULL;
        fi = 0;
        lat_objeto *o = lat_cadena_nueva(vm, fun->nombre->valor->val.cadena);
        o->num_linea = fun->nombre->num_linea;
        o->num_columna = fun->nombre->num_columna;
        o->num_params = __contar_num_parargs(fun->parametros, NODO_FUNCION_PARAMETROS);
        o->nombre_cfun = __str_duplicar(fun->nombre->valor->val.cadena);
        dbc(STORE_NAME, 0, 0, o);
    }
    break;
    case NODO_LISTA:
    {   
        int num_params = 0;
        if (node->izq)
        {
            pn(vm, node->izq);           
            num_params = __contar_num_parargs(node->izq, NODO_LISTA_AGREGAR_ELEMENTO);            
        }        
        dbc(BUILD_LIST, num_params, 0, NULL);
    }
    break;
    case NODO_LISTA_AGREGAR_ELEMENTO:
    {    
        if (node->izq)
        {
            pn(vm, node->izq);
        } 
        if (node->der)
        {
            pn(vm, node->der);
        }        
    }
    break;
    case NODO_LISTA_ASIGNAR_ELEMENTO:
    {
        nodo_lista_elem* nl = (nodo_lista_elem*)node; 
        pn(vm, nl->expresion);
        pn(vm, nl->identificador);        
        pn(vm, nl->posicion);
        dbc(STORE_SUBSCR, 0, 0, NULL);
    }
    break;
    case NODO_LISTA_OBTENER_ELEMENTO:
    {
        pn(vm, node->izq);
        pn(vm, node->der);
        dbc(BINARY_SUBSCR, 0, 0, NULL);
    }
    break;
    case NODO_DICCIONARIO:
    {
    }
    break;
    case NODO_DICC_AGREGAR_ELEMENTO:
    {
    }
    break;
    case NODO_DICC_ELEMENTO:
    {
    }
    break;
    case NODO_DICC_ASIGNAR_ELEMENTO:
    {
    }
    break;
    case NODO_DICC_OBTENER_ELEMENTO:
    {
    }
    break;
    default:
        printf("ERROR node->tipo:%i\n", node->tipo);
        return 0;
    }
    return i;
}

static void __mostrar_bytecode(lat_bytecode *bcode){
#if DEPURAR_AST
    lat_bytecode *inslist = bcode;
    lat_bytecode cur;
    lat_objeto *o = NULL;
    int pos;

    for (pos = 0, cur = inslist[pos]; cur.ins &&cur.ins != HALT; cur = inslist[++pos])
    {

        printf("%i\t", pos);
        switch (cur.ins)
        {
            case HALT:
                return;
                break;
            case NOP:
            case UNARY_MINUS:
            case BINARY_ADD:
            case BINARY_SUB:
            case BINARY_MUL:
            case BINARY_DIV:
            case BINARY_MOD:
            case OP_GT:
            case OP_GE:
            case OP_LT:
            case OP_LE:
            case OP_EQ:
            case OP_NEQ:
            case OP_AND:
            case OP_OR:
            case OP_NOT:
            case OP_INC:
            case OP_DEC:
            case CONCAT:
            case SETUP_LOOP:
            case POP_BLOCK:            
            case RETURN_VALUE:            
            case STORE_SUBSCR:
            case BINARY_SUBSCR:
                printf("%s\n", __obtener_bytecode_nombre(cur.ins));
            break;
            case CALL_FUNCTION:{                
                printf("CALL_FUNCTION\t%i\n", cur.a);
            }
            break;
            case LOAD_ATTR: {
                o = (lat_objeto*)cur.meta;
                printf("LOAD_ATTR\t(%s)\n", __objeto_a_cadena(o));
            }
            break;
            case LOAD_CONST:{
                o = (lat_objeto*)cur.meta;
                printf("LOAD_CONST\t(%s)\n", __objeto_a_cadena(o));
            } break;
            case LOAD_NAME: {
                o = (lat_objeto*)cur.meta;
                printf("LOAD_NAME \t(%s)\n", __objeto_a_cadena(o));
            } break;
            case STORE_NAME: {
                o = (lat_objeto*)cur.meta;
                printf("STORE_NAME\t(%s)\n", __objeto_a_cadena(o));
            } break;
            case JUMP_ABSOLUTE:{
                printf("JUMP_ABSOLUTE\t(%i)\n", (cur.a+1));
            }break;
            case POP_JUMP_IF_FALSE:{
                printf("POP_JUMP_IF_FALSE\t(%i)\n", (cur.a+1));
            }break;
            case POP_JUMP_IF_TRUE:{
                printf("POP_JUMP_IF_TRUE\t(%i)\n", (cur.a+1));
            }break;
            case INC:{
                o = (lat_objeto*)cur.meta;
                printf("INC\t(%s)\n", __objeto_a_cadena(o));
            }break;
            case DEC:{
                o = (lat_objeto*)cur.meta;
                printf("DEC\t(%s)\n", __objeto_a_cadena(o));
            }break;
            case MAKE_FUNCTION:{
                printf("MAKE_FUNCTION\n");
                printf("-------------------------------\n");
                __mostrar_bytecode(cur.meta);
                printf("-------------------------------\n");
            }break;
            case BUILD_LIST: {
                printf("BUILD_LIST\t%i\n", cur.a);
            }break;
        }
    }
#endif
}

lat_objeto *nodo_analizar_arbol(lat_mv *vm, ast *tree)
{
    lat_bytecode *bcode = (lat_bytecode *)__memoria_asignar(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    int i = nodo_analizar(vm, tree, bcode, 0);
    dbc(HALT, 0, 0, NULL);
    __memoria_reasignar(bcode, sizeof(lat_bytecode) * (i+1));
    __mostrar_bytecode(bcode);
    return lat_definir_funcion(vm, bcode);
}
