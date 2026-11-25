#pragma once
#include <array>
//the Board is responsible only for giving a visual representation of the board and pieces, enforces no logic
class PieceManager;
class Gamestate;
class Board {
private:
	PieceManager& piece_ref;
	Gamestate& state_ref;
	std::array<std::array<char, 8>, 8> board{};             //each piece is represented by a char, lowercase for blacks and uppercase for whites
public:
	Board(PieceManager& ref, Gamestate& state);
	void render();
	void writeBoard();
};

