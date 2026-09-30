#include "Board.h"

Board::Board(PieceManager& ref) : piece_ref{ ref } {
	for (std::size_t i = 2; i <= 5; ++i) {
		for (std::size_t j = 0; j < board.size(); ++j) {
			board[i][j] = '*';
		}
	}
	board[piece_ref.getWhiteKingPos().x][piece_ref.getWhiteKingPos().y] = piece_ref.getWhiteKingGraphics();
	board[piece_ref.getWhiteQueenPos().x][piece_ref.getWhiteQueenPos().y] = piece_ref.getWhiteQueenGraphics();
	board[piece_ref.getWhiteRookPos(0).x][piece_ref.getWhiteRookPos(0).y] = piece_ref.getWhiteRookGraphics();
	board[piece_ref.getWhiteRookPos(1).x][piece_ref.getWhiteRookPos(1).y] = piece_ref.getWhiteRookGraphics();
	board[piece_ref.getWhiteBishopPos(0).x][piece_ref.getWhiteBishopPos(0).y] = piece_ref.getWhiteBishopGraphics();
	board[piece_ref.getWhiteBishopPos(1).x][piece_ref.getWhiteBishopPos(1).y] = piece_ref.getWhiteBishopGraphics();
	board[piece_ref.getWhiteKnightPos(0).x][piece_ref.getWhiteKnightPos(0).y] = piece_ref.getWhiteKnightGraphics();
	board[piece_ref.getWhiteKnightPos(1).x][piece_ref.getWhiteKnightPos(1).y] = piece_ref.getWhiteKnightGraphics();
	for (std::size_t i = 0; i < 8; ++i) {
		board[piece_ref.getWhitePawnPos(i).x][piece_ref.getWhitePawnPos(i).y] = piece_ref.getWhitePawnGraphics();
	}
	board[piece_ref.getBlackKingPos().x][piece_ref.getBlackKingPos().y] = piece_ref.getBlackKingGraphics();
	board[piece_ref.getBlackQueenPos().x][piece_ref.getBlackQueenPos().y] = piece_ref.getBlackQueenGraphics();
	board[piece_ref.getBlackRookPos(0).x][piece_ref.getBlackRookPos(0).y] = piece_ref.getBlackRookGraphics();
	board[piece_ref.getBlackRookPos(1).x][piece_ref.getBlackRookPos(1).y] = piece_ref.getBlackRookGraphics();
	board[piece_ref.getBlackBishopPos(0).x][piece_ref.getBlackBishopPos(0).y] = piece_ref.getBlackBishopGraphics();
	board[piece_ref.getBlackBishopPos(1).x][piece_ref.getBlackBishopPos(1).y] = piece_ref.getBlackBishopGraphics();
	board[piece_ref.getBlackKnightPos(0).x][piece_ref.getBlackKnightPos(0).y] = piece_ref.getBlackKnightGraphics();
	board[piece_ref.getBlackKnightPos(1).x][piece_ref.getBlackKnightPos(1).y] = piece_ref.getBlackKnightGraphics();
	for (std::size_t i = 0; i < 8; ++i) {
		board[piece_ref.getBlackPawnPos(i).x][piece_ref.getBlackPawnPos(i).y] = piece_ref.getBlackPawnGraphics();
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

}
