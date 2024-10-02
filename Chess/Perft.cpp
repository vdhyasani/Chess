#include <ctime>
#include <iostream>
#include "Board/BoardTest.h"
#include <string>

// 8/8/4P1R1/8/2p1k3/2K5/8/4r3 w - - 0 1

using namespace std;

enum color {
    WHITE, BLACK
};

uint64_t perft(BoardTest board, int depth);

int captures;
int en_passants;

int main()
{
    string fen;
    cout << "Test FEN string: ";
    getline(cin, fen);
    BoardTest board(fen.c_str());

    string depth;
    cout << "Depth: ";
    getline(cin, depth);
    int t1 = time(0);
    cout << endl;
    uint64_t numNodes = perft(board, stoi(depth));
    cout << endl;
    cout << "Number of nodes at depth " << depth << ": " << numNodes << endl;
    int t2 = time(0);
    int time_diff = t2-t1;
    int nps = numNodes / time_diff;
    cout << "Nodes/sec: " <<  nps << endl;
    int arr[12];
}

uint64_t perft(BoardTest board, int depth) {
    return board.perft_driver(depth, depth);
}



