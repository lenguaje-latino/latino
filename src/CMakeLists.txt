if(UNIX)
    link_libraries(m)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")
else(UNIX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4")
    set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
endif(UNIX)

FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX REQUIRED)

ADD_DEFINITIONS(-D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

INCLUDE_DIRECTORIES(
    ${BISON_INCLUDE_DIR}
)

list(APPEND BISON_TARGET_cmdopt "--verbose")
list(APPEND BISON_TARGET_cmdopt "-y")

#IF(BISON_FOUND)
    #ADD_CUSTOM_COMMAND(
      #SOURCE ${CMAKE_SOURCE_DIR}/src/parse.y
      #COMMAND ${BISON_EXECUTABLE}
      #ARGS --defines=${CMAKE_SOURCE_DIR}/src/parse.h
           #-o ${CMAKE_SOURCE_DIR}/src/parse.c
           #${CMAKE_SOURCE_DIR}/src/parse.c
      #COMMENT "Generating parse.c"
      #OUTPUT ${CMAKE_SOURCE_DIR}/src/parse.c
    #)
#ENDIF(BISON_FOUND)

set(FlexOutput ${CMAKE_SOURCE_DIR}/lex.c)
set(FlexSpecFile lex.l)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
          OUTPUT ${FlexOutput}
          COMMAND ${FLEX_EXECUTABLE}
                --outfile=${FlexOutput}
                ${FlexSpecFile}
        ARGS ${FLEX_EXECUTABLE_opts} -o${Output} -i ${Input}
        DEPENDS ${FlexSpecFile} ${BisonOutput}
        COMMENT "Generating ${FlexOutput}"
        VERBATIM
    )
ENDIF(FLEX_FOUND)

BISON_TARGET(MyParser ${CMAKE_CURRENT_SOURCE_DIR}/parse.y ${CMAKE_CURRENT_SOURCE_DIR}/parse.c)
FLEX_TARGET(MyScanner ${CMAKE_CURRENT_SOURCE_DIR}/lex.l ${CMAKE_CURRENT_SOURCE_DIR}/lex.c)
ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    latino.h ast.h utils.h vm.h object.h libstring.h liblist.h libmem.h
    libstack.h khash.h lex.h
    latino.c ast.c utils.c vm.c object.c libstring.c liblist.c libmem.c
    libstack.c)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

ADD_EXECUTABLE(latino ${SOURCES} ${BISON_MyParser_OUTPUTS} ${FLEX_MyScanner_OUTPUTS} )

TARGET_LINK_LIBRARIES(latino
    ${BISON_LIBRARIES} ${CMAKE_DL_LIBS}
)
