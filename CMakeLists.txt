cmake_minimum_required(VERSION 3.27)
project(UTP_PRO1_s30853_C)

set(CMAKE_CXX_STANDARD 20)

add_library(UTP_PRO1_s30853_C SHARED
        ImplementationFiles/Game_Board.cpp
        ImplementationFiles/Board.cpp
        Headers/Board.h
        ImplementationFiles/Piece.cpp
        Headers/Piece.h
)

target_include_directories(UTP_PRO1_s30853_C PRIVATE "C:/Users/User/.jdks/openjdk-23/include")
target_include_directories(UTP_PRO1_s30853_C PRIVATE "C:/Users/User/.jdks/openjdk-23/include/win32")