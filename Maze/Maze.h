#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Maze {
public:
    Maze(int width, int height);
    void generate();
    void draw(sf::RenderWindow& window);

private:
    int width, height;
    std::vector<std::vector<Cell>> grid;
    void removeWall(Cell& current, Cell& next);
    std::vector<Cell*> getUnvisitedNeighbors(Cell& cell);
};

#endif
