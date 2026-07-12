#include <random>
#include "Objects.h"

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