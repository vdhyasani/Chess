#include "King.h"
#include <string.h>

King::King(bool col, int index)
{
    color = col;
    position = index;
    pieceValue = 3;
    id = 10 + color;
}

char King::get_piece_representation()
{
    return color == 0 ? 'K' : 'k';
}

bool King::get_color()
{
    return color;
}

void King::set_position(int position)
{
    this->position = position;
}

int King::get_position()
{
    return position;
}

int King::get_value()
{
    return pieceValue;
}

int King::get_id()
{
    return color ? piece::Black_King : piece::White_King;
}

uint64_t King::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    uint64_t squares_attacked = 0ULL;

    // initialize file and rank of piece
    int currFile = square % 8;
    int currRank = square / 8;

    // initialize target square
    int target_square;

    // square = (8 * rank) + file

    // up-left
    if (currFile-1 >= 0 && currRank-1 >= 0)
    {
        target_square = (8 * (currRank-1)) + currFile-1;
        squares_attacked |= (1ULL << target_square);
    }

    // up
    if (currRank-1 >= 0)
    {
        target_square = (8 * (currRank-1)) + currFile;
        squares_attacked |= (1ULL << target_square);
    }

    // up-right
    if (currFile+1 <= 7 && currRank-1 >= 0)
    {
        target_square = (8 * (currRank-1)) + currFile+1;
        squares_attacked |= (1ULL << target_square);
    }

    // right
    if (currFile+1 <= 7)
    {
        target_square = (8 * (currRank)) + currFile+1;
        squares_attacked |= (1ULL << target_square);
    }

    // down-right
    if (currFile+1 <= 7 && currRank+1 <= 7)
    {
        target_square = (8 * (currRank+1)) + currFile+1;
        squares_attacked |= (1ULL << target_square);
    }

    // down
    if (currRank+1 <= 7)
    {
        target_square = (8 * (currRank+1)) + currFile;
        squares_attacked |= (1ULL << target_square);
    }

    // down-left
    if (currFile-1 >= 0 && currRank+1 <= 7)
    {
        target_square = (8 * (currRank+1)) + currFile-1;
        squares_attacked |= (1ULL << target_square);
    }

    // left
    if (currFile-1 >= 0)
    {
        target_square = (8 * (currRank)) + currFile-1;
        squares_attacked |= (1ULL << target_square);
    }

    return squares_attacked;
}

// attack_bitboard and legal_moves output same thing
uint64_t King::attack_bitboard(int square, uint64_t bitboard)
{
    return legal_moves(square, bitboard);
}