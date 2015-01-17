ABSTRACTO
===
Este documento pretende explicar de manera general la definicion del nuevo lenguaje de programacion para
latinos.

Comentarios:
---
Los comentarios estaran delimitados por comillas dobles ("), es decir deberan iniciar 
con comillas dobles y terminar con comillas dobles incluyendo los comentarios multilinea, 
solo sera considerado como comentario si la linea empieza con dicho caracter,o es precedido con espacios o tabuladores.
Ejemplo:
"Este es un comentario de una linea"
"Este es 
un comentario
multilinea"
  "Este es un comentario con espacios al inicio de la linea"
	"Este es un comentario tabulado"

Variables:
---
Las variables son identificadores asociados a valores. Se declaran indicando el tipo de dato que almacenará y su identificador:
El tipo de dato es opcional cuando se inicializa con un valor la variable
identificador = valor
[tipo_dato] identificador

Un identificador puede:
* empezar por guion bajo (_)
* contener caracteres Unicode en mayúsculas y minúsculas (sensible a mayúsculas y minúsculas).
Un identificador no puede:
* empezar por un número.
* empezar por un símbolo, ni aunque sea una palabra clave.

Tabla tipo de dato
--------------------------------------
latino		|	C / C++ / Java / c#
--------------------------------------
entero		|	int
decimal		|	float / double / decimal
caracter	|	char
cadena		|	string / String
--------------------------------------

Constantes:
---
Las constantes son valores inmutables, y por tanto no se pueden cambiar.
Cuando se declara una constante con la palabra clave [constante|const], también se debe asignar el valor
constante decimal PI = 3.1416
const decimal PI = 3.1415

Operadores:
---
A continuacion se listan los operadores:

------------------------------------------------------
Categoría	Operadores
------------------------------------------------------
Aritmético			|	+ - * / % Division Entera(div), Mod
Lógico y a nivel de bits  	| 	^ ! ~ && y o no ||
Concatenación	    		|	+
Incremento, decremento		|	++ --
Desplazamiento			|	<< >>
Relacional			|	== != < > <= >=
Asignación			|	= ^= <<= >>=
Acceso a miembro		|	.
Indexación			|	[ ]
Conversión			|	( )
Condicional			|	? :

Estructuras de control:
---
si (if): Evalua una condicion y si el resultado es [cierto|verdadero] ejecuta las instrucciones a continuacion.

si (condicion)
   "codigo"
fin

si (condicion)
   "codigo"
otro 
   "codigo"
fin

si (condicion)
   "codigo"
otro si(condicion) 
         "codigo"
     fin
fin

seleccionar | elegir | escoger (switch): Evalua una opcion de multiples posibles casos. 

seleccionar (valor_cadena):
    caso "1":
	 "codigo"
    caso "2":
         "codigo"
    otro:
         "codigo"
fin

elegir (valor_caracter):
    opcion 'a':
	 "codigo"
    opcion 'b':
         "codigo"
    ninguna:
         "codigo"
fin

escoger (valor_decimal)
    entre 1.5 y 2.0:
    	  "codigo"
    entre 2.0 y 2.5:
    	  "codigo"
    otro:
	  "codigo"
fin

desde (for): Hace que una instrucción o bloque de instrucciones se repitan desde un valor inicial hasta un final
---
desde 0 hasta 10
      "codigo"
fin

desde 10 hasta 0
      "codigo"
fin

entero i = 0

desde i hasta 100
      "codigo"
fin

i = 10
desde i hasta 100 [incremento | inc] = 2
      "codigo"
fin

mientras (while): Hace que una instrucción o bloque de instrucciones se repitan mientra la condicion sea [cierto | verdadero]

mientras (condicion)
      "codigo"
fin

mientras (cierto)
      "codigo"
fin

hacer-mientras (do-while): Hace que una instrucción o bloque de instrucciones se repitan mientra la condicion sea [cierto | verdadero],
las intrucciones de codigo se ejecutan al menos una vez.

hacer
     "codigo"
mientras(verdadero)
