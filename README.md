<a href="http://lenguaje-latino.org/" target="_blank">
<img src ="https://raw.githubusercontent.com/primitivorm/latino/master/logo/banner-300x.png" />
</a>

[![https://t.me/joinchat/EBHu7z6l6_paWtcJgu9DVQ](https://img.shields.io/badge/Soporte-Telegram-green.svg?style=plastic)](https://t.me/joinchat/AAAAAD6l6_qIgQAAgu9DVQ)
[![Join the chat at https://gitter.im/primitivorm/latino](https://badges.gitter.im/primitivorm/latino.svg)](https://gitter.im/primitivorm/latino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Open Source Helpers](https://www.codetriage.com/primitivorm/latino/badges/users.svg)](https://www.codetriage.com/primitivorm/latino)

[![Build Status](https://travis-ci.org/primitivorm/latino.svg?branch=master)](https://travis-ci.org/primitivorm/latino)
<a href="http://lenguaje-latino.org"><img src="https://img.shields.io/npm/l/vue.svg" alt="License"></a>
[![codecov.io](http://codecov.io/github/primitivorm/latino/coverage.svg?branch=master)](http://codecov.io/github/primitivorm/latino?branch=master)

¿Qué es lenguaje Latino?
===

`Latino` es un lenguaje de programación creado en [C](https://es.wikipedia.org/wiki/C_(lenguaje_de_programaci%C3%B3n)), inspirado en [Lua](https://www.lua.org/) y [Python](https://www.python.org), este proyecto nace de la necesidad de incrementar la educación de nivel básico y avanzado para que niños, adolescentes y adultos también se motiven a entrar en el mundo de la programación y desarrollar aplicaciones en la sintaxis de su idioma,   `Latino` es también para desarrolladores ya que `Latino` es completamente funcional con cualquier [API](https://es.m.wikipedia.org/wiki/Interfaz_de_programaci%C3%B3n_de_aplicaciones).

<a href="http://www.youtube.com/watch?feature=player_embedded&v=ljQKPihnejU&t=1s" target="_blank">
<img src="https://i.ytimg.com/vi/ljQKPihnejU/2.jpg" alt="Ver introducción" width="320px" height="240px" border="10" />
</a>

A continuación menciono las principales características de este proyecto:

1. __Simplicidad:__ La sintaxis deberá de ser lo más parecido posible al lenguaje español.
2. __Sencillo de aprender:__ Al ser simple aprenderás más rápido éste nuevo lenguaje.
3. __Código abierto:__ Cualquiera puede descargar el código fuente del lenguaje, extender las librerías básicas y crear sus propias librerías si así lo desea.
4. __Lenguaje de alto nível:__ Cuando escribas código no tendrás que preocuparte por detalles de bajo nivel, como manejar la memoria empleada en tu programa, `Latino` asignará la memoria adecuada e inmediatamente liberará esa memoria cuando ya no sea necesaria.
5. __Portable:__ Cuando escribas tus programas en `Latino` podrás ejecutarlo en cualquier plataforma de manera segura y fácil.
6. __Programación Procedural, Funcional y Orientado a Objetos.__

<a href="https://github.com/lenguaje-latino/latino-sublimetext-plugin" target="_blank">
<img src ="https://raw.githubusercontent.com/lenguaje-latino/latino-sublimetext-plugin/master/latino_sublime.png" />
</a>

## INSTALAR

[Windows](doc/instalacion_windows.md)

[Debian/Ubuntu](doc/instalacion_debian.md)

[Fedora](doc/instalacion_fedora.md)

[Mac](doc/instalacion_mac.md)

[Plugins](https://github.com/lenguaje-latino)


DEFINICIÓN (lenguaje latino)
===

A continuación se explica de manera general la definición del lenguaje de programación `Latino`

Comentarios:
---
Los comentarios de una linea empezaran por el signo de gato `#` (como en python ) o `//` (como en C).

```
#Este es un comentario estilo python
//Este es un comentario estilo C
```

Los comentarios multilínea son al estilo C. inician con `/*` y terminan con `*/`.

```
/*
Este es un
comentario
multilínea
*/
```

Variables:
---
Las variables son identificadores asociados a valores.

```
nombre = "Juan Perez"
calificacion = 10
numeros = [1, 2, 3, 4, 5]  //esto es una lista ó arreglo.
sueldos = { "Jesus" : 10000, "Maria" : 20000, "Jose" : 30000 } //esto es un diccionario

```

Es posible asignar más de una variable en una sola línea de código
```
a, b, c = 1, 2, 3   #a = 1  b = 2  c = 3
a, b, c = 1, 2      #a = 1  b = 2  c = nulo
a, b    = 1, 2, 3   #a = 1  b = 2  se descarta el valor 3
```

__Un identificador puede:__
1. Empezar por guión bajo `_` o letras `a-z ó A-Z`. No son validas las letras acentuadas ni la `ñ` como letras en los identificadores.
2. Contener caracteres en mayúsculas y minúsculas.
Latino  es sensible a mayúsculas y minúsculas. Por lo que los siguientes identificadores no son los mismos.

```
mensaje = "Hola mundo"
Mensaje = "¡Hasta la vista baby!"
```

__Un identificador NO puede:__
1. Empezar por un número.
2. Empezar por un símbolo, ni tampoco que sea una palabra reservada.

Tipos de dato
---

| latino           | tipo de dato en C |
| ---------------- |:-----------------:|
| logico           |       bool        |
| numérico         |      double       |
| cadena o literal |      `char*`      |
| lista (arreglo)  |      struct       |
| diccionario      |      struct       |

Constantes:
---
Cuando se declara una constante, también se debe asignar el valor forzosamente.

Las constantes se deben declarar en mayúsculas.

```
PI = 3.14159
G = 9.8
```

Operadores:
---
A continuación se listan los operadores:

| Categoría              | Operadores                             |
| ---------------------- | -------------------------------------- |
| Aritmético             | `+, -, *, /, % (modulo), ^ (potencia)` |
| Lógico                 | && (y), &#124;&#124; (o)               |
| Concatenación          | `..`                                   |
| Incremento, decremento | `++, --` (valido solo en post)         |
| Relacional             | `==, !=, <, >, <=, >=, ~= (regex)`     |
| Asignación             | `=`                                    |
| Acceso a miembro       | `.`                                    |
| Operador ternario      |  `(condicion) ? opcion1 : opcion2`     |

La precedencia de operadores es la misma que otros lenguajes de programación como C / Python / Lua.

El operador ternario se puede usar para asignar valores basado en una condición, los paréntesis son requeridos para obtener el resultado esperado.

```
numero = -5
mensaje = (numero < 0) ? " es negativo" : " es positivo"
escribir("El número " .. numero .. mensaje)
#salida: El número -5 es negativo
```

Estructuras de control:
===

si (if)
---
Evalua una condición y si el resultado es `verdadero` ejecuta
las instrucciones a continuación. Los paréntesis son opcionales en la condición.

```
si (condicion)
   #codigo
fin

edad = 18
si edad >= 18
    escribir("Eres mayor de edad, ya puedes votar.")
fin
#salida: Eres mayor de edad, ya puedes votar.
```

En caso de que el resultado de la condición sea `falso` se deberá de ejecutar el código después de la palabra reservada `sino`.

```
si condicion
   #codigo
sino
   #codigo
fin

edad = 5
si edad >= 18
    escribir("Eres mayor de edad, ya puedes votar.")
sino
    escribir("Eres un niño, tienes que ir a la escuela.")
fin
#salida: Eres un niño, tienes que ir a la escuela.
```

Es posible el anidamiento de las sentencias `si-sino` de la siguiente manera:

```
si condicion
   #codigo
sino
    si condicion
        #codigo
    sino
        #codigo
    fin
fin
```
Existe una forma más elegante de escribir el código anterior con la palabra reservada `osi`. En python es `elif expresion:`.

```
si condicion1
    #codigo
osi condicion2
    #codigo
osi condicion3
    #codigo
sino
    #codigo
fin
```

elegir (switch)
---
Evalúa una opción de múltiples posibles casos.
La opción puede ser una expresión, en caso de que ninguna opción se cumpla en algún caso se ejecuta el código después de la palabra reservada `otro` o `defecto`.
Los valores de los casos solo pueden ser numéricos o cadenas.

```
elegir (opcion)
    caso valor1:
        #codigo
    caso valor2:
        #codigo
    caso valor3:
        #codigo
    defecto:
        #codigo
fin

calificacion = 'B'
elegir(calificacion)
    caso 'A':
        escribir("Excelente!.")    
    caso 'B':
        escribir("Bien echo!.")
    caso 'C':
        escribir("Bien echo!.")
    caso 'D':
        escribir("Todavia pasas.")
    caso 'F':
        escribir("Estas reprobado.")
    otro:
        escribir("Calificación invalida.")
fin
#salida: Bien echo!
```
Notese que se tiene que repetir el caso para `B` y `C` por el momento no se permiten casos múltiples como una sola opción.

desde (parecido al `for` de C)
---
Hace que una instrucción o bloque de instrucciones se repitan
desde una condición inicial y mientras la condición se cumpla (es decir sea `verdadero`), en esta sentencia los paréntesis si son requeridos.

```
desde (condicion_inicial; condicion; incremento)
     #codigo
fin

desde (i=0; i <= 10; i++)
     escribir(i)
fin
#salida: 0 1 2 3 4 5 6 7 8 9 10

desde (i=10; i >= 0; i--)
     escribir(i)
fin
#salida: 10 9 8 7 6 5 4 3 2 1 0
```

Se puede especificar un salto diferente cambiando la expresión de incremento.

```
desde(i=0; i < 50; i=i+10)
    imprimir(i)
fin
#salida: 0 10 20 30 40
```

mientras (while)
---
Hace que una instrucción o bloque de instrucciones se repitan
mientras la condición sea `verdadero`, los paréntesis son opcionales en la condición.

```
mientras (condicion)
    #codigo
fin

i=0
mientras i < 10
    escribir(i)
    i++ #incremento
fin
#salida: 0 1 2 3 4 5 6 7 8 9
```

repetir-hasta (parecido al `repeat` de Lua)
---
Hace que una instrucción o bloque de instrucciones
se repitan mientra la condición sea `falso`,
las instrucciones de código se ejecutan al menos una vez.
Los paréntesis son opcionales en la condición.

```
repetir
    #codigo
hasta condicion

i=0
repetir
    escribir(i)
    i++ #incremento
hasta i == 10
#salida: 0 1 2 3 4 5 6 7 8 9
```

Se puede salir de los bucles (`desde`, `mientras` y `repetir`) con la palabra reservada `romper`.

```
desde(i=0; i < 10; i++)
    si (i == 5)        
        romper    #se sale del ciclo desde
    fin
    imprimir(i)
fin
#salida: 0 1 2 3 4   #se imprime solo hasta el 4
```

Funciones
===
Una función consiste generalmente de una lista de sentencias a ejecutar, una lista de parámetros de entrada que regularán dicha acción.

Las funciones se definen con la palabra reservada `funcion` o la forma corta `fun`.

Se puede regresar el valor con la palabra clave `regresar`, `retornar` o la forma corta `ret`.
La estructura de una función es la siguiente:

```
funcion nombreFuncion (argumento1, argumento2)
    #codigo
    retornar resultado
fin

#La siguiente función suma dos números
fun sumar(a, b)
  ret a + b
fin
```

Para invocar (ejecutar) una función se hace con el nombre de la función y la lista de parámetros entre paréntesis.

```
r = sumar(2, 3)  #se almacena el resultado en la variable r
escribir(r)
#salida: 5
```

Se pueden crear funciones con un número variable de argumentos con `...` en el ultimo parámetro de la definición.

```
funcion varArgs(arg1, arg2, ...)
  va = [...] #se obtienen los parametros 3 en adelante como una lista y se asignan a la variable va
  escribir("parametro 1: " .. arg1) #imprime el parametro 1
  escribir("parametro 2: " .. arg2) #imprime el parametro 2
  escribir("parametro 3: " .. va[0]) #imprime el parametro 3
  retornar arg1 + arg2
fin

#llamada a función varArgs con 2 elementos
r = varArgs(1, 2)
escribir(r)
#salida:
parametro 1: 1
parametro 2: 2
parametro 3: nulo
3

#llamada a funcion varArgs con 3 elementos
r = varArgs(1, 2, 3)
escribir(r)
#salida:
parametro 1: 1
parametro 2: 2
parametro 3: 3
3
```

Listas
===
Una lista es un tipo de colección. Es equivalente a lo que en otros lenguajes se conoce por arreglos o vectores.

Las listas pueden contener cualquier tipo de dato: lógico, númerico, literal, cadena, listas, diccionarios.

Crear una lista es tan sencillo como indicar entre corchetes y separados por comas los valores que queremos incluir en la lista.
```
#declaracion de listas
numeros = [1, 2, 3, 4, 5]
vacia = []
```

Podemos acceder a cada uno de los elementos de la lista escribiendo el nombre de la lista e indicando el índice del elemento entre corchetes `[]`.
Ten en cuenta que el índice del primer elemento de la lista es 0:
```
escribir(numeros[1])
#salida: 2
```

También podemos utilizar este operador para modificar un elemento de la lista si lo
colocamos en la parte izquierda de una asignación:
```
numeros[0] = 99
escribir(numeros)
#salida: [99, 2, 3, 4, 5]
```

Podemos utilizar también números negativos. Si se utiliza un número negativo como índice, esto se traduce en que el índice empieza a contar desde el final, hacia la izquierda; es decir, con [-1] accederíamos al último elemento de la lista, con [-2] al penúltimo, con [-3], al antepenúltimo, y así sucesivamente.
```
escribir(numeros[-1])
#salida: 5
```

Diccionarios
===
Los diccionarios, también llamados matrices asociativas, deben su nombre a que son colecciones que relacionan una clave y un valor, entre llaves y separado el valor de la clave con dos puntos.
```
#Diccionario de personajes y actores:
actores = { "Chilindrina": "Maria Antonieta de las Nieves",
     "El chavo del 8": "Roberto Gomez Bolaños",
     "Tres patines": "Leopoldo Fernandez" }
```

El primer valor se trata de la clave y el segundo del valor asociado a la clave.

Como clave usamos cadenas, esto es así porque los diccionarios se implementan como tablas hash, y a la hora de introducir un nuevo par clave-valor en el diccionario se calcula el hash de la clave para después poder encontrar la entrada correspondiente rápidamente.

Si se modificara el objeto clave después de haber sido introducido en el diccionario, evidentemente,
su hash también cambiaría y no podría ser encontrado.

La diferencia principal entre los diccionarios y las listas es que a los valores almacenados en un diccionario se les accede no por su índice, porque de hecho no tienen orden, sino por su clave, utilizando corchetes `[]`.
```
escribir(actores["Chilindrina"])
#salida: Maria Antonieta de las Nieves
```

Al igual que en listas también se puede utilizar corchetes para reasignar valores.
```
actores["Chilindrina"] = "Maria Antonieta"
escribir(actores["Chilindrina"])
#salida: Maria Antonieta
```

Palabras reservadas hasta el momento
---
```
caso
cierto | verdadero
defecto | otro
desde
elegir
falso
fin
funcion | fun
global
hasta
mientras
nulo
repetir
regresar | retornar | ret
romper
si
sino
osi
```

Cualquier aportación o sugerencia es bienvenida.
