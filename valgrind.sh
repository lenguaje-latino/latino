#valgrind -v --leak-check=full --track-origins=yes ./latino ../ejemplos/coverage.lat
cd bin
valgrind -v --leak-check=full ./latino ../ejemplos/coverage.lat
cd ..
