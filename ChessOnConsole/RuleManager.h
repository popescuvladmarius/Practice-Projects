#pragma once

class PieceManager;
class RuleManager {
private:
	const PieceManager& piece_ref;
public:
	RuleManager(const PieceManager& ref) : piece_ref{ref} {}
	bool kingsideCastling() {
		if (piece_ref.getMasterArray())
	}
	bool queensideCastling() {

	}
	bool enpassant() {

	}

};