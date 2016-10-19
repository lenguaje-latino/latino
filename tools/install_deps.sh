#!/usr/bin/bash
echo "Instalando dependecias de paquetes para latino..."
OS=$(lsb_release -si)
if [ "$OS" == "Ubuntu" ] || [ "$OS" == "Debian" ] ;
then
  sudo apt-get update -qq -y
  sudo apt-get install bison -y
  sudo apt-get install flex -y
  sudo apt-get install build-essential -y
  sudo apt-get install gcc -y
  sudo apt-get install g++ -y
  sudo apt-get install libjansson-dev -y
  sudo apt-get install libcurl4-openssl-dev -y
  sudo apt-get install curl -y
  sudo apt-get autoremove -qq -y
elif [ "$OS" == "Fedora" ] ;
then
  sudo dnf update
  sudo dnf install bison
  sudo dnf install flex
  sudo dnf install build-essentials
  sudo dnf install gcc
  sudo dnf install g++
  sudo dnf install libjansson-dev
  sudo dnf install libcurl4-openssl-dev
  sudo dnf install curl
  sudo dnf install kernel-devel
  sudo dnf install jsoncpp
  sudo dnf autoremove
fi
