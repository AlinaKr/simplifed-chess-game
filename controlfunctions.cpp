#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <controlfunctions.h>

using namespace std;

bool isInputValid(string input){
    bool wrongInputFormat = input[2] != '-' || input[0] < 'a' || input[0] > 'h' || input[1] < '1' || input[1] > '8' || input[3] < 'a' || input[3] > 'h' || input[4] < '1' || input[4] > '8';
    bool wrongLength = input.length() < 5 || input.length() > 5;

    //validation of input
    if (wrongLength || wrongInputFormat){
        cout << "Input does not have the required length or correct format" << endl;
        return false;
    }
    else{
        return true;
    }
}

// Convert input char to int
int charToInt(char line) {
  int num = -1;
    switch (line){
        case 'a':
            num = 0;
            break;
        case 'b':
            num = 1;
            break;
        case 'c':
            num = 2;
            break;
        case 'd':
            num = 3;
            break;
        case 'e':
            num = 4;
            break;
        case 'f':
            num = 5;
            break;
        case 'g':
            num = 6;
            break;
        case 'h':
            num = 7;
            break;
        default:
            cout << "ERROR!";
    }
    return num;
}

// Convert int to char
char intToChar(int number) {
  char letter = ' ';
    switch (number){
        case 0:
            letter = 'a';
            break;
        case 1:
            letter = 'b';
            break;
        case 2:
            letter = 'c';
            break;
        case 3:
            letter = 'd';
            break;
        case 4:
            letter = 'e';
            break;
        case 5:
            letter = 'f';
            break;
        case 6:
            letter = 'g';
            break;
        case 7:
            letter = 'h';
            break;
        default:
            cout << "ERROR!";
    }
    return letter;
}

bool isValidMove(int yCurr, int yFut, int xCurr, int xFut, bool whiteIsPlaying, string chessboard [rows][cols]) {
    if (chessboard[yCurr][xCurr] == empty) {
        cout << "You need to have a figure on your starting position to move" << endl;
        return false;
    }
    else if (chessboard[yCurr][xCurr] == chessboard[yFut][xFut]) {
        cout << "You must not remain on the same position" << endl;
        return false;
    }
    else if ((whiteIsPlaying && chessboard[yCurr][xCurr][chessboard[yCurr][xCurr].length()-1] == 's')
    || (!whiteIsPlaying && chessboard[yCurr][xCurr][chessboard[yCurr][xCurr].length()-1] == 'w')){
        cout << "You have to play with your own figure and not those of the opponenent team" << endl;
        return false;
    }
    else if ((whiteIsPlaying && chessboard[yFut][xFut][chessboard[yFut][xFut].length()-1] == 'w')
    || (!whiteIsPlaying && chessboard[yFut][xFut][chessboard[yFut][xFut].length()-1] == 's')){
        cout << "The target position is already occupied by a figure of your own" << endl;
        return false;
    }
    else{
    //        char *str = chessboard[yCurr][xCurr];
            bool result;
            switch(chessboard[yCurr][xCurr][0]){
                case 'k':
                    result = isKnightMoveValid(yCurr, xCurr, xFut, yFut);
                    break;
                case 'b':
                    result = isBishopMoveValid(yCurr, xCurr, xFut, yFut, chessboard);
                    break;
                case 'K':
                    result = isKingMoveValid(yCurr, xCurr, xFut, yFut, chessboard);
                    break;
                case 'q':
                    result = isQueenMoveValid(yCurr, xCurr, xFut, yFut, chessboard);
                    break;
                case 'r':
                    result = isRookMoveValid(yCurr, xCurr, xFut, yFut, chessboard);
                    break;
                case 'p':
                    result = isPawnMoveValid(yCurr, xCurr, xFut, yFut, whiteIsPlaying, chessboard);
                    break;
                default:
                    cout << "ERROR!";
                    return false;
            }
            return result;
    }
}

