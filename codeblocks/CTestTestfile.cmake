# CMake generated Testfile for 
# Source directory: C:/src/latino
# Build directory: C:/src/latino/codeblocks
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/00-vacio.lat")
add_test(test1 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/01-comentarios.lat")
add_test(test2 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/02-hola.lat")
add_test(test3 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/03-variables.lat")
add_test(test4 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/04-expresiones.lat")
add_test(test5 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/05-si.lat")
add_test(test6 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/06-mientras.lat")
add_test(test7 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/07-hacer.lat")
add_test(test9 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/09-desde.lat")
add_test(test10 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/10-funciones.lat")
add_test(test11 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/11-fibonacci.lat")
add_test(test12 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/12-factorial.lat")
add_test(test16 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/16-funciones_cadena.lat")
add_test(test17 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/17-escribir_archivo.lat")
add_test(test18 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/18-leer_archivo.lat")
add_test(test19 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/19-operadores_logicos.lat")
add_test(test20 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/20-operadores_comparacion.lat")
add_test(test21 "C:/src/latino/codeblocks/bin/latino.exe" "ejemplos/21-operador_ternario.lat")
subdirs(src)
