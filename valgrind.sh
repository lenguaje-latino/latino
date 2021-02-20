#valgrind -v --leak-check=full --track-origins=yes ./latino ../ejemplos/coverage.lat
#valgrind -v --leak-check=full --track-origins=yes ./latino ../ejemplos/leaks.lat
#valgrind -v --leak-check=full ./latino ../ejemplos/leaks.lat
valgrind -v --leak-check=full src/latino ejemplos/leaks.lat