//
// Created by Vasista Dhyasani on 12/2/23.
//

#ifndef CHESS_SLIDINGPIECEATTACKS_H
#define CHESS_SLIDINGPIECEATTACKS_H

#include <cstdint>

/*
 * TODO:
 *
 * Generate a white/black pawn attack table,
 * similar to the rook and bishop (using magic bitboards)
 *
 * depending on the square and the occupancies,
 * output the legal moves of the pawn
 * (push one up/down, push two up/down, capture diagonally)
 *
 * the size of the attack table would be 48 for each color
 * the relevant bits would be 2,3,or 4 bits
 */

class SlidingPieceAttacks
{
private:
    /***    Shared Instance    ***/
    SlidingPieceAttacks* spa;

    /***    General Methods    ***/
    uint64_t generate_magic_number_candidate();
    int count_one_bits(uint64_t bb);
    uint64_t random_uint64();
    uint64_t attack_bitboard(int square, uint64_t blockersBitBoard, bool is_rook);

    /***    Rook    ***/
    uint64_t rook_attack_table[64][4096];
    uint64_t rook_attack_masks[64] = {
            0x000101010101017e, 0x000202020202027c, 0x000404040404047a, 0x0008080808080876, 0x001010101010106e, 0x002020202020205e, 0x004040404040403e, 0x008080808080807e,
            0x0001010101017e00, 0x0002020202027c00, 0x0004040404047a00, 0x0008080808087600, 0x0010101010106e00, 0x0020202020205e00, 0x0040404040403e00, 0x0080808080807e00,
            0x00010101017e0100, 0x00020202027c0200, 0x00040404047a0400, 0x0008080808760800, 0x00101010106e1000, 0x00202020205e2000, 0x00404040403e4000, 0x00808080807e8000,
            0x000101017e010100, 0x000202027c020200, 0x000404047a040400, 0x0008080876080800, 0x001010106e101000, 0x002020205e202000, 0x004040403e404000, 0x008080807e808000,
            0x0001017e01010100, 0x0002027c02020200, 0x0004047a04040400, 0x0008087608080800, 0x0010106e10101000, 0x0020205e20202000, 0x0040403e40404000, 0x0080807e80808000,
            0x00017e0101010100, 0x00027c0202020200, 0x00047a0404040400, 0x0008760808080800, 0x00106e1010101000, 0x00205e2020202000, 0x00403e4040404000, 0x00807e8080808000,
            0x007e010101010100, 0x007c020202020200, 0x007a040404040400, 0x0076080808080800, 0x006e101010101000, 0x005e202020202000, 0x003e404040404000, 0x007e808080808000,
            0x7e01010101010100, 0x7c02020202020200, 0x7a04040404040400, 0x7608080808080800, 0x6e10101010101000, 0x5e20202020202000, 0x3e40404040404000, 0x7e80808080808000
    };
    int rook_relevant_bits[64] = {
            12, 11, 11, 11, 11, 11, 11, 12,
            11, 10, 10, 10, 10, 10, 10, 11,
            11, 10, 10, 10, 10, 10, 10, 11,
            11, 10, 10, 10, 10, 10, 10, 11,
            11, 10, 10, 10, 10, 10, 10, 11,
            11, 10, 10, 10, 10, 10, 10, 11,
            11, 10, 10, 10, 10, 10, 10, 11,
            12, 11, 11, 11, 11, 11, 11, 12
    };
    uint64_t rook_magic_numbers[64];
    uint64_t generate_occupancies_for_rook(int square, int index);
    uint64_t generate_rook_attacks(int square, uint64_t occupancies);
    uint64_t find_rook_magic_numbers(int square, int relevant_bits);
    void populate_rook_magic_numbers_array();

    /***    Bishop    ***/
    uint64_t bishop_attack_table[64][512];
    uint64_t bishop_attack_masks[64] = {
            0x0040201008040200, 0x0000402010080400, 0x0000004020100a00, 0x0000000040221400, 0x0000000002442800, 0x0000000204085000, 0x0000020408102000, 0x0002040810204000,
            0x0020100804020000, 0x0040201008040000, 0x00004020100a0000, 0x0000004022140000, 0x0000000244280000, 0x0000020408500000, 0x0002040810200000, 0x0004081020400000,
            0x0010080402000200, 0x0020100804000400, 0x004020100a000a00, 0x0000402214001400, 0x0000024428002800, 0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
            0x0008040200020400, 0x0010080400040800, 0x0020100a000a1000, 0x0040221400142200, 0x0002442800284400, 0x0004085000500800, 0x0008102000201000, 0x0010204000402000,
            0x0004020002040800, 0x0008040004081000, 0x00100a000a102000, 0x0022140014224000, 0x0044280028440200, 0x0008500050080400, 0x0010200020100800, 0x0020400040201000,
            0x0002000204081000, 0x0004000408102000, 0x000a000a10204000, 0x0014001422400000, 0x0028002844020000, 0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
            0x0000020408102000, 0x0000040810204000, 0x00000a1020400000, 0x0000142240000000, 0x0000284402000000, 0x0000500804020000, 0x0000201008040200, 0x0000402010080400,
            0x0002040810204000, 0x0004081020400000, 0x000a102040000000, 0x0014224000000000, 0x0028440200000000, 0x0050080402000000, 0x0020100804020000, 0x0040201008040200
    };
    int bishop_relevant_bits[64] = {
            6, 5, 5, 5, 5, 5, 5, 6,
            5, 5, 5, 5, 5, 5, 5, 5,
            5, 5, 7, 7, 7, 7, 5, 5,
            5, 5, 7, 9, 9, 7, 5, 5,
            5, 5, 7, 9, 9, 7, 5, 5,
            5, 5, 7, 7, 7, 7, 5, 5,
            5, 5, 5, 5, 5, 5, 5, 5,
            6, 5, 5, 5, 5, 5, 5, 6
    };
    uint64_t bishop_magic_numbers[64];
    uint64_t generate_occupancies_for_bishop(int square, int index);
    uint64_t generate_bishop_attacks(int square, uint64_t occupancies);
    uint64_t find_bishop_magic_numbers(int square, int relevant_bits);
    void populate_bishop_magic_numbers_array();

