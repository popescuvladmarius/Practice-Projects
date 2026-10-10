#pragma once
#include "Pieces.h"
#include "PieceManager.h"
#include "Controller.h"
#include "Gamestate.h"
#include "Board.h"
#include "RuleManager.h"

class GameManager {
private:
	PieceManager piecemanager;
	Controller controller;
	Gamestate gamestate;
	Board board;
	RuleManager rules;
public:
	bool checkState();
	void selectPiece();
	void selectMove();
	void nextTurn();
	void run();
};