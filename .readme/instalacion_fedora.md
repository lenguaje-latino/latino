<img width="40%" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/fedora.svg" />

# Dependencias
Antes de instalar latino, vamos a instalar todos paquetes necesarios:
```
# Fedora ó basados

sudo dnf install bison flex cmake gcc g++ libjansson-dev libcurl4-openssl-dev libhiredis-dev redis-server curl jansson-devel groupinstall "Development Tools" "Development Libraries" groupinstall "RPM Development Tools" redhat-lsb libgtk-3-dev
```

# INSTALAR
```bash
 git clone --recursive https://github.com/primitivorm/latino
 cd latino
 git submodule update --init --recursive
 cmake .
 make
 sudo make install
```

Puedes comprobar si hay versiones nuevas de paquetes para Fedora y Ubuntu en la sección [RELEASES](https://github.com/primitivorm/latino/releases)

### Compilar
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
| libgtk-3-dev |  3.0 | Linux |
| kernel-devel| |Solo Fedora|
| jsoncpp| |Solo Fedora|

# DESINSTALAR
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

# Ayuda y Documentación:
[Foro de Latino para Mac](http://lenguaje-latino.org/foro/fedora-centos/)
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.