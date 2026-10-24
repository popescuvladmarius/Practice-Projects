#include "Team.h"

Team::Team(const PieceManager& ref) :
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
King& Team::getKing() { return king; }
const King& Team::getKing() const { return king; }
Queen& Team::getQueen() { return queen; }
const Queen& Team::getQueen() const { return queen; }
Rook& Team::getRook(int i) { return rooks[i]; }
const Rook& Team::getRook(int i) const { return rooks[i]; }
Bishop& Team::getBishop(int i) { return bishops[i]; }
const Bishop& Team::getBishop(int i) const { return bishops[i]; }
Knight& Team::getKnight(int i) { return knights[i]; }
const Knight& Team::getKnight(int i) const { return knights[i]; }
Pawn& Team::getPawn(int i) { return pawns[i]; }
const Pawn& Team::getPawn(int i) const { return pawns[i]; }
