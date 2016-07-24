#Latino
[![Join the chat at https://gitter.im/primitivorm/latino](https://badges.gitter.im/primitivorm/latino.svg)](https://gitter.im/primitivorm/latino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![https://telegram.me/joinchat/EBHu7z6l6_o0_qtHlnbdOw](https://img.shields.io/badge/Soporte-Telegram-green.svg?style=plastic)](https://telegram.me/joinchat/EBHu7z6l6_o0_qtHlnbdOw)
[![Build Status](https://travis-ci.org/primitivorm/latino.svg?branch=master)](https://travis-ci.org/primitivorm/latino)
<a href="http://lenguaje-latino.org"><img src="https://img.shields.io/npm/l/vue.svg" alt="License"></a>
[![codecov.io](http://codecov.io/github/primitivorm/latino/coverage.svg?branch=master)](http://codecov.io/github/primitivorm/latino?branch=master)

![latino sublime](https://raw.githubusercontent.com/primitivorm/latino/master/SublimeTextSyntax/latino_sublime.png "latino sublime")

Este proyecto nace de la necesidad de incrementar la educación de nivel básico (primaria y secundaria)
debido a que los niños tienen la capacidad de entender la lógica a muy temprana edad y es en esta edad
cuando más aprenden, esto motivará a los niños y jovenes por interesarse en el mundo del desarrollo de aplicaciones.

¿Y por que un lenguaje de programación más?
Si es bien sabido que ya hay muchos lenguajes de programación; pero no tenemos un lenguaje para programar
con sintaxis en español, y entonces ¿por qué no hacer uno?

¿Cuantos de ustedes no batallaron con el inglés?
¿Cúal seria la ventaja si no tuvieras que preocuparte por aprender javascript, html, css y mysql para desarrollar tus paginas web?

Pues bien si este proyecto suena ambicioso, realmente les puedo decir que dependerá de la participación de todos nosotros para que esto sea posible.

A continuación menciono las principales caracteristas de este proyecto:

1. Simplicidad: La sintaxis debera de ser lo más natural posible al lenguaje español.
2. Sencillo de aprender: Al ser simple aprenderas más rápido este nuevo lenguaje.
3. Libre: Cualquiera puede descargar el código fuente del lenguaje, extender las librerias basicas y crear sus propias librerias si asi lo desea.
4. Lenguaje de alto nivel: Cuando escribas código no tendrás que preocuparte por detalles de bajo nivel, como manejar la memoria empleada en tu programa.
5. Portable: Cuando escribas tus programas en “latino” podras ejecutarlo en cualquier plataforma.
6. Orientado a Objetos: Permitirá programación orientada a procedimientos así como orientada a objetos.

El lenguaje deberá de ser de código abierto bajo la licencia del MIT por ser la menos restrictiva:
http://opensource.org/licenses/MIT

Leer LICENSE.txt


###INSTALAR

#####Instalar en Linux

Cualquier versión de linux

```
 git clone https://github.com/primitivorm/latino
 cd latino
 cmake .
 make
 sudo make install
 
```


#####Otras opciones para instalar en Linux

Para instalar en Linux hay dos formas de hacerlo, la primera es con el install (automático y con utilidades) y la segunda es manualmente.

Para obtener el instalador ejecute el siguiente comando en su terminal.
```bash
wget https://github.com/primitivorm/latino/raw/master/install && chmod +x install
```


###### Paquete de Debian ó Ubuntu


``` bash
# Debian ó Ubuntu (amd64)
 # Con el instalador
 ./install --deb
 
 # Ó forma manual, mismo proceso.
 wget https://github.com/primitivorm/latino/releases/download/v0.5/latino-0.5.0-Linux.deb && sudo dpkg -i latino-0.5.0-Linux.deb && sudo rm -f latino-0.5.0-Linux.deb
```
 * [Descargar](https://github.com/primitivorm/latino/releases/download/v0.5/latino-0.5.0-Linux.deb)
 
--


######Otras distribuiciones:

``` bash
# Ejecuta esto si usas otra distribuición.
 # Con el instalador
 ./install --all
 ./install --clonar # Clona el repositorio (opcional)
 
```

---

#####Instalar en Windows
1. Descargue el instalador de la última version de https://github.com/primitivorm/latino/releases
2. Descompima el archivo zip
3. Ejecute el instalador

#####Nota:
Puede requerir el framework de C++, descarguelo desde la pagina oficial de Microsoft:
Si tu sistema operativo esta en español:
https://www.microsoft.com/es-ES/download/details.aspx?id=49984
Si tu sistema operativo esta en ingles:
https://www.microsoft.com/en-us/download/details.aspx?id=49984



### COMPILAR

---

|Requiere | Versión |
| :---    |    ---: |
| bison   |    3.04 |
| flex    |  2.5.39 |
| cmake   |   3.3.1 |
| gcc (Linux)|4.9.3 |
| CodeBlocks | * |
| Visual Studio Community Edition| * |
| CodeLite | * |


--

#####Compilar en Visual Studio https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx
1. Abra la solución visualstudio/latino.sln
2. Compile

--

#####Compilar en CodeBlocks http://www.codeblocks.org/
1. Abra el proyecto codeblocks/latino.cbp
2. Compile

--

#####Compilar en CodeLite http://codelite.org//
1. Abra el proyecto codelite/latino.workspace
2. Compile

####Cualquier aportación o sugerencia es bienvenida.
