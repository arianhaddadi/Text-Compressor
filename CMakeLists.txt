cmake_minimum_required(VERSION 3.21)
project(deflate_caesar)

set(CMAKE_CXX_STANDARD 23)

add_executable(deflate_caesar src/main.cpp src/CommandHandler.cpp src/CommandHandler.h src/common.h src/tree/Tree.cpp src/tree/Tree.h src/tree/Node.h src/operations/HuffmanCodec.cpp src/operations/HuffmanCodec.h src/operations/FileIO.cpp src/operations/FileIO.h src/operations/Cipherer.cpp src/operations/Cipherer.h src/operations/LZ77Codec.cpp src/operations/LZ77Codec.h)
