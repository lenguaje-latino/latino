set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall -std=c11")
set(CMAKE_VERBOSE_MAKEFILE true)

if(UNIX)
    link_libraries(m)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -std=c11")
    add_subdirectory(linenoise)
else(UNIX)
    if(CMAKE_COMPILER_IS_GNUCXX)
      add_definitions(-g -std=c11)
    endif()
    set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
endif(UNIX)

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

SET(SOURCES khash.h
    latino.h ast.h utils.h vm.h object.h libstring.h libmem.h
    lex.h parse.h libmath.h libio.h linenoise/utf8.h linenoise/linenoise.h
    latino.c ast.c utils.c vm.c object.c libstring.c libmem.c
    lex.c parse.c libmath.c libio.c linenoise/utf8.c linenoise/linenoise.c
    )

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SOURCES})

TARGET_LINK_LIBRARIES(latino LINK_PUBLIC
    ${BISON_LIBRARIES} ${CMAKE_DL_LIBS}
)

if(UNIX)
  install (TARGETS latino DESTINATION /usr/local/bin)
endif(UNIX)
