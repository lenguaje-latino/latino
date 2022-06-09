<img width="20%" src ="../imgs/debian.svg" />

Para instalar Latino en Debian y Ubuntu, primero abrimos la consola (Terminal) y ejecutamos los siguientes comandos:

```bash
sudo apt-get update
sudo apt-get install git cmake build-essential libreadline-dev libpthread-stubs0-dev
```
Una vez concluido esto, pasamos a instalar propiamente Latino en nuestro sistema

```bash
cd ~
sudo git clone https://github.com/lenguaje-latino/latino-core
cd latino-core
sudo cmake .
sudo make install 
```

# Instalación desde paquete .deb:
```bash
 # Descarga la version que desees desde:  https://github.com/lenguaje-latino/latino/releases/latest
sudo dpkg -i latino-XXX-Debian.deb
```

… y listo! para ejecutar Latino solo escribimos en nuestra terminal el comando latino

# DESINSTALAR
#### 1- Opción
Para desinstalar Latino de su sistema, necesitara el archivo "latino_desinstalacion-linux.sh" el cual puede conseguir desde el siguiente repositorio:
[https://github.com/lenguaje-latino/instalacion](https://github.com/lenguaje-latino/instalacion)

```bash
sudo chmod +x latino_desinstalacion-linux.sh && ./latino_desinstalacion-linux.sh
```

#### 2- Opción
 Sólo Debian / Ubuntu. Si instalaste paquete .deb
 ```bash
 sudo apt-get remove --purge latino -y
```

# Ayuda y Documentación:
[Comunidad de Latino en Stackoverflow](https://es.stackoverflow.com/questions/tagged/latino)<br/>
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.