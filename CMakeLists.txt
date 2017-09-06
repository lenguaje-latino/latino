CMAKE_MINIMUM_REQUIRED(VERSION 3.4.3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE) # Default to a Release build
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build [Release Debug]" FORCE)
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_TEST_NAME} gcov)
endif()

#find_path(GLIB_INCLUDE_DIR NAMES glib.h PATH_SUFFIXES glib-2.0)

PROJECT(latino)

ADD_SUBDIRECTORY(src)
#IF(UNIX)
#  execute_process(COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/tools/install_deps.sh)
#  execute_process(COMMAND bash ${CMAKE_CURRENT_LIST_DIR}/tools/key.sh)
#ENDIF(UNIX)

enable_testing ()
#se comentan los test que requieren entrada de datos leer()
add_test (NAME coverage COMMAND latino ejemplos/coverage.lat)

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
