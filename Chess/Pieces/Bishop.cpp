#include "Bishop.h"

Bishop::Bishop(bool col, int index) {
    color = col;
    position = index;
    pieceValue = 3;
    id = 4 + color;
}

char Bishop::get_piece_representation()
{
    return color == 0 ? 'B' : 'b';
}

bool Bishop::get_color()
{
    return color;
}

void Bishop::set_position(int position)
{
    this->position = position;
}

int Bishop::get_position()
{
    return position;
}

int Bishop::get_value()
{
    return pieceValue;
}

int Bishop::get_id()
{
    return color ? piece::Black_Bishop : piece::White_Bishop;
}

uint64_t Bishop::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    return spaInstance->bishop_attack_bitboard(square,bitboard);
}

// attack_bitboard and legal_moves output same thing
uint64_t Bishop::attack_bitboard(int square, uint64_t bitboard)
{
    return spaInstance->bishop_attack_bitboard(square,bitboard);
}