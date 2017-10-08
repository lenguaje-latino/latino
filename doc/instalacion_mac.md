<p align="center">
<img src ="https://raw.githubusercontent.com/primitivorm/latino/master/logo/banner-300x.png" /><br>http://lenguaje-latino.org/
</p>
<img src ="mac.png" />

## Dependencias
Antes de instalar latino, vamos a instalar todos paquetes necesarios:

```bash
sudo port selfupdate
sudo port install flex bison cmake gcc g++ clang readline
```

## INSTALAR
```bash
 git clone --recursive https://github.com/primitivorm/latino
 cd latino
 git submodule update --init --recursive
 cmake .
 make
 sudo make install
```

### Documentacion
1. http://manual.lenguaje-latino.org/
2. http://documentacion.lenguaje-latino.org/


### Pre requisitos

| Nombre paquete        | Versión
| :---------------------|--------:
| bison                 |  3.04
| flex                  |  2.5.39
| cmake                 |  3.3.1
| gcc                   |  4.9.3
| g++                   |  4.9.3
| readline              |  7.0-2

### DESINSTALAR

#### 1- Opción
```bash
# Si instalaste con `sudo make install`:
sudo bash uninstall.sh
```

#### 2- Opción
 ```
 bash
sudo port -f uninstall latino
 ```

## Ayuda en nuestro foro

http://lenguaje-latino.org/foro/mac/

Cualquier aportación o sugerencia es bienvenida.
