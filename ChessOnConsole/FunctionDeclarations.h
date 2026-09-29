#pragma once
#include <array>

struct Pos;
class Piece;
bool isOnLeftDiag(Pos pos, Pos inputPos);
bool isOnRightDiag(Pos pos, Pos inputPos);
bool isOnRow(Pos pos, Pos inputPos);
bool isOnCol(Pos pos, Pos inputPos);
bool isMoveValidOnRow(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnCol(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnRightDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
bool isMoveValidOnLeftDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece);