    /***    White pawn    ***/
    uint64_t white_pawn_attack_table[64][16];
    // the word 'attack' for pawns is used loosely here
    uint64_t white_pawn_attack_masks[64] = {
            0,0,0,0,0,0,0,0,
            0x3, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xc0,
            0x300, 0x700, 0xe00, 0x1c00, 0x3800, 0x7000, 0xe000, 0xc000,
            0x30000, 0x70000, 0xe0000, 0x1c0000, 0x380000, 0x700000, 0xe00000, 0xc00000,
            0x3000000, 0x7000000, 0xe000000, 0x1c000000, 0x38000000, 0x70000000, 0xe0000000, 0xc0000000,
            0x300000000, 0x700000000, 0xe00000000, 0x1c00000000, 0x3800000000, 0x7000000000, 0xe000000000, 0xc000000000,
            0x30100000000, 0x70200000000, 0xe0400000000, 0x1c0800000000, 0x381000000000, 0x702000000000, 0xe04000000000, 0xc08000000000,
            0,0,0,0,0,0,0,0
    };
    // last eight bits will be en passant bits
    uint64_t white_pawn_relevant_bits[64] = {
            0,0,0,0,0,0,0,0,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            3,4,4,4,4,4,4,3,
            0,0,0,0,0,0,0,0
    };
    uint64_t white_pawn_magic_numbers[64];
    uint64_t generate_occupancies_for_white_pawn(int square, int index);
    uint64_t generate_white_pawn_attacks(int square, uint64_t occupancies);
    uint64_t find_white_pawn_magic_numbers(int square, int relevant_bits);
    void populate_white_pawn_magic_numbers_array();

    /***    Black pawn    ***/
    uint64_t black_pawn_attack_table[64][16];
    uint64_t black_pawn_attack_masks[64] = {
            0,0,0,0,0,0,0,0,
            0x1030000, 0x2070000, 0x40e0000, 0x81c0000, 0x10380000, 0x20700000, 0x40e00000, 0x80c00000,
            0x3000000, 0x7000000, 0xe000000, 0x1c000000, 0x38000000, 0x70000000, 0xe0000000, 0xc0000000,
            0x300000000, 0x700000000, 0xe00000000, 0x1c00000000, 0x3800000000, 0x7000000000, 0xe000000000, 0xc000000000,
            0x30000000000, 0x70000000000, 0xe0000000000, 0x1c0000000000, 0x380000000000, 0x700000000000, 0xe00000000000, 0xc00000000000,
            0x3000000000000, 0x7000000000000, 0xe000000000000, 0x1c000000000000, 0x38000000000000, 0x70000000000000, 0xe0000000000000, 0xc0000000000000,
            0x300000000000000, 0x700000000000000, 0xe00000000000000, 0x1c00000000000000, 0x3800000000000000, 0x7000000000000000, 0xe000000000000000, 0xc000000000000000,
            0,0,0,0,0,0,0,0
    };
    uint64_t black_pawn_relevant_bits[64] = {
            0,0,0,0,0,0,0,0,
            3,4,4,4,4,4,4,3,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            2,3,3,3,3,3,3,2,
            0,0,0,0,0,0,0,0
    };
    uint64_t black_pawn_magic_numbers[64];
    uint64_t generate_occupancies_for_black_pawn(int square, int index);
    uint64_t generate_black_pawn_attacks(int square, uint64_t occupancies);
    uint64_t find_black_pawn_magic_numbers(int square, int relevant_bits);
    void populate_black_pawn_magic_numbers_array();

public:
    static SlidingPieceAttacks* getInstance();
    uint64_t rook_attack_bitboard(int square, uint64_t blockersBitBoard);
    uint64_t bishop_attack_bitboard(int square, uint64_t blockersBitBoard);
    // add enpassant flag
    uint64_t white_pawn_attack_bitboard(int square, uint64_t blockersBitBoard, uint64_t enpassant_flag);
    uint64_t black_pawn_attack_bitboard(int square, uint64_t blockersBitBoard, uint64_t enpassant_flag);
};


#endif //CHESS_SLIDINGPIECEATTACKS_H
