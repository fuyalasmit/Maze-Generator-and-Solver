#ifndef BACKTRACK_H
#define BACKTRACK_H

#include <vector>
#include "Cell.h"

class BackTrack {
public:
    BackTrack(int width, int height);
    void generateMaze();
    void draw(sf::RenderWindow& window, float cellSize);
    const std::vector<std::vector<Cell>>& getGrid() const;

private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    Cell* current;
    std::vector<Cell*> stack;

    Cell* checkNeighbors(Cell& cell);
    void removeWalls(Cell& a, Cell& b);
};

#endif // BACKTRACK_H
