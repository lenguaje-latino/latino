<img width="20%" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/debian.svg" />

# Dependencias en Debian / Ubuntu
Antes de instalar latino, vamos a instalar todos paquetes necesarios:
```bash
sudo apt-get update
sudo apt-get install git cmake gcc g++
sudo apt-get install libreadline-dev libpthread-stubs0-dev
```

# Clonar
```bash
cd ~
sudo git clone https://github.com/lenguaje-latino/latino-core
cd latino-core
```

# Compilar e instalar
Para compilarlo hay dos formas, puedes elegir la que desees:<br><br>
##### I.
```bash
 cmake .
 make
 sudo make install
 ```

##### II.
```bash
 sudo bash configure
 sudo make install
```

# Instalación desde paquete .deb:
```bash
 # Descarga la version que desees desde:  https://github.com/primitivorm/latino/releases/download/
sudo dpkg -i Latino-XXX-Debian.deb
```

# DESINSTALAR
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

# Ayuda y Documentación:
[Comunidad de Latino en Stackoverflow](https://es.stackoverflow.com/questions/tagged/latino)<br/>
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.