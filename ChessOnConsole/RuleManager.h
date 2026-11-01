#pragma once
#include <vector>

class PieceManager;
class Gamestate;

class RuleManager {
private:
	const PieceManager& piece_ref;
	const Gamestate& state_ref;
	bool check{ false };
	bool isWhiteKingsideCastlingPossible{ true };
	bool isWhiteQueensideCastlingPossible{ true };
	bool isBlackKingsideCastlingPossible{ true };
	bool isBlackQueensideCastlingPossible{ true };
	std::vector<Piece*> checkingPieces;
public:
	RuleManager(const PieceManager& piece, const Gamestate& state);
	void whiteKingMoved();
	void whiteLeftRookMoved();
	void whiteRightRookMoved();
	void blackKingMoved();
	void blackLeftRookMoved();
	void blackRightRookMoved();
	bool kingsideAreEmpty();
	bool queensideAreEmpty();
	bool kingsideCastlingIsValid();
	bool queensideCastingIsValid();
	void checkSignaled(Piece* piece);
};
