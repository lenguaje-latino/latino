<img width="40%" src ="https://raw.githubusercontent.com/MelvinG24/Latino/master/.readme/imgs/fedora.svg" />

# Dependencias
Antes de instalar latino, vamos a instalar todos paquetes necesarios:
```
su
sudo dnf update
sudo dnf install gcc-c++ git cmake kernel-devel
sudo dnf install readline-devel
```

# INSTALAR
```bash
cd ~
sudo git clone https://github.com/lenguaje-latino/latino-core
cd latino-core
```

# DESINSTALAR
#### 1- Opción
```bash
sudo ./uninstall.sh
```

#### 2- Opción
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
[Comunidad de Latino en Stackoverflow](https://es.stackoverflow.com/questions/tagged/latino)<br/>
[Manual Latino](http://manual.lenguaje-latino.org/)

Cualquier aportación o sugerencia es bienvenida.