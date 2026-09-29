#pragma once
#include <array>
#include "King.h"


class King;
class Queen;
class Rook;
class Bishop;
class Knight;
class Pawn;
class PieceManager;
class Team{
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