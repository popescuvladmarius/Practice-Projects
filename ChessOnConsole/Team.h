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
	const King& getKing() const;
	Queen& getQueen();
	const Queen& getQueen() const;
	Rook& getRook(int i);
	const Rook& getRook(int i) const;
	Bishop& getBishop(int i);
	const Bishop& getBishop(int i) const;
	Knight& getKnight(int i);
	const Knight& getKnight(int i) const;
	Pawn& getPawn(int i);
	const Pawn& getPawn(int i) const;
};