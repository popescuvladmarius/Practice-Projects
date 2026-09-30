#include <iostream>
#include <windows.h>
#include "Objects.h"
#include "Pieces.h"
#include "Gamestate.h"
#include "Board.h"

int main()
{
	PieceManager piecemanager;
	Gamestate gamestate;
	Board board(piecemanager);
	
	
	board.render();





	return 0;
}
