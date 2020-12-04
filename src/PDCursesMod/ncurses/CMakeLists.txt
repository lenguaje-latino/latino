cmake_minimum_required(VERSION 3.11)

set(CURSES_NEED_WIDE PDC_WIDE)
include(FindCurses)

if(CURSES_FOUND)
    # this project is dependent on libncurses5-dev, and libncursesw5-dev.

    PROJECT(ncurses VERSION "${PROJECT_VERSION}" LANGUAGES C)
    message(STATUS "**** ${PROJECT_NAME} ****")

    set(PDCURSES_DIST ${CMAKE_INSTALL_PREFIX})

    macro (unix_app dir targ)

        set(bin_name "${PROJECT_NAME}_${targ}")
        if(${targ} STREQUAL "tuidemo")
            set(src_files ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/tuidemo.c ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/tui.c)
        else()
            set(src_files ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/${targ}.c)
        endif()

        add_executable(${bin_name} ${src_files})

        target_compile_options(${bin_name} PUBLIC -Wall)
        target_compile_definitions(${bin_name} PUBLIC -D_XOPEN_SOURCE_EXTENDED)
        if(PDC_WIDE)
            target_compile_definitions(${bin_name} PUBLIC -DHAVE_NCURSESW)
        endif()

        target_include_directories(${bin_name} PUBLIC ${CURSES_INCLUDE_DIR})
        target_link_libraries(${bin_name} ${CURSES_LIBRARIES})
        set_target_properties(${bin_name} PROPERTIES OUTPUT_NAME ${targ})
        
        install(TARGETS ${bin_name} RUNTIME DESTINATION ${PDCURSES_DIST}/bin/${PROJECT_NAME} COMPONENT applications)

    endmacro ()

    # unix_app(../demos firework)
    # unix_app(../demos ozdemo)
    # unix_app(../demos newtest)
    # unix_app(../demos rain)
    # unix_app(../demos testcurs)
    # unix_app(../demos worm)
    # unix_app(../demos xmas)

endif()