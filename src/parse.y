%{
int yystopparser=0;
%}

%token PRINCIPAL FIN NOMBRECAMPO ENTERO DECIMAL LOGICO CARACTER CADENA T_CADENA
T_LOGICO T_ENTERO T_DECIMAL T_CARACTER ASIGNADOR SUMA RESTA MULTIPLICACION
DIVISION MODULO AUMENTAR DISMINUIR SI MAYOR MENOR IGUAL MAYORIGUAL MENORIGUAL
NOIGUAL DESDE HACER SALTO MIENTRAS SINO ELEGIR CASO HASTA CONTINUAR ROMPER
CONSTANTE CUANDO DEFECTO FUNCION CLASE PROPIEDAD ESTA CONSTRUCTOR RETORNO

%start programa

%%

programa:
principal funciones clases
| principal funciones
| principal  clases
| clases funciones
| principal
| funciones
| clases
;

principal:
PRINCIPAL '(' parametrosrecibe ')' lineascodigo FIN;

lineascodigo:
lineacodigo
|
;

lineacodigo:
lineacodigo linea
| linea
;

linea:
invocarmetodo
| crearvariable
| crearconstante
| buclecondicion
| CONTINUAR
| ROMPER
| incredismivariable
| propiedades
| asignaProp
| funciones
| ctor
| regresar
;

invocarmetodo:
NOMBRECAMPO '(' parametrosenvio ')'
;

parametrosenvio:
parenvio
|
;

parenvio:
penvio ',' penvio
| penvio
;

penvio:
valor
| NOMBRECAMPO;

parametrosrecibe:
parecibe
|
;

parecibe:
precibe ',' precibe
| precibe
;

precibe:
tipodato NOMBRECAMPO ASIGNADOR valor
| tipodato NOMBRECAMPO
;

valor:
LOGICO
| ENTERO
| DECIMAL
| CARACTER
| CADENA;

crearvariable:
tipodato NOMBRECAMPO
| tipodato NOMBRECAMPO asignarvalor
| NOMBRECAMPO asignarvalor
;

crearconstante:
CONSTANTE tipodato NOMBRECAMPO ASIGNADOR valor
| CONSTANTE NOMBRECAMPO ASIGNADOR valor
;

tipodato:
T_LOGICO
| T_ENTERO
| T_DECIMAL
| T_CARACTER
| T_CADENA
;

asignarvalor:
ASIGNADOR operasignacion
| ASIGNADOR valor
| ASIGNADOR NOMBRECAMPO
;

operasignacion:
aritmetico
| invocarmetodo
| incredismivariable
;

aritmetico:
oprcomun
| oprcomun oprcomplemento
;

oprcomun:
valor tipoopr valor
| valor tipoopr NOMBRECAMPO
| NOMBRECAMPO tipoopr valor
| NOMBRECAMPO tipoopr NOMBRECAMPO
| valor tipoopr oprcompuesto
| oprcompuesto tipoopr valor
| NOMBRECAMPO tipoopr oprcompuesto
| oprcompuesto tipoopr NOMBRECAMPO
| oprcompuesto tipoopr oprcompuesto
;

tipoopr:
SUMA
| RESTA
| MULTIPLICACION
| DIVISION
| MODULO
;

oprcomplemento:
oprcomplemento oprcom
| oprcom
;

oprcom:
tipoopr valor
| tipoopr NOMBRECAMPO
| tipoopr oprcompuesto
;

oprcompuesto:
'(' valor tipoopr valor ')'
| '('valor tipoopr NOMBRECAMPO ')'
| '('NOMBRECAMPO tipoopr valor ')'
|'('NOMBRECAMPO tipoopr NOMBRECAMPO ')'
;

incredismivariable:
NOMBRECAMPO incdis
| incdis NOMBRECAMPO
;

incdis:
AUMENTAR
| DISMINUIR
;

buclecondicion:
condicionif
| condicionswitch
| buclefor
| buclewhile
| bucledo
;

condicionif:
condicionsi
| condicionsi condicionno
;

condicionsi:
SI '(' condicion ')' lineascodigo FIN
| SI '(' condicion ')' lineascodigo condicionno
;

condicion:
valor condicional valor
| valor condicional NOMBRECAMPO
| NOMBRECAMPO condicional valor
| NOMBRECAMPO condicional NOMBRECAMPO
| NOMBRECAMPO
| LOGICO
;

condicional:
MAYOR
| MENOR
| IGUAL
| MAYORIGUAL
| MENORIGUAL
| NOIGUAL
;

condicionno:
SINO lineascodigo FIN
;

condicionswitch:
ELEGIR '(' NOMBRECAMPO ')' casos FIN
| ELEGIR '(' NOMBRECAMPO ')' casos elegirotro
;

casos:
casos uncaso
| uncaso
;

uncaso:
CASO valor ':' lineascodigo
|
;

elegirotro:
DEFECTO ':' lineascodigo FIN
;

buclefor:
DESDE iniciafor HASTA finfor lineascodigo FIN
| DESDE iniciafor HASTA iniciafor inc lineascodigo FIN
;

iniciafor:
tipodato NOMBRECAMPO asignarvalor
| NOMBRECAMPO asignarvalor
| NOMBRECAMPO
| valor
;

finfor:
NOMBRECAMPO
| valor
;

inc:
SALTO asignarvalor
;

buclewhile:
MIENTRAS '(' condicion ')' lineascodigo FIN
;

bucledo:
HACER lineascodigo CUANDO '(' condicion ')'
;

funciones:
funciones func
| func
;

func:
FUNCION NOMBRECAMPO '(' parametrosrecibe ')' lineascodigo FIN
;

clases:
clases clas
| clas
;

clas:
CLASE NOMBRECAMPO lineascodigo FIN
| CLASE NOMBRECAMPO ':' NOMBRECAMPO lineascodigo FIN
;

propiedades:
propiedades prop
| prop
;

prop:
PROPIEDAD tipodato NOMBRECAMPO
;

asignaProp:
ESTA '.' NOMBRECAMPO asignarvalor
;

ctor:
CONSTRUCTOR '(' parametrosrecibe ')' lineascodigo FIN
;

regresar:
RETORNO valor
| RETORNO NOMBRECAMPO
| RETORNO operasignacion
| RETORNO
;

%%
