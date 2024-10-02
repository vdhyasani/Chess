cmake_minimum_required(VERSION 3.25)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess
        main.cpp
        Board/Board.cpp
        Board/Board.h
        Board/Square.cpp
        Board/Square.h
        Move/Move.cpp
        Move/Move.h
        Pieces/Bishop.cpp
        Pieces/Bishop.h
        Pieces/King.cpp
        Pieces/King.h
        Pieces/Knight.cpp
        Pieces/Knight.h
        Pieces/Pawn.cpp
        Pieces/Pawn.h
        Pieces/Queen.cpp
        Pieces/Queen.h
        Pieces/Rook.cpp
        Pieces/Rook.h
        Move/SlidingPieceAttacks.cpp
        Move/SlidingPieceAttacks.h
        Pieces/Piece.h
        Board/Board.h Players/Player.h Players/Human.h Players/Bot.h)

add_executable(Test
        Perft.cpp
        Board/Square.cpp
        Board/Square.h
        Move/Move.cpp
        Move/Move.h
        Pieces/Bishop.cpp
        Pieces/Bishop.h
        Pieces/King.cpp
        Pieces/King.h
        Pieces/Knight.cpp
        Pieces/Knight.h
        Pieces/Pawn.cpp
        Pieces/Pawn.h
        Pieces/Queen.cpp
        Pieces/Queen.h
        Pieces/Rook.cpp
        Pieces/Rook.h
        Move/SlidingPieceAttacks.cpp
        Move/SlidingPieceAttacks.h
        Pieces/Piece.h
        Board/BoardTest.h
        Board/BoardTest.cpp)