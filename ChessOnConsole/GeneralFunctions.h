#pragma once
#include <array>

struct Pos;
enum class Flag;
class Piece;
bool isOnLeftDiag(Pos pos, Pos inputPos);
bool isOnRightDiag(Pos pos, Pos inputPos);
bool isOnRow(Pos pos, Pos inputPos);
bool isOnCol(Pos pos, Pos inputPos);
bool isMoveValidOnRow(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnCol(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnRightDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnLeftDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool scanRow(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);
bool scanCol(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);
bool scanLeftDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);
bool scanRightDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag);
void invalidPieceMessage();
void invalidMoveMessage();