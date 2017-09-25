#!/bin/bash

action=install # Se selecciona la acción a hacer con los paquetes a seguir.
sudo=true # Aquí obligas al usuario a ser sudo.

echo "Instalando dependecias para Latino..."

packages_all=( # Aquí indicamos los programas (generales) que se van a instalar en derivados de DEBIAN, Suse Linux, Archlinux y Fedora
    "bison"
    "flex"
    "gcc"
    "g++"
    "curl"
    "libjansson-dev"
    "libhiredis-dev"
    "redis-server"
    "libcurl4-openssl-dev"
    "libgtk-3-dev"
    )

packages_debian=( # Aquí nomás los de Debian, Ubuntu o derivados
	"build-essential"
  "libreadline-dev"
    )

packages_fedora=( # Aquí de Fedora o derivados
	"build-essentials"
  "readline-devel"
	"kernel-devel"
	"jsoncpp"
    )

source tools/lib_dibs # Aquí incluimos la librería de las acciones
