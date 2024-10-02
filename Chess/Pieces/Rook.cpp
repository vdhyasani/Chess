#include "Rook.h"
#include <string.h>

Rook::Rook(bool col, int index)
{
    color = col;
    position = index;
    pieceValue = 5;
    id = 6 + color;
}

char Rook::get_piece_representation()
{
    return color == 0 ? 'R' : 'r';
}

bool Rook::get_color()
{
    return color;
}

void Rook::set_position(int position)
{
    this->position = position;
}

int Rook::get_position()
{
    return position;
}

int Rook::get_value()
{
    return pieceValue;
}

int Rook::get_id()
{
    return color ? piece::Black_Rook : piece::White_Rook;
}

uint64_t Rook::legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag)
{
    return spaInstance->rook_attack_bitboard(square,bitboard);
}

uint64_t Rook::attack_bitboard(int square, uint64_t bitboard)
{
    return spaInstance->rook_attack_bitboard(square,bitboard);
}

// attack_bitboard and legal_moves output same thing

/*
 * Generate blockersBB:
 * First, generate the rook mask
 * This means that for the square the rook is on,
 * generate a mask of 1's along that file/rank (excluding edges)
 * (this can be precomputed and stored in an array)
 * AND this with full_bb
 * This will reveal the relevant blockers for the rook
 *
 * Now that we have the blockersBB,
 * we can use that as input for a hash table that outputs attackBB's
 * But first, the blockersBB number has to be compressed using a magic num
 * The compressed input:
 * (blockersBB * magicNum) >> (64 - n),
 * where 'n' is the number of 1's in the initial rook mask
 * (aka the number of squares attacked if no pieces block it)
 * and for the magicNum, you pull it out of your ass, but the point is,
 * the magic num for that particular square should give you a unique input
 * for every unique combination of blockers
 *
 * Putting the inputBB into the hash table,
 * you will get the exact squares that the rook can move to
 *
 * note: the piece can capture friendly pieces as well, must check this afterward
 */

/*
 * rook attack masks:
 *
 * uint64_t rookAttackMasks = {
 *  0x000101010101017e, 0x000202020202027c, 0x0004040404040479, 0x0008080808080876, 0x001010101010106e, 0x002020202020205e, 0x004040404040403e, 0x008080808080807e,
 *  0x0001010101017e00, 0x0002020202027c00, 0x0004040404047a00, 0x0008080808087600, 0x0010101010106e00, 0x0020202020205e00, 0x0040404040403e00, 0x0080808080807e00,
 *  0x00010101017e0100, 0x00020202027c0200, 0x00040404047a0400, 0x0008080808760800, 0x00101010106e1000, 0x00202020205e2000, 0x00404040403e4000, 0x00808080807e8000,
 *  0x000101017e010100, 0x000202027c020200, 0x000404047a040400, 0x0008080876080800, 0x001010106e101000, 0x002020205e202000, 0x004040403e404000, 0x008080807e808000,
 *  0x0001017e01010100, 0x0002027c02020200, 0x0004047a04040400, 0x0008087608080800, 0x0010106e10101000, 0x0020205e20202000, 0x0040403e40404000, 0x0080807e80808000,
 *  0x00017e0101010100, 0x00027c0202020200, 0x00047a0404040400, 0x0008760808080800, 0x00106e1010101000, 0x00205e2020202000, 0x00403e4040404000, 0x00807e8080808000,
 *  0x007a010101010100, 0x007c020202020200, 0x007a040404040400, 0x0076080808080800, 0x006e101010101000, 0x005e202020202000, 0x003e404040404000, 0x007e808080808000,
 *  0x7e01010101010100, 0x7c02020202020200, 0x7904040404040400, 0x7608080808080800, 0x6e10101010101000, 0x5e20202020202000, 0x3e40404040404000, 0x7e80808080808000,
 * }
 *
 * rook relevant bits:
 *
 * int RBits[64] = {
  12, 11, 11, 11, 11, 11, 11, 12,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  11, 10, 10, 10, 10, 10, 10, 11,
  12, 11, 11, 11, 11, 11, 11, 12
};
 *
 *
 *
 * bishop attack masks:
 *
 * uint64_t bishopAttackMasks = {
 *  0x0040201008040200, 0x0000402010080400, 0x0000004020100a00, 0x0000000040221400, 0x0000000002442800, 0x0000000204085000, 0x0000020408102000, 0x0002040810204000,
 *  0x0020100804020000, 0x0040201008040000, 0x00004020100a0000, 0x0000004022140000, 0x0000000244280000, 0x0000020408500000, 0x0002040810200000, 0x0004081020400000,
 *  0x0010080402000200, 0x0020100804000400, 0x004020100a000a00, 0x0000402214001400, 0x0000024428002800, 0x0002040850005000, 0x0004081020002000, 0x0008102040004000,
 *  0x0008040200020400, 0x0010080400040800, 0x0020100a000a1000, 0x0040221400142200, 0x0002442800284400, 0x0004085000500800, 0x0008102000201000, 0x0010204000402000,
 *  0x0004020002040800, 0x0008040004081000, 0x00100a000a102000, 0x0022140014224000, 0x0044280028440200, 0x0008500050080400, 0x0010200020100800, 0x0020400040201000,
 *  0x0002000204081000, 0x0004000408102000, 0x000a000a10204000, 0x0014001422400000, 0x0028002844020000, 0x0050005008040200, 0x0020002010080400, 0x0040004020100800,
 *  0x0000020408102000, 0x0000040810204000, 0x00000a1020400000, 0x0000142240000000, 0x0000284402000000, 0x0000500804020000, 0x0000201008040200, 0x0000402010080400,
 *  0x0002040810204000, 0x0004081020400000, 0x000a102040000000, 0x0014224000000000, 0x0028440200000000, 0x0050080402000000, 0x0020100804020000, 0x0040201008040200,
 * }
 *
 * bishop relevant bits:
 *
 * int BBits[64] = {
  6, 5, 5, 5, 5, 5, 5, 6,
  5, 5, 5, 5, 5, 5, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 9, 9, 7, 5, 5,
  5, 5, 7, 7, 7, 7, 5, 5,
  5, 5, 5, 5, 5, 5, 5, 5,
  6, 5, 5, 5, 5, 5, 5, 6
};
 */

