#include "AStarSolver.h"
#include <cmath>
#include <algorithm>

AStarSolver::AStarSolver(Maze& maze) : maze(maze) {}

void AStarSolver::solve() {
    // Implement the A* algorithm to solve the maze
}

void AStarSolver::drawSolution(sf::RenderWindow& window) {
    // Draw the solution path
}

std::vector<Cell*> AStarSolver::getNeighbors(Cell& cell) {
    // Get neighbors for the A* algorithm
    return std::vector<Cell*>();
}

float AStarSolver::heuristic(Cell& a, Cell& b) {
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}
