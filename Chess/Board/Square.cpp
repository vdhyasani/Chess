#include "Board.h"

Square::Square() {
    piece = nullptr;
    position = 0;
}

void Square::setPosition(int pos)
{
    position = pos;
}

int Square::getPosition()
{
    return position;
}

void Square::setPiece(Piece* piece)
{
    this->piece = piece;
}

Piece* Square::getPiece()
{
    return piece;
}

bool Square::containsPiece()
{
    if (piece == nullptr)
    {
        return false;
    } else
    {
        return true;
    }
}
