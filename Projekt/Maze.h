#pragma once

#include <iostream>
#include <array>
#include <vector>

class Cell {
public:
    int x, y;
    bool visited;
    bool wallT;
    bool wallR;
    bool wallB;
    bool wallL;


    Cell(int x, int y) : x(x), y(y), visited(false), wallT(true), wallR(true), wallB(true), wallL(true) {}
};

// zwraca labirynt, w którym nie ma żadnych połączeń między komórkami
std::vector<std::vector<Cell>> initMaze(int w, int h);

// generuje labirynt
void generateMaze(std::vector<std::vector<Cell>>& maze);

// odwiedza komórkę i tworzy losowe połączenia między nią a jej sąsiadami
void visitCell(Cell& cell, std::vector<std::vector<Cell>>& maze);

// zwraca informację, czy komórka jest poprawna, tj. czy nie wykracza poza labirynt i nie była jeszcze odwiedzona
bool isCellValid(int x, int y, std::vector<std::vector<Cell>>& maze);

// zwraca losowego sąsiada z poprawnych (nieodwiedzonych) sąsiadów danej komórki
Cell* hasNeighbours(Cell& cell, std::vector<std::vector<Cell>>& maze);

// zamienia "drzewo" na przyjazną dla człowieka macierz
void mazeToMatrix(std::vector<std::vector<Cell>>& maze, std::vector<std::vector<int>>& mat);

// ustawia punkt, z którego startujemy i punkt, do którego mamy dotrzeć
void setStartAndEndPoint(std::vector<std::vector<int>>& maze);

// tworzy okienko z labiryntem
void drawMaze(std::vector<std::vector<int>>& maze);

void createMaze(int w, int h);
