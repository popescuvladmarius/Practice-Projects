#include "RuleManager.h"
#include "PieceManager.h"
#include "Gamestate.h"

RuleManager::RuleManager(const PieceManager& piece, const Gamestate& state) : piece_ref{piece}, state_ref{state} {}
bool RuleManager::kingsideCastling() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.view_whiteKing().getPos().x == 7 && piece_ref.view_whiteKing().getPos().y == 4) {

		}
	}
}
bool RuleManager::queensideCastling() {

}
bool RuleManager::enpassant() {

}
