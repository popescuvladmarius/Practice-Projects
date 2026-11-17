#include "Gamestate.h"

void Gamestate::resetLoopStatus() {
	loopStatus = LoopStatus::initial;
}
LoopStatus Gamestate::getLoopStatus() {
	return loopStatus;
}
void Gamestate::setLoopStatus(LoopStatus status) {
	loopStatus = status;
}
Turn Gamestate::getTurn() const { return turn; }
void Gamestate::setTurn(Turn input) { turn = input; }
void Gamestate::nextTurn() {
	if (turn == Turn::white) {
		turn = Turn::black;
		resetLoopStatus();
	}
	else {
		turn = Turn::white;
		resetLoopStatus();
	}
}
void Gamestate::setSelectedPiece(Piece* piece) { selected_piece = piece; }
Piece* Gamestate::getSelectedPiece() { return selected_piece; }
void Gamestate::setState(bool input) { state = input; }
bool Gamestate::getState() const { return state; }
void Gamestate::setStatus(Status input) { status = input; }
Status Gamestate::getStatus() const { return status; }
void Gamestate::addMove(const Piece* const piece, MoveType move = MoveType::regular) { moveCollection.emplace_back(piece->getPos(), piece->getOldPos(), piece, piece->checkCapture(), move); }
const Move& Gamestate::readMove() { moveCollection.back(); }
const std::vector<Move>& Gamestate::getMoveCollection() { return moveCollection; }
