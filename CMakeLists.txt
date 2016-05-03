CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(latino)

ADD_SUBDIRECTORY(src)

enable_testing ()
add_test (NAME test COMMAND latino -v)
