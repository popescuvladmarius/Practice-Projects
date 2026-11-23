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
bool checkScanRow(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
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
bool checkScanCol(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
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
bool checkScanLeftDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
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
bool checkScanRightDiag(Pos pos, Pos kingPos, const std::array<std::array<Piece*, 8>, 8>& array, Flag flag) {
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
std::vector<Pos> getRowBaseMoveIterations(Pos pos, const std::array<std::array<Piece*, 8>, 8>& array, const Piece* const piece) {
	std::vector<Pos> moves;
	if (pos.y > 0) {
		pos.y -= 1;
		while (pos.y >= 0) {
			if (!array[pos.x][pos.y]) {
				moves.push_back(pos);
			}
			else if (array[pos.x][pos.y]->getFlag() != piece->getFlag()) {
				moves.push_back(pos);
				return moves;
			}
			else {
				return moves;
			}
			--pos.y;
		}
	}
}                        //to be discarded
void invalidPieceMessage() {
	std::cout << "Invalid Piece" << '\n' << "Select again" << '\n';
}
void invalidMoveMessage() {
	std::cout << "Invalid Move" << '\n' << "Select again" << '\n';
}
