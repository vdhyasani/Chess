#include <iostream>
#include "Board/Board.h"
#include <string>

// 8/8/4P1R1/8/2p1k3/2K5/8/4r3 w - - 0 1

using namespace std;

enum color {
    WHITE, BLACK
};

int convertCoordinatesToIndex(string basicString);

int main()
{
    string fen;
    cout << "FEN string: ";
    getline(cin, fen);
    cout << endl;
    Board board(fen.c_str());
    string sq;
    int sq1, sq2;

    cout << endl;
    board.print_board();
    cout << endl;
    bool side = 0;
    string to_move;
    while (true)
    {
        side = board.get_side();
        to_move = side ? "Black" : "White";
        while (true)
        {
            cout << to_move << " to move" << endl;
            cout << "Starting square: ";
            cin >> sq;
            sq1 = convertCoordinatesToIndex(sq);

            cout << "Target square: ";
            cin >> sq;
            sq2 = convertCoordinatesToIndex(sq);
            if (board.get_move(sq1, sq2)) {
                if (board.make_move(board.get_move(sq1, sq2), 0)) {
                    side ^= 1;
                    break;
                }
            }
            cout << "Illegal move" << endl;
        }
        board.print_board();
        cout << endl;
    }

    return 0;
}

int convertCoordinatesToIndex(string coordinates) {
    int posIndex = 0;
    int fileValue = 0, rankValue = 0;

    char file = coordinates[0];
    int rank = coordinates[1] - '0';
    switch(file)
    {
        case 'a':
            fileValue = 0;
            break;
        case 'b':
            fileValue = 1;
            break;
        case 'c':
            fileValue = 2;
            break;
        case 'd':
            fileValue = 3;
            break;
        case 'e':
            fileValue = 4;
            break;
        case 'f':
            fileValue = 5;
            break;
        case 'g':
            fileValue = 6;
            break;
        case 'h':
            fileValue = 7;
            break;
    }
    rankValue = 8 - rank;

    posIndex = (8 * rankValue) + fileValue;

    return posIndex;
}

int get_input()
{

}

