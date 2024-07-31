#include "AStarSolver.h"
#include <algorithm>
#include <cmath>

AStarSolver::AStarSolver(Maze& maze) : maze(maze) {}

void AStarSolver::solve() {
    solutionPath.clear();  // Clear any previous solution
    struct Node {
        Cell* cell;
        float g, f;
        Node* parent;
        Node(Cell* c, float g, float f, Node* p) : cell(c), g(g), f(f), parent(p) {}
    };

    auto compare = [](const Node* a, const Node* b) { return a->f > b->f; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> openSet(compare);
    std::vector<Node*> allNodes;

    Cell* start = &maze.grid[0][0];
    Cell* goal = &maze.grid[maze.height - 1][maze.width - 1];

    Node* startNode = new Node(start, 0, heuristic(*start, *goal), nullptr);
    openSet.push(startNode);
    allNodes.push_back(startNode);

    std::vector<std::vector<bool>> closedSet(maze.height, std::vector<bool>(maze.width, false));

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->cell == goal) {
            // Reconstruct path
            while (current != nullptr) {
                solutionPath.push_back(current->cell);
                current = current->parent;
            }
            std::reverse(solutionPath.begin(), solutionPath.end());
            break;
        }

        closedSet[current->cell->getY()][current->cell->getX()] = true;

        for (Cell* neighbor : getNeighbors(*current->cell)) {
            if (closedSet[neighbor->getY()][neighbor->getX()]) continue;

            float tentativeG = current->g + 1;

            Node* neighborNode = nullptr;
            bool isNew = true;

            for (Node* node : allNodes) {
                if (node->cell == neighbor) {
                    neighborNode = node;
                    isNew = false;
                    break;
                }
            }

            if (isNew) {
                neighborNode = new Node(neighbor, tentativeG, tentativeG + heuristic(*neighbor, *goal), current);
                allNodes.push_back(neighborNode);
                openSet.push(neighborNode);
            }
            else if (tentativeG < neighborNode->g) {
                neighborNode->g = tentativeG;
                neighborNode->f = tentativeG + heuristic(*neighbor, *goal);
                neighborNode->parent = current;

                // Re-add to openSet to update position
                openSet.push(neighborNode);
            }
        }
    }

    // Clean up memory
    for (Node* node : allNodes) {
        delete node;
    }
}

void AStarSolver::drawSolution(sf::RenderWindow& window) {
    if (solutionPath.empty()) return;

    sf::VertexArray lines(sf::LineStrip, solutionPath.size());
    int cellSize = 30; // Adjust this to match your maze cell size
    int offsetX = 50; // Adjust these offsets to match your maze drawing
    int offsetY = 50;

    for (size_t i = 0; i < solutionPath.size(); ++i) {
        float x = solutionPath[i]->getX() * cellSize + cellSize / 2 + offsetX;
        float y = solutionPath[i]->getY() * cellSize + cellSize / 2 + offsetY;
        lines[i].position = sf::Vector2f(x, y);
        lines[i].color = sf::Color::Red;
    }

    window.draw(lines);
}

std::vector<Cell*> AStarSolver::getNeighbors(Cell& cell) {
    std::vector<Cell*> neighbors;
    int x = cell.getX();
    int y = cell.getY();

    if (x > 0 && !cell.walls[3]) neighbors.push_back(&maze.grid[y][x - 1]);
    if (x < maze.width - 1 && !cell.walls[1]) neighbors.push_back(&maze.grid[y][x + 1]);
    if (y > 0 && !cell.walls[0]) neighbors.push_back(&maze.grid[y - 1][x]);
    if (y < maze.height - 1 && !cell.walls[2]) neighbors.push_back(&maze.grid[y + 1][x]);

    return neighbors;
}

float AStarSolver::heuristic(Cell& a, Cell& b) {
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}