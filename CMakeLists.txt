cmake_minimum_required(VERSION 3.21)
project(deflate_caesar)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE SOURCES "src/*.cpp")

include_directories(include)

add_executable(deflate_caesar ${SOURCES})
