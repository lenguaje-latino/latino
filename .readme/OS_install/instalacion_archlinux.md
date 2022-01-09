<img width="30%" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/archlinux.svg" />

Para instalar Latino en Arch Linux y Manjaro, primero abrimos la consola (Terminal) y ejecutamos los siguientes comandos:

```bash
sudo pacman -Syu
sudo pacman -S base-devel
```

Una vez concluido esto, pasamos a instalar propiamente Latino en nuestro sistema

```bash
cd ~
sudo git clone https://github.com/lenguaje-latino/latino-core
cd latino-core
cmake .
sudo make install 
```

… y listo! para ejecutar Latino solo escribimos en nuestra terminal el comando latino

# DESINSTALAR
#### 1- Opción
```bash
# Si instalaste con `sudo make install`:
sudo ./uninstall.sh
```

# Ayuda y Documentación:
[Comunidad de Latino en Stackoverflow](https://es.stackoverflow.com/questions/tagged/latino)<br/>
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.