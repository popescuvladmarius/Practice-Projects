#include "Gamestate.h"

Turn Gamestate::getTurn() { return turn; }
void Gamestate::setTurn(Turn input) { turn = input; }
void Gamestate::setSelectedPiece(Piece* piece) { selected_piece = piece; }
Piece* Gamestate::getSelectedPiece() { return selected_piece; }
void Gamestate::setSelectedMove(Pos pos) { selected_move = pos; }
Pos Gamestate::getSelectedMove() { return selected_move; }
void Gamestate::setState(bool input) { state = input; }
bool Gamestate::getState() { return state; }