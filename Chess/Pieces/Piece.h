#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

class Piece
{
public:
    Piece(){}
    enum piece { White_Pawn, White_Knight, White_Bishop, White_Rook, White_Queen, White_King,
                 Black_Pawn, Black_Knight, Black_Bishop, Black_Rook, Black_Queen, Black_King };
    virtual bool get_color() = 0;
    virtual char get_piece_representation() = 0;
    virtual int get_value() = 0;
    virtual int get_id() = 0;
    virtual int get_position() = 0;
    virtual void set_position(int pos) = 0;
    virtual uint64_t legal_moves(int square, uint64_t bitboard, uint64_t enpassant_flag) = 0;
    // This is specifically for the pawn, as only the pawn's legal moves and the squares it attacks are different
    virtual uint64_t attack_bitboard(int square, uint64_t bitboard) = 0;
};

#endif //CHESS_PIECE_H
