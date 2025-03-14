//
// Created by Vasista Dhyasani on 12/2/23.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "SlidingPieceAttacks.h"

static SlidingPieceAttacks *spaInstance;

/***    Method to take care of getting single instance of class    ***/
SlidingPieceAttacks* SlidingPieceAttacks::getInstance()
{
    if (spaInstance == nullptr)
    {
        spaInstance = new SlidingPieceAttacks();
        spaInstance->populate_rook_magic_numbers_array();
        spaInstance->populate_bishop_magic_numbers_array();
        spaInstance->populate_white_pawn_magic_numbers_array();
        spaInstance->populate_black_pawn_magic_numbers_array();
    }
    return spaInstance;
}

/***    General Methods    ***/
uint64_t SlidingPieceAttacks::random_uint64() {
    uint64_t n1 = ((uint64_t)std::rand()) & 0xFFFF;
    uint64_t n2 = ((uint64_t)std::rand()) & 0xFFFF;
    uint64_t n3 = ((uint64_t)std::rand()) & 0xFFFF;
    uint64_t n4 = ((uint64_t)std::rand()) & 0xFFFF;

    return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
}

uint64_t SlidingPieceAttacks::generate_magic_number_candidate()
{
    return random_uint64() & random_uint64() & random_uint64();
}

int SlidingPieceAttacks::count_one_bits(uint64_t bitBoard)
{
    int count = 0;

    while (bitBoard > 0)
    {
        count++;
        bitBoard &= (bitBoard - 1);
    }

    return count;
}

uint64_t SlidingPieceAttacks::attack_bitboard(int square, uint64_t bitboard, bool is_rook)
{
    if (is_rook)
    {
        uint64_t relevant_occupancies = bitboard & rook_attack_masks[square];
        int magic_index = (relevant_occupancies * rook_magic_numbers[square]) >> (64 - rook_relevant_bits[square]);

        return rook_attack_table[square][magic_index];
    }
    else
    {
        uint64_t relevant_occupancies = bitboard & bishop_attack_masks[square];
        int magic_index = (relevant_occupancies * bishop_magic_numbers[square]) >> (64 - bishop_relevant_bits[square]);

        return bishop_attack_table[square][magic_index];
    }
}

/***    Rook    ***/
uint64_t SlidingPieceAttacks::generate_occupancies_for_rook(int square, int index)
{
    uint64_t attack_mask = rook_attack_masks[square];
    uint64_t occupancies = attack_mask;

    // Loop through the blockermask to find the indices of all set bits.
    int8_t bitindex = 0;
    for (int8_t i = 0; i < 64; i++) {
        // Check if the i'th bit is set in the mask (and thus a potential blocker).
        if ( attack_mask & (1ULL<<i) ) {
            // Clear the i'th bit in the blockerboard if it's clear in the index at bitindex.
            if ( !(index & (1<<bitindex)) ) {
                occupancies &= ~(1ULL<<i); //Clear the bit.
            }
            // Increment the bit index in the 0-4096 index, so each bit in index will correspond
            // to each set bit in blockermask.
            bitindex++;
        }
    }
    return occupancies;
}

uint64_t SlidingPieceAttacks::generate_rook_attacks(int square, uint64_t occupancies)
{
    size_t squares_attacked = 0x0;
    int increment = 0;
    int current_index = square;
    bool ran_into_piece = false;

    // up direction
    increment = -8;
    while (current_index + increment >= 0 && !ran_into_piece)
    {
        if (occupancies & (1ULL << (current_index+increment)))
        {
            ran_into_piece = true;
        }
        current_index += increment;
        squares_attacked = squares_attacked | (1ULL << current_index);
    }

    // down direction
    increment = 8;
    current_index = square;
    ran_into_piece = false;
    while (current_index + increment <= 63 && !ran_into_piece)
    {
        if (occupancies & (1ULL << (current_index+increment)))
        {
            ran_into_piece = true;
        }
        current_index += increment;
        squares_attacked = squares_attacked | (1ULL << current_index);
    }

    // left direction
    increment = -1;
    current_index = square;
    ran_into_piece = false;
    while (current_index % 8 > 0 && !ran_into_piece)
    {
        if (occupancies & (1ULL << (current_index+increment)))
        {
            ran_into_piece = true;
        }
        current_index += increment;
        squares_attacked = squares_attacked | (1ULL << current_index);
    }

    // right direction
    increment = 1;
    current_index = square;
    ran_into_piece = false;
    while (current_index % 8 < 7 && !ran_into_piece)
    {
        if (occupancies & (1ULL << (current_index+increment)))
        {
            ran_into_piece = true;
        }
        current_index += increment;
        squares_attacked = squares_attacked | (1ULL << current_index);
    }

    return squares_attacked;
}

