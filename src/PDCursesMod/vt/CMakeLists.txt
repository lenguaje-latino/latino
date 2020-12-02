cmake_minimum_required(VERSION 3.11)

# if(NOT CMAKE_BUILD_TYPE)
#     set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build, options are: Debug, Release, or MinSizeRel." FORCE)
#     message(STATUS "No build type specified, defaulting to MinSizeRel.")
# endif()

PROJECT(vt VERSION "${PROJECT_VERSION}" LANGUAGES C)

INCLUDE(project_common)

if(DOS)
    string(APPEND CMAKE_C_FLAGS " -DDOS")
endif()

if(WATCOM)
    if(WATCOM_DOS16)
        string(APPEND CMAKE_C_FLAGS " -ml")  # memory model: options are large (-ml), memdium (-mm), small (-ms)
    else()
        string(APPEND CMAKE_C_FLAGS " -mf")  # memory model: options are flat (-mf), large (-ml), memdium (-mm), small (-ms)
    endif()
endif()

# demo_app(../demos firework)
# demo_app(../demos ozdemo)
# demo_app(../demos newtest WIN32)
# demo_app(../demos ptest)
# demo_app(../demos rain)
# demo_app(../demos testcurs)
# demo_app(../demos tuidemo)
# demo_app(../demos worm)
# demo_app(../demos xmas)


SET(CPACK_COMPONENTS_ALL applications)
