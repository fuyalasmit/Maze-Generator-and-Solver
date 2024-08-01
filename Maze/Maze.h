#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Maze {
public:
    Maze(int width, int height);
    void generateAnimated(sf::RenderWindow& window, const sf::Texture& wallTexture);
    void draw(sf::RenderWindow& window, const sf::Texture& wallTexture);

    int width, height;   //dimension for maze hai not cell
    std::vector<std::vector<Cell>> grid;

private:
    void removeWall(Cell& current, Cell& next);   //2ta adjacent cell ko bich ma wall remove
    std::vector<Cell*> getUnvisitedNeighbors(Cell& cell);  //Returns a list of unvisited neighboring cells.
    std::vector<Cell*> getVisitedNeighbors(Cell& cell);  //esma chahi visited.
};

#endif

//pointer use garyo vane harek cell ma copy garna parena, memory bachxa, 
// grid haru pani DMA hunxa, so pointer becomes effective
