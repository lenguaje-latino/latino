SET(CMAKE_VERBOSE_MAKEFILE true)
SET(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
SET(CMAKE_INSTALL_PREFIX /usr/bin)

IF(UNIX)
    INCLUDE_DIRECTORIES(../hiredis)
    LINK_LIBRARIES(m)
    LINK_LIBRARIES(jansson)
    LINK_LIBRARIES(curl)
    LINK_LIBRARIES(hiredis)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -Wall -std=c11")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -D_GNU_SOURCE -coverage -g -O0 -Wall -std=c11 -fprofile-arcs -ftest-coverage -coverage")
    # Use the package PkgConfig to detect GTK+ headers/library files
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    # Setup CMake to use GTK+, tell the compiler where to look for headers
    # and to the linker where to look for libraries
    include_directories(${GTK3_INCLUDE_DIRS})
    link_directories(${GTK3_LIBRARY_DIRS})
    # Add other flags to the compiler
    add_definitions(${GTK3_CFLAGS_OTHER})
ELSE(UNIX)
    IF(MSVC)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /W4")
        INCLUDE_DIRECTORIES(../curl/include)
        SET_PROPERTY(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
    ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        LINK_LIBRARIES(jansson)
        LINK_LIBRARIES(curl)
        #LINK_LIBRARIES(hiredis)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -std=c11")
    ENDIF(MSVC)
ENDIF(UNIX)

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
ADD_SUBDIRECTORY(linenoise)

INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(../jansson/src)

SET(SOURCES
    latino.h latast.h latmv.h latobj.h latmem.h
    latlist.h latdic.h latgc.h latlex.h latparse.h
    linenoise/utf8.h linenoise/linenoise.h latcompat.h
    latino.c latast.c latmv.c latobj.c latmem.c
    latlist.c latdic.c latgc.c latlex.c latparse.c
    libstr.c libcast.c libmath.c libfile.c libsys.c
    libcurl.c libjson.c libredis.c libbase.c
    linenoise/utf8.c linenoise/linenoise.c
    libgtk.c
    )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SOURCES})

TARGET_LINK_LIBRARIES(latino LINK_PUBLIC
    ${BISON_LIBRARIES} ${CMAKE_DL_LIBS} ${GTK3_LIBRARIES})

IF(MSVC)
    TARGET_LINK_LIBRARIES(latino jansson libcurl)
ENDIF(MSVC)

IF(UNIX)
  INSTALL(TARGETS latino DESTINATION ${CMAKE_INSTALL_PREFIX})
  INSTALL(FILES man/latino.1.gz DESTINATION /usr/share/man/man1)
  INSTALL(FILES gnu-utilities/latino.nanorc DESTINATION /usr/share/nano)
  INSTALL(FILES gnu-utilities/latino.desktop DESTINATION /usr/share/applications)
  INSTALL(FILES ../logo/desktop.png DESTINATION /usr/share/latino)
ENDIF(UNIX)

#crear paquete .deb https://cmake.org/Wiki/CMake/CPack/Examples/Linux/DEB
#ejecutar en terminal
#make package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "latino")
SET(CPACK_PACKAGE_VERSION "0.9.1")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "primitivo.roman.montero@gmail.com")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Lenguaje de programación de código abierto para latinos y de habla hispana. http://lenguaje-latino.org/")
SET(CPACK_DEBIAN_PACKAGE_SECTION "education")
INCLUDE(CPack)
