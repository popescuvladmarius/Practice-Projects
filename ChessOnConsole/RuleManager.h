#pragma once

class PieceManager;
class Gamestate;
class RuleManager {
private:
	const PieceManager& piece_ref;
	const Gamestate& state_ref;
	bool isKingSideCastlingPossible{ true };
	bool isQueenSideCastlingPossible{ true };
public:
	RuleManager(const PieceManager& piece, const Gamestate& state);
	bool kingSideCastlingAbsoluteCondition();
	
};