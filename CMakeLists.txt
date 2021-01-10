#[[
/***********************************************************************************
 * Copyright (c) 2015-2020 Lenguaje-Latino, programación con sintaxis al Español.  *
 *                                                                                 *
 *                            CMake_Root de Latino                                 *
 ***********************************************************************************/
]]


#
# CMAKE configuraciones
cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

project(latino)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build [Debug]" FORCE) # Default to a Debug build
endif()
set(CMAKE_BUILD_TYPE "Debug")


# if(CMAKE_COMPILER_IS_GNUCXX)
#     target_link_libraries(${PROJECT_TEST_NAME} gcov)
# endif()

set(program_files "$ENV{ProgramFiles}")

#
# Mensajes de construcion
include(LatLogo)
message(STATUS ".............................................." )
message(STATUS ">>>>>>   Latino ")
message(STATUS ".............................................." )
message(STATUS "Generador .............. ${CMAKE_GENERATOR}"    )
message(STATUS "Tipo de Build .......... ${CMAKE_BUILD_TYPE}"   )

include(GetLatVersion)
message(STATUS "Latino Version ......... ${LATINO_VERSION}"     )

include(BuildLatOptions)


#
# Codigo Fuente
add_subdirectory(src)


#
# Opciones
if(LAT_EJEMPLOS)
  
endif(LAT_EJEMPLOS)


#
# Extras

#find_path(GLIB_INCLUDE_DIR NAMES glib.h PATH_SUFFIXES glib-2.0)

#IF(UNIX)
#  execute_process(COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/tools/install_deps.sh)
#  execute_process(COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/tools/key.sh)
#ENDIF(UNIX)

enable_testing()
#se comentan los test que requieren entrada de datos leer()
add_test(NAME coverage COMMAND latino ejemplos/coverage.lat)

#if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
#    include(CodeCoverage)
#    setup_target_for_coverage(${PROJECT}_coverage ${PROJECT_TEST_NAME} coverage)
#
#    SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage -coverage")
#    SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage -coverage")
#endif() #CMAKE_BUILD_TYPE STREQUAL "Coverage"

set(GCOV "gcov")
if(DEFINED ENV{GCOV})
  set(GCOV $ENV{GCOV})
endif()
add_custom_target(coverage
  COMMAND lcov --gcov-tool ${GCOV} --capture --directory . --output-file coverage.info
  COMMAND lcov --gcov-tool ${GCOV} --remove coverage.info "/usr/*" "*/test/*" --output-file coverage.info
  COMMAND lcov --gcov-tool ${GCOV} --list coverage.info
  COMMAND genhtml coverage.info --output-directory ./coverage
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  VERBATIM)
