#include "Pawn.h"
#include <string.h>

Pawn::Pawn(bool col, int index)
{
    color = col;
    position = index;
    pieceValue = 1;
    id = 0 + color;
}

char Pawn::get_piece_representation()
{
    return color == 0 ? 'P' : 'p';
}

bool Pawn::get_color()
{
    return color;
}

void Pawn::set_position(int position)
{
    this->position = position;
}

int Pawn::get_position()
{
    return position;
}

int Pawn::get_value()
{
    return pieceValue;
}

int Pawn::get_id()
{
    return color ? piece::Black_Pawn : piece::White_Pawn;
}

uint64_t Pawn::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    if (color == 0)
        return spaInstance->white_pawn_attack_bitboard(square,bitboard,enpassant_flag);
    else
        return spaInstance->black_pawn_attack_bitboard(square,bitboard,enpassant_flag);
}

uint64_t Pawn::attack_bitboard(int square, uint64_t blockers_bit_board)
{
    uint64_t squares_attacked = 0;
    if (color == 0)
    {
        if (square%8 > 0)
        {
            squares_attacked |= (1ULL << square-9);
        }
        if (square%8 < 7)
        {
            squares_attacked |= (1ULL << square-7);
        }
    }
    else
    {
        if (square%8 > 0)
        {
            squares_attacked |= (1ULL << square+7);
        }
        if (square%8 < 7)
        {
            squares_attacked |= (1ULL << square+9);
        }
    }

    return squares_attacked;
}