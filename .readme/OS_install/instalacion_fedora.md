<img width="40%" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/fedora.svg" />

Para instalar Latino en Fedora, primero abrimos la consola (Terminal) y ejecutamos los siguientes comandos:

```bash
sudo dnf -y update
sudo dnf -y install gcc-c++ git cmake kernel-devel readline-devel
```

Una vez concluido esto, pasamos a instalar propiamente Latino en nuestro sistema

```bash
cd ~
sudo git clone https://github.com/lenguaje-latino/latino-core
cd latino-core
sudo cmake .
sudo make install 
```

… y listo! para ejecutar Latino solo escribimos en nuestra terminal el comando latino

# DESINSTALAR
Para desinstalar Latino de su sistema, necesitara el archivo "latino_desinstalacion-linux.sh" el cual puede conseguir desde el siguiente repositorio:
[https://github.com/lenguaje-latino/instalacion](https://github.com/lenguaje-latino/instalacion)

```bash
sudo chmod +x latino_desinstalacion-linux.sh && ./latino_desinstalacion-linux.sh
```

# Ayuda y Documentación:
[Comunidad de Latino en Stackoverflow](https://es.stackoverflow.com/questions/tagged/latino)<br/>
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.