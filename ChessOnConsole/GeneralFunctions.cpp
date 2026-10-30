#include "GeneralFunctions.h"
#include "Pieces.h"

bool isOnLeftDiag(Pos pos, Pos inputPos) {
	if (((pos.y - pos.x) == (inputPos.y - inputPos.x)) && (pos != inputPos)) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnRightDiag(Pos pos, Pos inputPos) {
	if (((std::abs(pos.y - pos.x) - std::abs(inputPos.y - inputPos.x)) % 2 == 0) && (pos != inputPos)) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnRow(Pos pos, Pos inputPos) {
	if (pos.x == inputPos.x && pos.y != inputPos.y) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnCol(Pos pos, Pos inputPos) {
	if (pos.y == inputPos.y && pos.x != inputPos.x) {
		return true;
	}
	else {
		return false;
	}
}
bool isMoveValidOnRow(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece) {
	if (array[endPos.x][endPos.y]) {
		if (array[endPos.x][endPos.y]->getFlag() == piece->getFlag()) {
			return false;
		}
	}
	if (endPos.y > pos.y) {
		pos.y += 1;
		for (pos.y; pos.y < endPos.y; ++pos.y) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
	if (endPos.y < pos.y) {
		pos.y -= 1;
		for (pos.y; pos.y > endPos.y; --pos.y) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
}
bool isMoveValidOnCol(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece) {
	if (array[endPos.x][endPos.y]) {
		if (array[endPos.x][endPos.y]->getFlag() == piece->getFlag()) {
			return false;
		}
	}
	if (endPos.x > pos.x) {
		pos.x += 1;
		for (pos.x; pos.x < endPos.x; ++pos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
	if (endPos.x < pos.x) {
		pos.x -= 1;
		for (pos.x; pos.x > endPos.x; --pos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
}
bool isMoveValidOnLeftDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece) {
	if (array[endPos.x][endPos.y]) {
		if (array[endPos.x][endPos.y]->getFlag() == piece->getFlag()) {
			return false;
		}
	}
	if (endPos.x > pos.x) {	
		pos.x += 1;
		pos.y += 1;
		while (pos.x < endPos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
			else {
				++pos.x;
				++pos.y;
			}
		}
		return true;
	}
	if (endPos.x < pos.x) {
		pos.x -= 1;
		pos.y -= 1;
		while (pos.x > endPos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
			else {
				--pos.x;
				--pos.y;
			}
		}
		return true;
	}
}
bool isMoveValidOnRightDiag(Pos pos, Pos endPos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* piece) {
	if (array[endPos.x][endPos.y]) {
		if (array[endPos.x][endPos.y]->getFlag() == piece->getFlag()) {
			return false;
		}
	}
	if (endPos.x < pos.x) {
		pos.x -= 1;
		pos.y += 1;
		while (pos.x > endPos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
			else {
				--pos.x;
				++pos.y;
			}
		}
		return true;
	}
	if (endPos.x > pos.x) {
		pos.x += 1;
		pos.y -= 1;
		while (pos.x < endPos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
			else {
				++pos.x;
				--pos.y;
			}
		}
		return true;
	}
}
bool scanRow(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
	int counter{ 0 };
		if (kingPos.x == pos.x) {
			if (kingPos.y > pos.y) {
				pos.y += 1;
				for (pos.y; pos.y < kingPos.y; ++pos.y) {
					if (array[pos.x][pos.y]) {
						if (array[pos.x][pos.y]->getFlag() == flag) {
							return false;
						}
						else {
							++counter;
						}
					}
				}
			}
			if (kingPos.y < pos.y) {
				pos.y -= 1;
				for (pos.y; pos.y > kingPos.y; --pos.y) {
					if (array[pos.x][pos.y]) {
						if (array[pos.x][pos.y]->getFlag() == flag) {
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
		else {
			return false;
		}
}
bool scanCol(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
	int counter{ 0 };
	if (kingPos.y == pos.y) {
		if (kingPos.x > pos.x) {
			pos.x += 1;
			for (pos.x; pos.x < kingPos.x; ++pos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
						return false;
					}
					else {
						++counter;
					}
				}
			}
		}
		if (kingPos.x < pos.x) {
			pos.x -= 1;
			for (pos.x; pos.x > kingPos.x; --pos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
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
	else {
		return false;
	}
}
bool scanLeftDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
	int counter{ 0 };
	if (isOnLeftDiag(pos, kingPos)) {
		if (pos.x > kingPos.x) {
			pos.x - 1;
			pos.y - 1;
			while (pos.x > kingPos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
						return false;
					}
					else {
						++counter;
					}
				}
				--pos.x;
				--pos.y;
			}
		}
		if (pos.x < kingPos.x) {
			pos.x + 1;
			pos.y + 1;
			while (pos.x < kingPos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
						return false;
					}
					else {
						++counter;
					}
				}
				++pos.x;
				++pos.y;
			}
		}
		if (counter == 0) return true;
		if (counter == 1) {
			//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
			return false;
		}
		if (counter > 1) return false;
	}
	else {
		return false;
	}
}
bool scanRightDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
	int counter{ 0 };
	if (isOnRightDiag(pos, kingPos)) {
		if (pos.x > kingPos.x) {
			pos.x - 1;
			pos.y + 1;
			while (pos.x > kingPos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
						return false;
					}
					else {
						++counter;
					}
				}
				--pos.x;
				++pos.y;
			}
		}
		if (pos.x < kingPos.x) {
			pos.x + 1;
			pos.y - 1;
			while (pos.x < kingPos.x) {
				if (array[pos.x][pos.y]) {
					if (array[pos.x][pos.y]->getFlag() == flag) {
						return false;
					}
					else {
						++counter;
					}
				}
				++pos.x;
				--pos.y;
			}
		}
		if (counter == 0) return true;
		if (counter == 1) {
			//must notify piecemanager of the piece to be locked, piecemanager then tells rulemanager to actually trigger the lock
			return false;
		}
		if (counter > 1) return false;
	}
	else {
		return false;
	}
}
void invalidPieceMessage() {
	std::cout << "Invalid Piece" << '\n' << "Select again" << '\n';
}
void invalidMoveMessage() {
	std::cout << "Invalid Move" << '\n' << "Select again" << '\n';
}
