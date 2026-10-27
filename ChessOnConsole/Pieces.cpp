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
		moved = true;
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
bool Piece::hasMovedOnce() const { return moved; }

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
		if (this->getFlag() == Flag::white && this->getPos().x == 6) {
			if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x + 1][endPos.y]) {
				return false;
			}
			else {
				return true;
			}
		}
		if (this->getFlag() == Flag::black && this->getPos().x == 1) {
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
		if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
			didCapture();
				return true;
		}
		else {
			return false;
		}
	}
	if (captureLeft() == endPos) {
		if (piece_ref.getMasterArray()[endPos.x][endPos.y] && piece_ref.getMasterArray()[endPos.x][endPos.y]->getFlag() != this->getFlag()) {
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
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[captureRight().x][captureRight().y]) && piece_ref.getMasterArray()[captureRight().x][captureRight().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[captureLeft().x][captureLeft().y]) && piece_ref.getMasterArray()[captureLeft().x][captureLeft().y]->getFlag() != this->getFlag()) {
		return true;
	}
	return false;
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
bool Knight::checkScanner(){
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getUpRightJump().x][getUpRightJump().y]) && piece_ref.getMasterArray()[getUpRightJump().x][getUpRightJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getUpLeftJump().x][getUpLeftJump().y]) && piece_ref.getMasterArray()[getUpLeftJump().x][getUpLeftJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getDownRightJump().x][getDownRightJump().y]) && piece_ref.getMasterArray()[getDownRightJump().x][getDownRightJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getDownLeftJump().x][getDownLeftJump().y]) && piece_ref.getMasterArray()[getDownLeftJump().x][getDownLeftJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getRightUpJump().x][getRightUpJump().y]) && piece_ref.getMasterArray()[getRightUpJump().x][getRightUpJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getRightDownJump().x][getRightDownJump().y]) && piece_ref.getMasterArray()[getRightDownJump().x][getRightDownJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getLeftUpJump().x][getLeftUpJump().y]) && piece_ref.getMasterArray()[getLeftUpJump().x][getLeftUpJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	if (dynamic_cast<King*>(piece_ref.getMasterArray()[getLeftDownJump().x][getLeftDownJump().y]) && piece_ref.getMasterArray()[getLeftDownJump().x][getLeftDownJump().y]->getFlag() != this->getFlag()) {
		return true;
	}
	return false;
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
	int counter{ 0 };
	switch (flag) {
	case Flag::white:
		if (piece_ref.view_blackKing().getPos().x == pos.x) {
			int end = piece_ref.view_blackKing().getPos().y;
			if (end > pos.y) {
				for (int i = pos.y + 1; i < end; ++i) {
					if (piece_ref.getMasterArray()[pos.x][i]) {
						if (piece_ref.getMasterArray()[pos.x][i]->getFlag() == Flag::white) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (pos.y > end) {
				for (int i = pos.y - 1; i > end; --i) {
					if (piece_ref.getMasterArray()[pos.x][i]) {
						if (piece_ref.getMasterArray()[pos.x][i]->getFlag() == Flag::white) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (counter == 0) return true;
			if (counter == 1) {
				//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
				return false;
			}
			if (counter > 1) return false;
		}
		if (piece_ref.view_blackKing().getPos().y == pos.y) {
			int end = piece_ref.view_blackKing().getPos().x;
			if (end > pos.x) {
				for (int i = pos.x + 1; i < end; ++i) {
					if (piece_ref.getMasterArray()[i][pos.y]) {
						if (piece_ref.getMasterArray()[i][pos.y]->getFlag() == Flag::white) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (pos.x > end) {
				for (int i = pos.x - 1; i > end; --i) {
					if (piece_ref.getMasterArray()[i][pos.y]) {
						if (piece_ref.getMasterArray()[i][pos.y]->getFlag() == Flag::white) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (counter == 0) return true;
			if (counter == 1) {
				//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
				return false;
			}
			if (counter > 1) return false;
		}
		return false;
		break;
	case Flag::black:
		if (piece_ref.view_whiteKing().getPos().x == pos.x) {
			int end = piece_ref.view_whiteKing().getPos().y;
			if (end > pos.y) {
				for (int i = pos.y + 1; i < end; ++i) {
					if (piece_ref.getMasterArray()[pos.x][i]) {
						if (piece_ref.getMasterArray()[pos.x][i]->getFlag() == Flag::black) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (pos.y > end) {
				for (int i = pos.y - 1; i > end; --i) {
					if (piece_ref.getMasterArray()[pos.x][i]) {
						if (piece_ref.getMasterArray()[pos.x][i]->getFlag() == Flag::black) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (counter == 0) return true;
			if (counter == 1) {
				//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
				return false;
			}
			if (counter > 1) return false;
		}
		if (piece_ref.view_whiteKing().getPos().y == pos.y) {
			int end = piece_ref.view_whiteKing().getPos().x;
			if (end > pos.x) {
				for (int i = pos.x + 1; i < end; ++i) {
					if (piece_ref.getMasterArray()[i][pos.y]) {
						if (piece_ref.getMasterArray()[i][pos.y]->getFlag() == Flag::black) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (pos.x > end) {
				for (int i = pos.x - 1; i > end; --i) {
					if (piece_ref.getMasterArray()[i][pos.y]) {
						if (piece_ref.getMasterArray()[i][pos.y]->getFlag() == Flag::black) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (counter == 0) return true;
			if (counter == 1) {
				//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
				return false;
			}
			if (counter > 1) return false;
		}
		return false;
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
		if (isOnLeftDiag(pos, piece_ref.view_blackKing().getPos())) {
			if (pos.x > piece_ref.view_blackKing().getPos().x) {
				int i = 0;
				int x = pos.x - 1;
				int y = pos.y - 1;
				while (x > piece_ref.view_blackKing().getPos().x) {
					if (piece_ref.getMasterArray()[x - i][y - i]) {

					}
				}
			}
		}
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
	if (endPos == backwards()) {
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
	if (endPos == right()) {
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
	if (endPos == left()) {
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
	if (endPos == up_right()) {
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
	if (endPos == up_left()) {
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
	if (endPos == down_right()) {
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
	if (endPos == down_left()) {
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