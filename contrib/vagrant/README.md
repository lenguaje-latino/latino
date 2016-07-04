## Desarrollando Latino con Vagrant

Vagrant es un sistema que crea el desarrollo de peso ligero, 
ambiente autónomo como máquinas virtuales. Este directorio contiene un archivo Vagrant el cual
configura una máquina virtual de 64 bits con Ubuntu 12.04 Precise Pangolin en VirtualBox para la 
construcción de Latino.

### Requisitos

Para desarrollar sobre Vagrant, necesitas instalar [Oracle VirtualBox](https://www.virtualbox.org/wiki/Downloads) y
[Vagrant](http://downloads.vagrantup.com/). Despues desde la linea de comandos entra al directorio
`contrib/vagrant` y escribe lo siguiente:

```
vagrant up
```

Una maquina virtual sera descargada si es necesaria, creada, y provista con la dependencias para
desarrollar Latino. Por default se expone un servidor SSH a tu maquina local en el puerto 2222. 
Ver la [documentacion de Vagrant](http://docs.vagrantup.com/v2/) para un detalle completo de como usar Vagrant.