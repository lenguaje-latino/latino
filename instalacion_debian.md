<p align="center">
<img src ="https://raw.githubusercontent.com/primitivorm/latino/master/logo/banner-300x.png" /><br>http://lenguaje-latino.org/<br><br>
<img src ="https://www.debian-tutorials.com/wp-content/uploads/2013/03/debian-banner.png" />
</p>

## Dependencias para instalar en DEBIAN

Antes de instalar latino, vamos a instalar todos paquetes necesarios: 

```
# Debian/Ubuntu o basados
sudo apt-get update; apt-get install bison flex cmake gcc g++ libjansson-dev libcurl4-openssl-dev libhiredis-dev redis-server curl libgtk-3-dev libreadline-dev libpthread-stubs0-dev
```

## Clonar


```bash
 git clone --recursive https://github.com/primitivorm/latino
 cd latino
 git submodule update --init --recursive
```

## Compilar e instalar

Para compilarlo hay dos formas, puedes elegir la que desees:<br><br>
#1
```bash
 cmake .
 make
 sudo make install
 ```

#2

```bash
 sudo ./configure
 sudo make install
```


Instalación en Ubuntu, DEBIAN, Mint o derivativos:

```bash
 # Versión 0.8.11
  # Descargar para sistemas de 32 bits(i386)
  wget https://github.com/primitivorm/latino/releases/download/v0.8.11/latino-0.8.11-Linux_i386.deb
  # Descargar para sistemas de 64 bits(amd64)
  wget https://github.com/primitivorm/latino/releases/download/v0.8.11/latino-0.8.11-Linux_amd64.deb
```


### Documentacion 
1. http://manual.lenguaje-latino.org/
2. http://documentacion.lenguaje-latino.org/


### COMPILAR

---

|Requiere               | Versión
| :---------------------|--------:
| bison                 |  3.04
| flex                  |  2.5.39
| cmake                 |  3.3.1
| gcc                   |  4.9.3
| g++                   |  4.9.3
| libjansson-dev        |  2.9 
| libcurl4-openssl-dev  |  *
| libhiredis-dev        |  *
| redis-server          |  *
| curl                  |  7.47.0
| libgtk-3-dev          |  3.0-2
| libreadline-dev       |  7.0-2
| libpthread-stubs0-dev |  0.3-4

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
sudo rm -f $(which latino)
 ```
 

#### 3- Opción

 **Sólo debian/ubuntu. si instalaste paquete deb
 
 ```bash
 sudo apt-get remove --purge latino -y```
```


## Ayuda en nuestro foro 

http://lenguaje-latino.org/foro/debian-ubuntu/


#### Cualquier aportación o sugerencia es bienvenida.
