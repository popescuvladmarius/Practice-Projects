#pragma once
#include <vector>
#include <array>
#include "Team.h"

class Pos;
class Piece;
class PieceManager {
private:
	std::unordered_map<std::string, Pos> pieceInitialPositions{
	{"WhiteKing", {7, 4} },
	{"WhiteQueen", {7, 3}},
	{"WhiteLeftRook", {7, 0}},
	{"WhiteRightRook", {7, 7}},
	{"WhiteLeftBishop", {7, 2}},
	{"WhiteRightBishop", {7, 5}},
	{"WhiteLeftKnight", {7, 1}},
	{"WhiteRightKnight", {7, 6}},
	{"BlackKing", {0, 4}},
	{"BlackQueen", {0, 3}},
	{"BlackLeftRook", {0, 0}},
	{"BlackRightRook", {0, 7}},
	{"BlackLeftBishop", {0, 2}},
	{"BlackRightBishop", {0, 5}},
	{"BlackLeftKnight", {0, 1}},
	{"BlackRightKnight", {0, 6}}
	};
	std::unordered_map<std::string, int> pawnInitialPositions{
		{"WhitePawns", 6},
		{"BlackPawns", 1}
	};
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
	const King& view_whiteKing() const;
	const King& view_blackKing() const;
	const Queen& view_whiteQueen() const;
	const Queen& view_blackQueen() const;
	const Rook& view_whiteRook_left() const;
	const Rook& view_whiteRook_right() const;
	const Rook& view_blackRook_left() const;
	const Rook& view_blackRook_right() const;
	const std::unordered_map<std::string, Pos>& getPieceMap() { return pieceInitialPositions; }
	const std::unordered_map<std::string, int>& getPawnMap() { return pawnInitialPositions; }
	const std::array<std::array<Piece*, 8>, 8>& getMasterArray() const;
	void updateArray(const Move& move);
};
