function limpiar_updates() {

while true; do {
   echo -en 'No hay apikey configurada\nEscribe tu apikey aquí: ' && read ApiKey
	res=$(curl -s 'https://api.telegram.org/bot'$ApiKey'/getUpdates')

	# Offset
	OFFSET=$(echo "$res" | jq -r '.result[0].update_id +1')

	if [ "$OFFSET" != 1 ]; then
		echo -e '\e[1;33m[ consulta con offset ] [ update_id = '$(expr $OFFSET - 1 )' ]\e[0m'
 		curl -s 'https://api.telegram.org/bot'$ApiKey'/getUpdates?offset='$OFFSET&>/dev/null
	else
		clear && echo -e '\e[0;32mTerminado!\e[0m'
		break
	fi

}; done
}


if [ "$1" == "limpiar" ]; then
    limpiar_updates
fi


if [ $0 ] || [ ! $1 ]; then
    latino bot.lat
fi
