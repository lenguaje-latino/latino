#!/usr/bin/bash
if [ -f "/etc/debian_version" ]; then
if [ `whoami` != "root" ]; then
	echo "Para añadir el keyfile necesitas permisos root"; exit
fi

if [[ `grep "lenguaje-latino" /etc/apt/sources.list` ]]; then
	echo "Ya haz añadido el repositorio de Latino anteriormente"
	echo "Abortado."; exit
fi
echo "Hemos detectado  que estás usando Debian o derivadas"
printf "%s \e[1;34m%s\e[0m %s\n" "Queremos añadir una llave para que cuando hagas" "apt upgrade" "se actualize Latino"
echo -n "¿Deseas añadirla? [S/n] "
read -t 13 opt
case $opt in

"Y"|"y"|"s"|"S")
	echo "deb http://debian.lenguaje-latino.org stable main" >> /etc/apt/sources.list
	wget -q -O - http://debian.lenguaje-latino.org/certificado.key | apt-key add -
	exit
	;;
"")
	echo -e "\nAnulado por tiempo de espera expirado o valor nulo."
	exit
;;
*)
	echo "Anulado."
	exit
esac
else exit; fi
