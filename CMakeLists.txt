cmake_minimum_required(VERSION 3.25)
project(GFL C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED 11)

file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.c)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(GFlex ${SRC})
add_executable(main main.c)

target_link_libraries(main GFlex)