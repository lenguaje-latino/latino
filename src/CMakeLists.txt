if(UNIX)
    link_libraries(m)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")
else(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4")
    set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
endif(UNIX)

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

SET(SOURCES khash.h
    latino.h ast.h utils.h vm.h object.h libstring.h libmem.h
    lex.h parse.h libmath.h
    latino.c ast.c utils.c vm.c object.c libstring.c libmem.c
    lex.c parse.c libmath.c
    )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SOURCES})

TARGET_LINK_LIBRARIES(latino
    ${BISON_LIBRARIES} ${CMAKE_DL_LIBS}
)
