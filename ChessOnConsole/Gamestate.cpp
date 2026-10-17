#include "Gamestate.h"

Turn Gamestate::getTurn() const { return turn; }
void Gamestate::setTurn(Turn input) { turn = input; }
void Gamestate::setSelectedPiece(Piece* piece) { selected_piece = piece; }
Piece* Gamestate::getSelectedPiece() { return selected_piece; }
void Gamestate::setState(bool input) { state = input; }
bool Gamestate::getState() const { return state; }
void Gamestate::setStatus(Status input) { status = input; }
Status Gamestate::getStatus() const { return status; }
void Gamestate::addMove(const Piece* const piece) { moveCollection.emplace_back(piece->getPos(), piece->getOldPos(), piece, piece->checkCapture()); }
const Move& Gamestate::readMove() { moveCollection.back(); }
const std::vector<Move>& Gamestate::getMoveCollection() { return moveCollection; }