// generate magic number for given square
uint64_t SlidingPieceAttacks::find_rook_magic_numbers(int square, int relevant_bits)
{
    int num_bits = 1 << relevant_bits;

    uint64_t occupancies[4096];
    uint64_t attacks[4096];
    uint64_t used_attacks[4096];

    for (int i = 0; i < num_bits; i++)
    {
        occupancies[i] = generate_occupancies_for_rook(square, i);
        attacks[i] = generate_rook_attacks(square,occupancies[i]);
    }

    // find magic number
    for (int i = 0; i < 10000000; i++)
    {
        uint64_t magic_number = generate_magic_number_candidate();

        // skipping over inappropriate magic numbers
        if (count_one_bits(magic_number * rook_attack_masks[square]) * 0xFF00000000000000 < 6)
        {
            continue;
        }

        std::memset(used_attacks, (uint64_t)0, sizeof(used_attacks));

        bool fail = false;
        for (int j = 0; !fail && j < num_bits; j++)
        {
            int magic_index = (int)((occupancies[j] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0)
            {
                used_attacks[magic_index] = attacks[j];
                rook_attack_table[square][magic_index] = attacks[j];
            } else
            {
                fail = true;
                std::memset(rook_attack_table[square], (uint64_t)0, sizeof(rook_attack_table[square]));
                break;
            }
        }

        // if right magic number found, return it
        // else, generate a different number and try again
        if (!fail)
        {
            return magic_number;
        }
    }

    // magic number not found, so return 0
    return 0;
}

// print magic numbers
void SlidingPieceAttacks::populate_rook_magic_numbers_array()
{
    for (int i = 0; i < 64; i++)
    {
        //std::cout << i << ": " << find_magic_number(i, rookRelevantBits[i]) << std::endl;
        rook_magic_numbers[i] = find_rook_magic_numbers(i, rook_relevant_bits[i]);
    }
}

uint64_t SlidingPieceAttacks::rook_attack_bitboard(int square, uint64_t blockersBitBoard)
{
    uint64_t relevant_occupancies = blockersBitBoard & rook_attack_masks[square];
    int magic_index = (relevant_occupancies * rook_magic_numbers[square]) >> (64 - rook_relevant_bits[square]);

    return rook_attack_table[square][magic_index];
}

/***    Bishop    ***/

uint64_t SlidingPieceAttacks::generate_occupancies_for_bishop(int square, int index)
{
    uint64_t attack_mask = bishop_attack_masks[square];
    uint64_t occupancies = attack_mask;

    // Loop through the blockermask to find the indices of all set bits.
    int8_t bitindex = 0;
    for (int8_t i = 0; i < 64; i++) {
        // Check if the i'th bit is set in the mask (and thus a potential blocker).
        if ( attack_mask & (1ULL<<i) ) {
            // Clear the i'th bit in the blockerboard if it's clear in the index at bitindex.
            if ( !(index & (1<<bitindex)) ) {
                occupancies &= ~(1ULL<<i); //Clear the bit.
            }
            // Increment the bit index in the 0-4096 index, so each bit in index will correspond
            // to each set bit in blockermask.
            bitindex++;
        }
    }
    return occupancies;
}

uint64_t SlidingPieceAttacks::generate_bishop_attacks(int square, uint64_t occupancies)
{
    size_t squares_attacked = 0x0;
    int increment = 0;
    int current_index = square;
    bool ran_into_piece = false;

    // init target files & ranks
    int currRank = square / 8;
    int currFile = square % 8;

    // down-right
    for (int r = currRank + 1, f = currFile + 1; r <= 7 && f <= 7; r++, f++)
    {
        squares_attacked |= (1ULL << (r * 8 + f));
        if (occupancies & (1ULL << (r * 8 + f))) break;
    }

    // down-left
    for (int r = currRank + 1, f = currFile - 1; r <= 7 && f >= 0; r++, f--)
    {
        squares_attacked |= (1ULL << (r * 8 + f));
        if (occupancies & (1ULL << (r * 8 + f))) break;
    }

    // up-right
    for (int r = currRank - 1, f = currFile + 1; r >= 0 && f <= 7; r--, f++)
    {
        squares_attacked |= (1ULL << (r * 8 + f));
        if (occupancies & (1ULL << (r * 8 + f))) break;
    }

    // up-left
    for (int r = currRank - 1, f = currFile - 1; r >= 0 && f >= 0; r--, f--)
    {
        squares_attacked |= (1ULL << (r * 8 + f));
        if (occupancies & (1ULL << (r * 8 + f))) break;
    }

    return squares_attacked;
}

// generate magic number for given square
uint64_t SlidingPieceAttacks::find_bishop_magic_numbers(int square, int relevant_bits)
{
    int num_bits = 1 << relevant_bits;

    uint64_t occupancies[num_bits];
    uint64_t attacks[num_bits];
    uint64_t used_attacks[num_bits];

    for (int i = 0; i < num_bits; i++)
    {
        occupancies[i] = generate_occupancies_for_bishop(square, i);
        attacks[i] = generate_bishop_attacks(square,occupancies[i]);
    }

    // find magic number
    for (int i = 0; i < 10000000; i++)
    {
        uint64_t magic_number = generate_magic_number_candidate();

        // skipping over inappropriate magic numbers
        if (count_one_bits(magic_number * bishop_attack_masks[square]) * 0xFF00000000000000 < 6)
        {
            continue;
        }

        std::memset(used_attacks, (uint64_t)0, sizeof(used_attacks));

        bool fail = false;
        for (int j = 0; !fail && j < num_bits; j++)
        {
            int magic_index = (int)((occupancies[j] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0)
            {
                used_attacks[magic_index] = attacks[j];
                bishop_attack_table[square][magic_index] = attacks[j];
            } else
            {
                fail = true;
                std::memset(bishop_attack_table[square], (uint64_t)0, sizeof(bishop_attack_table[square]));
                break;
            }
        }

        // if right magic number found, return it
        // else, generate a different number and try again
        if (!fail)
        {
            return magic_number;
        }
    }

    // magic number not found, so return 0
    return 0;
}

// print magic numbers
void SlidingPieceAttacks::populate_bishop_magic_numbers_array()
{
    for (int i = 0; i < 64; i++)
    {
        //std::cout << i << ": " << find_magic_number(i, rookRelevantBits[i]) << std::endl;
        bishop_magic_numbers[i] = find_bishop_magic_numbers(i, bishop_relevant_bits[i]);
    }
}

uint64_t SlidingPieceAttacks::bishop_attack_bitboard(int square, uint64_t blockersBitBoard)
{
    uint64_t relevant_occupancies = blockersBitBoard & bishop_attack_masks[square];
    int magic_index = (relevant_occupancies * bishop_magic_numbers[square]) >> (64 - bishop_relevant_bits[square]);

    return bishop_attack_table[square][magic_index];
}

/***    White pawn    ***/

uint64_t SlidingPieceAttacks::generate_occupancies_for_white_pawn(int square, int index)
{
    uint64_t attack_mask = white_pawn_attack_masks[square];
    uint64_t occupancies = attack_mask;

    // Loop through the blockermask to find the indices of all set bits.
    int8_t bitindex = 0;
    for (int8_t i = 0; i < 64; i++) {
        // Check if the i'th bit is set in the mask (and thus a potential blocker).
        if ( attack_mask & (1ULL<<i) ) {
            // Clear the i'th bit in the blockerboard if it's clear in the index at bitindex.
            if ( !(index & (1<<bitindex)) ) {
                occupancies &= ~(1ULL<<i); //Clear the bit.
            }
            // Increment the bit index in the 0-4096 index, so each bit in index will correspond
            // to each set bit in blockermask.
            bitindex++;
        }
    }
    return occupancies;
}

uint64_t SlidingPieceAttacks::generate_white_pawn_attacks(int square, uint64_t occupancies)
{
    size_t squares_sight = 0x0;
    int increment = 0;
    int current_index = square;
    bool ran_into_piece = false;

    // init target files & ranks
    int currRank = square / 8;
    int currFile = square % 8;

    // check if pawn can move one square up
    if (!((1ULL << square-8) & occupancies))
    {
        squares_sight |= (1ULL << (square-8));
    }

    // check if pawn can move two squares up
    if (currRank == 6 &&
        !((1ULL << square-8) & occupancies) &&
        !((1ULL << square-16) & occupancies))
    {
        squares_sight |= (1ULL << (square-16));
    }

    // check if pawn attacks a piece
    if (currFile > 0 && ((1ULL << square-9) & occupancies))   // up-left
    {
        squares_sight |= (1ULL << (square-9));
    }
    if (currFile < 7 && ((1ULL << square-7) & occupancies))   // up-left
    {
        squares_sight |= (1ULL << (square-7));
    }

    return squares_sight;
}

// generate magic number for given square
uint64_t SlidingPieceAttacks::find_white_pawn_magic_numbers(int square, int relevant_bits)
{
    int num_bits = 1 << relevant_bits;

    uint64_t occupancies[num_bits];
    uint64_t attacks[num_bits];
    uint64_t used_attacks[num_bits];

    for (int i = 0; i < num_bits; i++)
    {
        occupancies[i] = generate_occupancies_for_white_pawn(square, i);
        attacks[i] = generate_white_pawn_attacks(square,occupancies[i]);
    }

    // find magic number
    for (int i = 0; i < 10000000; i++)
    {
        uint64_t magic_number = generate_magic_number_candidate();

        // skipping over inappropriate magic numbers
        if (count_one_bits(magic_number * white_pawn_attack_masks[square]) * 0xFF00000000000000 < 6)
        {
            continue;
        }

        std::memset(used_attacks, (uint64_t)0, sizeof(used_attacks));

        bool fail = false;
        for (int j = 0; !fail && j < num_bits; j++)
        {
            int magic_index = (int)((occupancies[j] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0)
            {
                used_attacks[magic_index] = attacks[j];
                white_pawn_attack_table[square][magic_index] = attacks[j];
            } else
            {
                fail = true;
                std::memset(white_pawn_attack_table[square], (uint64_t)0, sizeof(white_pawn_attack_table[square]));
                break;
            }
        }

        // if right magic number found, return it
        // else, generate a different number and try again
        if (!fail)
        {
            return magic_number;
        }
    }

    // magic number not found, so return 0
    return 0;
}

// print magic numbers
void SlidingPieceAttacks::populate_white_pawn_magic_numbers_array()
{
    for (int i = 8; i < 56; i++)
    {
        //std::cout << i << ": " << find_white_pawn_magic_numbers(i, white_pawn_relevant_bits[i]) << std::endl;
        white_pawn_magic_numbers[i] = find_white_pawn_magic_numbers(i, white_pawn_relevant_bits[i]);
    }
}

uint64_t SlidingPieceAttacks::white_pawn_attack_bitboard(int square, uint64_t blockersBitBoard, uint64_t enpassant_flag)
{
    uint64_t relevant_occupancies = (blockersBitBoard | enpassant_flag) & white_pawn_attack_masks[square];
    int magic_index = (relevant_occupancies * white_pawn_magic_numbers[square]) >> (64 - white_pawn_relevant_bits[square]);

    return (white_pawn_attack_table[square][magic_index] | (white_pawn_attack_masks[square] & enpassant_flag));
}

/***    Black pawn     ***/

uint64_t SlidingPieceAttacks::generate_occupancies_for_black_pawn(int square, int index)
{
    uint64_t attack_mask = black_pawn_attack_masks[square];
    uint64_t occupancies = attack_mask;

    // Loop through the blockermask to find the indices of all set bits.
    int8_t bitindex = 0;
    for (int8_t i = 0; i < 64; i++) {
        // Check if the i'th bit is set in the mask (and thus a potential blocker).
        if ( attack_mask & (1ULL<<i) ) {
            // Clear the i'th bit in the blockerboard if it's clear in the index at bitindex.
            if ( !(index & (1<<bitindex)) ) {
                occupancies &= ~(1ULL<<i); //Clear the bit.
            }
            // Increment the bit index in the 0-4096 index, so each bit in index will correspond
            // to each set bit in blockermask.
            bitindex++;
        }
    }
    return occupancies;
}

uint64_t SlidingPieceAttacks::generate_black_pawn_attacks(int square, uint64_t occupancies)
{
    size_t squares_sight = 0x0;
    int increment = 0;
    int current_index = square;
    bool ran_into_piece = false;

    // init target files & ranks
    int currRank = square / 8;
    int currFile = square % 8;

    // check if pawn can move one square up
    if (!((1ULL << square+8) & occupancies))
    {
        squares_sight |= (1ULL << (square+8));
    }

    // check if pawn can move two squares up
    if (currRank == 1 &&
        !((1ULL << square+8) & occupancies) &&
        !((1ULL << square+16) & occupancies))
    {
        squares_sight |= (1ULL << (square+16));
    }

    // check if pawn attacks a piece
    if (currFile > 0 && ((1ULL << square+7) & occupancies))   // down-left
    {
        squares_sight |= (1ULL << (square+7));
    }
    if (currFile < 7 && ((1ULL << square+9) & occupancies))   // down-right
    {
        squares_sight |= (1ULL << (square+9));
    }

    return squares_sight;
}

// generate magic number for given square
uint64_t SlidingPieceAttacks::find_black_pawn_magic_numbers(int square, int relevant_bits)
{
    int num_bits = 1 << relevant_bits;

    uint64_t occupancies[num_bits];
    uint64_t attacks[num_bits];
    uint64_t used_attacks[num_bits];

    for (int i = 0; i < num_bits; i++)
    {
        occupancies[i] = generate_occupancies_for_black_pawn(square, i);
        attacks[i] = generate_black_pawn_attacks(square,occupancies[i]);
    }

    // find magic number
    for (int i = 0; i < 10000000; i++)
    {
        uint64_t magic_number = generate_magic_number_candidate();

        // skipping over inappropriate magic numbers
        if (count_one_bits(magic_number * black_pawn_attack_masks[square]) * 0xFF00000000000000 < 6)
        {
            continue;
        }

        std::memset(used_attacks, (uint64_t)0, sizeof(used_attacks));

        bool fail = false;
        for (int j = 0; !fail && j < num_bits; j++)
        {
            int magic_index = (int)((occupancies[j] * magic_number) >> (64 - relevant_bits));

            if (used_attacks[magic_index] == 0)
            {
                used_attacks[magic_index] = attacks[j];
                black_pawn_attack_table[square][magic_index] = attacks[j];
            } else
            {
                fail = true;
                std::memset(black_pawn_attack_table[square], (uint64_t)0, sizeof(black_pawn_attack_table[square]));
                break;
            }
        }

        // if right magic number found, return it
        // else, generate a different number and try again
        if (!fail)
        {
            return magic_number;
        }
    }

    // magic number not found, so return 0
    return 0;
}

// print magic numbers
void SlidingPieceAttacks::populate_black_pawn_magic_numbers_array()
{
    for (int i = 8; i < 56; i++)
    {
        //std::cout << i << ": " << find_magic_number(i, rookRelevantBits[i]) << std::endl;
        black_pawn_magic_numbers[i] = find_black_pawn_magic_numbers(i, black_pawn_relevant_bits[i]);
    }
}

uint64_t SlidingPieceAttacks::black_pawn_attack_bitboard(int square, uint64_t blockersBitBoard, uint64_t enpassant_flag)
{
    uint64_t relevant_occupancies = (blockersBitBoard | enpassant_flag) & black_pawn_attack_masks[square];
    int magic_index = (relevant_occupancies * black_pawn_magic_numbers[square]) >> (64 - black_pawn_relevant_bits[square]);

    return (black_pawn_attack_table[square][magic_index] | (black_pawn_attack_masks[square] & enpassant_flag));
}


