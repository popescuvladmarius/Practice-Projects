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

enum Flag {
	white,
	black
};

class Controller {
private:
	Pos inputPos{};
	char inputFile;
	int inputRank;
	std::array<char, 8> files;
public:
	Controller() {
		files[0] = 'a';
		files[1] = 'b';
		files[2] = 'c';
		files[3] = 'd';
		files[4] = 'e';
		files[5] = 'f';
		files[6] = 'g';
		files[7] = 'h';
	}
	void input() {
		std::cin >> inputFile >> inputRank;
	}
	bool checkInput() {
		if (inputRank <= 8 && inputRank >= 1) {
			for (std::size_t i = 0; i < 8; ++i) {
				if (inputFile == files[i]) {
					return true;
				}
			}
		}
		return false;
	}
	Pos getInputNormalized() {
		int row{};
		int col{};
		Pos temp{};
		for (std::size_t i = 0; i < 8; ++i) {
			if (inputFile == files[i]) {
				col = i;
				break;
			}
		}
		row = 7 - (inputRank - 1);
		temp.x = row;
		temp.y = col;
		return temp;
	}
	void select() {
		input();
		if (checkInput()) {
			inputPos = getInputNormalized();
		}
	}
	const Pos& getInputPos() const { return inputPos; }
};

class Team;
class PieceManager;

class Piece {
protected:
	Pos pos{};
	Pos endPos{};
	Flag flag{};
	const PieceManager& piece_ref;
public:
	Piece(const PieceManager& ref) : piece_ref{ ref } {}
    const Pos& getPos() { return pos; }
	void setPos(int x, int y) { pos.x = x; pos.y = y; }
	void setEndPos(Pos pos) { endPos = pos; }
	void setFlag(Flag input) { flag = input; }
	virtual Pos move() = 0;
	virtual ~Piece() = default;
};

