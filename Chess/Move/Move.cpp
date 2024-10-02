#include "Move.h"

// setters
void Move::set_side_to_move(bool side) { side_to_move = side; }
void Move::set_start_square(int square) { start_square = square; }
void Move::set_end_square(int square) { end_square = square; }
void Move::set_enpassant_mask(uint64_t mask) { enpassant_mask = mask; }
void Move::set_piece_moved(Piece* p) { piece_moved = p; }
void Move::set_piece_captured(Piece* p) { piece_captured = p; }
void Move::set_white_pieces_bitboard(uint64_t bitboard) { white_pieces_bitboard = bitboard; }
void Move::set_black_pieces_bitboard(uint64_t bitboard) { black_pieces_bitboard = bitboard; }
void Move::set_white_short_castle_flag(uint64_t flag) { white_short_castle_flag = flag; }
void Move::set_white_long_castle_flag(uint64_t flag) { white_long_castle_flag = flag; }
void Move::set_black_short_castle_flag(uint64_t flag) { black_short_castle_flag = flag; }
void Move::set_black_long_castle_flag(uint64_t flag) { black_long_castle_flag = flag; }
void Move::set_castled_rook(Piece *rook) { castled_rook = rook; }
void Move::set_short_castle(bool short_castle) { this->short_castle = short_castle; }
void Move::set_long_castle(bool long_castle) { this->long_castle = long_castle; }
void Move::set_piece_moved_bitboard(uint64_t bitboard) { piece_moved_bitboard = bitboard; }
void Move::set_piece_captured_bitboard(uint64_t bitboard) { piece_captured_bitboard = bitboard; }
void Move::set_king_bitboard(uint64_t bitboard) { king_bitboard = bitboard; }
void Move::set_rook_bitboard(uint64_t bitboard) { rook_bitboard = bitboard; }

// getters
bool Move::get_side_to_move() { return side_to_move; }
int Move::get_start_square() { return start_square; }
int Move::get_end_square() { return end_square; }
uint64_t Move::get_enpassant_mask() { return enpassant_mask; }
Piece* Move::get_piece_moved() {return piece_moved; }
Piece* Move::get_piece_captured() { return piece_captured; }
uint64_t Move::get_white_pieces_bitboard() { return white_pieces_bitboard; }
uint64_t Move::get_black_pieces_bitboard() { return black_pieces_bitboard; }
uint64_t Move::get_white_short_castle_flag() { return white_short_castle_flag; }
uint64_t Move::get_white_long_castle_flag() { return white_long_castle_flag; }
uint64_t Move::get_black_short_castle_flag() { return black_short_castle_flag; }
uint64_t Move::get_black_long_castle_flag() { return black_long_castle_flag; }
Piece* Move::get_castled_rook() { return castled_rook; }
bool Move::get_short_castle() { return this->short_castle; }
bool Move::get_long_castle() { return this->long_castle; }
uint64_t Move::get_piece_moved_bitboard() { return piece_moved_bitboard; }
uint64_t Move::get_piece_captured_bitboard() { return piece_captured_bitboard; }
uint64_t Move::get_king_bitboard() { return king_bitboard; }
uint64_t Move::get_rook_bitboard() { return rook_bitboard; }