#pragma once
#include "Pieces.h"
#include "GameloopStateMachine.h"

class Gamestate {
private:
	bool state{ true };
	Status status{ Status::init };
	LoopStatus loopStatus{ LoopStatus::initial };
	Turn turn{ Turn::white };
	Piece* selected_piece{ nullptr };
	std::vector<Move> moveCollection;
public:
	void resetLoopStatus();
	LoopStatus getLoopStatus();
	void setLoopStatus(LoopStatus status);
	Turn getTurn() const;
	void setTurn(Turn input);
	void nextTurn();
	void setSelectedPiece(Piece* piece);
	Piece* getSelectedPiece();
	void setState(bool input);
	bool getState() const;
	void setStatus(Status input);
	Status getStatus() const;
	void addMove(const Piece* const piece, MoveType move = MoveType::regular);
	const Move& readMove();
	const std::vector<Move>& getMoveCollection();
};
