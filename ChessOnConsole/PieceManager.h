#pragma once
#include <vector>
#include <array>
#include "Team.h"

class Pos;
class Piece;
class PieceManager {
private:
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
	const std::array<std::array<Piece*, 8>, 8>& getMasterArray() const;
	void updateArray(const Move& move);
};
