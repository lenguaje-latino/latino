#Estandares de programacion

A continuación se describen algunas sugerencias a seguir para la codificación en C / C++

###ifelse

Utilizar identado de 4 espacios, incluir la llave que abre ({) en la misma linea 
de la instrucción de la siguiente manera:

if (x == y) {
    ...
} else if (x > y) {
    ...
} else {
    ....
}

No es necesario usar llaves cuando se trata de una sola instrucción:

if (condition)
    action();
y

if (condition)
    do_this();
else
    do_that();

Lo anterior no aplica si solo una parte de la sentencia (if) contiene una sola instrucción:

if (condition) {
    do_this();
    do_that();
} else {
    otherwise();
}

###do


do {
    /* codigo */
} while (condition);

###while

while (condicion) {
    /* codigo */
}

###switch
Alinear los case's a la misma altura de la intrucción switch:

switch (suffix) {
case 'G':
case 'g':
    mem <<= 30;
    break;
case 'M':
case 'm':
    mem <<= 20;
    break;
case 'K':
case 'k':
    mem <<= 10;
    /* fall through */
default:
    break;
}

###Funcciones
Para el caso unico de las funciones iniciar la llave que abre en la siguiente línea:

int function(int x)
{
    /* cuerpo de la función */
}

###Espacios
Utilice un espacio después de las siguientes palabras reservadas:

if, switch, case, for, do, while

Pero no con sizeof, typeof, defined, alignof, or __attribute__

s = sizeof(struct file);

No agregar espacios dentro de las expresiones con parentesis.
Incorrecto:
if ( x == y ) {
    ...
} else if ( x > y ) {
    ...
}

Cuando declaren un apuntador o una función que regrese un apuntador, de preferencia
use el '*' adjunto al nombre de la variable y no adjunto al tipo de dato:

	char *linux_banner;
	unsigned long long memparse(char *ptr, char **retptr);
	char *match_strdup(substring_t *s);

Use un espacio alrededor (en cada lado) en operadores binarios y ternarios:

	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :

Pero no use espacios después de operadores unarios:

	&  *  +  -  ~  !  

No use espacios antes ni despúes de incrementos y decrementos de operadores unarios:

	++  --

No use espacios alrededor de miembros de las estructuras '.' y '->' 

	my_object->accion();

Elimine los espacios al final de la línea.

###Comentarios
Use los comentarios al estilo Linux C89: 

	/* ... */

No use los comentarios al estilo C99 

	// ... 
