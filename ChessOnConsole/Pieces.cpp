#include "Pieces.h"
#include "PieceManager.h"

Piece::Piece(const PieceManager& ref) : piece_ref{ ref } {}
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
void Piece::undoMove() {
	pos = oldPos;
	resetCapture();
}

Pawn::Pawn(const PieceManager& ref) : Piece{ ref } {}
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
		if (flag == Flag::white && pos.x == 6) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x + 1][endPos.y]) {
				return false;
			}
			else {
				return true;
			}
		}
		if (flag == Flag::black && pos.x == 1) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x - 1][endPos.y]) {
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

Knight::Knight(const PieceManager& ref) : Piece{ ref } {}
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

Rook::Rook(const PieceManager& ref) : Piece{ ref } {}
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

Bishop::Bishop(const PieceManager& ref) : Piece{ ref } {}
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

King::King(const PieceManager& ref) : Piece{ ref } {}
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
void King::kingsideCastlingSelected() {
	castlingMoveSelected = CastlingMove::kingsideCastling;
}
void King::queensideCastlingSelected() {
	castlingMoveSelected = CastlingMove::queensideCastling;
}
CastlingMove King::getCastlingMove() {
	return castlingMoveSelected;
}
void King::setCheck() { check = true; }
void King::resetCheck() { check = false; }
bool King::getCheckState() { return check; }
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
	if (endPos == kingsideCastling()) {                  //must be revised accoridng to the updated isValid logic
		if (piece_ref.queryKingsideCastling()) {
			kingsideCastlingSelected();
			return true;
		}
		else {
			return false;
		}
	}
	if (endPos == queensideCastling()) {
		if (piece_ref.queryQueensideCastling()) {
			queensideCastlingSelected();
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

Queen::Queen(const PieceManager& ref) : Piece{ ref } {}
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