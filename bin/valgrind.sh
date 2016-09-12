#valgrind -v --leak-check=full --track-origins=yes ./latino ../ejemplos/coverage.lat
#valgrind -v --leak-check=full ./latino ../ejemplos/debug.lat
valgrind -v --leak-check=full --show-leak-kinds=all ./latino ../ejemplos/00-vacio.lat
