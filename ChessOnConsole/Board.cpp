#include "Board.h"
#include "PieceManager.h"
#include "Gamestate.h"

Board::Board(PieceManager& ref, Gamestate& state) :
	piece_ref{ ref }, state_ref{ state }
{
	for (std::size_t i = 0; i < board.size(); ++i) {
		for (std::size_t j = 0;j < board.size(); ++j) {
			if (piece_ref.getMasterArray()[i][j]) {
				board[i][j] = piece_ref.getMasterArray()[i][j]->getGraphics();
			}
			else {
				board[i][j] = '*';
			}
		}
	}
}
void Board::render() {
	for (std::size_t i = 0; i < board.size(); ++i) {
		std::cout << board.size() - i << "  ";
		for (std::size_t j = 0; j < board.size(); ++j) {
			std::cout << board[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n' << "   " << "a " << "b " << "c " << "d " << "e " << "f " << "g " << "h " << '\n';
}
void Board::writeBoard() {
	board[state_ref.getSelectedPiece()->getPos().x][state_ref.getSelectedPiece()->getPos().y] = state_ref.getSelectedPiece()->getGraphics();
}
