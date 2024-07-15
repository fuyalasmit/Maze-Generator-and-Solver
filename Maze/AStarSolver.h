#ifndef ASTAR_SOLVER_H
#define ASTAR_SOLVER_H

#include <vector>
#include <queue>
#include "Maze.h"

class AStarSolver {
public:
    AStarSolver(Maze& maze);
    void solve();
    void drawSolution(sf::RenderWindow& window);
private:
    Maze& maze;
    std::vector<Cell*> solutionPath;
    std::vector<Cell*> getNeighbors(Cell& cell);
    float heuristic(Cell& a, Cell& b);
};
#endif