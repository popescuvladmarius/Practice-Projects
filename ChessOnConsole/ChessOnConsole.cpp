#include <iostream>
#include <windows.h>
#include "Objects.h"


int main()
{
	PieceManager piecemanager;
	Board board(piecemanager);
	
	board.render();




	return 0;
}

