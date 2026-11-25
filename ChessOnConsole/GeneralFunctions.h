#pragma once
#include <array>
//these functions are used for the rook, bishop and queen because are reusable and better implemented as normal functions rather than member functions
struct Pos;
enum class Flag;
class Piece;
bool isOnLeftDiag(Pos pos, Pos inputPos);                   //checks if a piece is on the left diagonale of the selected piece, pos param expects the selected piece and inputPos the piece to check against
bool isOnRightDiag(Pos pos, Pos inputPos);            //same thing but on right diagonale
bool isOnRow(Pos pos, Pos inputPos);                 //checks if it is on the same row
bool isOnCol(Pos pos, Pos inputPos);                //on the same column
bool isMoveValidOnRow(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);          //checks if the selected move (endPos param) is valid on the row, by sweeping the squares in between including the endPos position, which must be either empty or with an enemy piece
bool isMoveValidOnCol(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);          //same thing on column
bool isMoveValidOnRightDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);      //idem on right diagonale
bool isMoveValidOnLeftDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);      //idem on left diagonale
bool checkScanRow(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);            //scans on row for the king or a piece to lock
bool checkScanCol(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);          //idem on column
bool checkScanLeftDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);            //idem on left diagonale
bool checkScanRightDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);          //idem on right diagonale
void invalidPieceMessage();          //prints invalid message
void invalidMoveMessage();         //prints invalid message