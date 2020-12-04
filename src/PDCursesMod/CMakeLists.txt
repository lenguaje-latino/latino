cmake_minimum_required(VERSION 3.11)

include (get_version)
project(pdcurses VERSION "${CURSES_VERSION}" LANGUAGES C)

if(MSVC)
    set(CMAKE_DEBUG_POSTFIX d)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")  # enable parallel builds
endif()

message(STATUS ".............................................." )
message(STATUS ">>>>>>   PDCursesMod ")
message(STATUS ".............................................." )
# message(STATUS "Generator .............. ${CMAKE_GENERATOR}")
# message(STATUS "Build Type ............. ${CMAKE_BUILD_TYPE}")

include(build_options)
include(build_dependencies)

message(STATUS "PDC Version ............ ${PROJECT_VERSION}")

include(gen_config_header)

file(GLOB pdcurses_src_files pdcurses/*.c)

# if(CYGWIN)
#     message(STATUS "Windows Kit UM lib path = ${WINDOWS_KIT_LIBRARY_DIR}")
#     link_directories(${WINDOWS_KIT_LIBRARY_DIR})
# endif()

add_subdirectory(ncurses)
add_subdirectory(wincon)
add_subdirectory(wingui)

if(PDC_SDL2_BUILD)
    add_subdirectory(sdl2)
endif()

add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_SOURCE_DIR}/PDCursesMod/cmake/make_uninstall.cmake")

set(CPACK_COMPONENTS_ALL applications)
