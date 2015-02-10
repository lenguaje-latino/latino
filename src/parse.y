%{
int yystopparser=0;
%}

%token PRINCIPAL FIN NOMBRECAMPO ENTERO DECIMAL LOGICO CARACTER CADENA T_CADENA
T_LOGICO T_ENTERO T_DECIMAL T_CARACTER ASIGNADOR SUMA RESTA MULTIP
DIVISION MODULO AUMENTAR DISMINUIR SI MAYOR MENOR IGUAL MAYORIGUAL MENORIGUAL
NOIGUAL DESDE HACER SALTO MIENTRAS SINO ELEGIR CASO HASTA CONTINUAR ROMPER
CONSTANTE CUANDO DEFECTO FUNCION CLASE PROPIEDAD ESTA CONSTRUCTOR RETORNO
NEGATIVO PAREN_IZQ PAREN_DER

/*
 * presedencia de operadores
 * 0: -
 * 1: * /
 * 2: + -
 *
 */

%left SUMA RESTA
%left MULTIP DIVISION MODULO
%left NEGATIVO


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
PRINCIPAL PAREN_IZQ parametrosrecibe PAREN_DER lineascodigo FIN;

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
NOMBRECAMPO PAREN_IZQ parametrosenvio PAREN_DER
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
expresion
| invocarmetodo
| incredismivariable
;

expresion:
primary
| primary SUMA primary
| primary RESTA primary
| primary MULTIP primary
| primary DIVISION primary
| primary MODULO primary
| expresion SUMA primary
| expresion RESTA primary
| expresion MULTIP primary
| expresion DIVISION primary
| expresion MODULO primary
;

primary:
valor
| NOMBRECAMPO
| PAREN_IZQ expresion PAREN_DER
| invocarmetodo
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
SI PAREN_IZQ condicion PAREN_DER lineascodigo FIN
| SI PAREN_IZQ condicion PAREN_DER lineascodigo condicionno
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
ELEGIR PAREN_IZQ NOMBRECAMPO PAREN_DER casos FIN
| ELEGIR PAREN_IZQ NOMBRECAMPO PAREN_DER casos elegirotro
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
MIENTRAS PAREN_IZQ condicion PAREN_DER lineascodigo FIN
;

bucledo:
HACER lineascodigo CUANDO PAREN_IZQ condicion PAREN_DER
;

funciones:
funciones func
| func
;

func:
FUNCION NOMBRECAMPO PAREN_IZQ parametrosrecibe PAREN_DER lineascodigo FIN
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
CONSTRUCTOR PAREN_IZQ parametrosrecibe PAREN_DER lineascodigo FIN
;

regresar:
RETORNO operasignacion
| RETORNO
;

%%
