#include "RuleManager.h"
#include "PieceManager.h"
#include "Gamestate.h"

RuleManager::RuleManager(const PieceManager& piece, const Gamestate& state) : piece_ref{piece}, state_ref{state} {}
bool RuleManager::kingsideCastling() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.view_whiteKing().hasMoved() || piece_ref.view_whiteRook_right().hasMoved() ) {

		}
	}
}

