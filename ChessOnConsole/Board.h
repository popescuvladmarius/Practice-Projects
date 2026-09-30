#pragma once
#include "PieceManager.h"

class Board {
private:
	PieceManager& piece_ref;
	std::array<std::array<char, 8>, 8> board{};
public:
	Board(PieceManager& ref);
	void render();
	void writeBoard();
};
