#pragma once
#include "Pieces.h"
#include "Controller.h"
#include "Board.h"
#include "Gamestate.h"

class GameManager {
private:
	PieceManager piecemanager;
	Controller controller;
	Board board;
	Gamestate gamestate;
public:
	bool checkState();
	void selectPiece();
	void selectMove();
	void nextTurn();
	void run();
};