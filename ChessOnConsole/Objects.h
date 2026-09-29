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
		rooks{
			Rook(ref),
			Rook(ref)
		},
		bishops{
			Bishop(ref),
			Bishop(ref)
		},
		knights{
			Knight(ref),
			Knight(ref)
		},
		pawns{
			Pawn(ref),
			Pawn(ref),
			Pawn(ref),
			Pawn(ref),
			Pawn(ref),
			Pawn(ref),
			Pawn(ref),
			Pawn(ref)
		}
	{
	}
	King& getKing() { return king; }
	Queen& getQueen() { return queen; }
	Rook& getRook(int i) { return rooks[i]; }
	Bishop& getBishop(int i) { return bishops[i]; }
	Knight& getKnight(int i) { return knights[i]; }
	Pawn& getPawn(int i) { return pawns[i]; }
};

class PieceManager {
private:
	int whiteCount{ 16 };
	int blackCount{ 16 };
	int totalCount{ whiteCount + blackCount };
	Team whites;
	Team blacks;
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	std::array<std::array <Piece*, 8>, 8> masterArray;
	void reserve() {
		whitePieces.reserve(16);
		blackPieces.reserve(16);
	}
	void initializeWhites() {
		whites.getKing().setPos(7, 4);
		whites.getKing().setFlag(white);
		whitePieces.push_back(&(whites.getKing()));
		masterArray[7][4] = &(whites.getKing());
		whites.getQueen().setPos(7, 3);
		whites.getQueen().setFlag(white);
		whitePieces.push_back(&(whites.getQueen()));
		masterArray[7][3] = &(whites.getQueen());
		whites.getRook(0).setPos(7, 0);
		whites.getRook(0).setFlag(white);
		whitePieces.push_back(&(whites.getRook(0)));
		masterArray[7][0] = &(whites.getRook(0));
		whites.getRook(1).setPos(7, 7);
		whites.getRook(1).setFlag(white);
		whitePieces.push_back(&(whites.getRook(1)));
		masterArray[7][7] = &(whites.getRook(1));
		whites.getBishop(0).setPos(7, 2);
		whites.getBishop(0).setFlag(white);
		whitePieces.push_back(&(whites.getBishop(0)));
		masterArray[7][2] = &(whites.getBishop(0));
		whites.getBishop(1).setPos(7, 5);
		whites.getBishop(1).setFlag(white);
		whitePieces.push_back(&(whites.getBishop(1)));
		masterArray[7][5] = &(whites.getBishop(1));
		whites.getKnight(0).setPos(7, 1);
		whites.getKnight(0).setFlag(white);
		whitePieces.push_back(&(whites.getKnight(0)));
		masterArray[7][1] = &(whites.getKnight(0));
		whites.getKnight(1).setPos(7, 6);
		whites.getKnight(1).setFlag(white);
		whitePieces.push_back(&(whites.getKnight(1)));
		masterArray[7][6] = &(whites.getKnight(1));
		for (std::size_t i = 0; i < 8; ++i) {
			whites.getPawn(i).setPos(6, i);
			whites.getPawn(i).setFlag(white);
			whitePieces.push_back(&(whites.getPawn(i)));
			masterArray[6][i] = &(whites.getPawn(i));
		}
	}
	void initializeBlacks() {
		blacks.getKing().setPos(0, 4);
		blacks.getKing().setFlag(black);
		blackPieces.push_back(&(blacks.getKing()));
		masterArray[0][4] = &(blacks.getKing());
		blacks.getQueen().setPos(0, 3);
		blacks.getQueen().setFlag(black);
		blackPieces.push_back(&(blacks.getQueen()));
		masterArray[0][3] = &(blacks.getQueen());
		blacks.getRook(0).setPos(0, 0);
		blacks.getRook(0).setFlag(black);
		blackPieces.push_back(&(blacks.getRook(0)));
		masterArray[0][0] = &(blacks.getRook(0));
		blacks.getRook(1).setPos(0, 7);
		blacks.getRook(1).setFlag(black);
		blackPieces.push_back(&(blacks.getRook(1)));
		masterArray[0][7] = &(blacks.getRook(1));
		blacks.getBishop(0).setPos(0, 2);
		blacks.getBishop(0).setFlag(black);
		blackPieces.push_back(&(blacks.getBishop(0)));
		masterArray[0][2] = &(blacks.getBishop(0));
		blacks.getBishop(1).setPos(0, 5);
		blacks.getBishop(1).setFlag(black);
		blackPieces.push_back(&(blacks.getBishop(1)));
		masterArray[0][5] = &(blacks.getBishop(1));
		blacks.getKnight(0).setPos(0, 1);
		blacks.getKnight(0).setFlag(black);
		blackPieces.push_back(&(blacks.getKnight(0)));
		masterArray[0][1] = &(blacks.getKnight(0));
		blacks.getKnight(1).setPos(0, 6);
		blacks.getKnight(1).setFlag(black);
		blackPieces.push_back(&(blacks.getKnight(1)));
		masterArray[0][6] = &(blacks.getKnight(1));
		for (std::size_t i = 0; i < 8; ++i) {
			blacks.getPawn(i).setPos(1, i);
			blacks.getPawn(i).setFlag(black);
			blackPieces.push_back(&(blacks.getPawn(i)));
			masterArray[1][i] = &(blacks.getPawn(i));
		}
	}
	void initializeArray() {
		for (std::size_t i = 2; i <= 5; ++i) {
			for (std::size_t j = 0; j < masterArray.size(); ++j) {
				masterArray[i][j] = nullptr;
			}
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
		initializeArray();
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
	std::vector<Piece*> getWhiteVector() { return whitePieces; }
	std::vector<Piece*> getBlackVector() { return blackPieces; }
	const std::array<std::array<Piece*, 8>, 8> getMasterArray() const { return masterArray; }
};

class Queen : public Piece {
private:
	char graphics{ 'Q' };
public:
	Queen(const PieceManager& ref) : Piece{ ref } {}
	char getGraphics() const { return graphics; }
	bool isValid() override {
		if (isOnRow(pos, endPos)) {
			if (isMoveValidOnRow(pos, endPos, piece_ref.getMasterArray(), this)) {
				return true;
			}
			else {
				return false;
			}
		}
		if (isOnCol(pos, endPos)) {
			if (isMoveValidOnCol(pos, endPos, piece_ref.getMasterArray(), this)) {
				return true;
			}
			else {
				return false;
			}
		}
		if (isOnRightDiag(pos, endPos)) {
			if (isMoveValidOnRightDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
				return true;
			}
			else {
				return false;
			}
		}
		if (isOnLeftDiag(pos, endPos)) {
			if (isMoveValidOnLeftDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
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
public:
	enum Turn {
		white,
		black
	};
	Turn getTurn() { return turn; }
	void setTurn(Turn input) { turn = input; }
	void setSelectedPiece(Piece* piece) { selected_piece = piece; }
	Piece* getSelectedPiece() { return selected_piece; }
	void setSelectedMove(Pos pos) { selected_move = pos; }
	Pos getSelectedMove() { return selected_move; }
	void setState(bool input) { state = input; }
	bool getState() { return state; }
private:
	bool state{ true };
	Turn turn{ white };
	Piece* selected_piece{ nullptr };
	Pos selected_move{};
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
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == white) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
			}
			else {
				gamestate.setSelectedPiece(nullptr);
				gamestate.setState(false);
			}
			break;
		case black:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == black) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
			}
			else {
				gamestate.setSelectedPiece(nullptr);
				gamestate.setState(false);
			}
			break;
		}
	}
	void selectMove() {
		if (gamestate.getSelectedPiece()) {
			controller.select();
			gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
			if (gamestate.getSelectedPiece()->isValid()) {
				gamestate.getSelectedPiece()->move();
				gamestate.setSelectedMove(gamestate.getSelectedPiece()->getPos());
			}
			else {
				gamestate.setState(false);
			}
		}
		else {
			gamestate.setState(false);
		}

	}
	void nextTurn() {
		if (gamestate.getTurn() == white) {
			gamestate.setTurn(Gamestate::black);
		}
		else {
			gamestate.setTurn(Gamestate::white);
		}
	}
	void run() {

	}
};

