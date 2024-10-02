//
// Created by Vasista Dhyasani on 1/1/24.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include <cstdint>
#include "../Pieces/Piece.h"

class Move
{
private:
    // the side to move
    bool side_to_move;

    // starting and ending squares
    int start_square, end_square;

    // whether enpassant exists
    uint64_t enpassant_mask;

    // piece moved, captured (could be null)
    Piece *piece_moved, *piece_captured;

    // colored bitboard flags
    uint64_t white_pieces_bitboard, black_pieces_bitboard;
    uint64_t piece_moved_bitboard, piece_captured_bitboard;

    // castling
    uint64_t white_short_castle_flag, white_long_castle_flag; // in board class, make castling bools
    uint64_t black_short_castle_flag, black_long_castle_flag;
    bool short_castle, long_castle;
    Piece* castled_rook;
    uint64_t king_bitboard, rook_bitboard;

    // Pawn promotions
    Piece *promoted_pawn;

public:
    // setters
    void set_side_to_move(bool side);
    void set_start_square(int square);
    void set_end_square(int square);
    void set_enpassant_mask(uint64_t mask);
    void set_piece_moved(Piece* p);
    void set_piece_captured(Piece* p);
    void set_white_pieces_bitboard(uint64_t bitboard);
    void set_black_pieces_bitboard(uint64_t bitboard);
    void set_white_short_castle_flag(uint64_t can_castle);
    void set_white_long_castle_flag(uint64_t can_castle);
    void set_black_short_castle_flag(uint64_t can_castle);
    void set_black_long_castle_flag(uint64_t can_castle);
    void set_castled_rook(Piece* rook);
    void set_short_castle(bool short_castle);
    void set_long_castle(bool long_castle);
    void set_piece_moved_bitboard(uint64_t bitboard);
    void set_piece_captured_bitboard(uint64_t bitboard);
    void set_king_bitboard(uint64_t bitboard);
    void set_rook_bitboard(uint64_t bitboard);

    // getters
    bool get_side_to_move();
    int get_start_square();
    int get_end_square();
    uint64_t get_enpassant_mask();
    Piece* get_piece_moved();
    Piece* get_piece_captured();
    uint64_t get_white_pieces_bitboard();
    uint64_t get_black_pieces_bitboard();
    uint64_t get_white_short_castle_flag();
    uint64_t get_white_long_castle_flag();
    uint64_t get_black_short_castle_flag();
    uint64_t get_black_long_castle_flag();
    Piece* get_castled_rook();
    bool get_short_castle();
    bool get_long_castle();
    uint64_t get_piece_moved_bitboard();
    uint64_t get_piece_captured_bitboard();
    uint64_t get_king_bitboard();
    uint64_t get_rook_bitboard();
};

#endif //CHESS_MOVE_H
