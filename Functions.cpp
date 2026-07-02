#include <iostream>
#include <windows.h>
#include <conio.h>
#include <array>
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <algorithm>
#include "Objects.h"

int randomGen(int min, int max) {
	static std::mt19937 random{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
void writeBoard(Snake& snake, Board& board) {
	board.setBoard(snake.getHeadGraphics(), snake.getHeadPosition());
	for (const auto& a : snake.readCache()) {
		board.setBoard(snake.getTailGraphics(), a);
	}
	board.setBoard(board.getGrassGraphics(), snake.getTrailPosition());
}