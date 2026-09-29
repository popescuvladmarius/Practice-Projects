#include "Objects.h"
#include "FunctionDeclarations.h"

bool isOnLeftDiag(Pos pos, Pos inputPos) {
	if ((pos.y - pos.x) == (inputPos.y - inputPos.x)) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnRightDiag(Pos pos, Pos inputPos) {
	if ((std::abs(pos.y - pos.x) - std::abs(inputPos.y - inputPos.x)) % 2 == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnRow(Pos pos, Pos inputPos) {
	if (pos.x == inputPos.x) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnCol(Pos pos, Pos inputPos) {
	if (pos.y == inputPos.y) {
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
		for (pos.y + 1; pos.y < endPos.y; ++pos.y) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
	if (endPos.y < pos.y) {
		for (pos.y - 1; pos.y > endPos.y; --pos.y) {
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
		for (pos.x + 1; pos.x < endPos.x; ++pos.x) {
			if (array[pos.x][pos.y]) {
				return false;
			}
		}
		return true;
	}
	if (endPos.x < pos.x) {
		for (pos.x - 1; pos.x > endPos.x; --pos.x) {
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
		int i = 1;
		pos.x += i;
		pos.y += i;
		while (pos.x < endPos.x) {
			if (array[pos.x + i][pos.y + i]) {
				return false;
			}
			else {
				++i;
			}
		}
		return true;
	}
	if (endPos.x < pos.x) {
		int i = 1;
		pos.x -= i;
		pos.y -= i;
		while (pos.x > endPos.x) {
			if (array[pos.x - i][pos.y - i]) {
				return false;
			}
			else {
				++i;
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
		int i = 1;
		pos.x -= i;
		pos.y += i;
		while (pos.x > endPos.x) {
			if (array[pos.x - i][pos.y + i]) {
				return false;
			}
			else {
				++i;
			}
		}
		return true;
	}
	if (endPos.x > pos.x) {
		int i = 1;
		pos.x += i;
		pos.y -= i;
		while (pos.x < endPos.x) {
			if (array[pos.x + i][pos.y - i]) {
				return false;
			}
			else {
				++i;
			}
		}
		return true;
	}
}