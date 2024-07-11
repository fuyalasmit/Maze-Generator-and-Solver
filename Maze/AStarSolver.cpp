#include "AStarSolver.h"

AStarSolver::AStarSolver(Maze& maze) : maze(maze) {}

void AStarSolver::solve() {
    // Implement the A* algorithm to solve the maze
    // Initialize data structures, perform A* search, and populate solutionPath
}

void AStarSolver::drawSolution(sf::RenderWindow& window) {
    // Draw the solution path on the SFML window
    for (Cell* cell : solutionPath) {
        // Example: Highlight cell or draw connecting lines to visualize the path
        // Adjust based on your specific visualization needs
        // Example: sf::RectangleShape, sf::Vertex, etc.
    }
}



std::vector<Cell*> AStarSolver::getNeighbors(Cell& cell) {
    // Get neighboring cells for the A* algorithm
    // Implement logic to return valid neighbors based on maze configuration
    return std::vector<Cell*>();
}

float AStarSolver::heuristic(Cell& a, Cell& b) {
    // Heuristic function for A* algorithm
    // Implement a suitable heuristic to estimate distance between cells a and b
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}
