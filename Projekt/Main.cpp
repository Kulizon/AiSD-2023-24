#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Maze.h"

int main() {
    // ustawiamy ziarno dla generatora liczb losowych
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // wymiary labiryntu
    int width = 15;
    int height = 15;

    createMaze(width, height, 10);

    return 0;
}
