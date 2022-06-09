<img width="40%" src ="../imgs/CentOS.svg" />

Para instalar Latino en RHEL (Red Hat) y CentOS, primero abrimos la consola (Terminal) y ejecutamos los siguientes comandos:

## CentOS ^9/8
CentOS 8 en adelante disponen tanto de YUM y DNF para la instalación de paquetes, en este caso usaremos DNF ya que es más rápido que YUM
```bash
sudo dnf -y update
sudo dnf -y install git cmake readline-devel
sudo dnf -y groupinstall "Development Tools"
```
## CentOS 7/6/5
CentOS 7 y previos solo disponen tanto de YUM para la instalación de paquetes
```bash
sudo yum -y update
sudo yum -y install git cmake readline-devel
sudo yum -y groupinstall "Development Tools"
```
### Solo para CentOS 7/6/5
Con CentOS 7 y previos no es posible la instalación de CMake ^3, la cual es la versión requerida para compilar Latido desde su código fuente, por esta razón procedemos a ejecutar los siguientes pasos
```bash
sudo yum -y remove cmake
sudo yum -y install epel-release
sudo yum -y install epel-release cmake3

sudo rm -rf /usr/bin/cmake
sudo ln -s /usr/bin/cmake3 /usr/bin/cmake
cmake --version
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