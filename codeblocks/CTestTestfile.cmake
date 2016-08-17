# CMake generated Testfile for 
# Source directory: /home/primi/src/latino
# Build directory: /home/primi/src/latino/codeblocks
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(00-vacio "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/00-vacio.lat")
add_test(01-comentarios "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/01-comentarios.lat")
add_test(02-hola "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/02-hola.lat")
add_test(03-variables "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/03-variables.lat")
add_test(04-expresiones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/04-expresiones.lat")
add_test(05-si "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/05-si.lat")
add_test(06-mientras "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/06-mientras.lat")
add_test(07-hacer "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/07-hacer.lat")
add_test(09-desde "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/09-desde.lat")
add_test(10-funciones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/10-funciones.lat")
add_test(11-fibonacci "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/11-fibonacci.lat")
add_test(12-factorial "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/12-factorial.lat")
add_test(16-funciones "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/16-funciones_cadena.lat")
add_test(17-escribir_archivo "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/17-escribir_archivo.lat")
add_test(18-leer_archivo "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/18-leer_archivo.lat")
add_test(19-operadores_logicos "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/19-operadores_logicos.lat")
add_test(20-operadores_comparacion "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/20-operadores_comparacion.lat")
add_test(21-operador_ternario "/home/primi/src/latino/codeblocks/bin/latino" "ejemplos/21-operador_ternario.lat")
subdirs(src)
