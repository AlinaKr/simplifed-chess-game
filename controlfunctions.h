#ifndef CONTROLFUNCTIONS_H
#define CONTROLFUNCTIONS_H
#include <string>

const std::string empty = "__________";
const int rows = 8;
const int cols = 8;

const std::string rook_w = "rook_w", knight_w = "knight_w", bishop_w ="bishop_w", queen_w ="queen_w", King_w ="King_w", pawn_w ="pawn_w", rook_b ="rook_s", knight_b ="knight_b", bishop_b ="bishop_b", queen_b ="queen_b", King_b ="King_b", pawn_b ="pawn_b";

bool isInputValid(std::string input);
int charToInt(char line);
char intToChar(int number);
bool isValidMove(int yCurr, int yFut, int xCurr, int xFut, bool whiteIsPlaying, std::string chessboard [rows][cols]);
bool isKnightMoveValid(int yCurr, int xCurr, int xFut, int yFut);
bool isRookMoveValid(int yCurr, int xCurr, int xFut, int yFut, std::string chessboard [8][8]);
bool isKingMoveValid(int yCurr, int xCurr, int xFut, int yFut, std::string chessboard [8][8]);
bool isBishopMoveValid(int yCurr, int xCurr, int xFut, int yFut, std::string chessboard [8][8]);
bool isQueenMoveValid(int yCurr, int xCurr, int xFut, int yFut, std::string chessboard [8][8]);
bool isPawnMoveValid(int yCurr, int xCurr, int xFut, int yFut, bool whiteIsPlaying, std::string chessboard [8][8]);
bool isMoveCapture(int xFut, int yFut, bool whiteIsPlaying, std::string chessboard [8][8], std::string figure);
void printCapture(bool whiteIsPlaying, std::string fig, std::string field, char beatenFigure);
std::string isKingThreatened(bool whiteIsPlaying, int xFut,int yFut, std::string chessboard[8][8]);
bool isGameOver(bool whiteIsPlaying, std::string chessboard[8][8]);



#endif // CONTROLFUNCTIONS_H