bool isPawnMoveValid (int yCurr, int xCurr, int xFut, int yFut, bool whiteIsPlaying, string chessboard [rows][cols]){
    //pawns are only allowed to move vertically
    if (xCurr != xFut){
        return false;
    }
    //target position has to be free since pawn pieces capture diagonally
    else if(chessboard[yFut][xFut] != empty) {
        return false;
    }
    //white pawns are allowed to move only downwards, black pawns only upwards
    else if ((whiteIsPlaying && yFut < yCurr)
    || (!whiteIsPlaying && yFut > yCurr)) {
        return false;
    }
    //pawns can only take 2 steps at once when it is their first move. Check individually for white(second row) and black(forelast row) pawns
    else if (whiteIsPlaying && yCurr + 2 == yFut){
        if (yCurr != 1) return false;
        if (chessboard[yCurr + 1][xCurr] != empty) return false;
        if (yCurr == 1) return true;
    }
    else if (!whiteIsPlaying && yCurr - 2 == yFut){
        if (yCurr != 6) return false;
        if (chessboard[yCurr - 1][xCurr] != empty) return false;
        if (yCurr == 6) return true;
    }
    //moving more than 2 steps at once is forbidden under all circumstances. In this case, return false
    else if(whiteIsPlaying && (yFut-yCurr) > 2) {
        return false;
    }
    else if (!whiteIsPlaying && yCurr-yFut > 2) return false;
    else{
        return true;
    }
}

bool isRookMoveValid (int yCurr, int xCurr, int xFut, int yFut, string chessboard [rows][cols]){
    if (xCurr != xFut && yCurr != yFut) return false;
    //if move is upwards
    else if (yFut < yCurr){
        for(int i = yCurr-1; i > yFut; i--){
            //check if the way to the target position is not blocked. Otherwise, return false
            if (chessboard[i][xCurr] != empty) return false;
        }
    }
    //if move is downwards
    else if (yFut > yCurr){
        for(int i = yCurr+1; i < yFut; i++){
            //check if the way to the target position is not blocked. Otherwise, return false
            if (chessboard[i][xCurr] != empty) return false;
        }
    }
    //if move is sidewards to the left
    else if (xFut < xCurr){
        for(int i = xCurr-1; i > xFut; i--){
            if (chessboard[yCurr][i] != empty) return false;
        }
    }
    //if move is sidewards to the right
    else if (xFut > xCurr){
        for(int i = xCurr+1; i < xFut; i++){
            if (chessboard[yCurr][i] != empty) return false;
        }
    }
    return true;
}

bool isBishopMoveValid (int yCurr, int xCurr, int xFut, int yFut, string chessboard [rows][cols]){
    //if the following two expressions are not equal, we are always dealing with an invalid bishop move
    // because it is limited to diagonal movement
    if (abs(xFut-xCurr) != abs(yFut-yCurr)) return false;

    //save indexes of possible valid fields in variables
    int xToCheckDownLeft = xCurr - 1;
    int yToCheckDownLeft = yCurr - 1;
    int xToCheckUpLeft = xCurr - 1;
    int yToCheckUpLeft = yCurr + 1;
    int xToCheckUpRight = xCurr + 1;
    int yToCheckUpRight = yCurr + 1;
    int xToCheckDownRight = xCurr + 1;
    int yToCheckDownRight = yCurr - 1;

    //if move is to the buttom left
    if (yFut < yCurr && xFut < xCurr){
        //check if the way to the target position is not blocked. Otherwise, return false
        while (yFut < yToCheckDownLeft){
            if (chessboard[yToCheckDownLeft--][xToCheckDownLeft--] != empty) return false;
        }
    }
    //if move is to the top left
    else if (yFut > yCurr && xFut < xCurr){
         while (yFut > yToCheckUpLeft){
            if (chessboard[yToCheckUpLeft++][xToCheckUpLeft--] != empty) return false;
        }
    }
    //if move is to the top right
    else if (yFut > yCurr && xFut > xCurr){
        while (yFut > yToCheckUpRight){
            if (chessboard[yToCheckUpRight++][xToCheckUpRight++] != empty) return false;
        }
    }
    //if move is to the buttom right
    else if (yFut < yCurr && xFut > xCurr){
        while (yFut < yToCheckDownRight){
            if (chessboard[yToCheckDownRight--][xToCheckDownRight++] != empty) return false;
        }
    }
    return true;
}

bool isQueenMoveValid (int yCurr, int xCurr, int xFut, int yFut, string chessboard [rows][cols]){
    //the Queen's possible moves are a combination of the Bishop's and Rook's
    if (isBishopMoveValid(yCurr, xCurr, xFut, yFut, chessboard) || isRookMoveValid(yCurr, xCurr, xFut, yFut, chessboard)) return true;
    else{
        return false;
    }

}

