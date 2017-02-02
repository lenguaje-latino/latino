#!/usr/bin/bash
if [ -f "/etc/debian_version" ]; then
	if [ `whoami` != "root" ]; then
		printf "%s\n\t\033[1m%s\033[0m\n%s\n\n\033[3m" "Para añadir una llave para que al hacer:"\
		"sudo apt upgrade"\
		"se actualize Latino, ejecuta esta comando con sudo al inicio."; exit
	fi

	if [[ `grep "lenguaje-latino" /etc/apt/sources.list` ]]; then
		echo "Ya haz añadido el repositorio de Latino anteriormente"
		echo "Abortado."; exit
	fi
	printf "¿Deseas que añadir el repositorio de Latino en /etc/apt/sources.list?\n[S/n] "
	printf "\033[3m"
	read -t 8 opt
	case $opt in

		"Y"|"y"|"s"|"S")
		echo "deb http://debian.lenguaje-latino.org stable main" >> /etc/apt/sources.list
		wget -q -O - http://debian.lenguaje-latino.org/certificado.key | apt-key add -
		exit
		;;
		"")
		echo -e "\nAnulado por tiempo de espera expirado o valor nulo."
		printf "\033[3m"
		exit
		;;
		*)
		echo "Anulado."
		printf "\033[3m"
		exit
	esac
else exit; fi
