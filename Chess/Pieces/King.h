#ifndef CHESS_KING_H
#define CHESS_KING_H

#include <iostream>
#include "string.h"
#include "Piece.h"
#include "../Move/SlidingPieceAttacks.h"

class King:public Piece
{
private:
    SlidingPieceAttacks* spaInstance = spaInstance->getInstance();
    int position;
    int pieceValue;
    int color;
    int id;

public:
    King(bool col, int index);
    char get_piece_representation() override;
    int get_value() override;
    void set_position(int position);
    int get_position() override;
    bool get_color() override;
    int get_id() override;
    uint64_t legal_moves(int square, uint64_t blockers_bit_board, uint64_t enpassant_flag=0) override;    // THIS IS IMPORTANT
    uint64_t attack_bitboard(int square, uint64_t blockersBitBoard) override;
};


#endif //CHESS_KING_H
