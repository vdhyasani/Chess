#include "Queen.h"
#include <string.h>

Queen::Queen(bool col, int index)
{
    color = col;
    position = index;
    pieceValue = 9;
    id = 8 + color;
}

char Queen::get_piece_representation()
{
    return color == 0 ? 'Q' : 'q';
}

bool Queen::get_color()
{
    return color;
}

void Queen::set_position(int position)
{
    this->position = position;
}

int Queen::get_position()
{
    return position;
}

int Queen::get_value()
{
    return pieceValue;
}

int Queen::get_id()
{
    return color ? piece::Black_Queen : piece::White_Queen;
}

uint64_t Queen::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    return spaInstance->rook_attack_bitboard(square,bitboard) | spaInstance->bishop_attack_bitboard(square,bitboard);
}

// attack_bitboard and legal_moves output same thing
uint64_t Queen::attack_bitboard(int square, uint64_t bitboard)
{
    return spaInstance->rook_attack_bitboard(square,bitboard) | spaInstance->bishop_attack_bitboard(square,bitboard);
}