CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_TEST_NAME} gcov)
endif()

PROJECT(latino)

ADD_SUBDIRECTORY(src)

enable_testing ()
add_test (NAME test COMMAND latino -v)
