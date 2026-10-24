#include "RuleManager.h"
#include "PieceManager.h"
#include "Gamestate.h"

RuleManager::RuleManager(const PieceManager& piece, const Gamestate& state) : piece_ref{piece}, state_ref{state} {}
void RuleManager::kingsideAbsoluteCondition() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.view_whiteKing().hasMovedOnce() || piece_ref.view_whiteRook_right().hasMovedOnce()) {
			isWhiteKingsideCastlingPossible = false;
		}
		break;
	case Turn::black:
		if (piece_ref.view_blackKing().hasMovedOnce() || piece_ref.view_blackRook_right().hasMovedOnce()) {
			isBlackKingsideCastlingPossible = false;
		}
		break;
	}
}
void RuleManager::queensideAbosuluteCondition() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.view_whiteQueen().hasMovedOnce() || piece_ref.view_whiteRook_left().hasMovedOnce()) {
			isWhiteQueensideCastlingPossible = false;
		}
		break;
	case Turn::black:
		if (piece_ref.view_blackQueen().hasMovedOnce() || piece_ref.view_blackRook_left().hasMovedOnce()) {
			isBlackQueensideCastlingPossible = false;
		}
		break;
	}
}

