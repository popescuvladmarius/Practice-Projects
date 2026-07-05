#include <iostream>
#include <chrono>
#include <thread>
#include "Objects.h"

int main()
{
    Board board{};
    Snake snake(1);
    Food food{};
    CollisionManager collisionManager(snake, food);
    Gamestate gamestate(snake, collisionManager);

    foodSafeSpawn(food, collisionManager);
    while (!gamestate.getGameState()) {
        board.draw();
        board.resetCursor();
        snake.input();
        snake.movement();
        snake.movementCorrector();
        snake.addCache();
        snake.updateCache();
        writeBoard(snake, board, food);
        if (collisionManager.foodCollisionCheck()) {
            snake.addSnakeLength();
            foodSafeSpawn(food, collisionManager);
        }
        gamestate.solveState();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    return 0;
}

