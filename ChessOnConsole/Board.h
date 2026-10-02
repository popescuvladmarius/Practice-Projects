#pragma once
#include <array>

class PieceManager;
class Gamestate;
class Board {
private:
	PieceManager& piece_ref;
	Gamestate& state_ref;
	std::array<std::array<char, 8>, 8> board{};
public:
	Board(PieceManager& ref, Gamestate& state);
	void render();
	void writeBoard();
};