class Pawn : public Piece{
private:
	char graphics{ 'p' };
public:
	Pawn(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
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
	Pos move() override {
		if (forward() == endPos) {
			pos = endPos;
			return pos;
		}
		if (forwardDouble() == endPos) {
			pos = endPos;
			return pos;
		}
		if (captureRight() == endPos) {
			pos = endPos;
			return pos;
		}
		if (captureLeft() == endPos) {
			pos = endPos;
			return pos;
		}
	}
};

class Knight : public Piece {
private:
	char graphics{ 'k'};
public:
	Knight(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
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
	Pos move() override {
		if (endPos == getUpRightJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getUpLeftJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getDownRightJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getDownLeftJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getRightUpJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getRightDownJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getLeftUpJump()) {
			pos = endPos;
			return pos;
		}
		if (endPos == getLeftDownJump()) {
			pos = endPos;
			return pos;
		}
	}
};

class Rook : public Piece{
private:
	char graphics{ 'R' };
public:
	Rook(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
	Pos move() override {
		if (isOnRow(pos, endPos) || isOnCol(pos, endPos)) {
			pos = endPos;
			return pos;
		}
		if (isOnRow(pos, endPos)) {
			if (endPos.y > pos.y){

			}
		}
		if (isOnCol(pos, endPos)) {

		}
	}
};

class Bishop : public Piece{
private:
	char graphics{ 'B' };
public:
	Bishop(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
	Pos move() override {
		if (isOnRightDiagonale(pos, endPos) || isOnLeftDiagonale(pos, endPos)) {
			pos = endPos;
			return pos;
		}
	}
};

class King : public Piece{
private:
	char graphics{ 'K' };
public:
	King(const PieceManager& ref) : Piece{ref} {}
	char getGraphics() const { return graphics; }
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
	Pos move() override {
		if (endPos == forward()) {
			pos = endPos;
			return pos;
		}
		if (endPos == backwards()) {
			pos = endPos;
			return pos;
		}
		if (endPos == right()) {
			pos = endPos;
			return pos;
		}
		if (endPos == left()) {
			pos = endPos;
			return pos;
		}
		if (endPos == up_right()) {
			pos = endPos;
			return pos;
		}
		if (endPos == up_left()) {
			pos = endPos;
			return pos;
		}
		if (endPos == down_right()) {
			pos = endPos;
			return pos;
		}
		if (endPos == down_left()) {
			pos = endPos;
			return pos;
		}
	}
};

class Queen : public Piece {
private:
	char graphics{ 'Q' };
public:
	Queen(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
	Pos move() override {
		if (isOnRow(pos, endPos) || isOnCol(pos, endPos) || isOnRightDiagonale(pos, endPos) || isOnLeftDiagonale(pos, endPos)) {
			pos = endPos;
			return pos;
		}
	}
};

class Team {
private:
	King king;
	Queen queen;
	std::array<Rook, 2> rooks;
	std::array<Bishop, 2> bishops;
	std::array<Knight, 2> knights;
	std::array<Pawn, 8> pawns;
public:
	Team(const PieceManager& ref) : 
	king(ref),
	queen(ref),
	rooks {
		Rook(ref),
		Rook(ref)
	},
	bishops {
		Bishop(ref),
		Bishop(ref)
	},
	knights {
		Knight(ref),
		Knight(ref)
	},
	pawns {
		Pawn(ref),
		Pawn(ref),
		Pawn(ref),
		Pawn(ref),
		Pawn(ref),
		Pawn(ref),
		Pawn(ref),
		Pawn(ref)
	}
	{}
	King& getKing() { return king; }
	Queen& getQueen() { return queen; }
	Rook& getRook(int i) { return rooks[i]; }
	Bishop& getBishop(int i) { return bishops[i]; }
	Knight& getKnight(int i) { return knights[i]; }
	Pawn& getPawn(int i) { return pawns[i]; }
};

class PieceManager {
private:
	int whiteCount{16};
	int blackCount{16};
	int totalCount{ whiteCount + blackCount };
	Team whites;
	Team blacks;
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	void reserve() {
		whitePieces.reserve(16);
		blackPieces.reserve(16);
		}
	void initializeWhites() {
		whites.getKing().setPos(7, 4);
		whites.getKing().setFlag(white);
		whitePieces.push_back(&(whites.getKing()));
		whites.getQueen().setPos(7, 3);
		whites.getQueen().setFlag(white);
		whitePieces.push_back(&(whites.getQueen()));
		whites.getRook(0).setPos(7, 0);
		whites.getRook(0).setFlag(white);
		whitePieces.push_back(&(whites.getRook(0)));
		whites.getRook(1).setPos(7, 7);
		whites.getRook(1).setFlag(white);
		whitePieces.push_back(&(whites.getRook(1)));
		whites.getBishop(0).setPos(7, 2);
		whites.getBishop(0).setFlag(white);
		whitePieces.push_back(&(whites.getBishop(0)));
		whites.getBishop(1).setPos(7, 5);
		whites.getBishop(1).setFlag(white);
		whitePieces.push_back(&(whites.getBishop(1)));
		whites.getKnight(0).setPos(7, 1);
		whites.getKnight(0).setFlag(white);
		whitePieces.push_back(&(whites.getKnight(0)));
		whites.getKnight(1).setPos(7, 6);
		whites.getKnight(1).setFlag(white);
		whitePieces.push_back(&(whites.getKnight(1)));
		for (std::size_t i = 0; i < 8; ++i) {
			whites.getPawn(i).setPos(6, i);
			whites.getPawn(i).setFlag(white);
			whitePieces.push_back(&(whites.getPawn(i)));
		}
	}
	void initializeBlacks() {
		blacks.getKing().setPos(0, 4);
		blacks.getKing().setFlag(black);
		blackPieces.push_back(&(blacks.getKing()));
		blacks.getQueen().setPos(0, 3);
		blacks.getQueen().setFlag(black);
		blackPieces.push_back(&(blacks.getQueen()));
		blacks.getRook(0).setPos(0, 0);
		blacks.getRook(0).setFlag(black);
		blackPieces.push_back(&(blacks.getRook(0)));
		blacks.getRook(1).setPos(0, 7);
		blacks.getRook(1).setFlag(black);
		blackPieces.push_back(&(blacks.getRook(1)));
		blacks.getBishop(0).setPos(0, 2);
		blacks.getBishop(0).setFlag(black);
		blackPieces.push_back(&(blacks.getBishop(0)));
		blacks.getBishop(1).setPos(0, 5);
		blacks.getBishop(1).setFlag(black);
		blackPieces.push_back(&(blacks.getBishop(1)));
		blacks.getKnight(0).setPos(0, 1);
		blacks.getKnight(0).setFlag(black);
		blackPieces.push_back(&(blacks.getKnight(0)));
		blacks.getKnight(1).setPos(0, 6);
		blacks.getKnight(1).setFlag(black);
		blackPieces.push_back(&(blacks.getKnight(1)));
		for (std::size_t i = 0; i < 8; ++i) {
			blacks.getPawn(i).setPos(1, i);
			blacks.getPawn(i).setFlag(black);
			blackPieces.push_back(&(blacks.getPawn(i)));
		}
	}
public:
	PieceManager() :
		whites(*this),
		blacks(*this)
	{
		reserve();
		initializeWhites();
		initializeBlacks();
	}
	Pos getWhiteKingPos() { return whites.getKing().getPos(); }
	char getWhiteKingGraphics() { return 'K'; }
	Pos getWhiteQueenPos() { return whites.getQueen().getPos(); }
	char getWhiteQueenGraphics() { return 'Q'; }
	Pos getWhiteRookPos(int i) { return whites.getRook(i).getPos(); }
	char getWhiteRookGraphics() { return 'R'; }
	Pos getWhiteBishopPos(int i) { return whites.getBishop(i).getPos(); }
	char getWhiteBishopGraphics() { return 'B'; }
	Pos getWhiteKnightPos(int i) { return whites.getKnight(i).getPos(); }
	char getWhiteKnightGraphics() { return 'C'; }
	Pos getWhitePawnPos(int i) { return whites.getPawn(i).getPos(); }
	char getWhitePawnGraphics() { return 'P'; }
	Pos getBlackKingPos() { return blacks.getKing().getPos(); }
	char getBlackKingGraphics() { return 'k'; }
	Pos getBlackQueenPos() { return blacks.getQueen().getPos(); }
	char getBlackQueenGraphics() { return 'q'; }
	Pos getBlackRookPos(int i) { return blacks.getRook(i).getPos(); }
	char getBlackRookGraphics() { return 'r'; }
	Pos getBlackBishopPos(int i) { return blacks.getBishop(i).getPos(); }
	char getBlackBishopGraphics() { return 'b'; }
	Pos getBlackKnightPos(int i) { return blacks.getKnight(i).getPos(); }
	char getBlackKnightGraphics() { return 'c'; }
	Pos getBlackPawnPos(int i) { return blacks.getPawn(i).getPos(); }
	char getBlackPawnGraphics() { return 'p'; }
	std::vector<Piece*>& getWhiteVector() { return whitePieces; }
	std::vector<Piece*>& getBlackVector() { return blackPieces; }
};

class Board {
private:
 PieceManager& piece_ref;
	std::array<std::array<char, 8>, 8> board{};
public:
	Board(PieceManager& ref) : piece_ref{ref} {
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
		std::cout << '\n' << "   " << "a " << "b " << "c " << "d " << "e " << "f " << "g " << "h " << '\n';
	}
	void writeBoard() {

	}
};

class Gamestate {
private:
	bool state{ true };
	enum Turn {
		white,
		black
	};
	Turn turn;
	Piece* selected_piece{ nullptr };
	Pos selected_move{};
public:
	Turn& getTurn() { return turn; }
	void setSelectedPiece(Piece* piece) { selected_piece = piece; }
	Piece* getSelectedPiece() { return selected_piece; }
	void setState(bool input) { state = input; }
	bool getState() { return state; }
};

class GameManager {
private:
	PieceManager piecemanager;
	Controller controller;
	Board board;
	Gamestate gamestate;
public:
	bool checkState() {
		if (gamestate.getState()) {
			return true;
		}
		return false;
	}
	void selectPiece() {
		controller.select();
		switch (gamestate.getTurn()) {
		case white:
			for (const auto& a : piecemanager.getWhiteVector()) {
				if (controller.getInputPos() == a->getPos()) {
					gamestate.setSelectedPiece(a);
					break;
				}
				else {
					gamestate.setSelectedPiece(nullptr);
					gamestate.setState(false);
				}
			}
			break;
		case black:
			for (const auto& a : piecemanager.getBlackVector()) {
				if (controller.getInputPos() == a->getPos()) {
					gamestate.setSelectedPiece(a);
					break;
				}
				else {
					gamestate.setSelectedPiece(nullptr);
					gamestate.setState(false);
				}
			}
			break;
		}
	}
	void selectMove() {
		if (gamestate.getSelectedPiece()) {
			controller.select();
			gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
		}
		else {
			gamestate.setState(false);
		}

	}
	void run() {

	}
};

