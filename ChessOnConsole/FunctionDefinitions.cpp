#include "Objects.h"

bool isOnLeftDiagonale(Pos pos, Pos inputPos) {
	if ((pos.y - pos.x) == (inputPos.y - inputPos.x)) {
		return true;
	}
	else {
		return false;
	}
}
bool isOnRightDiagonale(Pos pos ,Pos inputPos) {
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
