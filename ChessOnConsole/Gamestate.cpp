#include "Gamestate.h"

Turn Gamestate::getTurn() { return turn; }
void Gamestate::setTurn(Turn input) { turn = input; }
void Gamestate::setSelectedPiece(Piece* piece) { selected_piece = piece; }
Piece* Gamestate::getSelectedPiece() { return selected_piece; }
void Gamestate::setState(bool input) { state = input; }
bool Gamestate::getState() { return state; }
void Gamestate::setStatus(Status input) { status = input; }
Status Gamestate::getStatus() { return status; }
void Gamestate::addMove(Pos move, char graphics) {
	moveCollection.emplace_back(move, graphics);
}