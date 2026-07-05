#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <windows.h>
#include <conio.h>


struct Pos {
	int x{};
	int y{};
};

enum Direction {
	none,
	up,
	down,
	left,
	right,
	quit
};

class Snake {
private:
	char snakeHead{ 'O' };
	char snakeTail{ 'o' };
	int snakeLength{};
	int headX{};
	int headY{};
	int tailX{};
	int tailY{};
	Pos headPos{};
	Pos tailPos{};
	Pos trail{};
	std::vector<Pos> cache{};
	Direction direction{ right };
	Direction directionCheck{ direction };
	Direction prevDirection{};
public:
	Snake(int length) :
		snakeLength{ length }
	{

		headX = 9;
		headY = 9;
		tailX = 8;
		tailY = 8;
		cache.reserve(400);
	}
	void addSnakeLength() {
		++snakeLength;
	}
	Pos getHeadPosition() {
		headPos.x = headX;
		headPos.y = headY;
		return headPos;
	}
	Pos getTailPosition() {
		tailPos.x = tailX;
		tailPos.y = tailY;
		return tailPos;
	}
	Pos getTrailPosition() {
		return trail;
	}
	const std::vector<Pos>& readCache() {
		return cache;
	}
	char getHeadGraphics() { return snakeHead; }
	char getTailGraphics() { return snakeTail; }
	int boundsCheck(int x) {
		if (x < 0) {
			x = 19;
			return x;
		}
		if (x > 19) {
			x = 0;
			return x;
		}
		return x;
	}
	void input() {
		if (_kbhit()) {
			switch (_getch()) {
			case 'w':
				if (direction == down) {
					direction = down;
				}
				else {
					direction = up;
				}
				break;
			case 's':
				if (direction == up) {
					direction = up;
				}
				else {
					direction = down;
				}
				break;
			case 'a':
				if (direction == right) {
					direction = right;
				}
				else {
					direction = left;
				}
				break;
			case 'd':
				if (direction == left) {
					direction = left;
				}
				else {
					direction = right;
				}
				break;
			case 'x':
				direction = quit;
				break;
			}
		}
	}
	bool isDirectionChanged() {
		if (direction != directionCheck) {
			prevDirection = directionCheck;
			directionCheck = direction;
			return true;
		}
		else {
			return false;
		}
	}
	void movement() {
		switch (direction) {
		case up:
			--headX;
			headX = boundsCheck(headX);
			--tailX;
			tailX = boundsCheck(tailX);
			break;
		case down:
			++headX;
			headX = boundsCheck(headX);
			++tailX;
			tailX = boundsCheck(tailX);
			break;
		case right:
			++headY;
			headY = boundsCheck(headY);
			++tailY;
			tailY = boundsCheck(tailY);
			break;
		case left:
			--headY;
			headY = boundsCheck(headY);
			--tailY;
			tailY = boundsCheck(tailY);
			break;
		}
	}
	void movementCorrector() {
		if (isDirectionChanged()) {
			switch (direction) {
			case up:
				switch (prevDirection) {
				case right:
					++tailY;
					tailY = boundsCheck(tailY);
					++tailX;
					tailX = boundsCheck(tailX);
					break;
				case left:
					--tailY;
					tailY = boundsCheck(tailY);
					++tailX;
					tailX = boundsCheck(tailX);
					break;
				}
				break;
			case down:
				switch (prevDirection) {
				case right:
					++tailY;
					tailY = boundsCheck(tailY);
					--tailX;
					tailX = boundsCheck(tailX);
					break;
				case left:
					--tailY;
					tailY = boundsCheck(tailY);
					--tailX;
					tailX = boundsCheck(tailX);
					break;
				}
				break;
			case right:
				switch (prevDirection) {
				case up:
					--tailX;
					tailX = boundsCheck(tailX);
					--tailY;
					tailY = boundsCheck(tailY);
					break;
				case down:
					++tailX;
					tailX = boundsCheck(tailX);
					--tailY;
					tailY = boundsCheck(tailY);
					break;
				}
				break;
			case left:
				switch (prevDirection) {
				case up:
					--tailX;
					tailX = boundsCheck(tailX);
					++tailY;
					tailY = boundsCheck(tailY);
					break;
				case down:
					++tailX;
					tailX = boundsCheck(tailX);
					++tailY;
					tailY = boundsCheck(tailY);
					break;
				}
				break;
			}
		}
	}
	void addCache() {
		while (cache.size() < snakeLength) {
			cache.push_back(getTailPosition());
		}
	}
	void updateCache() {
		for (int i = cache.size() - 1; i > 0; --i) {
			trail = cache[i];
			cache[i] = cache[i - 1];
		}
		cache[0] = getTailPosition();
	}
	bool selfCollisionCheck() {
		for (const auto& a : cache) {
			if (a.x == headX && a.y == headY) {
				return true;
			}
		}
		return false;
	}
};

class Board {
private:
	std::array<std::array<char, 20>, 20> board{};
	char grass{ '*' };
public:
	Board() {
		for (auto& row : board) {
			for (auto& col : row) {
				col = grass;
			}
		}
	}
	char getGrassGraphics() {
		return grass;
	}
	void setBoard(char graphics, Pos location) {
		board[location.x][location.y] = graphics;
	}
	void draw() {
		for (auto const& a : board) {
			for (auto const& b : a) {
				std::cout << b << "  ";
			}
			std::cout << '\n';
		}
	}
	void resetCursor() {
		std::cout << "\x1B[H";
	}
};

class Food {
private:
	char food{ '$' };
	Pos foodPos{};
public:
	Pos getFoodPosition() { return foodPos; }
	Pos spawnFood() {
		foodPos.x = randomGen(0, 19);
		foodPos.y = randomGen(0, 19);
	}
};

class Gamestate {
private:
	bool gameover{ false };
	 
public:
	bool getGameState() const { return gameover; }
	void setGameState(bool state) { gameover = state; }
};