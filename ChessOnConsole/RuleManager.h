#pragma once

class PieceManager;
class Gamestate;
class RuleManager {
private:
	const PieceManager& piece_ref;
	const Gamestate& state_ref;
public:
	RuleManager(const PieceManager& piece, const Gamestate& state);
	bool kingsideCastling();
	bool queensideCastling();
	bool enpassant();
};