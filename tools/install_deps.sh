#!/bin/bash

action=install # Se selecciona la acción a hacer con los paquetes a seguir.
sudo=true # Aquí obligas al usuario a ser sudo.
update_packages=true # Aquí indica que al finalizar la instalación se actualizen los repositorios.
upgrade_packages=true # Aquí indica que al finalizar la instalación se actualizen los paquetes.
autoremove_packages=true # Aquí indica que al finalizar la instalación se autoremuevan los paquetes innecesarios.

echo "Instalando dependecias para Latino..."

packages_all=( # Aquí indicamos los programas (generales) que se van a instalar en derivados de DEBIAN, Suse Linux, Archlinux y Fedora
    "bison"
    "flex"
    "gcc"
    "g++"
    "curl"
	"libjansson-dev"
    "libcurl4-openssl-dev"
    )
    
packages_debian=( # Aquí nomás los de Debian, Ubuntu o derivados
	"build-essential"
    )

packages_fedora=( # Aquí de Fedora o derivados
	"build-essentials"
	"kernel-devel"
	"jsoncpp"
    )

source tools/lib_dibs # Aquí incluimos la librería de las acciones
