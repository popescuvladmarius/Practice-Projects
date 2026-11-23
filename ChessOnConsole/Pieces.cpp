#include "Pieces.h"
#include "PieceManager.h"

Piece::Piece(const PieceManager& ref, ActionType action) : piece_ref{ ref }, actionType{ action } {}
Pos Piece::getPos() const { return pos; }
Pos Piece::getOldPos() const { return oldPos; }
void Piece::setPos(int x, int y) { pos.x = x; pos.y = y; }
void Piece::setEndPos(Pos pos) { endPos = pos; }
void Piece::setFlag(Flag input) { flag = input; }
Flag Piece::getFlag() const { return flag; }
void Piece::move() {
	oldPos = pos;
	pos = endPos;
	if (!moved) {
		hasMovedOnce();
		switch (flag) {
		case Flag::white:
			if (oldPos == piece_ref.getPieceMap().at("WhiteLeftRook")) {
				piece_ref.notify_whiteLeftRookMoved();
			}
			if (oldPos == piece_ref.getPieceMap().at("WhiteRightRook")) {
				piece_ref.notify_whiteRightRookMoved();
			}
			if (oldPos == piece_ref.getPieceMap().at("WhiteKing")) {
				piece_ref.notify_whiteKingMoved();
			}
		break;
		case Flag::black:
			if (oldPos == piece_ref.getPieceMap().at("BlackLeftRook")) {
				piece_ref.notify_blackLeftRookMoved();
			}
			if (oldPos == piece_ref.getPieceMap().at("BlackRightRook")) {
				piece_ref.notify_blackRightRookMoved();
			}
			if (oldPos == piece_ref.getPieceMap().at("BlackKing")) {
				piece_ref.notify_blackKingMoved();
			}
			break;
		}
	}
}
int Piece::dir() {
	if (this->getFlag() == Flag::white) {
		return -1;
	}
	else {
		return 1;
	}
}
void Piece::setGraphics(char value) { graphics = value; }
char Piece::getGraphics() const { return graphics; }
void Piece::didCapture() { capture = true; }
bool Piece::checkCapture() const { return capture; }
void Piece::resetCapture() { capture = false; }
void Piece::hasMovedOnce() { moved = true; }
ActionType Piece::getActionType() const {
	return actionType;
}
void Piece::undoMove() {
	pos = oldPos;
	resetCapture();
}

