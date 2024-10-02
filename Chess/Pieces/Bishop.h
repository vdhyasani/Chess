#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "../Move/SlidingPieceAttacks.h"
#include "Piece.h"

class Bishop : public Piece
{
private:
    SlidingPieceAttacks *spaInstance = spaInstance->getInstance();
    int position;
    int pieceValue;
    int color;
    int id;

public:
    Bishop(bool col, int index);
    char get_piece_representation() override;
    int get_value() override;
    void set_position(int position) override;
    int get_position() override;
    bool get_color() override;
    int get_id() override;
    uint64_t legal_moves(int square, uint64_t blockers_bit_board, uint64_t enpassant_flag = 0) override; // THIS IS IMPORTANT
    uint64_t attack_bitboard(int square, uint64_t blockersBitBoard) override;
};

#endif // CHESS_BISHOP_H
