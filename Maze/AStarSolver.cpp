#include "AStarSolver.h"
#include <algorithm>
#include <cmath>

AStarSolver::AStarSolver(Maze& maze) : maze(maze) {}

void AStarSolver::solve() {
    Cell* start = &maze.grid[0][0];
    Cell* end = &maze.grid[maze.height - 1][maze.width - 1];

    std::priority_queue<std::pair<float, Cell*>, std::vector<std::pair<float, Cell*>>, std::greater<>> openSet;
    openSet.emplace(0.0f, start);

    std::unordered_map<Cell*, Cell*> cameFrom;
    std::unordered_map<Cell*, float> gScore;
    gScore[start] = 0.0f;

    std::unordered_map<Cell*, float> fScore;
    fScore[start] = heuristic(*start, *end);

    while (!openSet.empty()) {
        Cell* current = openSet.top().second;
        openSet.pop();

        if (current == end) {
            reconstructPath(cameFrom, current);
            return;
        }

        for (Cell* neighbor : getNeighbors(*current)) {
            float tentative_gScore = gScore[current] + 1; // All edges have same weight

            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(*neighbor, *end);
                openSet.emplace(fScore[neighbor], neighbor);
            }
        }
    }
}

void AStarSolver::reconstructPath(std::unordered_map<Cell*, Cell*>& cameFrom, Cell* current) {
    solutionPath.clear();
    while (cameFrom.find(current) != cameFrom.end()) {
        solutionPath.push_back(current);
        current = cameFrom[current];
    }
    solutionPath.push_back(current);
    std::reverse(solutionPath.begin(), solutionPath.end());
}

std::vector<Cell*> AStarSolver::getNeighbors(Cell& cell) {
    std::vector<Cell*> neighbors;
    int x = cell.getX();
    int y = cell.getY();

    if (x > 0 && !maze.grid[y][x - 1].walls[1]) neighbors.push_back(&maze.grid[y][x - 1]);
    if (x < maze.width - 1 && !maze.grid[y][x + 1].walls[3]) neighbors.push_back(&maze.grid[y][x + 1]);
    if (y > 0 && !maze.grid[y - 1][x].walls[2]) neighbors.push_back(&maze.grid[y - 1][x]);
    if (y < maze.height - 1 && !maze.grid[y + 1][x].walls[0]) neighbors.push_back(&maze.grid[y + 1][x]);

    return neighbors;
}

float AStarSolver::heuristic(Cell& a, Cell& b) {
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}

void AStarSolver::drawSolution(sf::RenderWindow& window) {
    for (size_t i = 0; i < solutionPath.size() - 1; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(solutionPath[i]->getX() * 20 + 10, solutionPath[i]->getY() * 20 + 10)),
            sf::Vertex(sf::Vector2f(solutionPath[i + 1]->getX() * 20 + 10, solutionPath[i + 1]->getY() * 20 + 10))
        };
        window.draw(line, 2, sf::Lines);
    }
}
