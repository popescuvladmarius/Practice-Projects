#pragma once
#include <array>
#include <cmath>
#include "FunctionDeclarations.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

class Board {
private:
	std::array<std::array<char, 8>, 8> board{};
public:
	Board() {
		
	}

};

class White {

};

class Black {

};

class Controller {
private:
	Pos inputPos{};
public:
	void selectPiece() {

	}

	void setInput(Pos input) {
		inputPos = input;
	}
	Pos getInputPos() const { return inputPos; }
};

class RuleManager {

};

class CollisionManager {

};

class Pawn {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getPawnPos() { return pos; }
	Pos forward() {
		Pos temp{ pos };
		++temp.x;
		return temp;
	}
	Pos forwardDouble() {
		Pos temp{ pos };
		temp.x + 2;
		return temp;
	}
	Pos captureRight() {
		Pos temp{ pos };
		++temp.x;
		++temp.y;
		return temp;
	}
	Pos captureLeft() {
		Pos temp{ pos };
		++temp.x;
		--temp.y;
		return temp;
	}
	Pos move() {
		if (forward() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (forwardDouble() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (captureRight() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (captureLeft() == controller_ref.getInputPos()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Knight {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getKnightPos() { return pos; }
	Pos getUpRightJump() {
		Pos temp{ pos };
		temp.x += 2;
		temp.y += 1;
		return temp;
	}
	Pos getUpLeftJump() {
		Pos temp{ pos };
		temp.x += 2;
		temp.y -= 1;
		return temp;
	}
	Pos getDownRightJump() {
		Pos temp{ pos };
		temp.x -= 2;
		temp.y += 1;
		return temp;
	}
	Pos getDownLeftJump() {
		Pos temp{ pos };
		temp.x -= 2;
		temp.y -= 1;
		return temp;
	}
	Pos getRightUpJump() {
		Pos temp{ pos };
		temp.x += 1;
		temp.y += 2;
		return temp;
	}
	Pos getRightDownJump() {
		Pos temp{ pos };
		temp.x -= 1;
		temp.y += 2;
		return temp;
	}
	Pos getLeftUpJump() {
		Pos temp{ pos };
		temp.x += 1;
		temp.y -= 2;
		return temp;
	}
	Pos getLeftDownJump() {
		Pos temp{ pos };
		temp.x -= 1;
		temp.y -= 2;
		return temp;
	}
	Pos move() {
		if (controller_ref.getInputPos() == getUpRightJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getUpLeftJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getDownRightJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getDownLeftJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getRightUpJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getRightDownJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getLeftUpJump()) {
			pos = controller_ref.getInputPos();
		}
		if (controller_ref.getInputPos() == getLeftDownJump()) {
			pos = controller_ref.getInputPos();
		}
	}
};

class Rook {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getRookPos() { return pos; }
	Pos move() {
		if (isOnRow(pos, controller_ref.getInputPos()) || isOnCol(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Bishop {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getBishopPos() { return pos; }
	Pos move() {
		if (isOnRightDiagonale(pos, controller_ref.getInputPos()) || isOnLeftDiagonale(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class King {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getKingPos() { return pos; }
	Pos forward() {
		Pos temp{ pos };
		++temp.x;
		return temp;
	}
	Pos backwards() {
		Pos temp{ pos };
		--temp.x;
		return temp;
	}
	Pos right() {
		Pos temp{ pos };
		++temp.y;
		return temp;
	}
	Pos left() {
		Pos temp{ pos };
		--temp.y;
		return temp;
	}
	Pos up_right() {
		Pos temp{ pos };
		++temp.x;
		++temp.y;
		return temp;
	}
	Pos up_left() {
		Pos temp{ pos };
		++temp.x;
		--temp.y;
		return temp;
	}
	Pos down_right() {
		Pos temp{ pos };
		--temp.x;
		++temp.y;
		return temp;
	}
	Pos down_left() {
		Pos temp{ pos };
		--temp.x;
		--temp.y;
		return temp;
	}
	Pos move(){
		if (controller_ref.getInputPos() == forward()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == backwards()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == up_right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == up_left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == down_right()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
		if (controller_ref.getInputPos() == down_left()) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Queen {
private:
	Pos pos{};
	const Controller& controller_ref{};
public:
	Pos getQueenPos() { return pos; }
	Pos move() {
		if (isOnRow(pos, controller_ref.getInputPos()) || isOnCol(pos, controller_ref.getInputPos()) || isOnRightDiagonale(pos, controller_ref.getInputPos()) || isOnLeftDiagonale(pos, controller_ref.getInputPos())) {
			pos = controller_ref.getInputPos();
			return pos;
		}
	}
};

class Gamestate {

};

