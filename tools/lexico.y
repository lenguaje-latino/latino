%{
int yystopparser=0;
%}

%token PRINCIPAL FIN NOMBRECAMPO ENTERO DECIMAL LOGICO CARACTER CADENA T_CADENA T_LOGICO T_ENTERO T_DECIMAL T_CARACTER ASIGNADOR SUMA RESTA MULTIPLICACION DIVISION MODULO AUMENTAR DISMINUIR SI MAYOR MENOR IGUAL MAYORIGUAL MENORIGUAL NOIGUAL DESDE HACER INCREMENTO MIENTRAS OTRO ELEGIR CASO HASTA CONTINUAR ROMPER CONSTANTE CUANDO

%start programa

%%

programa                    : principal funciones | principal;

principal                   : PRINCIPAL '(' parametrosrecibe ')' lineascodigo FIN;

lineascodigo                : lineacodigo |;

lineacodigo                 : lineacodigo linea | linea;

linea                       : invocarmetodo | crearvariable | crearconstante | buclecondicion | CONTINUAR | ROMPER | incredismivariable;

invocarmetodo               : NOMBRECAMPO '(' parametrosenvio ')';

parametrosenvio             : parenvio |;

parenvio                    : penvio ',' penvio | penvio;

penvio                      : valor | NOMBRECAMPO;

parametrosrecibe            : parecibe |;

parecibe                    : precibe ',' precibe | precibe;

precibe                     : tipodato NOMBRECAMPO |;

valor                       : LOGICO | ENTERO | DECIMAL | CARACTER |  CADENA;

crearvariable               : tipodato NOMBRECAMPO | tipodato NOMBRECAMPO asignarvalor | NOMBRECAMPO asignarvalor;

crearconstante              : CONSTANTE tipodato NOMBRECAMPO ASIGNADOR valor | CONSTANTE NOMBRECAMPO ASIGNADOR valor;

tipodato                    : T_LOGICO | T_ENTERO | T_DECIMAL | T_CARACTER | T_CADENA;

asignarvalor                : ASIGNADOR operasignacion | ASIGNADOR valor | ASIGNADOR NOMBRECAMPO;

operasignacion              : aritmetico | invocarmetodo | incredismivariable;

aritmetico                  : oprcomun | oprcomun oprcomplemento;

oprcomun                    : valor tipoopr valor | valor tipoopr NOMBRECAMPO | NOMBRECAMPO tipoopr valor | NOMBRECAMPO tipoopr NOMBRECAMPO;

tipoopr                     : SUMA | RESTA | MULTIPLICACION | DIVISION | MODULO;

oprcomplemento              : oprcomplemento oprcom | oprcom;

oprcom                      : tipoopr valor | tipoopr NOMBRECAMPO;

incredismivariable          : NOMBRECAMPO incdis | incdis NOMBRECAMPO;

incdis                      : AUMENTAR | DISMINUIR;

buclecondicion              : condicionif | condicionswitch | buclefor | buclewhile | bucledo;

condicionif                 : condicionsi | condicionsi condicionno;

condicionsi                 : SI '(' condicion ')' lineascodigo FIN | SI '(' condicion ')' lineascodigo condicionno;

condicion                   : valor condicional valor | valor condicional NOMBRECAMPO | NOMBRECAMPO condicional valor | NOMBRECAMPO condicional NOMBRECAMPO | NOMBRECAMPO | LOGICO;

condicional                 : MAYOR | MENOR | IGUAL | MAYORIGUAL | MENORIGUAL | NOIGUAL;

condicionno                 : OTRO lineascodigo FIN;

condicionswitch             : ELEGIR '(' NOMBRECAMPO ')' casos FIN | ELEGIR '(' NOMBRECAMPO ')' casos elegirotro;

casos                       : casos uncaso | uncaso;

uncaso                      : CASO valor ':' lineascodigo |;

elegirotro                  : OTRO ':' lineascodigo FIN;

buclefor                    : DESDE iniciafor HASTA finfor lineascodigo FIN | DESDE iniciafor HASTA iniciafor inc lineascodigo FIN;

iniciafor                   : tipodato NOMBRECAMPO asignarvalor | NOMBRECAMPO asignarvalor | NOMBRECAMPO | valor;

finfor                      : NOMBRECAMPO | valor;

inc                         : INCREMENTO asignarvalor;

buclewhile                  : MIENTRAS '(' condicion ')' lineascodigo FIN;

bucledo                     : HACER lineascodigo CUANDO '(' condicion ')';

funciones                   : funciones funcion | funcion;

funcion                     : NOMBRECAMPO '(' parametrosrecibe ')' lineascodigo FIN | NOMBRECAMPO '(' parametrosrecibe ')' tipodato lineascodigo FIN | NOMBRECAMPO '(' parametrosenvio ')';