Pawn::Pawn(const PieceManager& ref) : Piece(ref, ActionType::point) {}
inline Pos Pawn::forward() {
	Pos temp{ pos };
	temp.x += dir();
	return temp;
}
inline Pos Pawn::forwardDouble() {
	Pos temp{ pos };
	temp.x += 2 * dir();
	return temp;
}
inline Pos Pawn::captureRight() {
	Pos temp{ pos };
	temp.x += dir();
	++temp.y;
	return temp;
}
inline Pos Pawn::captureLeft() {
	Pos temp{ pos };
	temp.x += dir();
	--temp.y;
	return temp;
}
void Pawn::promotion() {

}
std::vector<Pos> Pawn::getBaseMovesIteration(Pos checkingPiecePos) {
	std::vector<Pos> basicMoves;
	if (!piece_ref.getMasterArray()[forward().x][forward().y]) {
		basicMoves.push_back(forward());
	}
	if (!moved && !(piece_ref.getMasterArray()[forwardDouble().x][forwardDouble().y] || piece_ref.getMasterArray()[forwardDouble().x - dir()][forwardDouble().y])) {
		basicMoves.push_back(forwardDouble());
	}
	if (piece_ref.getMasterArray()[captureLeft().x][captureLeft().y] && piece_ref.getMasterArray()[captureLeft().x][captureLeft().y]->getFlag() != flag) {
		basicMoves.push_back(captureLeft());
	}
	if (piece_ref.getMasterArray()[captureRight().x][captureRight().y] && piece_ref.getMasterArray()[captureRight().x][captureRight().y]->getFlag() != flag) {
		basicMoves.push_back(captureRight());
	}
}
bool Pawn::isValid() {
	if (forward() == endPos) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			return false;
		}
		else {
			return true;
		}
	}
	if (forwardDouble() == endPos) {
		if (!moved) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y] || piece_ref.getMasterArray()[endPos.x - dir()][endPos.y]) {
				return false;
			}
			else {
				return true;
			}
		}
		return false;
	}
	if (captureRight() == endPos) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
			didCapture();
				return true;
		}
		else {
			return false;
		}
	}
	if (captureLeft() == endPos) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
			didCapture();
				return true;
			}
			else {
				return false;
			}
		}
	return false;
}
bool Pawn::checkScanner() {
	switch (flag) {
	case Flag::white:
		if (captureRight() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (captureLeft() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		if (captureRight() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (captureLeft() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		return false;
		break;
	}
}

Knight::Knight(const PieceManager& ref) : Piece(ref, ActionType::point) {}
inline Pos Knight::getUpRightJump() {
	Pos temp{ pos };
	temp.x += 2 * dir();
	++temp.y;
	return temp;
}
inline Pos Knight::getUpLeftJump() {
	Pos temp{ pos };
	temp.x += 2 * dir();
	--temp.y;
	return temp;
}
inline Pos Knight::getDownRightJump() {
	Pos temp{ pos };
	temp.x -= 2 * dir();
	++temp.y;
	return temp;
}
inline Pos Knight::getDownLeftJump() {
	Pos temp{ pos };
	temp.x -= 2 * dir();
	--temp.y;
	return temp;
}
inline Pos Knight::getRightUpJump() {
	Pos temp{ pos };
	temp.x += dir();
	temp.y += 2;
	return temp;
}
inline Pos Knight::getRightDownJump() {
	Pos temp{ pos };
	temp.x -= dir();
	temp.y += 2;
	return temp;
}
inline Pos Knight::getLeftUpJump() {
	Pos temp{ pos };
	temp.x += dir();
	temp.y -= 2;
	return temp;
}
inline Pos Knight::getLeftDownJump() {
	Pos temp{ pos };
	temp.x -= dir();
	temp.y -= 2;
	return temp;
}
std::vector<Pos> Knight::getBaseMovesIteration(Pos checkingPiecePos) {
	std::vector<Pos> basicMoves;
	if (piece_ref.getMasterArray()[getUpRightJump().x][getUpRightJump().y]) {
		if (piece_ref.getMasterArray()[getUpRightJump().x][getUpRightJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getUpRightJump());
		}
	}
	else {
		basicMoves.push_back(getUpRightJump());
	}
	if (piece_ref.getMasterArray()[getUpLeftJump().x][getUpLeftJump().y]) {
		if (piece_ref.getMasterArray()[getUpLeftJump().x][getUpLeftJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getUpLeftJump());
		}
	}
	else {
		basicMoves.push_back(getUpLeftJump());
	}
	if (piece_ref.getMasterArray()[getDownRightJump().x][getDownRightJump().y]) {
		if (piece_ref.getMasterArray()[getDownRightJump().x][getDownRightJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getDownRightJump());
		}
	}
	else {
		basicMoves.push_back(getDownRightJump());
	}
	if (piece_ref.getMasterArray()[getDownLeftJump().x][getDownLeftJump().y]) {
		if (piece_ref.getMasterArray()[getDownLeftJump().x][getDownLeftJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getDownLeftJump());
		}
	}
	else {
		basicMoves.push_back(getDownLeftJump());
	}
	if (piece_ref.getMasterArray()[getRightUpJump().x][getRightUpJump().y]) {
		if (piece_ref.getMasterArray()[getRightUpJump().x][getRightUpJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getRightUpJump());
		}
	}
	else {
		basicMoves.push_back(getRightUpJump());
	}
	if (piece_ref.getMasterArray()[getRightDownJump().x][getRightDownJump().y]) {
		if (piece_ref.getMasterArray()[getRightDownJump().x][getRightDownJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getRightDownJump());
		}
	}
	else {
		basicMoves.push_back(getRightDownJump());
	}
	if (piece_ref.getMasterArray()[getLeftUpJump().x][getLeftUpJump().y]) {
		if (piece_ref.getMasterArray()[getLeftUpJump().x][getLeftUpJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getLeftUpJump());
		}
	}
	else {
		basicMoves.push_back(getLeftUpJump());
	}
	if (piece_ref.getMasterArray()[getLeftDownJump().x][getLeftDownJump().y]) {
		if (piece_ref.getMasterArray()[getLeftDownJump().x][getLeftDownJump().y]->getFlag() != this->getFlag()) {
			basicMoves.push_back(getLeftDownJump());
		}
	}
	else {
		basicMoves.push_back(getLeftDownJump());
	}
	return basicMoves;
}
bool Knight::isValid() {
	if (endPos == getUpRightJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getUpLeftJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getDownRightJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getDownLeftJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getRightUpJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getRightDownJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getLeftUpJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == getLeftDownJump()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	return false;
}
bool Knight::checkScanner() {
	switch (flag) {
	case Flag::white:
		if (getUpRightJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getUpLeftJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getDownRightJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getDownLeftJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getRightUpJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getRightDownJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getLeftUpJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (getLeftDownJump() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		if (getUpRightJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getUpLeftJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getDownRightJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getDownLeftJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getRightUpJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getRightDownJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getLeftUpJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (getLeftDownJump() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		return false;
		break;
	}
}

Rook::Rook(const PieceManager& ref) : Piece(ref, ActionType::diffusal) {}
std::vector<Pos> Rook::getBaseMovesIteration(Pos checkingPiecePos) {
	if (isOnRow(pos, checkingPiecePos)) {
		if (isMoveValidOnRow(pos, checkingPiecePos, piece_ref.getMasterArray(), this)) {

		}
	}
}
bool Rook::isValid() {
	if (isOnRow(pos, endPos)) {
		if (isMoveValidOnRow(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	if (isOnCol(pos, endPos)) {
		if (isMoveValidOnCol(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool Rook::checkScanner() {
	switch (flag) {
	case Flag::white:
		if (checkScanRow(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) || checkScanCol(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (checkScanRow(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) || checkScanCol(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

Bishop::Bishop(const PieceManager& ref) : Piece(ref, ActionType::diffusal) {}
bool Bishop::isValid() {
	if (isOnLeftDiag(pos, endPos)) {
		if (isMoveValidOnLeftDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	if (isOnRightDiag(pos, endPos)) {
		if (isMoveValidOnRightDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool Bishop::checkScanner() {
	switch (flag) {
	case Flag::white:
		if (checkScanLeftDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) || checkScanRightDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (checkScanLeftDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) || checkScanRightDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}

King::King(const PieceManager& ref) : Piece(ref, ActionType::point) {}
inline Pos King::forward() {
	Pos temp{ pos };
	temp.x += dir();
	return temp;
}
inline Pos King::backwards() {
	Pos temp{ pos };
	temp.x -= dir();
	return temp;
}
inline Pos King::right() {
	Pos temp{ pos };
	++temp.y;
	return temp;
}
inline Pos King::left() {
	Pos temp{ pos };
	--temp.y;
	return temp;
}
inline Pos King::up_right() {
	Pos temp{ pos };
	temp.x += dir();
	++temp.y;
	return temp;
}
inline Pos King::up_left() {
	Pos temp{ pos };
	temp.x += dir();
	--temp.y;
	return temp;
}
inline Pos King::down_right() {
	Pos temp{ pos };
	temp.x -= dir();
	++temp.y;
	return temp;
}
inline Pos King::down_left() {
	Pos temp{ pos };
	temp.x -= dir();
	--temp.y;
	return temp;
}
inline Pos King::kingsideCastling() {
	Pos temp{ pos };
	temp.y += 2;
	return temp;
}
inline Pos King::queensideCastling() {
	Pos temp{ pos };
	temp.y -= 2;
	return temp;
}
inline Pos King::kingsideStepping() {
	pos.y += 1;
}
inline Pos King::queensideStepping() {
	pos.y -= 1;
}
void King::resetCastlingMove() {
	castlingMoveSelected = CastlingMove::other;
}
CastlingMove King::getCastlingMove() {
	return castlingMoveSelected;
}
void King::setCheck() { check = true; }
void King::resetCheck() { check = false; }
bool King::getCheckState() const { return check; }
std::vector<Pos> King::getBaseMovesIteration(Pos checkingPiecePos) {
	std::vector<Pos> basicMoves;
	if (piece_ref.getMasterArray()[forward().x][forward().y]) {
		if (piece_ref.getMasterArray()[forward().x][forward().y]->getFlag() != flag) {
			basicMoves.push_back(forward());
		}
	}
	else {
		basicMoves.push_back(forward());
	}
	if (piece_ref.getMasterArray()[backwards().x][backwards().y]) {
		if (piece_ref.getMasterArray()[backwards().x][backwards().y]->getFlag() != flag) {
			basicMoves.push_back(backwards());
		}
	}
	else {
		basicMoves.push_back(backwards());
	}
	if (piece_ref.getMasterArray()[right().x][right().y]) {
		if (piece_ref.getMasterArray()[right().x][right().y]->getFlag() != flag) {
			basicMoves.push_back(right());
		}
	}
	else {
		basicMoves.push_back(right());
	}
	if (piece_ref.getMasterArray()[left().x][left().y]) {
		if (piece_ref.getMasterArray()[left().x][left().y]->getFlag() != flag) {
			basicMoves.push_back(left());
		}
	}
	else {
		basicMoves.push_back(left());
	}
	if (piece_ref.getMasterArray()[up_right().x][up_right().y]) {
		if (piece_ref.getMasterArray()[up_right().x][up_right().y]->getFlag() != flag) {
			basicMoves.push_back(up_right());
		}
	}
	else {
		basicMoves.push_back(up_right());
	}
	if (piece_ref.getMasterArray()[up_left().x][up_left().y]) {
		if (piece_ref.getMasterArray()[up_left().x][up_left().y]->getFlag() != flag) {
			basicMoves.push_back(up_left());
		}
	}
	else {
		basicMoves.push_back(up_left());
	}
	if (piece_ref.getMasterArray()[down_right().x][down_right().y]) {
		if (piece_ref.getMasterArray()[down_right().x][down_right().y]->getFlag() != flag) {
			basicMoves.push_back(down_right());
		}
	}
	else {
		basicMoves.push_back(down_right());
	}
	if (piece_ref.getMasterArray()[down_left().x][down_left().y]) {
		if (piece_ref.getMasterArray()[down_left().x][down_left().y]->getFlag() != flag) {
			basicMoves.push_back(down_left());
		}
	}
	else {
		basicMoves.push_back(down_left());
	}
	return basicMoves;
}
bool King::isValid() {
	if (endPos == forward()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
			else {
				return true;
			}
	}
	if (endPos == backwards()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
			else {
				return true;
			}
	}
	if (endPos == right()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == left()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == up_right()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == up_left()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == down_right()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == down_left()) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != flag) {
				didCapture();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return true;
		}
	}
	if (endPos == kingsideCastling()) {                  
		if (piece_ref.queryKingsideCastling()) {
			castlingMoveSelected = CastlingMove::kingsideCastling;
			return true;
		}
		else {
			return false;
		}
	}
	if (endPos == queensideCastling()) {
		if (piece_ref.queryQueensideCastling()) {
			castlingMoveSelected = CastlingMove::queensideCastling;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool King::checkScanner() {  
	switch (flag) {
	case Flag::white:
		if (forward() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (backwards() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (right() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (left() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (up_right() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (up_left() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (down_right() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		if (down_left() == piece_ref.view_blackKing().getPos()) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		if (forward() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (backwards() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (right() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (left() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (up_right() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (up_left() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (down_right() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		if (down_left() == piece_ref.view_whiteKing().getPos()) {
			return true;
		}
		return false;
		break;
	}
}

Queen::Queen(const PieceManager& ref) : Piece(ref, ActionType::diffusal) {}
bool Queen::isValid() {
	if (isOnRow(pos, endPos)) {
		if (isMoveValidOnRow(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	if (isOnCol(pos, endPos)) {
		if (isMoveValidOnCol(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	if (isOnRightDiag(pos, endPos)) {
		if (isMoveValidOnRightDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	if (isOnLeftDiag(pos, endPos)) {
		if (isMoveValidOnLeftDiag(pos, endPos, piece_ref.getMasterArray(), this)) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y]) {
				didCapture();
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool Queen::checkScanner() {
	switch (flag) {
	case Flag::white:
		if (checkScanRow(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanCol(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanLeftDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanRightDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (checkScanRow(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanCol(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanLeftDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			checkScanRightDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}