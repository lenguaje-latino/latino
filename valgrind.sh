#valgrind -v --leak-check=full --track-origins=yes ./latino ../ejemplos/coverage.lat
valgrind -v --leak-check=full src/latino ejemplos/coverage.lat