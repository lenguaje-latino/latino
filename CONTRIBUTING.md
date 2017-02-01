# Issues
Deberá tomar en cuenta estos puntos muy importantes para que su problema reportado sea arreglado inmediatamente y nos facilite el entendimiento:
- Mandar el código donde está obteniendo el error.
- Si su error incluye "backtrace", favor de enviarlo.
- Mandar el error que obtiene en la consola, en Linux, puede usar `latino script.lat 2> log.txt` para separar el error en un archivo.
- Reportar si está teniendo conflicos con la memoria ese error.
- ¿Ese error solo ocurre en el REPL (al ejecutar `latino`) o también el ejecutar su archivo?
- ¿Existe alguna función específica donde tiene el error?



# Estandares de programación

A continuación se describen algunas sugerencias a seguir para la codificación en C / C++

### If-else if-else

Utilizar identado de 4 espacios, incluir la llave que abre ({) en la misma linea 
de la instrucción de la siguiente manera:

```c
if (x == y) {
    ...
} else if (x > y) {
    ...
} else {
    ....
}
```

No es necesario usar llaves cuando se trata de una sola instrucción:

```c
if (condition)
    action();
```
y

```c
if (condition)
    do_this();
else
    do_that();
```

Lo anterior no aplica si solo una parte de la sentencia (if) contiene una sola instrucción:

```c
if (condition) {
    do_this();
    do_that();
} else {
    otherwise();
}
```

### Do


```c
do {
    /* codigo */
} while (condition);
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
switch (suffix) {
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
void function(int x) {
    /* cuerpo de la función */
}
```

También trate de tener un orden en los parámetros:
```c
void function(int a, char *x, int b) { ...
```

### Espacios
Utilice un espacio después de las siguientes palabras reservadas:

```c
if, switch, case, for, do, while
```

Pero no con sizeof, typeof, defined, alignof, or `__attribute__`

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
use el '*' adjunto al nombre de la variable y no adjunto al tipo de dato:
```c
	char *linux_banner;
	unsigned long long memparse(char *ptr, char **retptr);
	char *match_strdup(substring_t *s);
```
Use un espacio alrededor (en cada lado) en operadores binarios y ternarios:
```c
	=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :
```
Pero no use espacios después de operadores unarios:
```c
	&  *  +  -  ~  !  
```
No use espacios antes ni despúes de incrementos y decrementos de operadores unarios:
```c
	++  --
```
No use espacios alrededor de miembros de las estructuras '.' y '->' 
```c
	my_object->accion();
```
Elimine los espacios al final de la línea.

### For
Use un espacio entre el inicio a la condición y de la condición al incremento, ejemplo erróneo:
```c
for(int i=0;i<10;i++){
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
