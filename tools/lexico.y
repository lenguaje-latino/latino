%{
int yystopparser=0;
%}

%token MAIN FIN NOMBRECAMPO ENTERO DECIMAL LOGICO CARACTER CADENA T_CADENA T_LOGICO T_ENTERO T_DECIMAL T_CARACTER ASIGNADOR SUMA RESTA MULTIPLICACION DIVISION MODULO AUMENTAR DISMINUIR SI MAYOR MENOR IGUAL MAYORIGUAL MENORIGUAL NOIGUAL DESDE HACER INCREMENTO MIENTRAS OTRO ELEGIR CASO HASTA

%start programa

%%

programa                    : principal funciones | principal;

principal                   : MAIN '(' ')' lineascodigo FIN;

lineascodigo                : lineacodigo |;

lineacodigo                 : lineacodigo linea | linea;

linea                       : invocarmetodo | crearvariable | cambiarvalor | buclecondicion;

invocarmetodo               : NOMBRECAMPO '(' parametrosenvio ')';

parametrosenvio             : parenvio |;

parenvio                    : parenvio ',' penvio | penvio;

penvio                      : valor | NOMBRECAMPO;

valor                       : LOGICO | ENTERO | DECIMAL | CARACTER |  CADENA;

crearvariable               : tipodato NOMBRECAMPO | tipodato NOMBRECAMPO asignarvalor;

tipodato                    : T_LOGICO | T_ENTERO | T_DECIMAL | T_CARACTER | T_CADENA;

asignarvalor                : ASIGNADOR operasignacion | ASIGNADOR valor | ASIGNADOR NOMBRECAMPO;

operasignacion              : aritmetico | invocarmetodo | incredismivariable;

aritmetico                  : oprcomun | oprcomun oprcomplemento;

oprcomun                    : valor tipoopr valor | valor tipoopr NOMBRECAMPO | NOMBRECAMPO tipoopr valor | NOMBRECAMPO tipoopr NOMBRECAMPO;

tipoopr                     : SUMA | RESTA | MULTIPLICACION | DIVISION | MODULO;

oprcomplemento              : oprcomplemento oprcom | oprcom;

oprcom                      : tipoopr valor | tipoopr NOMBRECAMPO;

incredismivariable          : NOMBRECAMPO incdis;

incdis                      : AUMENTAR | DISMINUIR;

cambiarvalor                : NOMBRECAMPO ASIGNADOR cambvalor;

cambvalor                   : valor | operasignacion | NOMBRECAMPO;

buclecondicion              : condicionif | condicionswitch | buclefor | buclewhile | bucledo;

condicionif                 : condicionsi | condicionsi condicionno;

condicionsi                 : SI '(' condicion ')' lineascodigo FIN;

condicion                   : valor condicional valor | valor condicional NOMBRECAMPO | NOMBRECAMPO condicional valor | NOMBRECAMPO condicional NOMBRECAMPO;

condicional                 : MAYOR | MENOR | IGUAL | MAYORIGUAL | MENORIGUAL | NOIGUAL;

condicionno                 : OTRO lineascodigo FIN;

condicionswitch             : ELEGIR '(' NOMBRECAMPO ')' casos FIN | ELEGIR '(' NOMBRECAMPO ')' casos OTRO lineascodigo FIN;

casos                       : uncaso uncaso | uncaso;

uncaso                      : CASO valor ':' lineascodigo;

buclefor                    : DESDE iniciafor HASTA iniciafor lineascodigo FIN | DESDE iniciafor HASTA iniciafor inc;

iniciafor                   : tipodato NOMBRECAMPO asignarvalor | NOMBRECAMPO asignarvalor | NOMBRECAMPO;

inc                         : INCREMENTO asignarvalor;

buclewhile                  : MIENTRAS '(' condicion ')' lineascodigo FIN;

bucledo                     : HACER lineascodigo MIENTRAS '(' condicion ')';

funciones                   : funciones funcion | funcion;

funcion                     : NOMBRECAMPO '(' parametrosenvio ')' lineascodigo FIN | NOMBRECAMPO '(' parametrosenvio ')' tipodato lineascodigo FIN;
