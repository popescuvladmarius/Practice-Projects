#pragma once
class Snake;
class Board;
class Food;
class CollisionManager;

int randomGen(int min, int max);
void writeBoard(const Snake& snake, Board& board, const Food& food);
void foodSafeSpawn(Food& food, const CollisionManager& manager);