#Latino
[![Join the chat at https://gitter.im/primitivorm/latino](https://badges.gitter.im/primitivorm/latino.svg)](https://gitter.im/primitivorm/latino?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![https://telegram.me/joinchat/EBHu7z6l6_o0_qtHlnbdOw](https://img.shields.io/badge/Soporte-Telegram-green.svg?style=plastic)](https://telegram.me/joinchat/EBHu7z6l6_o0_qtHlnbdOw)
[![Build Status](https://travis-ci.org/primitivorm/latino.svg?branch=master)](https://travis-ci.org/primitivorm/latino)
<a href="http://lenguaje-latino.org"><img src="https://img.shields.io/npm/l/vue.svg" alt="License"></a>
[![codecov.io](http://codecov.io/github/primitivorm/latino/coverage.svg?branch=master)](http://codecov.io/github/primitivorm/latino?branch=master)

![latino sublime](https://raw.githubusercontent.com/lenguaje-latino/latino-sublimetext-plugin/master/latino_sublime.png "latino sublime")

Este proyecto nace de la necesidad de incrementar la educación de nivel básico (primaria y secundaria)
debido a que los niños tienen la capacidad de entender la lógica a muy temprana edad y es en esta edad
cuando más aprenden, esto motivará a los niños y jovenes por interesarse en el mundo del desarrollo de aplicaciones.

¿Y por qué un lenguaje de programación más?
Si bien se sabe, que ya hay muchos lenguajes de programación; pero no tenemos un lenguaje para programar
con sintaxis en español, y entonces ¿por qué no hacer uno?

¿Cuántos de ustedes no batallaron con el inglés?
¿Cúal sería la ventaja si no tuvieras que preocuparte por aprender javascript, html, css y mysql para desarrollar tus páginas web?

Pues bien si este proyecto suena ambicioso, realmente les puedo decir que dependerá de la participación de todos nosotros para que esto sea posible.

A continuación menciono las principales características de este proyecto:

1. Simplicidad: la sintaxis deberá de ser lo más natural posible al lenguaje español.
2. Sencillo de aprender: al ser simple aprenderás más rápido éste nuevo lenguaje.
3. Libre: cualquiera puede descargar el código fuente del lenguaje, extender las librerías básicas y crear sus propias librerías si así lo desea.
4. Lenguaje de alto nivel: cuando escribas código no tendrás que preocuparte por detalles de bajo nivel, como manejar la memoria empleada en tu programa.
5. Portable: cuando escribas tus programas en “latino” podrás ejecutarlo en cualquier plataforma.
6. Orientado a objetos: permitirá programación orientada a procedimientos así como orientada a objetos.

El lenguaje deberá de ser de código abierto bajo la licencia del MIT por ser la menos restrictiva:
http://opensource.org/licenses/MIT

Leer LICENSE.txt


## INSTALAR

### Instalar en Linux

Cualquier versión/distribución de linux

```bash
 git clone --recursive https://github.com/primitivorm/latino
 cd latino
 git submodule update --init --recursive
 cmake .
 make
 sudo make install
```

Ahora en una sola linea

```
 git clone --recursive https://github.com/primitivorm/latino && cd latino && git submodule update --init --recursive && cmake . && make && sudo make install

```


Instalación en Ubuntu, DEBIAN, Mint o derivativos:

```bash
 # Versión 0.8.11
  # Descargar para sistemas de 32 bits(i386)
  wget https://github.com/primitivorm/latino/releases/download/v0.8.11/latino-0.8.11-Linux_i386.deb
  # Descargar para sistemas de 64 bits(amd64)
  wget https://github.com/primitivorm/latino/releases/download/v0.8.11/latino-0.8.11-Linux_amd64.deb
```

Instalación:
```bash
  sudo dpkg -i *0.8.11*.deb
```

Puedes comprobar si hay versiones nuevas en [RELEASES](https://github.com/primitivorm/latino/releases)


### Instalar en Windows
1. Descargue el instalador de la última version de https://github.com/primitivorm/latino/releases
2. Descompima el archivo zip
3. Ejecute el instalador

#### Nota:
Puede requerir el framework de C++, descarguelo desde la pagina oficial de Microsoft:
https://www.microsoft.com/es-ES/download/details.aspx?id=48145

### COMPILAR

---

|Requiere | Versión | SO |
| :---    |    ---: |:---|
| bison   |    3.04 |Linux|
| flex    |  2.5.39 |Linux|
| cmake   |   3.3.1 |Linux|
| gcc     |   4.9.3 |Linux|
| g++     |   4.9.3 |Linux|
| libjansson-dev |   2.9   |Linux|
| libcurl4-openssl-dev |  |Linux|
| libhiredis-dev |  |Linux|
| redis-server |  |Linux|
| curl    | 7.47.0 |Linux|
| kernel-devel| |Solo Fedora|
| jsoncpp| |Solo Fedora|
--

### DESINSTALAR

#### 1- Opción
```bash
# Si instalaste con `sudo make install`:
sudo ./uninstall.sh
```

#### 2- Opción

Puedes ver un video de como proceder aca https://youtu.be/Q5xGm_Bp22k

Pirmero debes saber donde esta instalado

 ```bash
 whereis latino
 ```

 Te dará algo parecido a esto:

 ```bash
 latino: /usr/local/bin/latino

 ```

 Ahora que sabemos dónde está solamente lo borramos:
 ```bash
 sudo rm /usr/local/bin/latino

 ```

#### 3- Opción

 **Sólo debian/ubuntu. si instalaste paquete deb
 ```bash
 # Ubuntu 16.x.x en adelante
 sudo apt remove latino
 # Ubuntu 14.x.x hacía atrás
 sudo apt-get remove latino
 ```

####Cualquier aportación o sugerencia es bienvenida.
