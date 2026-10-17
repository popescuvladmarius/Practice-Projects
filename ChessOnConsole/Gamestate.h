#pragma once
#include "Pieces.h"

class Gamestate {
private:
	bool state{ true };
	Status status{ Status::init };
	Turn turn{ Turn::white };
	Piece* selected_piece{ nullptr };
	std::vector<Move> moveCollection;
public:
	Turn getTurn() const;
	void setTurn(Turn input);
	void setSelectedPiece(Piece* piece);
	Piece* getSelectedPiece();
	void setState(bool input);
	bool getState() const;
	void setStatus(Status input);
	Status getStatus() const;
	void addMove(const Piece* const piece);
	const Move& readMove();
	const std::vector<Move>& getMoveCollection();
};
