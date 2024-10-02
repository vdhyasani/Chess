//
// Created by Vasista Dhyasani on 10/17/23.
//

#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "../Pieces/Piece.h"

class Square
{
private:
    int position;
    Piece* piece;

public:
    Square();
    void setPosition(int pos);
    int getPosition();
    void setPiece(Piece* piece);
    Piece* getPiece();
    bool containsPiece();
};

#endif //CHESS_SQUARE_H
