#include <random>
#include <chrono>
#include <thread>
#include "Objects.h"

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
int clampLength(int length) {
	if (length < 1) { return 1; }
	if (length > 400) { return 400; }
	return length;
}
int randomGen(int min, int max) {
	static std::mt19937 random{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}
void writeBoard(const Snake& snake, Board& board, const Food& food) {
	board.setBoard(snake.getHeadGraphics(), snake.getHeadPosition());
	for (const auto& a : snake.readCache()) {
		board.setBoard(snake.getTailGraphics(), a);
	}
	board.setBoard(board.getGrassGraphics(), snake.getTrailPosition());
	board.setBoard(food.getFoodGraphics(), food.getFoodPosition());
}
void foodSafeSpawn(Food& food, const CollisionManager& manager) {
	do {
		food.spawnFood();
	} while (manager.foodSpawnCollisionCheck());
}
void sleep() {
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
}