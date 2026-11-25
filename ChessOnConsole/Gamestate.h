#pragma once
#include "Pieces.h"

class Gamestate {
private:
	bool state{ true };                           //the game state upon which the main game loop runs
	Status status{ Status::init };                  //to be deprecated
	LoopStatus loopStatus{ LoopStatus::initial };              //indicates the stage of execution of an iteration of the game loop
	Turn turn{ Turn::white };                       //game turn, defaulted to white
	Piece* selected_piece{ nullptr };               //the piece selected through input is stored in this pointer
	std::vector<Move> moveCollection;               //a store of all Moves performed during game
	std::vector<Piece*> whiteCheckingPieces;          //stores all the pieces that signal a check during a turn and consulted by GameManager to evaluate the checkmate. Will be emptied at each next turn
	std::vector<Piece*> blackCheckingPieces;          //idem for blacks
public:
	void resetLoopStatus();          
	LoopStatus getLoopStatus();
	void setLoopStatus(LoopStatus status);
	Turn getTurn() const;
	void setTurn(Turn input);
	void nextTurn();                             //switches to next turn and resets the loop status to LoopStatus::initial
	void setSelectedPiece(Piece* piece);
	Piece* getSelectedPiece();
	void setState(bool input);
	bool getState() const;
	void setStatus(Status input);
	Status getStatus() const;
	void addMove(const Piece* const piece, MoveType move = MoveType::regular);            //writes move to moveCollection, defaults the MoveType to regular
	const Move& readMove();                          //reads the last element in the vector
	const std::vector<Move>& getMoveCollection();               //returns a const ref to the whole vector
	void addToWhiteCheckingPieceArray(Piece* piece);             //adds a piece to the corresponding vector
	void addToBlackCheckingPieceArray(Piece* piece);            //same
	const std::vector<Piece*>& getWhiteCheckingPieces();         //const ref to the corresponding vector
	const std::vector<Piece*>& getBlackCheckingPieces();          //const ref to the corresponding vector
};