bool isKingMoveValid (int yCurr, int xCurr, int xFut, int yFut, string chessboard [rows][cols]){
    //A king can move one square in any direction (horizontally, vertically, or diagonally)
    //two loops going through all those possible positions for the king and checking if future field is included
    for (int rowTest = yCurr -1; rowTest <= yCurr +1; rowTest++ ) {
        for (int colTest = xCurr-1; colTest <= xCurr+1; colTest++){
            if (xFut == colTest && yFut == rowTest) {
                return true;
            }
        }
    }
    return false;
}

bool isKnightMoveValid (int yCurr, int xCurr, int xFut, int yFut){
     //the knight moves to a square that is two squares away horizontally and one square vertically, or two squares
     //vertically and one square horizontally.
    if ((xCurr+1==xFut && yCurr+2==yFut) || (xCurr+1==xFut && yCurr-2==yFut) || (xCurr+2==xFut && yCurr+1==yFut) || (xCurr+2==xFut && yCurr-1==yFut)
    || (xCurr-1==xFut && yCurr+2==yFut) || (xCurr-1==xFut && yCurr-2==yFut) || (xCurr-2==xFut && yCurr+1==yFut) || (xCurr-2==xFut && yCurr-1==yFut)) {
        //since knights can jump over pieces, we can return true immediately once the future position matches one of the expressions above
        return true;
    }
    return false;
}

bool isMoveCapture(int xFut, int yFut, bool whiteIsPlaying, string chessboard [8][8], string figure){
    char blackFigure = 'b', whiteFigure = 'w';

    char figureOfField = chessboard[yFut][xFut][2];
    char figureOfFieldpawn1;
    char figureOfFieldpawn2;
    whiteIsPlaying ? figureOfFieldpawn1=chessboard[yFut+1][xFut-1][2] : figureOfFieldpawn1=chessboard[yFut-1][xFut-1][2];
    whiteIsPlaying ? figureOfFieldpawn2=chessboard[yFut+1][xFut+1][2] : figureOfFieldpawn2=chessboard[yFut-1][xFut+1][2];
    std::string field = "";

        //Considering that pawns do not capture in the same direction they move:
        //check if move is capture when pawn is white and currently playing
        if(figure == "pawn" && whiteIsPlaying){
            //white pawns can capture to the bottom left and bottom right
            //check if bottom left is still a field inside the gameboard
            if(yFut+1 < 8 && xFut-1 >= 0){
                //check for opposite piece on corresponding field
                if(figureOfFieldpawn1 == blackFigure) {
                    //if there is an opposite figure..
                    //convert integer coordinates of the fiel to its corresponding name (e.g. b4)
                    field += (intToChar(xFut-1));
                    field += std::to_string(yFut+2);
                    printCapture(whiteIsPlaying, "pawn", field, chessboard[yFut+1][xFut-1][0]);
                    //empty field
                    chessboard[yFut+1][xFut-1] = empty;
                    return true;}
            }
            //check if bottom right is still a field inside the gameboard
            if(yFut+1 < 8 && xFut+1 < 8){
                //check for opposite piece on corresponding field
                if(figureOfFieldpawn2 == blackFigure){
                    //if there is an opposite figure..
                    //convert integer coordinates of the fiel to its corresponding name (e.g. b4)
                    field += (intToChar(xFut+1));
                    field += std::to_string(yFut+2);
                    printCapture(whiteIsPlaying, "pawn", field, chessboard[yFut+1][xFut+1][0]);
                    //empty field
                    chessboard[yFut+1][xFut+1] = empty;
                    return true;}
            }
        }
        //check if move is capture when pawn is black and currently playing
        else if (figure == "pawn" && !whiteIsPlaying ){
            //black pawns can capture to the top left and bottom right
            //check if top left is still a field inside the gameboard
            if(yFut-1 >= 0 && xFut-1 >= 0){
                if(figureOfFieldpawn1 == whiteFigure) {
                    field += (intToChar(xFut-1));
                    field += std::to_string(yFut);
                    printCapture(whiteIsPlaying, "pawn", field, chessboard[yFut-1][xFut-1][0]);
                    chessboard[yFut-1][xFut-1] = empty;
                    return true;
                }
            }
            if(yFut-1 >= 0 && xFut+1 < 8){
                if(figureOfFieldpawn2 == whiteFigure) {
                    field += intToChar(xFut+1);
                    field += std::to_string(yFut);
                    printCapture(whiteIsPlaying, "pawn", field, chessboard[yFut-1][xFut+1][0]);
                    chessboard[yFut-1][xFut+1] = empty;
                    return true;
                }
            }
        }
        //Otherwise we are dealing with a piece that captures the same way it moves and a much simpler logic
         else{
                //check for rival piece on the future position
                //if current playing piece is white
                if( whiteIsPlaying && figureOfField == blackFigure){
                    //if there is one, move is a capture!
                    return true;
                }
                //if current playing piece is black
                else if( !whiteIsPlaying && figureOfField == whiteFigure){
                    return true;
                }

        }
    return false;
}

