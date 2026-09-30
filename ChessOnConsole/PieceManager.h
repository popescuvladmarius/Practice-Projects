#pragma once
#include <vector>
#include <array>
#include "Team.h"

class Pos;
class Team;
class Piece;
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
	void reserve();
	void initializeWhites();
	void initializeBlacks();
	void initializeArray();
public:
	PieceManager();
	Pos getWhiteKingPos();
	char getWhiteKingGraphics();
	Pos getWhiteQueenPos();
	char getWhiteQueenGraphics();
	Pos getWhiteRookPos(int i);
	char getWhiteRookGraphics();
	Pos getWhiteBishopPos(int i);
	char getWhiteBishopGraphics();
	Pos getWhiteKnightPos(int i);
	char getWhiteKnightGraphics();
	Pos getWhitePawnPos(int i);
	char getWhitePawnGraphics();
	Pos getBlackKingPos();
	char getBlackKingGraphics();
	Pos getBlackQueenPos();
	char getBlackQueenGraphics();
	Pos getBlackRookPos(int i);
	char getBlackRookGraphics();
	Pos getBlackBishopPos(int i);
	char getBlackBishopGraphics();
	Pos getBlackKnightPos(int i);
	char getBlackKnightGraphics();
	Pos getBlackPawnPos(int i);
	char getBlackPawnGraphics();
	std::vector<Piece*> getWhiteVector();
	std::vector<Piece*> getBlackVector();
	const std::array<std::array<Piece*, 8>, 8> getMasterArray() const;
};