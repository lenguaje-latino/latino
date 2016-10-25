SET(CMAKE_VERBOSE_MAKEFILE true)
SET(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
SET(CMAKE_INSTALL_PREFIX /usr/bin)

IF(UNIX)
    LINK_LIBRARIES(m)
    LINK_LIBRARIES(jansson)
    LINK_LIBRARIES(curl)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -Wall -std=c11")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -D_GNU_SOURCE -coverage -g -O0 -Wall -std=c11")
ELSE(UNIX)
    IF(MSVC)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /W4")
        INCLUDE_DIRECTORIES(../curl/include)
        SET_PROPERTY(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
    ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        LINK_LIBRARIES(jansson)
        LINK_LIBRARIES(curl)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -std=c11")
    ENDIF(MSVC)
ENDIF(UNIX)

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
ADD_SUBDIRECTORY(linenoise)

INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(../jansson/src)

SET(SOURCES compat.h
    latino.h ast.h vm.h object.h libstring.h libmem.h liblist.h
    lex.h parse.h libmath.h libio.h  libnet.h libdict.h gc.h
    linenoise/utf8.h linenoise/linenoise.h
    latino.c ast.c vm.c object.c libstring.c libmem.c liblist.c
    lex.c parse.c libmath.c libio.c libnet.c libdict.c gc.c
    linenoise/utf8.c linenoise/linenoise.c )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SOURCES})

TARGET_LINK_LIBRARIES(latino LINK_PUBLIC
    ${BISON_LIBRARIES} ${CMAKE_DL_LIBS})

IF(MSVC)
    TARGET_LINK_LIBRARIES(latino jansson libcurl)
ENDIF(MSVC)

IF(UNIX)
  INSTALL(TARGETS latino DESTINATION ${CMAKE_INSTALL_PREFIX})
  INSTALL(FILES man/latino.1.gz DESTINATION /usr/share/man/man1)
  INSTALL(FILES nano/latino.nanorc DESTINATION /usr/share/nano)
ENDIF(UNIX)

#crear paquete .deb https://cmake.org/Wiki/CMake/CPack/Examples/Linux/DEB
#ejecutar en terminal
#make package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "latino")
SET(CPACK_PACKAGE_VERSION "0.8.11")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "primitivo.roman.montero@gmail.com")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Lenguaje de programación de código abierto para latinos y de habla hispana. http://lenguaje-latino.org/")
SET(CPACK_DEBIAN_PACKAGE_SECTION "education")
INCLUDE(CPack)
