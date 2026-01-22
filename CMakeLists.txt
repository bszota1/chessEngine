cmake_minimum_required(VERSION 4.1)
project(chessEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(chessEngine main.cpp
        src/core/Types.hpp
        src/board/position.hpp
        src/core/bitboard.cpp
        src/core/bitboard.hpp
        src/core/zobrist.hpp
        src/core/zobrist.cpp
        src/board/position.cpp

)
