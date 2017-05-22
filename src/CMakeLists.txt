SET(CMAKE_VERBOSE_MAKEFILE true)
SET(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
SET(INSTALL_BIN ${CMAKE_INSTALL_PREFIX}/bin)
SET(INSTALL_LIB ${CMAKE_INSTALL_PREFIX}/lib)
SET(INSTALL_INCLUDE ${CMAKE_INSTALL_PREFIX}/include)
SET(INSTALL_SHARE ${CMAKE_INSTALL_PREFIX}/share)

if (WIN32)
    option ( LATINO_BUILD_AS_DLL "Crea latino como libreria DLL" ${BUILD_SHARED_LIBS} )
    IF(MSVC)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /W4")
        ADD_LIBRARY(regex SHARED IMPORTED)
        SET_PROPERTY(TARGET regex PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/Debug/regex2.dll")
        SET_PROPERTY(TARGET regex PROPERTY IMPORTED_IMPLIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/Debug/regex.lib")
        SET_PROPERTY(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
    ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")
        SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -std=c11")
    ENDIF(MSVC)
else ()
    LINK_LIBRARIES(m)
    LINK_LIBRARIES(readline)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_GNU_SOURCE -Wall -std=c11 -rdynamic -ldl")
    # -fprofile-arcs -ftest-coverage -coverage
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -D_GNU_SOURCE -g -O0 -Wall -std=c11 -rdynamic -ldl")
endif ()

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
ADD_SUBDIRECTORY(linenoise)

INCLUDE_DIRECTORIES(linenoise)
INCLUDE_DIRECTORIES(../include)

SET(SRC_LIB latino.c latlex.c latparse.c latast.c latmem.c
latdic.c latdo.c latlist.c latmv.c latobj.c latpaqlib.c latrepl.c latgc.c
#librerias
latbaselib.c latstrlib.c latlistlib.c latdiclib.c latfilelib.c
latmathlib.c latsyslib.c latpaqlib.c
#extra
linenoise/utf8.c linenoise/linenoise.c)

SET(SRC_LATINO ${SRC_LIB})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SRC_LATINO} ${SRC_LIB})
TARGET_LINK_LIBRARIES(latino LINK_PUBLIC ${CMAKE_DL_LIBS})

IF(MSVC)
    TARGET_LINK_LIBRARIES(latino regex)
    set (LATINO_DEF latino.def )
	link_libraries(regex)
ENDIF(MSVC)

# Create dynamic library
add_library ( liblatino SHARED ${SRC_LIB} ${LATINO_DEF})
set_target_properties ( liblatino PROPERTIES OUTPUT_NAME latino CLEAN_DIRECT_OUTPUT 1 )

if ( LATINO_BUILD_AS_DLL )
	target_link_libraries ( liblatino regex )
    set_target_properties ( liblatino PROPERTIES COMPILE_DEFINITIONS LATINO_BUILD_AS_DLL )
endif ( )

IF(UNIX)
  INSTALL(TARGETS latino DESTINATION ${INSTALL_BIN})
  INSTALL(TARGETS liblatino DESTINATION ${INSTALL_LIB})
  INSTALL(FILES man/latino.1.gz DESTINATION ${INSTALL_SHARE}/man/man1)
  INSTALL(FILES gnu-utilities/latino.nanorc DESTINATION ${INSTALL_SHARE}/nano)
  INSTALL(FILES gnu-utilities/latino.desktop DESTINATION ${INSTALL_SHARE}/applications)
  INSTALL(FILES ../logo/desktop.png DESTINATION ${INSTALL_SHARE}/latino)
  INSTALL (FILES ../include/latino.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latast.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latcompat.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latdic.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latdo.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latlist.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latmem.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latmv.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
  INSTALL (FILES ../include/latobj.h DESTINATION ${INSTALL_INCLUDE} COMPONENT Header)
ENDIF(UNIX)

#crear paquete .deb https://cmake.org/Wiki/CMake/CPack/Examples/Linux/DEB
#ejecutar en terminal
#make package
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_NAME "latino")
SET(CPACK_PACKAGE_VERSION "1.0.0")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "primitivo.roman.montero@gmail.com")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Lenguaje de programación de código abierto para latinos y de habla hispana. http://lenguaje-latino.org/")
SET(CPACK_DEBIAN_PACKAGE_SECTION "education")
INCLUDE(CPack)
