include_guard()

set(CMAKE_SYSTEM_NAME "Windows")

set(CMAKE_BUILD_TYPE RelWithDebInfo)

set(CMAKE_C_COMPILER "wcl386")
set(CMAKE_CXX_COMPILER "wcl386")
set(CMAKE_ASM_COMPILER "wasm")

message(STATUS "Configured for Windows (32-bit)")
set(WATCOM_WIN32 TRUE)
