#pragma once
#include <array>

class Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

class Board {
private:
	std::array<std::array<char, 9>, 9> board{};
public:
	Board() {
		board[0] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
		board[1][0] = '1';
		board[2][0] = '2';
		board[3][0] = '3';
		board[4][0] = '4';
		board[5][0] = '5';
		board[6][0] = '6';
		board[7][0] = '7';
		board[8][0] = '8';
	}

};

class Pawn {
private:
	char pawn{ 'P' };
	Pos pos{};
public:
	Pos getPawnPos() { return pos; }

};

class Knight {
private:
	char knight{ 'K' };
	Pos pos{};
public:
	Pos getKnightPos() { return pos; }
};

class Rook {
private:
	char rook{ 'R' };
	Pos pos{};
public:
	Pos getRookPos() { return pos; }
};

class Bishop {
private:
	char bishop{ 'B' };
	Pos pos{};
public:
	Pos getBishopPos() { return pos; }
};

class King {
private:
	char king{ 'K' };
	Pos pos{};
public:
	Pos getKingPos() { return pos; }
};

class Queen {
private:
	char queen{ 'Q' };
	Pos pos{};
public:
	Pos getQueenPos() { return pos; }
};

class Controller {
public:
	void input() {

	}
};

