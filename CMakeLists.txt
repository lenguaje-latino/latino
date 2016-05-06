CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(latino)

ADD_SUBDIRECTORY(src)

enable_testing ()
add_test (NAME test COMMAND latino -v)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_TEST_NAME} gcov)
endif()
