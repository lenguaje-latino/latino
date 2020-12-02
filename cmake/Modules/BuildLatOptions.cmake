
#
# Latino Opciones
option(LAT_EJEMPLOS "Compilar los ejemplos de archivo .Lat con Latino"  OFF )
option(LAT_CURSES   "Compilar libreria de Curses con Latino"            ON  )
option(LAT_JSON     "Compilar libreria de Json con Latino"              OFF )
option(LAT_MySQL    "Compilar libreria de MySQL con Latino"             OFF )
option(LAT_REDIS    "Compilar libreria de Redis con Latino"             OFF )

message(STATUS "LAT_EJEMPLOS ........... ${LAT_EJEMPLOS}" )
message(STATUS "LAT_CURSES ............. ${LAT_CURSES}"   )
message(STATUS "LAT_JSON ............... ${LAT_JSON}"     )
message(STATUS "LAT_MySQL .............. ${LAT_MySQL}"    )
message(STATUS "LAT_REDIS .............. ${LAT_REDIS}"    )

if(WIN32)
    set(BUILD_SHARED_LIBS ON)
    option(LATINO_BUILD_AS_DLL "Crea Latino como libreria DLL" ${BUILD_SHARED_LIBS} )
    message(STATUS "LATINO_BUILD_AS_DLL: ... ${LATINO_BUILD_AS_DLL}"                )
endif(WIN32)


file(TO_CMAKE_PATH "${CMAKE_INSTALL_PREFIX}" CMAKE_INSTALL_PREFIX)