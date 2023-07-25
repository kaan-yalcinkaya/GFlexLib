cmake_minimum_required(VERSION 3.25)
project(GFL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED 11)

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB CSRC ${CMAKE_SOURCE_DIR}/Containers/src/*.c)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/Containers/include
    )

add_library(GFlex ${SRC} ${CSRC})
add_executable(main ${CMAKE_SOURCE_DIR}/test/main.c)

target_link_libraries(main GFlex)