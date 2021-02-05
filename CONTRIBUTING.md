# Errores o bugs en Latino

Deberá tomar en cuenta estos puntos muy importantes para que su problema reportado sea arreglado inmediatamente y nos facilite el entendimiento:

-   Mandar el código donde está obteniendo el error.
-   Si su error incluye "backtrace", favor de enviarlo.
-   Mandar el error que obtiene en la consola, en Linux, puede usar `latino script.lat 2> log.txt` para separar el error en un archivo.
-   Reportar si está teniendo conflicos con la memoria ese error.
-   ¿Ese error solo ocurre en el REPL (al ejecutar `latino`) o también el ejecutar su archivo?
-   ¿Existe alguna función específica donde tiene el error?

# Estándares de programación y requisitos

A continuación se describen algunas sugerencias a seguir para la codificación y flexibilidad en C:

-   Indentar código en tabulador tamaño 4.
-   Palabras reservadas en inglés (como match, regex, json, etc) deberán ser usadas como tal, pero NO palabras no reservadas como string, print, time, etc.
-   La memoria reservada deberá ser liberada cuando se deje de usar si es posible.
-   La memoria que reserves no deberá ser mayor al doble de lo que en realidad se necesitará.
-   Deberás indicar en la descripción todos los detalles de esa función, y dejar libre la edición por los contribuidores de Latino, en caso de que no tengas el tiempo necesario de reparar algo en tu código, así nosotros te ayudaremos y daremos crédito en tu ayuda.
-   Los comentarios no son obligatorios, pero será de buena ayuda que los pongas explicando qué haces en caso.
-   El estilo de programación Linux es usado en Latino.

## Sugerencia de estándares de programación en C Latino

### If-else if-else

Incluir la llave que abre ({) en la misma linea
de la instrucción, separar de la siguiente manera:

```c
if (x == y) {
    ...
} else if (x > y) {
    ...
} else {
    ....
}
```

Recuerda que no es necesario usar llaves cuando se trata de una sola instrucción:

```c
if (condicion)
    instruccion();
```

y

```c
if (condicion)
    instruccion();
else
    instruccion();
```

Pero para mejor órden, usa las instrucciones de esta manera sólo si es en una línea:

```c
if (condicion) { instruccion(); };
```

Lo anterior no aplica si solo una parte de la sentencia (if) contiene una sola instrucción:

```c
if (condicion) {
    instruccion();
    instruccion2();
} else {
    otra_instruccion();
}
```

### Do-While

```c
do {
    /* codigo */
} while (condicion);
```

### While

```c
while (condicion) {
    /* codigo */
}
```

### Switch

Tabular switch, case's y código a diferentes alturas:

```c
switch (valor) {
    case 'G':
    case 'g':
        /* codigo */
        break;
    case 'M':
    case 'm':
        /* codigo */
        break;
    case 'K':
    case 'k':
        /* codigo */
        break;
    default:
        break;
}
```

### Funciones

Iniciar la llave que abre en la siguiente línea:

```c
void funcion(int x) {
    /* cuerpo de la función */
}
```

También trate de tener un orden en los parámetros, separando entre espacio parámetro por parámetro:

```c
void funcion(int a, char *x, int b) { ...
```

### Espacios

Utilice un espacio después de las siguientes palabras reservadas:

```c
if, switch, case, for, do, while
```

Pero no con sizeof, typeof, defined, alignof, o `__attribute__`

```c
s = sizeof(struct file);
```

No agregar espacios dentro de las expresiones con parentesis.
Incorrecto:

```c
if ( x == y ) {
    ...
} else if ( x > y ) {
    ...
}
```

Cuando declaren un apuntador o una función que regrese un apuntador, de preferencia
use el '\*' adjunto al nombre de la variable y no adjunto al tipo de dato:

```c
	char *linux_banner;
	unsigned long long memoria_parser(char *ptr, char **retptr);
	char *match_strdup(substring_t *s);
```

Use un espacio alrededor (en cada lado) en operadores binarios y ternarios:

```c
	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :
```

Pero no use espacios después de operadores unarios (un operador solo):

```c
	*  +  -  ~  ! &
```

No use espacios antes ni despúes de incrementos y decrementos de operadores unarios:

```c
	++  --
```

No use espacios alrededor de miembros de las estructuras '.' y '->'

```c
	mi_objeto->accion();
```

Elimine los espacios al final de la línea.

### For

Use un espacio entre el inicio a la condición y de la condición al incremento, ejemplo erróneo:

```c
for(int i=0;i<10;i++){
	// código
}
```

Deberá ir de esta forma:

```c
for (int i=0; i<10; i++) {

```

### Comentarios

Use los comentarios al estilo Linux C89 en multilínea:

```c
/*
    ...
    ...
*/
```

No use los comentarios al estilo C99

```c
// ...
// ...
// ...
```
