#pragma once
#include "Objects.h"

int randomGen(int min, int max);
void writeBoard(Snake& snake, Board& board);
bool collisionCheck(Snake& snake, Food& food);