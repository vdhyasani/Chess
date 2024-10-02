#include "Knight.h"
#include <string.h>

Knight::Knight(bool col, int index)
{
    color = col;
    position = index;
    pieceValue = 3;
    id = 2 + color;
}

char Knight::get_piece_representation()
{
    return color == 0 ? 'N' : 'n';
}

bool Knight::get_color()
{
    return color;
}

void Knight::set_position(int position)
{
    this->position = position;
}

int Knight::get_position()
{
    return position;
}

int Knight::get_value()
{
    return pieceValue;
}

int Knight::get_id()
{
    return color ? piece::Black_Knight : piece::White_Knight;
}

uint64_t Knight::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    uint64_t squares_attacked = 0ULL;

    // initialize file and rank of piece
    int currFile = square % 8;
    int currRank = square / 8;

    // initialize target square
    int target_square;

    // square = (8 * rank) + file

    // 1 o'clock
    if (currFile+1 <= 7 && currRank-2 >= 0)
    {
        target_square = (8 * (currRank-2)) + currFile+1;
        squares_attacked |= (1ULL << target_square);
    }

    // 2 o'clock
    if (currFile+2 <= 7 && currRank-1 >= 0)
    {
        target_square = (8 * (currRank-1)) + currFile+2;
        squares_attacked |= (1ULL << target_square);
    }

    // 4 o'clock
    if (currFile+2 <= 7 && currRank+1 <= 7)
    {
        target_square = (8 * (currRank+1)) + currFile+2;
        squares_attacked |= (1ULL << target_square);
    }

    // 5 o'clock
    if (currFile+1 <= 7 && currRank+2 <= 7)
    {
        target_square = (8 * (currRank+2)) + currFile+1;
        squares_attacked |= (1ULL << target_square);
    }

    // 7 o'clock
    if (currFile-1 >= 0 && currRank+2 <= 7)
    {
        target_square = (8 * (currRank+2)) + currFile-1;
        squares_attacked |= (1ULL << target_square);
    }

    // 8 o'clock
    if (currFile-2 >= 0 && currRank+1 <= 7)
    {
        target_square = (8 * (currRank+1)) + currFile-2;
        squares_attacked |= (1ULL << target_square);
    }

    // 10 o'clock
    if (currFile-2 >= 0 && currRank-1 >= 0)
    {
        target_square = (8 * (currRank-1)) + currFile-2;
        squares_attacked |= (1ULL << target_square);
    }

    // 11 o'clock
    if (currFile-1 >= 0 && currRank-2 >= 0)
    {
        target_square = (8 * (currRank-2)) + currFile-1;
        squares_attacked |= (1ULL << target_square);
    }

    return squares_attacked;
}

// attack_bitboard and legal_moves output same thing
uint64_t Knight::attack_bitboard(int square, uint64_t bitboard)
{
    return legal_moves(square, bitboard);
}
