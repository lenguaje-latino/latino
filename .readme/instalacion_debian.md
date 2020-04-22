<p align="center">
<img src ="https://raw.githubusercontent.com/primitivorm/latino/master/logo/banner-300x.png" /><br>http://lenguaje-latino.org/<br><br>
</p>
<img src ="https://www.debian-tutorials.com/wp-content/uploads/2013/03/debian-banner.png" />


## Dependencias en Debian / Ubuntu

Antes de instalar latino, vamos a instalar todos paquetes necesarios:

```
# Debian / Ubuntu o derivados
sudo apt-get update
sudo apt-get install bison flex cmake gcc g++ libreadline-dev
```

## Clonar

```bash
 git clone --recursive https://github.com/primitivorm/latino
 cd latino
 git submodule update --init --recursive
```

## Compilar e instalar

Para compilarlo hay dos formas, puedes elegir la que desees:<br><br>
1.
```bash
 cmake .
 make
 sudo make install
 ```

2.

```bash
 sudo bash configure
 sudo make install
```


## Instalación desde paquete .deb:

```bash
 # Descarga la version que desees desde:  https://github.com/primitivorm/latino/releases/download/
sudo dpkg -i latino-version.deb
```

### Documentacion
1. http://manual.lenguaje-latino.org/
2. http://documentacion.lenguaje-latino.org/

### Dependencias

| Nombre paquete        | Versión |
| :---------------------|--------:|
| bison                 |  3.04   |
| flex                  |  2.5.39 |
| cmake                 |  3.3.1  |
| gcc                   |  4.9.3  |
| g++                   |  4.9.3  |
| libreadline-dev       |  7.0-2  |

### DESINSTALAR

#### 1- Opción
```bash
# Si instalaste con `sudo make install`:
sudo ./uninstall.sh
```

#### 2- Opción

Puedes ver un video de como proceder aquí: https://youtu.be/Q5xGm_Bp22k

 ```bash
sudo rm -f $(which latino)
 ```
#### 3- Opción

 Sólo Debian / Ubuntu. Si instalaste paquete deb

 ```bash
 sudo apt-get remove --purge latino -y
```

## Ayuda en nuestro foro

http://lenguaje-latino.org/foro/debian-ubuntu/


Cualquier aportación o sugerencia es bienvenida.
