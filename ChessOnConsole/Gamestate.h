#pragma once
#include "Objects.h"

class Piece;
class Gamestate {
private:
	bool state{ true };
	Status status{ Status::init };
	Turn turn{ Turn::white };
	Piece* selected_piece{ nullptr };
	std::vector<Move> moveCollection;
public:
	Turn getTurn();
	void setTurn(Turn input);
	void setSelectedPiece(Piece* piece);
	Piece* getSelectedPiece();
	void setState(bool input);
	bool getState();
	void setStatus(Status input);
	Status getStatus();
	void addMove(Pos move, char graphics, bool capture);
};