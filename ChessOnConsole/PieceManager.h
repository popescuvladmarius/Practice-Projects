#pragma once
#include <vector>
#include <array>
#include "Team.h"

class Pos;
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
	std::vector<Piece*> getWhiteVector();
	std::vector<Piece*> getBlackVector();
	const std::array<std::array<Piece*, 8>, 8> getMasterArray() const;
};