/*
 * generate blockers_bb:
 * uint64_t generateBlockersBitBoard(int square, uint64_t full_bb)
 * {
 *      return rookAttackMask[square] & full_bb;
 * }
 *
 * uint64_t blockersBitBoard = generateBlockersBitBoard(square, fullBB);
 *
 *
 * uint64_t attackBitBoard(int square, uint64_t blockersBitBoard)
 * {
 *   int magicIndex = (blockersBitBoard * magicNums[square]) >> (64 - relevantBits[square]);
 *
 *   return rookAttackTable[square][magicIndex];
 * }
 *
 * void populateRookAttackTable(int square, uint64_t blockersBitBoard)
  {
    int magicIndex = (blockersBitBoard * magicNums[square]) >> (64 - relevantBits[square]);

    rookAttackTable[square][magicIndex] = generateRookAttacksOnTheFly(square, blockersBitBoard);
  }

  uint64_t generateRookAttacksOnTheFly(int square, uint64_t blockersBitBoard)
  {
    bool ranIntoPiece = false;
    int increment = 0;
    int currentIndex = getPosition();

    // up direction
    increment = -8;
    while (currentIndex+increment >= 0 && !ranIntoPiece)
    {
      if (pieceAtIndex(ownColorBitBoard, currentIndex+increment) == 1)
      {
        ranIntoPiece = true;
      }
      currentIndex += increment;
      squaresAttacked = squaresAttacked | ((size_t)0x1 << currentIndex);
    }

    increment = 8;
    currentIndex = getPosition();
    ranIntoPiece = false;
    while (currentIndex+increment >= 0 && !ranIntoPiece)
    {
      if (pieceAtIndex(ownColorBitBoard, currentIndex+increment) == 1)
      {
        ranIntoPiece = true;
      }
      currentIndex += increment;
      squaresAttacked = squaresAttacked | ((size_t)0x1 << currentIndex);
    }

    increment = -1;
    currentIndex = getPosition();
    ranIntoPiece = false;
    while (currentIndex+increment >= 0 && !ranIntoPiece)
    {
      if (pieceAtIndex(ownColorBitBoard, currentIndex+increment) == 1)
      {
        ranIntoPiece = true;
      }
      currentIndex += increment;
      squaresAttacked = squaresAttacked | ((size_t)0x1 << currentIndex);
    }

    increment = 1;
    currentIndex = getPosition();
    ranIntoPiece = false;
    while (currentIndex+increment >= 0 && !ranIntoPiece)
    {
      if (pieceAtIndex(ownColorBitBoard, currentIndex+increment) == 1)
      {
        ranIntoPiece = true;
      }
      currentIndex += increment;
      squaresAttacked = squaresAttacked | ((size_t)0x1 << currentIndex);
    }
  }
*/

