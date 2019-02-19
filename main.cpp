#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <controlfunctions.h>
#include <boardsetup.h>


using namespace std;


int main()
{
    //declare variables and constants
    string input;
    int yCurr, xCurr, yFut, xFut;
    string chessboard[rows][cols]={};

    //set up start of game
    setUpBoard(chessboard);
    bool whiteIsPlaying = true;
    bool GameRunning = true;

    // Loop while game is running (input is not exit)
    while(GameRunning){
        printChessboard(chessboard);
        // Output instructions
        whiteIsPlaying? cout << "White is playing!" << endl : cout << "Black is playing!" << endl;
        cout << "Please enter a move (e.g. b1-c3) Enter exit to abort:\n ";
        cin >> input;

        if(input == "exit") break;

        if (!isInputValid(input)) continue;

        //initialize field identifier variables with corresponding index values
        yCurr = (input[1] - '0') - 1;
        yFut = (input[4] - '0') - 1;
        xCurr = charToInt(input[0]);
        xFut = charToInt(input[3]);

        char typeOfFutureField = chessboard[yFut][xFut][0];
        string nameOfFutureField = input.substr(3,4);

        //check if move is valid
        if (isValidMove(yCurr, yFut, xCurr, xFut, whiteIsPlaying, chessboard)){
            //extract current playing figure
            switch(chessboard[yCurr][xCurr][0]){
                    case 'k':
                    if (isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "Knight")){
                        printCapture(whiteIsPlaying, "Knight", nameOfFutureField, typeOfFutureField);
                    }
                        break;
                    case 'b':
                    if (isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "Bishop")){
                        printCapture(whiteIsPlaying, "Bishop", nameOfFutureField, typeOfFutureField);
                    }
                        break;
                    case 'K':
                    if (isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "King")){
                        printCapture(whiteIsPlaying, "King", nameOfFutureField, typeOfFutureField);
                    }
                        break;
                    case 'q':
                    if (isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "Queen")){
                        printCapture(whiteIsPlaying, "Queen", nameOfFutureField, typeOfFutureField);
                    }
                        break;
                    case 'r':
                    if (isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "Rook")){
                        printCapture(whiteIsPlaying, "Rook", nameOfFutureField, typeOfFutureField);
                    }
                        break;
                    case 'p':
                    //Exceptional case with pawn, who does not capture in the same direction that it moves.
                    isMoveCapture(xFut, yFut, whiteIsPlaying, chessboard, "pawn");
                        break;
                    default:
                        cout << "ERROR!";
                }


            //Update positions
            chessboard[yFut][xFut] = chessboard[yCurr][xCurr];
            chessboard[yCurr][xCurr] = empty;

            //Check if king of opposite party is threatened
            string threatenedKing;
            whiteIsPlaying ? threatenedKing="Black King" : threatenedKing="White King";
            if (isKingThreatened(whiteIsPlaying, xFut, yFut, chessboard) != "") {
                cout << threatenedKing << " at " << isKingThreatened(whiteIsPlaying, xFut, yFut, chessboard)
                << " is in check " << endl;
            }

            //If game is won (ergo king was captured in this chess version), the game loop will be terminated.
            //Otherwise execute player exchange (switch color of current playing team)
            isGameOver(whiteIsPlaying, chessboard) ? GameRunning = false : whiteIsPlaying = !whiteIsPlaying;

        }
        //if move is invalid, display message
        else{
            cout << "Invalid move for this piece. Try again." << endl;
        }
    }
}
