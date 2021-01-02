#[[
/***********************************************************************************
 * Copyright (c) 2015-2020 Lenguaje-Latino, programación con sintaxis al Español.  *
 *                                                                                 *
 *                             CMake_SRC de Latino                                 *
 ***********************************************************************************/
]]


#
# Configuraciones (GLOBALES)
set(CMAKE_EXPORT_COMPILE_COMMANDS           ON  )
set(CMAKE_VERBOSE_MAKEFILE                  TRUE)
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE        ON  )
set(INSTALL_BIN                             ${CMAKE_INSTALL_PREFIX}/bin     )
set(INSTALL_INCLUDE                         ${CMAKE_INSTALL_PREFIX}/include )
set(INSTALL_LIB                             ${CMAKE_INSTALL_PREFIX}/lib     )
set(INSTALL_SHARE                           ${CMAKE_INSTALL_PREFIX}/share   )


#
# Sistemas Operativos
    # ---
    # MS-Windows
if(WIN32)
    #
    # MS-VC configuraciones
    if(MSVC)
        set(CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS} /W4"                          )
        set(CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS_DEBUG} /W4"                    )
        set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS  )
    elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CMAKE_C_FLAGS                   "${CMAKE_C_FLAGS} -Wall -std=c11"               )
        set(CMAKE_C_FLAGS_DEBUG             "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -std=c11"  )
    endif(MSVC)

else()
    #
    # UNIX
    link_libraries(m)
    link_libraries(readline)
    set(CMAKE_C_FLAGS                       "${CMAKE_C_FLAGS} -D_GNU_SOURCE -Wall -std=c11 -rdynamic -ldl -fPIC"        )
    set(CMAKE_C_FLAGS_DEBUG                 "${CMAKE_C_FLAGS} -D_GNU_SOURCE -g -O0 -Wall -std=c11 -rdynamic -ldl -fPIC" )
endif()


#
# Arquitectura del build
set(TARGET_ARCH_REGEX                       "^.*-march[= ]([^ ]+).*$")
string(REGEX MATCH                          "${TARGET_ARCH_REGEX}" TARGET_ARCH_MATCH ${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS})

if(TARGET_ARCH_MATCH)
    string(REGEX REPLACE                    "${TARGET_ARCH_REGEX}" "\\1" TARGET_ARCH ${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS})
else()
    set(TARGET_ARCH                         ${CMAKE_HOST_SYSTEM_PROCESSOR})
endif()

message(STATUS "TARGET_ARCH: ........... ${TARGET_ARCH}")


#
# librerias
add_definitions(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
add_subdirectory(linenoise)

if(WIN32)
    message(STATUS "CURRENT PATH WIN32.......... ${CMAKE_CURRENT_SOURCE_DIR}")
    include_directories(regex-2.7-src/src)
    add_subdirectory(regex-2.7-src)
endif()

include_directories(linenoise)
include_directories(../include)

set(SRC_LIB latino.c latlex.c latparse.c latast.c latmem.c
latdic.c latdo.c latlist.c latmv.c latobj.c latpaqlib.c latrepl.c latgc.c
#librerias
latbaselib.c latstrlib.c latlistlib.c latdiclib.c latfilelib.c
latmathlib.c latsyslib.c latpaqlib.c latdevlib.c latuilib.c
#extra
linenoise/utf8.c linenoise/linenoise.c)

set(SRC_LATINO ${SRC_LIB})

add_executable(latino ${SRC_LATINO} ${SRC_LIB})
target_link_libraries(latino LINK_PUBLIC ${CMAKE_DL_LIBS})

if(MSVC)
    message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
    link_directories("${CMAKE_CURRENT_BINARY_DIR}/regex-2.7-src/src/${CMAKE_BUILD_TYPE}")
    target_link_libraries(latino regex2)
    link_libraries(regex2)
    set(LATINO_DEF latino.def)
endif(MSVC)

# Create dynamic library
add_library(liblatino SHARED ${SRC_LIB} ${LATINO_DEF})
set_target_properties(liblatino PROPERTIES OUTPUT_NAME latino CLEAN_DIRECT_OUTPUT 1)

# message(STATUS "LATINO_BUILD_AS_DLL: ${LATINO_BUILD_AS_DLL}")
if(LATINO_BUILD_AS_DLL)
    target_link_libraries (liblatino regex2)
    set_target_properties (liblatino PROPERTIES COMPILE_DEFINITIONS LATINO_BUILD_AS_DLL)
endif ()

#Create static library
add_library(liblatino_static STATIC ${SRC_LIB})
target_link_libraries(liblatino_static ${LIBS})


#
# Ubicacion de archivos en UNIX
if(UNIX)
    install(TARGETS     latino                          DESTINATION     ${INSTALL_BIN}                      )
    install(TARGETS     liblatino                       DESTINATION     ${INSTALL_LIB}                      )
    install(TARGETS     liblatino_static                DESTINATION     ${INSTALL_LIB}                      )
    install(FILES       man/latino.1.gz                 DESTINATION     ${INSTALL_SHARE}/man/man1           )
    install(FILES       gnu-utilities/latino.nanorc     DESTINATION     ${INSTALL_SHARE}/nano               )
    install(FILES       gnu-utilities/latino.desktop    DESTINATION     ${INSTALL_SHARE}/applications       )
    install(FILES       ../logo/Latino-logo.png         DESTINATION     ${INSTALL_SHARE}/latino             )
    install(FILES       ../include/latast.h             DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latcompat.h          DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latdic.h             DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latdo.h              DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latgc.h              DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latino.h             DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latlex.h             DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latlist.h            DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latmem.h             DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latmv.h              DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latparse.h           DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
    install(FILES       ../include/latrepl.h            DESTINATION     ${INSTALL_INCLUDE} COMPONENT Header )
#else()
#https://stackoverflow.com/questions/13556885/how-to-change-the-executable-output-directory-for-win32-builds-in-cmake
#  add_custom_command(target latino
#          POST_BUILD
#          COMMAND ${CMAKE_COMMAND} -E copy ${EXAMPLE_BIN_NAME} ${PROJECT_BINARY_DIR}/.)
endif(UNIX)


#
# Paquete .deb

# ---
# crear paquete .deb https://cmake.org/Wiki/CMake/CPack/Examples/Linux/DEB
# ejecutar en terminal
# make package
set(CPACK_GENERATOR                         "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME               "latino")
set(CPACK_PACKAGE_VERSION                   "${LATINO_VERSION}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER         "melving24@gmail.com")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION        "Lenguaje de programación de código abierto para latinos y de habla hispana. http://lenguajelatino.org/")
set(CPACK_DEBIAN_PACKAGE_SECTION            "education")

include(CPack)
