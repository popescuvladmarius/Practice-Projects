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
#include "FunctionDeclarations.h"

int main()
{
    Board board{};
    Gamestate gamestate{};
    Snake snake(1);

    while (!gamestate.getGameState()) {
        board.draw();
        board.resetCursor();
        snake.input();
        snake.movement();
        snake.movementCorrector();
        snake.addCache();
        snake.updateCache();
        writeBoard(snake, board);
        

    }

    return 0;
}

