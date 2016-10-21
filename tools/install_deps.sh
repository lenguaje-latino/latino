#!/bin/bash

echo "Instalando dependecias de "$(lsb_release -si)" para Latino..."

action=install

packages_debian=(
	"bison"
	"flex"
	"build-essential"
	"gcc"
	"g++"
	"libjansson-dev"
	"curl"
	"libcurl4-openssl-dev"
    )

packages_fedora=(
	"bison"
	"flex"
	"build-essentials"
	"gcc"
	"g++"
	"libjansson-dev"
	"curl"
	"libcurl4-openssl-dev"
	"kernel-devel"
	"jsoncpp"
    )

source tools/lib_dibs

update_packages_debian
update_packages_fedora
autoremove_packages_debian
autoremove_packages_fedora
