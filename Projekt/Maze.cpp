#include "Maze.h"

// sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev

// stworz okienko w sdl pokazujace labirynt
void createMaze(int w, int h, int sleepMs) {
    const int scale = 20;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Labirynt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (w*2 + 1) * scale, (h*2 + 1) * scale, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    std::vector<std::vector<Cell>> maze = initMaze(w, h);
    generateMaze(maze, renderer, sleepMs);

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

void drawMaze(std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer) {
    std::vector<std::vector<int>> matrixMaze;
    mazeToMatrix(maze, matrixMaze);

    drawMaze(matrixMaze, renderer);
}

void drawMaze(std::vector<std::vector<int>>& matrixMaze, SDL_Renderer* renderer) {
    const int scale = 20;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (size_t i = 0; i < matrixMaze.size(); i++) {
        for (size_t j = 0; j < matrixMaze[0].size(); j++) {
            SDL_Rect rect = { static_cast<int>(j * scale), static_cast<int>(i * scale), scale, scale };
            if (matrixMaze[i][j] == 0) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            if (matrixMaze[i][j] == 1) SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
            if (matrixMaze[i][j] == 2) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            if (matrixMaze[i][j] == 3) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);

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

void visitCell(Cell& cell, std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer, int sleepMs) {
    cell.visited = true;
    Cell* neighbour = hasNeighbours(cell, maze);

    while (neighbour) {  // tworzymy sciezke miedzy komorka, ktora odwiedzmay i jej sasiadami
        int xDif = neighbour->x - cell.x;
        int yDif = neighbour->y - cell.y;

        // sasiad z prawej strony od komorki, ktora odwiedzamy 
        if (xDif == 1) {
            cell.wallR = false;
            neighbour->wallL = false;
        }

        // sasiad z lewej strony od komorki, ktora odwiedzamy 
        if (xDif == -1) {
            cell.wallL = false;
            neighbour->wallR = false;
        }

        // sasiad z doly komorki, ktora odwiedzamy 
        if (yDif == 1) {
            cell.wallB = false;
            neighbour->wallT = false;
        }

        // s�siad z gory komorki, ktora odwiedzamy 
        if (yDif == -1) {
            cell.wallT = false;
            neighbour->wallB = false;
        }

        drawMaze(maze, renderer);
        SDL_Delay(sleepMs);

        visitCell(*neighbour, maze, renderer, sleepMs); // odwiedzamy komorki tego sasiada i tworzymy sciezke od niego
        neighbour = hasNeighbours(cell, maze); // jezeli sasiadnia komorka nie ma juz sasiadow, to bierzemy kolejnego sasiada komorki, ktora odiedzamy 
    }
}

void generateMaze(std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer, int sleepMs) {
    // wybieramy losowy punkt startowy generacji labiryntu
    Cell* curCell = &maze[std::rand() % maze.size()][std::rand() % maze[0].size()];
    visitCell(*curCell, maze, renderer, sleepMs);

    SDL_Delay(sleepMs);

    setStartAndEndPoint(maze, renderer);
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
}

void setStartAndEndPoint(std::vector<std::vector<Cell>>& maze, SDL_Renderer* renderer) {
    std::vector<std::vector<int>> matrixMaze;
    mazeToMatrix(maze, matrixMaze);

    std::vector<std::array<int, 2>> directions = { {1, 0}, {1, (int)matrixMaze.size() - 1}, {(int)matrixMaze[0].size() - 1, 1}, {(int)matrixMaze[0].size() - 1, (int)matrixMaze.size() - 2}};

    int s1 = std::rand() % 4;
    int s2 = std::rand() % 4;
    while (s1 == s2) {
        s2 = std::rand() % 4;
    }
    
    std::array<int, 2> startPoint = directions[s1];
    std::array<int, 2> endPoint = directions[s2];

    matrixMaze[startPoint[0]][startPoint[1]] = 2;
    matrixMaze[endPoint[0]][endPoint[1]] = 3;

    
    drawMaze(matrixMaze, renderer);

}
