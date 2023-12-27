#pragma once

#include <iostream>
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


// zwraca labirynt, w kt�rym nie ma �adnych po��czen mi�dzy kom�rkami
std::vector<std::vector<Cell>> initMaze(int w, int h);

// generuje labirynt
void generateMaze(std::vector<std::vector<Cell>>& maze);

// odwiedza kom�rk� i tworzy losowe po��czenia mi�dzy ni� i jej s�siadami
void visitCell(Cell& cell, std::vector<std::vector<Cell>>& maze);

// zwraca informacj�, czy kom�rka jest poprawna, tj. czy nie wykracza poza labirynt i nie by�a jeszcze odwiedzona
bool isCellValid(int x, int y, std::vector<std::vector<Cell>>& maze);

// zwraca losowego s�siada z poprawnych (nieodwiedzonych) s�siad�w danej kom�rki
Cell* hasNeighbours(Cell& cell, std::vector<std::vector<Cell>>& maze);

// zamienia "drzewo" na przyjazn� dla cz�owieka macierz
void mazeToMatrix(std::vector<std::vector<Cell>>& maze, std::vector<std::vector<int>>& mat);

// ustawia punkt, z kt�rego startujemy i punkt, do kt�rego mamy dotrze�
void setStartAndEndPoint(std::vector<std::vector<int>>& maze);

// tworzy okienko z labiryntem
void drawMaze(std::vector<std::vector<int>>& maze);

void createMaze(int w, int h);