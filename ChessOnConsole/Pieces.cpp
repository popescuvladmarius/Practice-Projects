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
bool Pawn::kingsideScanner() {
	switch (flag) {
	case Flag::white:
		std::array<Pos, 2> blackSquares{ {
		{0, 5},
		{0, 6}
} };
		if (captureRight() == blackSquares[0] || captureRight() == blackSquares[1]) {
			return true;
		}
		if (captureLeft() == blackSquares[0] || captureLeft() == blackSquares[1]) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		std::array<Pos, 2> whiteSquares{ {
		{7, 5},
		{7, 6}
} };
		if (captureRight() == whiteSquares[0] || captureRight() == whiteSquares[1]) {
			return true;
		}
		if (captureLeft() == whiteSquares[0] || captureLeft() == whiteSquares[1]) {
			return true;
		}
		return false;
		break;
	}
}
bool Pawn::queensideScanner() {
	switch (flag) {
	case Flag::white:
		std::array<Pos, 2> blackSquares{ {
			{0, 2},
			{0, 3}
} };

		break;
	case Flag::black:
		std::array<Pos, 2> whitequares{ {
			{7, 2},
			{7, 3}
} };

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
bool Knight::kingsideScanner() {
	switch (flag) {
	case Flag::white:
		std::array<Pos, 2> blackSquares{ {
		{0, 5},
		{0, 6}
} };
		if (getUpRightJump() == blackSquares[0] || getUpRightJump() == blackSquares[1]) {
			return true;
		}
		if (getUpLeftJump() == blackSquares[0] || getUpLeftJump() == blackSquares[1]) {
			return true;
		}
		if (getDownRightJump() == blackSquares[0] || getDownRightJump() == blackSquares[1]) {
			return true;
		}
		if (getDownLeftJump() == blackSquares[0] || getDownLeftJump() == blackSquares[1]) {
			return true;
		}
		if (getRightUpJump() == blackSquares[0] || getRightUpJump() == blackSquares[1]) {
			return true;
		}
		if (getRightDownJump() == blackSquares[0] || getRightDownJump() == blackSquares[1]) {
			return true;
		}
		if (getLeftUpJump() == blackSquares[0] || getLeftUpJump() == blackSquares[1]) {
			return true;
		}
		if (getLeftDownJump() == blackSquares[0] || getLeftDownJump() == blackSquares[1]) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		std::array<Pos, 2> whiteSquares{ {
		{7, 5},
		{7, 6}
	} };
		if (getUpRightJump() == whiteSquares[0] || getUpRightJump() == whiteSquares[1]) {
			return true;
		}
		if (getUpLeftJump() == whiteSquares[0] || getUpLeftJump() == whiteSquares[1]) {
			return true;
		}
		if (getDownRightJump() == whiteSquares[0] || getDownRightJump() == whiteSquares[1]) {
			return true;
		}
		if (getDownLeftJump() == whiteSquares[0] || getDownLeftJump() == whiteSquares[1]) {
			return true;
		}
		if (getRightUpJump() == whiteSquares[0] || getRightUpJump() == whiteSquares[1]) {
			return true;
		}
		if (getRightDownJump() == whiteSquares[0] || getRightDownJump() == whiteSquares[1]) {
			return true;
		}
		if (getLeftUpJump() == whiteSquares[0] || getLeftUpJump() == whiteSquares[1]) {
			return true;
		}
		if (getLeftDownJump() == whiteSquares[0] || getLeftDownJump() == whiteSquares[1]) {
			return true;
		}
		return false;
		break;
	}
}
bool Knight::queensideScanner() {
	switch (flag) {
	case Flag::white:
		std::array<Pos, 2> blackSquares{ {
			{0, 2},
			{0, 3}
} };
		if (getUpRightJump() == blackSquares[0] || getUpRightJump() == blackSquares[1]) {
			return true;
		}
		if (getUpLeftJump() == blackSquares[0] || getUpLeftJump() == blackSquares[1]) {
			return true;
		}
		if (getDownRightJump() == blackSquares[0] || getDownRightJump() == blackSquares[1]) {
			return true;
		}
		if (getDownLeftJump() == blackSquares[0] || getDownLeftJump() == blackSquares[1]) {
			return true;
		}
		if (getRightUpJump() == blackSquares[0] || getRightUpJump() == blackSquares[1]) {
			return true;
		}
		if (getRightDownJump() == blackSquares[0] || getRightDownJump() == blackSquares[1]) {
			return true;
		}
		if (getLeftUpJump() == blackSquares[0] || getLeftUpJump() == blackSquares[1]) {
			return true;
		}
		if (getLeftDownJump() == blackSquares[0] || getLeftDownJump() == blackSquares[1]) {
			return true;
		}
		return false;
		break;
	case Flag::black:
		std::array<Pos, 2> whiteSquares{ {
			{7, 2},
			{7, 3}
} };
		if (getUpRightJump() == whiteSquares[0] || getUpRightJump() == whiteSquares[1]) {
			return true;
		}
		if (getUpLeftJump() == whiteSquares[0] || getUpLeftJump() == whiteSquares[1]) {
			return true;
		}
		if (getDownRightJump() == whiteSquares[0] || getDownRightJump() == whiteSquares[1]) {
			return true;
		}
		if (getDownLeftJump() == whiteSquares[0] || getDownLeftJump() == whiteSquares[1]) {
			return true;
		}
		if (getRightUpJump() == whiteSquares[0] || getRightUpJump() == whiteSquares[1]) {
			return true;
		}
		if (getRightDownJump() == whiteSquares[0] || getRightDownJump() == whiteSquares[1]) {
			return true;
		}
		if (getLeftUpJump() == whiteSquares[0] || getLeftUpJump() == whiteSquares[1]) {
			return true;
		}
		if (getLeftDownJump() == whiteSquares[0] || getLeftDownJump() == whiteSquares[1]) {
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
		if (scanRow(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) || scanCol(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (scanRow(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) || scanCol(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
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
		if (scanLeftDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) || scanRightDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (scanLeftDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) || scanRightDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
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
		if (scanRow(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanCol(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanLeftDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanRightDiag(pos, piece_ref.view_blackKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Flag::black:
		if (scanRow(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanCol(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanLeftDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag) ||
			scanRightDiag(pos, piece_ref.view_whiteKing().getPos(), piece_ref.getMasterArray(), flag)) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}