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
Queen& Team::getQueen() { return queen; }
Rook& Team::getRook(int i) { return rooks[i]; }
Bishop& Team::getBishop(int i) { return bishops[i]; }
Knight& Team::getKnight(int i) { return knights[i]; }
Pawn& Team::getPawn(int i) { return pawns[i]; }
