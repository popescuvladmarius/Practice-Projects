#pragma once
#include "Pieces.h"
#include "PieceManager.h"
#include "Controller.h"
#include "Gamestate.h"
#include "Board.h"
#include "RuleManager.h"
//the master class that owns all other actors and executes the game loop 
class GameManager {
private:
	PieceManager piecemanager;
	Controller controller;
	Gamestate gamestate;
	Board board;
	RuleManager rules;

public:
	void interpretSelection();                     //handles an iteration of the game loop by switching on the loopStatus enum and allowing only the corresponding functions for each loop stage to be called
	void selectPiece(char& counter);             //selects a piece. It implements a counter so that in the pieceSelected stage selectMove() can be called only if selectPiece() has not been called again (check the cpp file for further details on its implementation)
	void selectMove();                        //selects a move (check the cpp file for further details on its implementation)
	void selectEvadingMove();               //selects a move that must evade from check. (check the cpp file for more detials on its implementation)
	King* getCheckedKing();                //returns a pointer to the king being checked
	void handleCheck();                   //handles the game loop during check conditions
	bool isCheckmate();                   //evaluates if it's checkmate, still to implement
	void run();                          //the game loop. It is still incomplete, has to handle checkmate evaluation and potentially a user interface for when the game ends, also the 
	                                     //possibility to browse through all the moves perfromed in the game.
};