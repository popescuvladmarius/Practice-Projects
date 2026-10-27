#pragma once

class PieceManager;
class Gamestate;

class RuleManager {
private:
const PieceManager& piece_ref;
const Gamestate& state_ref;
bool check{ false };
bool isWhiteKingsideCastlingPossible{ true };
bool isBlackKingsideCastlingPossible{ true };
bool isWhiteQueensideCastlingPossible{ true };
bool isBlackQueensideCastlingPossible{ true };
public:
	RuleManager(const PieceManager& piece, const Gamestate& state);
	void kingsideAbsoluteCondition();
	void queensideAbosuluteCondition();
};