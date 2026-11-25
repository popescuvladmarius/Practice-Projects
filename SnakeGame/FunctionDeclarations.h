#pragma once
class Snake;
class Board;
class Food;
class CollisionManager;

int boundsCheck(int x);                    //makes sure the snake doesn't go out of bounds 
int clampLength(int length);                  //clamps length of snake to 400 max and 1 min
int randomGen(int min, int max);               //generates a random integer with uniform distribution
void writeBoard(const Snake& snake, Board& board, const Food& food);              //writes to graphical board
void foodSafeSpawn(Food& food, const CollisionManager& manager);                  //spawns food safely by avoiding to spawn on the snake's tail locations
void sleep();                  //makes the thread go to sleep for 150 ms during the loop to slow down speed