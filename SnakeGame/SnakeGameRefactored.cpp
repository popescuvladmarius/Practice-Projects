#include <iostream>
#include "Objects.h"

int main()
{
    Board board{};
    Controller controller;
    Snake snake(1, controller);
    Food food{};
    CollisionManager collisionManager(snake, food);
    Gamestate gamestate(snake, collisionManager, controller);

    foodSafeSpawn(food, collisionManager);
    while (!gamestate.getGameState()) {
        board.draw();
        controller.input();
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
        board.resetCursor();
        sleep();
    }

    return 0;
}

