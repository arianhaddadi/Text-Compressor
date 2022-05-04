cmake_minimum_required(VERSION 3.21)
project(compressor)

set(CMAKE_CXX_STANDARD 23)

add_executable(compressor main.cpp CommandHandler.cpp CommandHandler.h Common.h tree/Tree.cpp tree/Tree.h tree/Node.cpp tree/Node.h)
