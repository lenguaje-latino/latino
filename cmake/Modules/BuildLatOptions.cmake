#
# Latino Opciones
option(LAT_EJEMPLOS "Compilar los ejemplos de archivo .Lat con Latino"  OFF )

message(STATUS "LAT_EJEMPLOS ........... ${LAT_EJEMPLOS}" )

if(WIN32)
    set(BUILD_SHARED_LIBS ON)
    option(LATINO_BUILD_AS_DLL "Crea Latino como libreria DLL" ${BUILD_SHARED_LIBS} )
    message(STATUS "LATINO_BUILD_AS_DLL: ... ${LATINO_BUILD_AS_DLL}"                )
endif(WIN32)


file(TO_CMAKE_PATH "${CMAKE_INSTALL_PREFIX}" CMAKE_INSTALL_PREFIX)