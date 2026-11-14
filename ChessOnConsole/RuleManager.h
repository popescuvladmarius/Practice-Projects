#pragma once
#include <vector>

class PieceManager;
class Gamestate;
class Piece;
enum class CheckStatus;

class RuleManager {
private:
	const PieceManager& piece_ref;
	const Gamestate& state_ref;
	CheckStatus checkStatus{ CheckStatus::noneChecked };
	bool whiteCheck{ false };
	bool blackCheck{ false };
	bool checkmate{ false };
	bool isWhiteKingsideCastlingPossible{ true };
	bool isWhiteQueensideCastlingPossible{ true };
	bool isBlackKingsideCastlingPossible{ true };
	bool isBlackQueensideCastlingPossible{ true };
	std::vector<Piece*> whiteCheckingPieces;
	std::vector<Piece*> blackCheckingPieces;
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
	void addToWhiteCheckingPieceArray(Piece* piece);
	void addToBlackCheckingPieceArray(Piece* piece);
	bool whiteCheckState();
	bool blackCheckState();
	CheckStatus getCheckStatus();
};