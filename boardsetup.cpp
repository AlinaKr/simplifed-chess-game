#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <controlfunctions.h>


using namespace std;


void setUpBoard(string chessboard[rows][cols])
{


    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            chessboard[row][col] = empty;
        }
    }


    //place pawns in second and penultimate row (white ones are on top)
    for (int col = 0; col < 8; col++) {
        chessboard[1][col] = pawn_w;
        chessboard[6][col] = pawn_b;
    }



    //place remaining figures
    chessboard[0][0] = rook_w;
    chessboard[0][1] = knight_w;
    chessboard[0][2] = bishop_w;
    chessboard[0][3] = queen_w;
    chessboard[0][4] = King_w;
    chessboard[0][5] = bishop_w;
    chessboard[0][6] = knight_w;
    chessboard[0][7] = rook_w;
    chessboard[7][0] = rook_b;
    chessboard[7][1] = knight_b;
    chessboard[7][2] = bishop_b;
    chessboard[7][3] = queen_b;
    chessboard[7][4] = King_b;
    chessboard[7][5] = bishop_b;
    chessboard[7][6] = knight_b;
    chessboard[7][7] = rook_b;

}

void printChessboard(string chessboard[rows][cols]){

    cout << setw(11) << "a" << setw(11) << "b" << setw(11) << "c" << setw(11) << "d" << setw(11) << "e" << setw(11) << "f" << setw(11) << "g" << setw(11) << "h" << endl;
    for (int row = 0; row < 8; row++) {
        cout << row + 1;
        for (int col= 0; col < 8; col++) {
            cout << setw(11) << chessboard[row][col];
        }
        cout << endl;

    }
}
