#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "FunctionDeclarations.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

class Controller {
private:
	Pos inputPos{};
public:
	void selectPiece() {

	}

	void setInputPos(Pos input) {
		inputPos = input;
	}
	Pos getInputPos() const { return inputPos; }
};

class RuleManager {

};

class CollisionManager {

};

class Pawn {
private:
	Pos pos{};
	char graphics{ 'p' };
	const Controller& controller_ref{};
public:
	Pos getPawnPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setPawnPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos forward() {
		Pos temp{ pos };
		++temp.x;
		return temp;
	}
	Pos forwardDouble() {
		Pos temp{ pos };
		temp.x += 2;
		return temp;
	}
	Pos captureRight() {
		Pos temp{ pos };
		++temp.x;
		++temp.y;
		return temp;
	}
	Pos captureLeft() {
		Pos temp{ pos };
		++temp.x;
		--temp.y;
		return temp;
	}
	Pos move() {
		if (forward() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (forwardDouble() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (captureRight() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (captureLeft() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Knight {
private:
	Pos pos{};
	char graphics{ 'k'};
	const Controller& controller_ref{};
public:
	Pos getKnightPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setKnightPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos getUpRightJump() {
		Pos temp{ pos };
		temp.x += 2;
		temp.y += 1;
		return temp;
	}
	Pos getUpLeftJump() {
		Pos temp{ pos };
		temp.x += 2;
		temp.y -= 1;
		return temp;
	}
	Pos getDownRightJump() {
		Pos temp{ pos };
		temp.x -= 2;
		temp.y += 1;
		return temp;
	}
	Pos getDownLeftJump() {
		Pos temp{ pos };
		temp.x -= 2;
		temp.y -= 1;
		return temp;
	}
	Pos getRightUpJump() {
		Pos temp{ pos };
		temp.x += 1;
		temp.y += 2;
		return temp;
	}
	Pos getRightDownJump() {
		Pos temp{ pos };
		temp.x -= 1;
		temp.y += 2;
		return temp;
	}
	Pos getLeftUpJump() {
		Pos temp{ pos };
		temp.x += 1;
		temp.y -= 2;
		return temp;
	}
	Pos getLeftDownJump() {
		Pos temp{ pos };
		temp.x -= 1;
		temp.y -= 2;
		return temp;
	}
	Pos move() {
		if (controller_ref.getInputPos() == getUpRightJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getUpLeftJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getDownRightJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getDownLeftJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getRightUpJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getRightDownJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getLeftUpJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == getLeftDownJump()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Rook {
private:
	Pos pos{};
	char graphics{ 'R' };
	const Controller& controller_ref{};
public:
	Pos getRookPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setRookPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos move() {
		if (isOnRow(pos, controller_ref.getInputPos()) || isOnCol(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Bishop {
private:
	Pos pos{};
	char graphics{ 'B' };
	const Controller& controller_ref{};
public:
	Pos getBishopPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setBishopPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos move() {
		if (isOnRightDiagonale(pos, controller_ref.getInputPos()) || isOnLeftDiagonale(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class King {
private:
	Pos pos{};
	char graphics{ 'K' };
	const Controller& controller_ref{};
public:
	Pos getKingPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setKingPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos forward() {
		Pos temp{ pos };
		++temp.x;
		return temp;
	}
	Pos backwards() {
		Pos temp{ pos };
		--temp.x;
		return temp;
	}
	Pos right() {
		Pos temp{ pos };
		++temp.y;
		return temp;
	}
	Pos left() {
		Pos temp{ pos };
		--temp.y;
		return temp;
	}
	Pos up_right() {
		Pos temp{ pos };
		++temp.x;
		++temp.y;
		return temp;
	}
	Pos up_left() {
		Pos temp{ pos };
		++temp.x;
		--temp.y;
		return temp;
	}
	Pos down_right() {
		Pos temp{ pos };
		--temp.x;
		++temp.y;
		return temp;
	}
	Pos down_left() {
		Pos temp{ pos };
		--temp.x;
		--temp.y;
		return temp;
	}
	Pos move(){
		if (controller_ref.getInputPos() == forward()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == backwards()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == up_right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == up_left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == down_right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == down_left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Queen {
private:
	Pos pos{};
	char graphics{ 'Q' };
	const Controller& controller_ref{};
public:
	Pos getQueenPos() { return pos; }
	char getGraphics() const { return graphics; }
	void setQueenPos(int x, int y) { pos.x = x; pos.y = y; }
	Pos move() {
		if (isOnRow(pos, controller_ref.getInputPos()) || isOnCol(pos, controller_ref.getInputPos()) || isOnRightDiagonale(pos, controller_ref.getInputPos()) || isOnLeftDiagonale(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Team {
private:
	King king{};
	Queen queen{};
	std::array<Rook, 2> rooks{};
	std::array<Bishop, 2> bishops{};
	std::array<Knight, 2> knights{};
	std::array<Pawn, 8> pawns{};
public:
	King getKing() const { return king; }
	Queen getQueen() const { return queen; }
	Rook getRook(int i) const { return rooks[i]; }
	Bishop getBishop(int i) const { return bishops[i]; }
	Knight getKnight(int i) const { return knights[i]; }
	Pawn getPawn(int i) const { return pawns[i]; }
};

class PieceManager {
private:
	int whiteCount{16};
	int blackCount{16};
	int totalCount{ whiteCount + blackCount };
	Team whites{};
	Team blacks{};
	void initializeWhites() {
		whites.getKing().setKingPos(7, 4);
		whites.getQueen().setQueenPos(7, 3);
		whites.getRook(0).setRookPos(7, 0);
		whites.getRook(1).setRookPos(7, 7);
		whites.getBishop(0).setBishopPos(7, 2);
		whites.getBishop(1).setBishopPos(7, 5);
		whites.getKnight(0).setKnightPos(7, 1);
		whites.getKnight(1).setKnightPos(7, 6);
		for (std::size_t i = 0; i < 8; ++i) {
			whites.getPawn(i).setPawnPos(6, i);
		}
	}
	void initializeBlacks() {
		blacks.getKing().setKingPos(0, 4);
		blacks.getQueen().setQueenPos(0, 3);
		blacks.getRook(0).setRookPos(0, 0);
		blacks.getRook(1).setRookPos(0, 7);
		blacks.getBishop(0).setBishopPos(0, 2);
		blacks.getBishop(1).setBishopPos(0, 5);
		blacks.getKnight(0).setKnightPos(0, 1);
		blacks.getKnight(1).setKnightPos(0, 6);
		for (std::size_t i = 0; i < 8; ++i) {
			blacks.getPawn(i).setPawnPos(1, i);
		}
	}
public:
	PieceManager() {
		initializeWhites();
		initializeBlacks();
	}
	Pos getWhiteKingPos() const { return whites.getKing().getKingPos(); }
	char getWhiteKingGraphics() const { return 'K'; }
	Pos getWhiteQueenPos() const { return whites.getQueen().getQueenPos(); }
	char getWhiteQueenGraphics() const { return 'Q'; }
	Pos getWhiteRookPos(int i) const { return whites.getRook(i).getRookPos(); }
	char getWhiteRookGraphics() const { return 'R'; }
	Pos getWhiteBishopPos(int i) const { return whites.getBishop(i).getBishopPos(); }
	char getWhiteBishopGraphics() const { return 'B'; }
	Pos getWhiteKnightPos(int i) const { return whites.getKnight(i).getKnightPos(); }
	char getWhiteKnightGraphics() const { return 'C'; }
	Pos getWhitePawnPos(int i) const { return whites.getPawn(i).getPawnPos(); }
	char getWhitePawnGraphics() const { return 'P'; }
	Pos getBlackKingPos() const { return blacks.getKing().getKingPos(); }
	char getBlackKingGraphics() const { return 'k'; }
	Pos getBlackQueenPos() const { return blacks.getQueen().getQueenPos(); }
	char getBlackQueenGraphics() const { return 'q'; }
	Pos getBlackRookPos(int i) const { return blacks.getRook(i).getRookPos(); }
	char getBlackRookGraphics() const { return 'r'; }
	Pos getBlackBishopPos(int i) const { return blacks.getBishop(i).getBishopPos(); }
	char getBlackBishopGraphics() const { return 'b'; }
	Pos getBlackKnightPos(int i) const { return blacks.getKnight(i).getKnightPos(); }
	char getBlackKnightGraphics() const { return 'c'; }
	Pos getBlackPawnPos(int i) const { return blacks.getPawn(i).getPawnPos(); }
	char getBlackPawnGraphics() const { return 'p'; }
};

class Board {
private:
	std::array<std::array<char, 8>, 8> board{};
	const PieceManager& piece_ref{};
public:
	Board(const PieceManager& ref) : piece_ref{ref} {
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
	void render() {
		for (std::size_t i = 0; i < board.size(); ++i) {
			std::cout << board.size() - i << "  ";
			for (std::size_t j = 0; j < board.size(); ++j) {
				std::cout << board[i][j] << ' ';
			}
			std::cout << '\n';
		}
		std::cout << "   " << "a " << "b " << "c " << "d " << "e " << "f " << "g " << "h " << '\n';
	}

	void writeBoard() {

	}
};

class Gamestate {

};

