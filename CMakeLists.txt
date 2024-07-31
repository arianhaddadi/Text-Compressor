cmake_minimum_required(VERSION 3.21)
project(deflate_caesar)

set(CMAKE_CXX_STANDARD 23)

add_executable(deflate_caesar src/main.cpp src/command_handler.cpp src/command_handler.h src/common.h src/tree/tree.cpp src/tree/tree.h src/tree/node.h src/operations/huffman_codec.cpp src/operations/huffman_codec.h src/operations/file_handler.cpp src/operations/file_handler.h src/operations/cipherer.cpp src/operations/cipherer.h src/operations/lz77_codec.cpp src/operations/lz77_codec.h)