void printCapture(bool whiteIsPlaying, string fig, string field, char beatenFigure){
    string currPlayerColor = "white";
    string oppPlayerColor = "white";
    whiteIsPlaying ? oppPlayerColor="black" : currPlayerColor="black";


        switch(beatenFigure){
            case 'j':
                cout << fig << " " << currPlayerColor << " beats knight " << oppPlayerColor << " at " << field << endl;
                break;
            case 'b':
                cout << fig << " " << currPlayerColor << " beats bishop " << oppPlayerColor << " at " << field << endl;
                break;
            case 'k':
                cout << fig << " " << currPlayerColor << " beats king " << oppPlayerColor << " at " << field << endl;
                break;
            case 'q':
                cout << fig << " " << currPlayerColor << " beats queen " << oppPlayerColor << " at " << field << endl;
                break;
            case 't':
                cout << fig << " " << currPlayerColor << " beats rook " << oppPlayerColor << " at " << field << endl;
                break;
            case 'p':
                cout << fig << " " << currPlayerColor << " beats pawn " << oppPlayerColor << " at " << field << endl;
                break;
            default:
                    cout << "ERROR!";
             }
}

std::string isKingThreatened (bool whiteIsPlaying, int xFut,int yFut, string chessboard[8][8]){
    string opponentKing = whiteIsPlaying ? "King_b" : "King_w";
    std::string field ="";

    for (int row = 0; row <=7; row++) {
        for(int col = 0; col <=7; col++) {
            if(chessboard[row][col] == opponentKing) {
                    //check if move to opponent king is valid with current playing piece (which is not a pawn)
                    if(isValidMove(yFut, row, xFut, col, whiteIsPlaying, chessboard)
                    && chessboard[yFut][xFut][0] != 'p'){
                        //convert indexes to actual name of position. (e.g. b7)
                        field += (intToChar(col));
                        field += to_string(row+1);
                    }
                    //all exceptional cases, if current playing piece is a white pawn
                    else if (whiteIsPlaying && chessboard[yFut][xFut][0] == 'p'){
                        //is pawn on a position enabling it to capture the opposite king diagonally during the next move?
                        if (yFut+2 < 8 && xFut-1 >= 0 && chessboard[yFut+2][xFut-1] == opponentKing) {
                            field += (intToChar(col-1));
                            field += to_string(row+3);
                        }
                        else if (yFut+2 < 8 && xFut+1 < 8 && chessboard[yFut+2][xFut+1] == opponentKing){
                            field += (intToChar(col+1));
                            field += to_string(row+3);
                        }
                    }
                    //all exceptional cases, if current playing piece is a black pawn
                    else if (!whiteIsPlaying && chessboard[yFut][xFut][0] == 'p')
                        //is pawn on a position enabling it to capture the opposite king diagonally during the next move?
                        if (yFut-2 >= 0 && xFut-1 >= 0 && chessboard[yFut-2][xFut-1] == opponentKing){
                             field += (intToChar(col-1));
                             field += to_string(row-1);
                         }
                         else if (yFut-2 >= 0 && xFut+1 < 8 && chessboard[yFut-2][xFut+1] == opponentKing){
                             field += (intToChar(col+1));
                             field += to_string(row-1);
                         }
                    }

         }
    }
    //return name of the threatened king position or an empty string if king is not exposed to any threat
    return field;
}


//Simplified method to verify the end of the fame
bool isGameOver(bool whiteIsPlaying, string chessboard[8][8]){
    string searchedKing = "";
    whiteIsPlaying ? searchedKing="King_b" : searchedKing="King_w";
    for (int row = 0; row < 8; row++) {
        for (int col= 0; col < 8; col++){
            if (chessboard[row][col]==searchedKing) return false;
        }
    }
    //if opposite king has been captured, the game is over
    cout << "Checkmate" << endl;
    return true;
}




