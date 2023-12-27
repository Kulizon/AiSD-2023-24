#include "Maze.h"
#include <SDL2/SDL.h>

// sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev

void createMaze(int w, int h) {
    std::vector<std::vector<Cell>> maze = initMaze(w, h);
    generateMaze(maze);

    std::vector<std::vector<int>> matrixMaze;
    mazeToMatrix(maze, matrixMaze);

    // stw�rz okienko w sdl pokazuj�ce labirynt
    drawMaze(matrixMaze);
}

void drawMaze(std::vector<std::vector<int>>& maze) {
    const int scale = 20;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Labirynt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, maze[0].size() * scale, maze.size() * scale, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < maze.size(); i++) {
        for (size_t j = 0; j < maze[0].size(); j++) {
            SDL_Rect rect = { static_cast<int>(j * scale), static_cast<int>(i * scale), scale, scale };
            if (maze[i][j] == 0) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            if (maze[i][j] == 1) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            if (maze[i][j] == 2) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            if (maze[i][j] == 3) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }


    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



std::vector<std::vector<Cell>> initMaze(int w, int h) {
    std::vector<std::vector<Cell>> maze;

    for (int y = 0; y < h; y++) {
        maze.push_back(std::vector<Cell>());
        for (int x = 0; x < w; x++) {
            maze[y].push_back(Cell(x, y));
        }
    }

    return maze;
}

bool isCellValid(int x, int y, std::vector<std::vector<Cell>>& maze) {
    return (size_t)x >= 0 && (size_t)x < maze.size() && (size_t)y >= 0 && (size_t)y < maze[0].size() && !maze[y][x].visited;
}

Cell* hasNeighbours(Cell& cell, std::vector<std::vector<Cell>>& maze) {
    std::vector<Cell*> neighbours;

    if (isCellValid(cell.x + 1, cell.y, maze)) neighbours.push_back(&maze[cell.y][cell.x + 1]);
    if (isCellValid(cell.x - 1, cell.y, maze)) neighbours.push_back(&maze[cell.y][cell.x - 1]);
    if (isCellValid(cell.x, cell.y - 1, maze)) neighbours.push_back(&maze[cell.y - 1][cell.x]);
    if (isCellValid(cell.x, cell.y + 1, maze)) neighbours.push_back(&maze[cell.y + 1][cell.x]);

    if (neighbours.empty()) return nullptr;
    return neighbours[std::rand() % neighbours.size()];
}

void visitCell(Cell& cell, std::vector<std::vector<Cell>>& maze) {
    cell.visited = true;
    Cell* neighbour = hasNeighbours(cell, maze);

    while (neighbour) {  // tworzymy �cie�k� mi�dzy kom�rk�, kt�r� odwiedzmay i jej s�siadami
        int xDif = neighbour->x - cell.x;
        int yDif = neighbour->y - cell.y;

        // s�siad z prawej strony od kom�rki, kt�r� odwiedzamy 
        if (xDif == 1) {
            cell.wallR = false;
            neighbour->wallL = false;
        }

        // s�siad z lewej strony od kom�rki, kt�r� odwiedzamy 
        if (xDif == -1) {
            cell.wallL = false;
            neighbour->wallR = false;
        }

        // s�siad z do�y kom�rki, kt�r� odwiedzamy 
        if (yDif == 1) {
            cell.wallB = false;
            neighbour->wallT = false;
        }

        // s�siad z g�ry kom�rki, kt�r� odwiedzamy 
        if (yDif == -1) {
            cell.wallT = false;
            neighbour->wallB = false;
        }

        visitCell(*neighbour, maze); // odwiedzamy kom�rki tego s�siada i tworzymy �cie�k� od niego
        neighbour = hasNeighbours(cell, maze); // je�eli s�siadnia kom�rka nie ma ju� s�siad�w, to bierzemy kolejnego s�siada kom�rki, kt�ra odiedzamy 
    }
}

void generateMaze(std::vector<std::vector<Cell>>& maze) {
    // wybieramy losowy punkt startowy generacji labiryntu
    Cell* curCell = &maze[std::rand() % maze.size()][std::rand() % maze[0].size()];
    visitCell(*curCell, maze);
}

void mazeToMatrix(std::vector<std::vector<Cell>>& maze, std::vector<std::vector<int>>& mat) {
    for (size_t i = 0; i < maze.size() * 2 + 1; i++) {
        mat.push_back(std::vector<int>());
        for (size_t j = 0; j < maze[0].size() * 2 + 1; j++) {
            mat[i].push_back(0);
        }
    }

    int i = 0;
    int j = 0;
    for (size_t y = 1; y < maze.size() * 2 + 1; y += 2) {
        for (size_t x = 1; x < maze[0].size() * 2 + 1; x += 2) {
            Cell cell = maze[i][j];

            mat[y - 1][x + 1] = 1;
            mat[y + 1][x + 1] = 1;
            mat[y - 1][x - 1] = 1;
            mat[y + 1][x - 1] = 1;

            if (cell.wallT) mat[y - 1][x] = 1;
            if (cell.wallB) mat[y + 1][x] = 1;
            if (cell.wallL) mat[y][x - 1] = 1;
            if (cell.wallR) mat[y][x + 1] = 1;
            
            j++;
        }
        i++;
        j = 0;
    }

    setStartAndEndPoint(mat);
}

void setStartAndEndPoint(std::vector<std::vector<int>>& mat) {
    std::vector<std::string> directions = { "t", "r", "b", "l" };
    std::string startingWall = directions[std::rand() % 4];

    if (startingWall == "t" || startingWall == "b") {
        int dirA = (startingWall == "t") ? 1 : mat.size() - 2;
        int pointA = std::rand() % mat[0].size();
        while (mat[dirA][pointA] == 1) {
            pointA = std::rand() % mat[0].size();
        }

        int dirB = (startingWall == "t") ? mat.size() - 2 : 1;
        int pointB = std::rand() % mat[0].size();
        while (mat[dirB][pointB] == 1) {
            pointB = std::rand() % mat[0].size();
        }

        mat[dirA == 1 ? 0 : mat.size() - 1][pointA] = 2;
        mat[dirB == 1 ? 0 : mat.size() - 1][pointB] = 3;
    }

    if (startingWall == "r" || startingWall == "l") {
        int dirA = (startingWall == "l") ? 1 : mat[0].size() - 2;
        int pointA = std::rand() % mat.size();
        while (mat[pointA][dirA] == 1) {
            pointA = std::rand() % mat.size();
        }

        int dirB = (startingWall == "l") ? mat[0].size() - 2 : 1;
        int pointB = std::rand() % mat.size();
        while (mat[pointB][dirB] == 1) {
            pointB = std::rand() % mat.size();
        }

        mat[pointA][dirA == 1 ? 0 : mat[0].size() - 1] = 2;
        mat[pointB][dirB == 1 ? 0 : mat[0].size() - 1] = 3;
    }
}
