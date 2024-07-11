#include "Maze.h"
#include <stack>
#include <cstdlib>
#include <ctime>

Maze::Maze(int width, int height) : width(width), height(height) {
    srand(static_cast<unsigned int>(time(0)));
    for (int y = 0; y < height; ++y) {
        std::vector<Cell> row;
        for (int x = 0; x < width; ++x) {
            row.push_back(Cell(x, y));
        }
        grid.push_back(row);
    }
}

/*
void Maze::generate() {
    std::stack<Cell*> stack;
    Cell* current = &grid[0][0];
    current->visited = true;

    while (true) {
        std::vector<Cell*> neighbors = getUnvisitedNeighbors(*current);
        if (!neighbors.empty()) {
            Cell* next = neighbors[rand() % neighbors.size()];
            stack.push(current);
            removeWall(*current, *next);
            current = next;
            current->visited = true;
        }
        else if (!stack.empty()) {
            current = stack.top();
            stack.pop();
        }
        else {
            break;
        }
    }
}
*/


void Maze::generateAnimated(sf::RenderWindow& window) {
    std::stack<Cell*> stack;
    Cell* current = &grid[0][0];
    current->visited = true;

    while (true) {
        std::vector<Cell*> neighbors = getUnvisitedNeighbors(*current);
        if (!neighbors.empty()) {
            Cell* next = neighbors[rand() % neighbors.size()];
            stack.push(current);
            removeWall(*current, *next);
            current = next;
            current->visited = true;

            // Redraw the maze after each modification
            window.clear();
            draw(window);
            window.display();

            // Optional: Add a delay to slow down animation
            sf::sleep(sf::milliseconds(10)); // Adjust delay as needed...
        }
        else if (!stack.empty()) {
            current = stack.top();
            stack.pop();
        }
        else {
            break;
        }
    }
}



void Maze::draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell& cell = grid[y][x];
            int cellSize = 20;
            sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
            rectangle.setPosition(x * cellSize, y * cellSize);

            if (cell.walls[0]) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x * cellSize, y * cellSize)),
                    sf::Vertex(sf::Vector2f((x + 1) * cellSize, y * cellSize))
                };
                window.draw(line, 2, sf::Lines);
            }
            if (cell.walls[1]) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f((x + 1) * cellSize, y * cellSize)),
                    sf::Vertex(sf::Vector2f((x + 1) * cellSize, (y + 1) * cellSize))
                };
                window.draw(line, 2, sf::Lines);
            }
            if (cell.walls[2]) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f((x + 1) * cellSize, (y + 1) * cellSize)),
                    sf::Vertex(sf::Vector2f(x * cellSize, (y + 1) * cellSize))
                };
                window.draw(line, 2, sf::Lines);
            }
            if (cell.walls[3]) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x * cellSize, (y + 1) * cellSize)),
                    sf::Vertex(sf::Vector2f(x * cellSize, y * cellSize))
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }
}

void Maze::removeWall(Cell& current, Cell& next) {
    int x = current.getX() - next.getX();
    if (x == 1) {
        current.removeWall(3);
        next.removeWall(1);
    }
    else if (x == -1) {
        current.removeWall(1);
        next.removeWall(3);
    }

    int y = current.getY() - next.getY();
    if (y == 1) {
        current.removeWall(0);
        next.removeWall(2);
    }
    else if (y == -1) {
        current.removeWall(2);
        next.removeWall(0);
    }
}

std::vector<Cell*> Maze::getUnvisitedNeighbors(Cell& cell) {
    std::vector<Cell*> neighbors;
    int x = cell.getX();
    int y = cell.getY();

    if (x > 0 && !grid[y][x - 1].visited) neighbors.push_back(&grid[y][x - 1]);
    if (x < width - 1 && !grid[y][x + 1].visited) neighbors.push_back(&grid[y][x + 1]);
    if (y > 0 && !grid[y - 1][x].visited) neighbors.push_back(&grid[y - 1][x]);
    if (y < height - 1 && !grid[y + 1][x].visited) neighbors.push_back(&grid[y + 1][x]);

    return neighbors;
}
