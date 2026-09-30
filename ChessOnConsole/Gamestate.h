#pragma once
#include "Objects.h"

class Gamestate {
private:
	bool state{ true };
	Turn turn{ Turn::white };
	Piece* selected_piece{ nullptr };
	Pos selected_move{};
public:
	Turn getTurn();
	void setTurn(Turn input);
	void setSelectedPiece(Piece* piece);
	Piece* getSelectedPiece();
	void setSelectedMove(Pos pos);
	Pos getSelectedMove();
	void setState(bool input);
	bool getState();
};