#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <windows.h>
#include <conio.h>
#include "FunctionDeclarations.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

enum Direction {
	none,
	up,
	down,
	left,
	right,
};

class Controller {
private:
	Direction direction{ right };
	Direction directionCheck{ direction };
	Direction prevDirection{};
	bool quitButton{ false };
public:
	Direction getDirection() const { return direction; }
	Direction getPrevDirection() const { return prevDirection; }
	bool getQuitState() const { return quitButton; }
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
				quitButton = true;
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
};

class Snake {
private:
	char snakeHead{ 'O' };
	char snakeTail{ 'o' };
	int snakeLength{};
	Pos headPos{};
	Pos tailPos{};
	Pos trail{};
	std::vector<Pos> cache{};
	Controller* controller_ptr;
public:
	Snake(int length, Controller& controller) :
		snakeLength{ clampLength(length) },
		controller_ptr{ &controller }
	{
		headPos.x = 9;
		headPos.y = 9;
		tailPos.x = 9;
		tailPos.y = 8;
		cache.reserve(400);
	}
	int getSnakeLength() const { return snakeLength; }
	Pos getHeadPosition() const { return headPos; }
	Pos getTailPosition() const { return tailPos; }
	Pos getTrailPosition() const { return trail; }
	char getHeadGraphics() const { return snakeHead; }
	char getTailGraphics() const { return snakeTail; }
	void addSnakeLength() {
		++snakeLength;
	}
	const std::vector<Pos>& readCache() const {
		return cache;
	}
	void addCache() {
		while (cache.size() < snakeLength) {
			cache.push_back(getTailPosition());
		}
	}
	void updateCache() {
		trail = cache.back();
		for (int i = cache.size() - 1; i > 0; --i) {
			cache[i] = cache[i - 1];
		}
		cache[0] = tailPos;
	}
	void movement() {
		switch (controller_ptr->getDirection()) {
		case up:
			--headPos.x;
			headPos.x = boundsCheck(headPos.x);
			--tailPos.x;
			tailPos.x = boundsCheck(tailPos.x);
			break;
		case down:
			++headPos.x;
			headPos.x = boundsCheck(headPos.x);
			++tailPos.x;
			tailPos.x = boundsCheck(tailPos.x);
			break;
		case right:
			++headPos.y;
			headPos.y = boundsCheck(headPos.y);
			++tailPos.y;
			tailPos.y = boundsCheck(tailPos.y);
			break;
		case left:
			--headPos.y;
			headPos.y = boundsCheck(headPos.y);
			--tailPos.y;
			tailPos.y = boundsCheck(tailPos.y);
			break;
		}
	}
	void movementCorrector() {
		if (controller_ptr->isDirectionChanged()) {
			switch (controller_ptr->getDirection()) {
			case up:
				switch (controller_ptr->getPrevDirection()) {
				case right:
					++tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					++tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					break;
				case left:
					--tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					++tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					break;
				}
				break;
			case down:
				switch (controller_ptr->getPrevDirection()) {
				case right:
					++tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					--tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					break;
				case left:
					--tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					--tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					break;
				}
				break;
			case right:
				switch (controller_ptr->getPrevDirection()) {
				case up:
					--tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					--tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					break;
				case down:
					++tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					--tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					break;
				}
				break;
			case left:
				switch (controller_ptr->getPrevDirection()) {
				case up:
					--tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					++tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					break;
				case down:
					++tailPos.x;
					tailPos.x = boundsCheck(tailPos.x);
					++tailPos.y;
					tailPos.y = boundsCheck(tailPos.y);
					break;
				}
				break;
			}
		}
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
	void spawnFood() {
		foodPos.x = randomGen(0, 19);
		foodPos.y = randomGen(0, 19);
	}
	Pos getFoodPosition() const { return foodPos; }
	char getFoodGraphics() const { return food; }
};

class CollisionManager {
private:
	const Snake* const snake_ptr;
	const Food* const food_ptr;
public:
	CollisionManager(const Snake& snake, const Food& food) :
		snake_ptr{ &snake }, food_ptr{ &food }
	{}
	bool selfCollisionCheck() const{
		for (const auto& a : snake_ptr->readCache()) {
			if (snake_ptr->getHeadPosition() == a) {
				return true;
			}
		}
		return false;
	}
	bool foodCollisionCheck() const {
		if (snake_ptr->getHeadPosition() == food_ptr->getFoodPosition()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool foodSpawnCollisionCheck() const {
		for (const auto& a : snake_ptr->readCache()) {
			if (food_ptr->getFoodPosition() == a) {
				return true;
			}
		}
		if (food_ptr->getFoodPosition() == snake_ptr->getHeadPosition()) {
			return true;
		}
		return false;
	}
};

class Gamestate {
private:
	bool gameover{ false };
	const Snake* const snake_ptr;
	const CollisionManager* const collision_ptr;
	const Controller* const controller_ptr;
public:
	Gamestate(const Snake& snake, const CollisionManager& manager, const Controller& controller) : 
		snake_ptr{ &snake }, 
		collision_ptr{ &manager },
		controller_ptr{ &controller }
	{}
	bool getGameState() { return gameover; }
	void solveState() {
		if (collision_ptr->selfCollisionCheck()) {
			gameover = true;
			std::cout << "Game Over!" << '\n';
		}
		if (controller_ptr->getQuitState()) {
			gameover = true;
			std::cout << "Game Over!" << '\n';
		}
		if (snake_ptr->getSnakeLength() >= 400) {
			std::cout << "You won!" << '\n';
		}
	}
};