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
        if (snake.selfCollisionCheck()) {
            gamestate.setGameState(true);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    std::cout << "Game Over!" << '\n';

    return 0;
}

