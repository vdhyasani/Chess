#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include <iostream>
#include "string.h"
#include "Piece.h"
#include "../Move/SlidingPieceAttacks.h"

class Pawn:public Piece
{
private:
    SlidingPieceAttacks* spaInstance = spaInstance->getInstance();
    int position;
    int pieceValue;
    int color;
    int id;

public:
    Pawn(bool col, int index);
    char get_piece_representation() override;
    int get_value() override;
    void set_position(int position);
    int get_position() override;
    bool get_color() override;
    int get_id() override;
    // add en passant flag
    uint64_t legal_moves(int square, uint64_t blockers_bit_board, uint64_t enpassant_flag) override;    // THIS IS IMPORTANT
    uint64_t attack_bitboard(int square, uint64_t blockers_bit_board) override;
};


#endif //CHESS_PAWN_H
