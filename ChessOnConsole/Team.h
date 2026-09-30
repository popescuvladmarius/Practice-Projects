#pragma once
#include "Pieces.h"

class Team{
private:
	King king;
	Queen queen;
	std::array<Rook, 2> rooks;
	std::array<Bishop, 2> bishops;
	std::array<Knight, 2> knights;
	std::array<Pawn, 8> pawns;
public:
	Team(const PieceManager& ref);
	King& getKing();
	Queen& getQueen();
	Rook& getRook(int i);
	Bishop& getBishop(int i);
	Knight& getKnight(int i);
	Pawn& getPawn(int i);
};