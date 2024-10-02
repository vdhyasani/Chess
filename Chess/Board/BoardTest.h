#ifndef CHESS_BACKUP_BOARDTEST_H
#define CHESS_BACKUP_BOARDTEST_H


#include <string>
#include <vector>
#include <stack>
#include "../Pieces/Rook.h"
#include "../Pieces/Bishop.h"
#include "../Pieces/Queen.h"
#include "../Pieces/Knight.h"
#include "../Pieces/King.h"
#include "../Pieces/Pawn.h"
#include "Square.h"
#include "../Move/Move.h"
#include <ctime>

using namespace std;

class BoardTest
{
private:
    char gameBoard[64];
    Square squareBoard[64];

    // move list structure
    typedef struct {
        // moves
        int moves[256];

        // move count
        int count;
    } moves;

    enum {
        a8, b8, c8, d8, e8, f8, g8, h8,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a1, b1, c1, d1, e1, f1, g1, h1, no_sq
    };

    // convert squares to coordinates
    const char *square_to_coordinates[64] = {
            "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
            "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
            "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
            "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
            "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
            "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
            "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
            "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    };

    // convert ASCII character pieces to encoded constants
    int char_pieces[500] = {
            ['P'] = P,
            ['N'] = N,
            ['B'] = B,
            ['R'] = R,
            ['Q'] = Q,
            ['K'] = K,
            ['p'] = p,
            ['n'] = n,
            ['b'] = b,
            ['r'] = r,
            ['q'] = q,
            ['k'] = k
    };

    // promoted pieces
    char promoted_pieces[500] = {
            [Q] = 'q',
            [R] = 'r',
            [B] = 'b',
            [N] = 'n',
            [q] = 'q',
            [r] = 'r',
            [b] = 'b',
            [n] = 'n'
    };

// encode pieces
    enum { P, N, B, R, Q, K, p, n, b, r, q, k };

// piece bitboards
    uint64_t bitboards[12];

// occupancy bitboards
    uint64_t occupancies[3];

// sides to move (colors)
    enum { white, black, both };

// bishop and rook
    enum { rook, bishop };

    int side;

    // pawn attacks table [side][square]
    uint64_t pawn_attacks[2][64];

// knight attacks table [square]
    uint64_t knight_attacks[64];

// king attacks table [square]
    uint64_t king_attacks[64];

// bishop attack masks
    uint64_t bishop_masks[64];

// rook attack masks
    uint64_t rook_masks[64];

    SlidingPieceAttacks* spa;

// enpassant square
    int enpassant;

// castling rights
    int castle;

    enum { wk = 1, wq = 2, bk = 4, bq = 8 };

    uint64_t not_h_file = 0x7f7f7f7f7f7f7f7f;
    uint64_t not_a_file = 0xfefefefefefefefe;
    uint64_t not_hg_file = 4557430888798830399ULL;
    uint64_t not_ab_file = 18229723555195321596ULL;

    // move types
    enum { all_moves, only_captures };

    // castling rights update constants
    const int castling_rights[64] = {
            7, 15, 15, 15,  3, 15, 15, 11,
            15, 15, 15, 15, 15, 15, 15, 15,
            15, 15, 15, 15, 15, 15, 15, 15,
            15, 15, 15, 15, 15, 15, 15, 15,
            15, 15, 15, 15, 15, 15, 15, 15,
            15, 15, 15, 15, 15, 15, 15, 15,
            15, 15, 15, 15, 15, 15, 15, 15,
            13, 15, 15, 15, 12, 15, 15, 14
    };

    long nodes;

    /*** Perft Info ***/
    uint64_t num_nodes = 0;

public:
    BoardTest(const char* fen);
    void setEmptyBoard();
    string convertFen(string origFen);
    uint64_t generate_checkmask(int sq1, int sq2, bool rook_attack);

    // starting color for main

    // legal moves
    bool is_legal_move(bool side_to_move, int sq1, int sq2);
    vector<short> legal_move_list(bool side_to_move);

    void make_move_bitboard_for_white(int pos1, int pos2);
    void make_move_bitboard_for_black(int pos1, int pos2);
    uint64_t get_side_attack_bitboard(bool side_to_move, uint64_t bitboard, uint64_t friendly_bitboard);

    // Pawn promotions
    void promote_pawn(bool side_to_move);

    // Removing element from vector
    void remove_element_from_vector(vector<Piece*> &v, Piece *p);

    // Get index of bit from bitboard
    unsigned int get_first_set_bit_pos(uint64_t n)
    {
        return log2(n & -n) + 1;
    }

    // New moves implementation
    inline void add_move(moves *move_list, int move);
    inline void generate_moves(moves *move_list);

    inline int count_bits(uint64_t bitboard);
    inline int get_ls1b_index(uint64_t bitboard);
    inline int is_square_attacked(int square, int side);

    uint64_t mask_knight_attacks(int square);
    uint64_t mask_king_attacks(int square);
    uint64_t mask_pawn_attacks(int side, int square);
    void init_leapers_attacks();

    // make move on chess board
    inline int make_move2(int move, int move_flag);

    void perft_test(int depth);
    uint64_t perft_driver(int depth, int orig_depth);

    void parse_fen(const char* fen);

    void print_load_bar(int size_of_moves, int current_iteration);
};


#endif //CHESS_BACKUP_BOARDTEST_H
