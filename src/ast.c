ast* nodo_nuevo(nodo_tipo tipoNodo, ast* izquierdo, ast* derecho, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo: %i\n", nt);
    ast* a = (ast*)malloc(sizeof(ast));
    a->tipo = tipoNodo;
    a->izquierdo = izquierdo;
    a->derecho = derecho;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast* nodo_nuevo_op(char* operador, ast* izquierdo, ast* derecho, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_op: %s\n", op);
    ast_op* a = (ast_op*)malloc(sizeof(ast_op));
    a->tipo = NODO_OPERADOR;
    //a->operador = nodo_strdup0(op);
    a->operador = operador;
    a->izquierdo = izquierdo;
    a->derecho = derecho;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_entero(long entero, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, entero: %ld\n", num_linea, num_columna, i);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_VALOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_ENTERO;
    val->entero = entero;
    val->cadena = NULL;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_numerico(double numerico, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, numerico: %.14g\n", num_linea, num_columna, d);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_VALOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_NUMERICO;
    val->numerico = numerico;
    val->cadena = NULL;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_logico(int logico, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, logico: %i\n", num_linea, num_columna, b);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_VALOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_LOGICO;
    val->logico = logico;
    val->cadena = NULL;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_literal(char* literal, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, literal: %s\n", num_linea, num_columna, s);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_VALOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_LITERAL;
    val->cadena = nodo_strdup0(literal);
    //val->cadena = s;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_cadena(char* cadena, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, cadena: %s\n", num_linea, num_columna, s);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_VALOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->cadena = nodo_strdup0(cadena);
    //val->cadena = s;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_constante(char* identificador, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, constante: %s\n", num_linea, num_columna, s);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->cadena = nodo_strdup0(identificador);
    //val->cadena = s;
    a->valor = val;
    a->valor->es_constante = true;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_identificador(char* identificador, int num_linea, int num_columna)
{
    //printf("linea %i, columna %i, identificador: %s\n", num_linea, num_columna, s);
    ast_valor* a = (ast_valor*)malloc(sizeof(ast_valor));
    a->tipo = NODO_IDENTIFICADOR;
    nodo_valor* val = (nodo_valor*)malloc(sizeof(nodo_valor));
    val->t = VALOR_CADENA;
    val->cadena = nodo_strdup0(identificador);
    //val->cadena = s;
    a->valor = val;
    a->valor->es_constante = false;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_asignacion(ast* identificadord, ast* expresion, int num_linea, int num_columna)
{
    ast* a = (ast*)malloc(sizeof(ast));
    a->tipo = NODO_ASIGNACION;
    a->izquierdo = identificadord;
    a->derecho = expresion;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast* nodo_nuevo_asignacion_lista_elem(ast* identificador, ast* expresion, ast* pos, int num_linea, int num_columna)
{
    ast_lista_elem* a = (ast_lista_elem*)malloc(sizeof(ast_lista_elem));
    a->tipo = NODO_LISTA_ASIGNAR_ELEMENTO;
    a->identificador = identificador;
    a->expresion = expresion;
    a->posicion = pos;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_asignacion_dicc_elem(ast* identificador, ast* expresion, ast* llave, int num_linea, int num_columna)
{
    ast_dicc_elem* a = (ast_dicc_elem*)malloc(sizeof(ast_dicc_elem));
    a->tipo = NODO_DICC_ASIGNAR_ELEMENTO;
    a->identificador = identificador;
    a->expresion = expresion;
    a->llave = llave;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_si(ast* condicion, ast* entonces, ast* sino, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_si\n");
    ast_si* a = (ast_si*)malloc(sizeof(ast_si));
    a->tipo = NODO_SI;
    a->condicion = condicion;
    a->entonces = entonces;
    a->sino = sino;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_mientras(ast* condicion, ast* sentencias, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_mientras\n");
    ast* a = (ast*)malloc(sizeof(ast));
    a->tipo = NODO_MIENTRAS;
    a->izquierdo = condicion;
    a->derecho = sentencias;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast* nodo_nuevo_repetir(ast* condicion, ast* sentencias, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_repetir\n");
    ast* a = (ast*)malloc(sizeof(ast));
    a->tipo = NODO_REPETIR;
    a->izquierdo = condicion;
    a->derecho = sentencias;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

ast* nodo_nuevo_por(ast* identificador, ast* iterable, ast* sentencias, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_por\n");
    ast_por* a = (ast_por*)malloc(sizeof(ast_por));
    a->tipo = NODO_POR;
    a->identificador = identificador;
    a->iterable = iterable;
    a->sentencias = sentencias;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*) a;
}

ast* nodo_nuevo_funcion(ast* identificador, ast* parametros, ast* sentencias, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_funcion\n");
    ast_funcion* a = (ast_funcion*)malloc(sizeof(ast_funcion));
    a->tipo = NODO_FUNCION_USUARIO;
    a->nombre = identificador;
    a->parametros = parametros;
    a->sentencias = sentencias;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return (ast*)a;
}

ast* nodo_nuevo_incluir(ast* ruta, int num_linea, int num_columna)
{
    //printf("linea 0, columna 0, nodo_nuevo_incluir\n");
    ast* a = (ast*)malloc(sizeof(ast));
    a->tipo = NODO_INCLUIR;
    a->izquierdo = ruta;
    a->derecho = NULL;
    a->num_linea = num_linea;
    a->num_columna = num_columna;
    return a;
}

void nodo_liberar(ast* a)
{
    if (a)
    {
        //printf("liberando nodo tipo: %i\n", a->tipo);
        switch (a->tipo)
        {
        case NODO_OPERADOR:
        {
            ast_op* op = (ast_op*) a;
            if (op->derecho)
                nodo_liberar(op->derecho);
            if (op->izquierdo)
                nodo_liberar(op->izquierdo);
        }
        break;
        case NODO_SI:
        {
            ast_si* nsi = (ast_si*) a;
            nodo_liberar(nsi->condicion);
            nodo_liberar(nsi->entonces);
            if (nsi->sino)
                nodo_liberar(nsi->sino);
        }
        break;
        case NODO_POR:
        {
            ast_por* npor = (ast_por*) a;
            nodo_liberar(npor->identificador);
            nodo_liberar(npor->iterable);
            nodo_liberar(npor->sentencias);
        }
        break;
        case NODO_FUNCION_USUARIO:
        {
            ast_funcion* nfun = (ast_funcion*)a;
            nodo_liberar(nfun->nombre);
            nodo_liberar(nfun->parametros);
            nodo_liberar(nfun->sentencias);
        }
        break;
        case NODO_LISTA_ASIGNAR_ELEMENTO:
        {
            ast_lista_elem* nelem = (ast_lista_elem*)a;
            nodo_liberar(nelem->expresion);
            nodo_liberar(nelem->identificador);
            nodo_liberar(nelem->posicion);
        }
        break;
        case NODO_DICC_ASIGNAR_ELEMENTO:
        {
            ast_dicc_elem* nelem = (ast_dicc_elem*)a;
            nodo_liberar(nelem->expresion);
            nodo_liberar(nelem->identificador);
            nodo_liberar(nelem->llave);
        }
        break;
        case NODO_IDENTIFICADOR:
        {
            ast_valor* v = (ast_valor*)a;
            if (v->valor->cadena)
                free(v->valor->cadena);
            if (v->valor)
                free(v->valor);
        }
        break;
        case NODO_VALOR:
        {
            ast_valor* v = (ast_valor*)a;
            if (v->valor->cadena)
                free(v->valor->cadena);
            free(v->valor);
        }
        break;
        default:
        {            
            if (a->tipo >= 0){
                if (a->izquierdo)
                    nodo_liberar(a->izquierdo);
                if (a->derecho)
                    nodo_liberar(a->derecho);
            }
        }
        break;
        }
        if (a->tipo >= 0){
            free(a);
        }
    }
}

static void pintar_espacios(int num, int ident)
{
    int i;
    for (i = 0; i < num; ++i)
    {
        if(i % ident == 0)
            printf("|");
        else
            printf(" ");
    }
}

static void nodo_mostrar_recursivo(ast* a, int ident, int nivel)
{
    int espacios = ident * nivel;
    if (a)
    {
        //printf("formateando tipo: %i\n", a->tipo);
        switch (a->tipo)
        {
        case NODO_ASIGNACION:
        {
            pintar_espacios(espacios, ident);
            printf("`-VarDecl <linea:%i, %i> ", a->num_linea, a->num_columna);
            ast_valor* val = (ast_valor*)a->izquierdo;
            printf("%s\n", val->valor->cadena);
            nodo_mostrar_recursivo(a->derecho, ident, nivel+1);
        }
        break;
        case NODO_OPERADOR:
        {
            ast_op* op = (ast_op *)a;
            pintar_espacios(espacios, ident);
            if (op->derecho)
                printf("`-BinaryOperator <linea: %i, %i> %s\n", op->num_linea, op->num_columna, op->operador);
            else
                printf("`-UnaryOperator <linea: %i, %i> %s\n", op->num_linea, op->num_columna, op->operador);
            nodo_mostrar_recursivo(op->izquierdo, ident, nivel + 1);
            if (op->derecho)
            {
                nodo_mostrar_recursivo(op->derecho, ident, nivel + 1);
            }
        }
        break;
        case NODO_IDENTIFICADOR:
        {
            ast_valor *val = (ast_valor*)a;
            pintar_espacios(espacios, ident);
            printf("`-DeclRef <linea: %i, %i> ", val->num_linea, val->num_columna);
            printf("%s\n", val->valor->cadena);
        }
        break;
        case NODO_VALOR:
        {
            ast_valor *val = (ast_valor*)a;
            pintar_espacios(espacios, ident);
            if (val->valor->t == VALOR_LOGICO)
            {
                if (val->valor->logico)
                    printf("`-BooleanLiteral <linea: %i, %i> verdadero\n", val->num_linea, val->num_columna);
                else
                    printf("`-BooleanLiteral <linea: %i, %i> falso\n", val->num_linea, val->num_columna);
            }
            else if (val->valor->t == VALOR_ENTERO)
            {
                printf("`-LongLiteral <linea: %i, %i> %ld\n", val->num_linea, val->num_columna, val->valor->entero);
            }
            else if (val->valor->t == VALOR_NUMERICO)
            {
                printf("`-DoubleLiteral <linea: %i, %i> %.14g\n", val->num_linea, val->num_columna, val->valor->numerico);
            }
            else if (val->valor->t == VALOR_CADENA)
            {
                printf("`-StringLiteral <linea: %i, %i> \"%s\"\n", val->num_linea, val->num_columna, val->valor->cadena);
            }
            else if (val->valor->t == VALOR_LITERAL)
            {
                printf("`-StringLiteral <linea: %i, %i> \'%s\'\n", val->num_linea, val->num_columna, val->valor->cadena);
            }
        }
        break;
        /*case NODO_BLOQUE:
        {
            if (a->izquierdo)
                nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            if (a->derecho)
                nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }
        break;*/
        case NODO_SI:
        {
            ast_si* nsi = (ast_si*) a;
            pintar_espacios(espacios, ident);
            printf("`-IfStat <linea: %i, %i>\n", nsi->num_linea, nsi->num_columna);
            nodo_mostrar_recursivo(nsi->condicion, ident, nivel+1);
            nodo_mostrar_recursivo(nsi->entonces, ident, nivel+1);
            if (nsi->sino)
            {
                nodo_mostrar_recursivo(nsi->sino, ident, nivel+1);
            }
        }
        break;
        case NODO_MIENTRAS:
        {
            pintar_espacios(espacios, ident);
            printf("`-WhileStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel+1);
            nodo_mostrar_recursivo(a->derecho, ident, nivel+1);
        }
        break;
        case NODO_REPETIR:
        {
            pintar_espacios(espacios, ident);
            printf("`-RepeatStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel+1);
            nodo_mostrar_recursivo(a->derecho, ident, nivel+1);
        }
        break;
        case NODO_POR:
        {
            ast_por* np = (ast_por*)a;
            pintar_espacios(espacios, ident);
            printf("`-ForStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(np->identificador, ident, nivel+1);
            nodo_mostrar_recursivo(np->iterable, ident, nivel+1);
            nodo_mostrar_recursivo(np->sentencias, ident, nivel+1);
        }
        break;
        case NODO_FUNCION_PARAMETROS:
        {
            pintar_espacios(espacios, ident);
            printf("`-ParmVarDecl <linea: %i, %i> ", a->num_linea, a->num_columna);
            ast_valor* val = (ast_valor*)a->izquierdo;
            printf("%s\n", val->valor->cadena);
            nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }
        break;
        case NODO_FUNCION_ARGUMENTOS:
        {
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }
        break;
        case NODO_FUNCION_LLAMADA:
        {
            pintar_espacios(espacios, ident);
            printf("`-CallExpr <linea: %i, %i> ", a->num_linea, a->num_columna);
            ast_valor* val = (ast_valor*)a->izquierdo;
            printf("%s\n", val->valor->cadena);
            nodo_mostrar_recursivo(a->derecho, ident, nivel+1);
        }
        break;
        case NODO_FUNCION_USUARIO:
        {
            ast_funcion* nfun = (ast_funcion*)a;
            pintar_espacios(espacios, ident);
            printf("`-FunctionDecl <linea: %i, %i> ", a->num_linea, a->num_columna);
            ast_valor* val = (ast_valor*)a->izquierdo;
            printf("%s\n", val->valor->cadena);
            nodo_mostrar_recursivo(nfun->parametros, ident, nivel+1);
            nodo_mostrar_recursivo(nfun->sentencias, ident, nivel+1);
        }
        break;
        case NODO_RETORNO:
            pintar_espacios(espacios, ident);
            printf("`-ReturnStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel+1);
            break;
        case NODO_ROMPER:
            pintar_espacios(espacios, ident);
            printf("`-BreakStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            break;
        case NODO_CONTINUAR:
            pintar_espacios(espacios, ident);
            printf("`-ContinueStat <linea: %i, %i>\n", a->num_linea, a->num_columna);
            break;
        case NODO_LISTA:
        {
            pintar_espacios(espacios, ident);
            printf("`-ListLiteral <linea: %i, %i>\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel+1);
        }
        break;
        /*case NODO_LISTA_AGREGAR_ELEMENTO:
        {
            if (a->izquierdo)
                nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            if (a->derecho)
                nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }*/
        break;
        case NODO_DICCIONARIO:
        {
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
        }
        break;
        /*case NODO_DICC_AGREGAR_ELEMENTO:
        {
            if (a->izquierdo)
                nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            if (a->derecho)
                nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }
        break;
        case NODO_DICC_ELEMENTO:
        {
            if (a->izquierdo)
                nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            if (a->derecho)
                nodo_mostrar_recursivo(a->derecho, ident, nivel);
        }
        break;
        */
        case NODO_INCLUIR:
        {
            pintar_espacios(espacios, ident);
            printf("`-FuncDecl <linea: %i, %i> incluir\n", a->num_linea, a->num_columna);
            nodo_mostrar_recursivo(a->izquierdo, ident, nivel+1);
        }
        break;
        default:
            if (a->izquierdo)
                nodo_mostrar_recursivo(a->izquierdo, ident, nivel);
            if (a->derecho)
                nodo_mostrar_recursivo(a->derecho, ident, nivel);
            break;
        }
    }
}

void nodo_mostrar(ast* a, int ident, int nivel)
{
    nodo_mostrar_recursivo(a, ident, nivel);
    printf("\n");
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
        if (!find_list(vm->modulos, (void*)mod))
        {
            //encontrar el modulo en la ruta actual
            char dir_actual[MAX_PATH_LENGTH];
            getcwd(dir_actual, sizeof(dir_actual));
            strcat(dir_actual, PATH_SEP);
            strcat(dir_actual, archivo);
            if (!endsWith(dir_actual, ".lat"))
            {
                strcat(dir_actual, ".lat");
            }
            if (legible(dir_actual))
            {
                insert_list(vm->modulos, mod);
                pn(vm, lat_analizar_archivo(vm, dir_actual));
            }
            else
            {
                //sino existe buscar en el path_home de latino/lib
                char* latino_lib = getenv("LATINO_LIB");
                if (latino_lib != NULL)
                {
                    strcat(latino_lib, PATH_SEP);
                    strcat(latino_lib, archivo);
                    if (!endsWith(latino_lib, ".lat"))
                    {
                        strcat(latino_lib, ".lat");
                    }
                    if (legible(latino_lib))
                    {
                        insert_list(vm->modulos, mod);
                        pn(vm, lat_analizar_archivo(vm, latino_lib));
                    }
                }
            }
        }
    }
    break;
    case NODO_BLOQUE:
    {
        if (node->r)
        {
            pn(vm, node->r);
        }
        if (node->l)
        {
            pn(vm, node->l);
        }
    }
    break;
    case NODO_IDENTIFICADOR: /*GET*/
    {
        dbc(OP_LOCALNS, 1, 0, NULL);
        lat_objeto *ret = lat_cadena_nueva(vm, node->valor->v.s);
        dbc(OP_STORESTR, 2, 0, ret);
        dbc(MAYOR_IGUALT, 2, 1, NULL);
        dbc(OP_MOV, 255, 2, NULL);
#if DEBUG_VM
        printf("LOCALNS R1\n");
        printf("STORESTR R2 %s\n", ret->data.str);
        printf("GET R2 R1\n");
        printf("MOV R255 R2\n");
#endif
    }
    break;
    case NODO_ASIGNACION: /*SET*/
    {
        pn(vm, node->l);
        dbc(OP_PUSH, 255, 0, NULL);
        lat_objeto *ret = lat_cadena_nueva(vm, node->r->valor->v.s);
        if (ret->num_declared < 0)
        {
            ret->num_declared = 0;
        }
        ret->es_constante = node->r->valor->es_constante;
        ret->num_declared++;
        if (ret->es_constante && ret->num_declared > 1)
        {
            lat_error("Linea %d: %s", (node->r->valor->num_linea + 1),  "Intento de asignar un nuevo valor a una constante ");
        }
        dbc(OP_LOCALNS, 1, 0, NULL);
        dbc(OP_POP, 255, 0, NULL);
        dbc(OP_SET, 255, 1, ret);
#if DEBUG_VM
        printf("PUSH R255 R0\n");
        printf("LOCALNS R1 R0\n");
        printf("POP R255 R0\n");
        printf("SET R255 R1\n");
#endif
    }
    break;
    case NODO_LITERAL:
    {
        lat_objeto *ret = lat_literal_nuevo(vm, node->valor->v.c);
        dbc(OP_STORELIT, 255, 0, ret);
#if DEBUG_VM
        printf("STORECHAR R255 %s\n", ret->data.str);
#endif
    }
    break;
    case NODO_ENTERO:
    {
        lat_objeto *ret = lat_entero_nuevo(vm, node->valor->v.i);
        dbc(OP_STOREINT, 255, 0, ret);
#if DEBUG_VM
        printf("STOREINT R255 %ld\n", ret->data.i);
#endif
    }
    break;
    case NODO_DECIMAL:
    {
        lat_objeto *ret = lat_decimal_nuevo(vm, node->valor->v.d);
        dbc(OP_STOREDOUBLE, 255, 0, ret);
#if DEBUG_VM
        printf("OP_STOREDOUBLE R255 %.14g\n", ret->data.d);
#endif
    }
    break;
    case NODO_CADENA:
    {
        lat_objeto *ret = lat_cadena_nueva(vm, node->valor->v.s);
        dbc(OP_STORESTR, 255, 0, ret);
#if DEBUG_VM
        printf("STORESTR R255 %s\n", ret->data.str);
#endif
    }
    break;
    case NODO_LOGICO:
    {
        lat_objeto *ret = (node->valor->v.b == true) ? vm->objeto_cierto : vm->objeto_falso;
        dbc(OP_STOREBOOL, 255, 0, ret);
#if DEBUG_VM
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
        pn(vm, nIf->th);
        bcode[temp[0]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEBUG_VM
        printf("MOV R2 R255\n");
        printf("MOV R3 R255\n");
        printf("NOT\n");
        printf("NOP R0 R0\n");
        printf("JMPIF R%i R2\n", i);
#endif
        if (nIf->el)
        {
            temp[1] = i;
            dbc(OP_NOP, 0, 0, NULL);
            pn(vm, nIf->el);
            bcode[temp[1]] = lat_bc(OP_JMPIF, i, 3, NULL);
#if DEBUG_VM
            printf("NOP\n");
            printf("MOV R3 R255\n");
            printf("JMPIF R%i R3\n", i);
#endif
        }
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
        pn(vm, node->r);
        dbc(OP_JMP, temp[0], 0, NULL);
        bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEBUG_VM
        printf("MOV R2 R255\n");
        printf("NOT R2 R0\n");
        printf("NOP\n");
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
        pn(vm, node->r);
        dbc(OP_JMP, temp[0], 0, NULL);
        bcode[temp[1]] = lat_bc(OP_JMPIF, i, 2, NULL);
#if DEBUG_VM
        printf("MOV R2 R255\n");
        printf("NOT R2 R0\n");
        printf("NOP\n");
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
#if DEBUG_VM
        printf("CALL R255\n");
#endif
    }
    break;
    case NODO_RETORNO:
    {
        pn(vm, node->l);
        dbc(OP_END, 0, 0, NULL);
#if DEBUG_VM
        printf("END R255\n");
#endif
    }
    break;
    case NODO_FUNCION_ARGUMENTOS:
    {
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_PUSH, 255, 0, NULL);
#if DEBUG_VM
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
#if DEBUG_VM
                printf("PUSH R255\n");
#endif
            }
        }
    }
    break;
    case NODO_LISTA_PARAMETROS:
    {
        if (node->l)
        {
            dbc(OP_LOCALNS, 1, 0, NULL);
            dbc(OP_POP, 2, 0, NULL);
            lat_objeto *ret = lat_clonar_objeto(vm, lat_cadena_nueva(vm, node->l->valor->v.s));
            dbc(OP_SET, 2, 1, ret);
#if DEBUG_VM
            printf("LOCALNS R1\n");
            printf("POP R2\n");
            printf("SET R2 R1 %s\n", ret->data.str);
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
        }
    }
    break;
    case NODO_FUNCION_USUARIO:
    {
        funcion_bcode =
            (lat_bytecode *)lat_asignar_memoria(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
        fi = 0;
        if (node->l)
        {
            fpn(vm, node->l);
        }
        fpn(vm, node->r);
        dbc(OP_FN, 255, 0, funcion_bcode);
#if DEBUG_VM
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
#if DEBUG_VM
        printf("STORELIST R%i\n", nested);
#endif
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 255, nested, NULL);
#if DEBUG_VM
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
#if DEBUG_VM
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
#if DEBUG_VM
            printf("MOV R3 R255\n");
#endif
        }
        if (elem->id)
        {
            pn(vm, elem->pos);
            dbc(OP_MOV, 4, 255, NULL);
#if DEBUG_VM
            printf("MOV R4 R255\n");
#endif
            pn(vm, elem->id);
            dbc(OP_LISTSETITEM, 255, 3, (void *)4);
#if DEBUG_VM
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
#if DEBUG_VM
            printf("MOV R3 R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_LISTGETITEM, 255, 3, NULL);
#if DEBUG_VM
            printf("LISTGETITEM R55 R3\n");
#endif
        }
    }
    break;
    case NODO_DICCIONARIO:
    {
        nested++;
        dbc(OP_STOREDICT, nested, 0, NULL);
#if DEBUG_VM
        printf("STOREDICT R%i\n", nested);
#endif
        if (node->l)
        {
            pn(vm, node->l);
            dbc(OP_MOV, 255, nested, NULL);
#if DEBUG_VM
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
#if DEBUG_VM
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
#if DEBUG_VM
            printf("PUSH R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_PUSH, 255, 0, NULL);
#if DEBUG_VM
            printf("PUSH R255\n");
#endif
        }
        dbc(OP_PUSHDICTELEM, 0, 0, NULL);
#if DEBUG_VM
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
#if DEBUG_VM
            printf("MOV R3 R255\n");
#endif
        }
        if (elem->id)
        {
            pn(vm, elem->llave);
            dbc(OP_MOV, 4, 255, NULL);
#if DEBUG_VM
            printf("MOV R4 R255\n");
#endif
            pn(vm, elem->id);
            dbc(OP_DICTSETITEM, 255, 3, (void*)4);
#if DEBUG_VM
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
#if DEBUG_VM
            printf("MOV R3 R255\n");
#endif
        }
        if (node->r)
        {
            pn(vm, node->r);
            dbc(OP_DICTGETITEM, 255, 3, NULL);
#if DEBUG_VM
            printf("MOV R255 R3\n");
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
    lat_bytecode *bcode = (lat_bytecode *)lat_asignar_memoria(sizeof(lat_bytecode) * MAX_BYTECODE_FUNCTION);
    int i = nodo_analizar(vm, tree, bcode, 0);
    dbc(OP_END, 0, 0, NULL);
    nodo_liberar(tree);
    return lat_definir_funcion(vm, bcode);
}

