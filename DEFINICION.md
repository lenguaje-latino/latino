#DEFINICIÓN (latino)

Este documento pretende explicar de manera general la definición del nuevo
lenguaje de programación "Latino"

Comentarios:
---
Los comentarios empezaran por el signo de numero (#), sólo será considerado
como comentario si la línea empieza con dicho cáracter,o es precedido con espacios o tabuladores.
no existe comentarios multilinea.

#Este es un comentario de una linea
    #Este es un comentario con espacios al inicio de la linea
        #Este es un comentario tabulado

Variables:
---
Las variables son identificadores asociados a valores.

identificador = valor
numero = 1

Un identificador puede:
* empezar por guión bajo (_) o letras
* contener caracteres en mayúsculas y minúsculas (sensible a mayúsculas y minúsculas)
Un identificador NO puede:
* empezar por un número.
* empezar por un símbolo, ni tampoco que sea una palabra reservada.

Tabla tipo de dato
-------------------------------------------------------------
latino      |   lenguajes como C / C++ / Java / C# / etc.
-------------------------------------------------------------
logico      |   bool
entero      |   int
decimal     |   float / double / decimal
caracter    |   char
cadena      |   string / String
-------------------------------------------------------------

Constantes:
---
Cuando se declara una constante, también se debe asignar el valor forzosamente.
Las costantes se deben de declarar en mayúsculas

PI = 3.1416

Operadores:
---
A continuacion se listan los operadores:

------------------------------------------------------------
Categoría               Operadores
------------------------------------------------------------
Aritmético             |   + - * / % (Modulo)
Lógico                 |   & |
Concatenación          |   +
Incremento, decremento |   ++ --
Relacional             |   == != < > <= >=
Asignación             |   =
Acceso a miembro       |   .
------------------------------------------------------------

Estructuras de control:
---
si (if): Evalua una condicion y si el resultado es [verdadero] ejecuta
las instrucciones a continuacion.

si (condicion)
   #codigo
fin

En caso de que el resultado de la condición sea [falso] se deberá de ejecutar
el código despues de la palabra reservada [sino]

si (condicion)
   #codigo
sino
   #codigo
fin

Es posible el anidamiento de las sentencias [si] de la siguiente manera:
si (condicion)
   #codigo
sino si (condicion)
        #codigo
     sino
        #codigo
     fin
fin

elegir (switch): Evalua una opción de multiples posibles casos.

elegir (opcion)
    caso "1":
        #codigo
    caso "2":
        #codigo
    caso "3":
        #codigo
    defecto:
        #codigo
fin

desde (for): Hace que una instrucción o bloque de instrucciones se repitan
desde un valor inicial hasta uno final
---
desde 0 hasta 10
      imprimir(i)
fin
salida: 0 1 2 3 4 5 6 7 8 9 10

desde 10 hasta 0
      imprimir(i)
fin
salida: 10 9 8 7 6 5 4 3 2 1 0

Se puede especificar el salto del ciclo con la palabra clave [salto]

i = 10
desde i hasta 50 salto = 10
    imprimir(i)
fin
salida: 10 20 30 40 50

mientras (while): Hace que una instrucción o bloque de instrucciones se repitan
mientras la condicion sea [verdadero]

mientras (condicion)
    #codigo
fin

mientras (verdadero)
    #codigo
fin

hacer-cuando (do-while): Hace que una instrucción o bloque de instrucciones
se repitan mientra la condicion sea [verdadero],
las intrucciones de codigo se ejecutan al menos una vez.

hacer
    #codigo
cuando (condicion)

se puede condicionar salir del bucle o continuar con la siguiente permutación
con las palabrar clave [romper y continuar]

i = 0
desde i hasta 10
    si (i == 5)
        romper
     imprimir(i)
    fin
fin
salida: 0 1 2 3 4 5

i = 0
desde i hasta 10
    si (i == 5)
        continuar
        imprimir(i)
    fin
fin
salida: 0 1 2 3 4 6 7 8 9 10

Metodos / Funciones
---
un método consiste generalmente de una serie de sentencias para llevar a cabo una acción,
un juego de parámetros de entrada que regularán dicha acción o, las funciones se definen con
la palabra reservada[funcion]:
La estructura de un método es la siguiente:

funcion NombreFuncion ()
    #codigo
    retorno
fin

Se puede regresar el valor con la palabra clave [retorno]

funcion NombreFuncion (variable, variable2)
    i = 10;
    #codigo
    retorno i
fin

Se puede sobrecargar un método siempre y cuando los parámetros varien en numero.
funcion NombreFuncion (variable, variable2, variable3)
    i = 10;
    #codigo
    retorno i
fin

Clases
---
Una clase (class) es una plantilla para la creación de objetos de datos según un modelo predefinido.
Las clases se utilizan para representar entidades o conceptos, como los sustantivos en el lenguaje.
Se definen con la palabra clave [clase]

clase Auto
    #codigo
fin

las clases pueden contener constructor (inicialización de la clase), propiedades y métodos.

clase Auto
    #se define una propiedad con la palabra reservada propiedad
    propiedad Marca
    propiedad NoPuertas

    #se define un constructor con la palabra reservada constructor
    constructor ()
    fin

    constructor (marca, noPuertas)
        #se asigna el valor de la propiedad con la palabra clave [esta]
        esta.Marca = marca
        esta.NoPuertas = noPuertas
    fin

    #funcion ejemplo
    funcion Encender ()
        #codigo
        retorno
    fin
fin

Herencia: Se puede heredar de una clase con dos puntos (:) ClaseHijo : ClasePadre
---
clase Bochito : Auto
     constructor ()
         esta.NoPuertas = 2
     fin
fin

Palabras reservadas hasta el momento:
---
si    defecto verdadero    falso    fin    sino    elegir    caso    desde
hasta    cuando salto    mientras    hacer    romper    continuar    clase
propiedad    constructor    esta    lista    diccionario    retorno    funcion
