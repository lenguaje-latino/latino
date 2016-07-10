# CMake generated Testfile for 
# Source directory: /home/primi/src/latino
# Build directory: /home/primi/src/latino/codeblocks
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(00-vacio "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/00-vacio.lat")
ADD_TEST(01-comentarios "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/01-comentarios.lat")
ADD_TEST(02-hola "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/02-hola.lat")
ADD_TEST(03-variables "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/03-variables.lat")
ADD_TEST(04-expresiones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/04-expresiones.lat")
ADD_TEST(05-si "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/05-si.lat")
ADD_TEST(06-mientras "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/06-mientras.lat")
ADD_TEST(07-hacer "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/07-hacer.lat")
ADD_TEST(09-desde "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/09-desde.lat")
ADD_TEST(10-funciones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/10-funciones.lat")
ADD_TEST(11-fibonacci "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/11-fibonacci.lat")
ADD_TEST(12-factorial "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/12-factorial.lat")
ADD_TEST(16-funciones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/16-funciones_cadena.lat")
ADD_TEST(17-escribir_archivo "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/17-escribir_archivo.lat")
ADD_TEST(18-leer_archivo "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/18-leer_archivo.lat")
ADD_TEST(19-operadores_logicos "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/19-operadores_logicos.lat")
ADD_TEST(20-operadores_comparacion "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/20-operadores_comparacion.lat")
ADD_TEST(21-operador_ternario "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/21-operador_ternario.lat")
SUBDIRS(src)
