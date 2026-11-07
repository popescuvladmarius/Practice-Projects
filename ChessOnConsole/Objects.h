#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "GeneralFunctions.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

enum class Flag {
	white,
	black
};

enum class Turn {
	white,
	black
};

enum class Status {
	init,
	validPiece,
	validMove,
	invalidPiece,
	invalidMove
};

enum class CheckStatus {
	noneChecked,
	whiteChecked,
	blackChecked,
	bothChecked
};

enum class CastlingMove {
	other,
	kingsideCastling,
	queensideCastling
};

struct Move {
	Pos move;
	Pos oldPos;
	Piece* piece;
	bool capture;
};

