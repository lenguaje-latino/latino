#Arquitectura del lenguaje de programación latino

##Introducción
Un intérprete es un procesador del lenguaje que analiza un programa escrito en
un lenguaje de alto nivel y si es correcto lo ejecuta directamente en el lenguaje
de la máquina en que se está ejecutando el intérprete.

##Ventajas de los intérpretes
__Fexibilidad:__ los lenguajes interpretativos suelen ser más flexibles y permiten
realizar acciones más complejas a menudo imposibles o muy difíciles de procesar
para un compilador.

__Facilidad de depuración:__ La ejecución del programa puede interrumpirse en
cualquier momento, corregir o modificar el programa sin necesidad de compilar
nuevamente el código.

__Rapidez en el desarrollo:__ Los programadores que utilizan un lenguaje
interpretado suelen conseguir mayor eficiencia de programación que los que
programan en lenguajes compilables.

##Estructura de un intérprete
La diferencia principal entre un compilador y un intérprete estriba en la ausencia
de una etapa de generación de código, que sustituye por un componente de ejecución
de código.

![interprete](https://raw.githubusercontent.com/primitivorm/latino/master/doc/interprete.png "interprete")

La estructura del lenguaje de programación latino radica principalmente en los
siguientes archivos dentro de la carpeta src/

__structs.h:__  Contiene las estructuras de datos necesarias para el manejo del lenguaje.

__parse.y:__ Contiene las reglas gramáticales para el analizador gramátical del
lenguaje, se utiliza el programa bison para la generación del código en C.

para más información ver http://www.gnu.org/software/bison/manual/bison.html

__lex.l:__ Contiene las reglas lexicas para el analizador lexico del lenguaje, se utiliza el programa flex para la generación del código en C.

para más información ver http://flex.sourceforge.net/manual/

__eval.c:__ Contiene la lógica del lenguaje para evaluar las expresiones.

__latino.h:__ Contiene las configuraciones del lenguaje.

__latino.c:__ Contiene la llamada principal del interprete del lenguaje.

##Definición de la sintaxis
En esta sección se describirá la gramática libre de contexto del lenguaje latino,
o simplemente gramática.
Una gramática describe naturalmente la estructura gerarquica de la mayoria de
lenguajes de programación. Por ejemplo una sentencia if-else in Java puede ser de la siguiente forma:

__if__ ( expression ) statement __else__ statement

Esto es, una sentencia if-else es la concatenación de la palabra reservada __if__,
un parentesis que abre, una expresion, un parentesis que cierra, una sentencia,
la palabra __else__, y otra sentencia. Usando la variable expr para denotar una
expresion y la variable stmt para denotar una sentencia, esta gramática estructurada
puede ser definida como:

stmt -> __if__ ( expr ) stmt __else__ stmt

En donde la flecha -> puede ser leida como "puede tener la forma", asi una regla puede ser
llamada producción. En una producción, los elementos lexicos como la palabra __if__ y los parentesis
son llamados TERMINALES. Las variables como expr y stmt representan una secuencia de terminales y
son llamadas NO TERMINALES.
