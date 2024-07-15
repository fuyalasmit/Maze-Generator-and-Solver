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
    int offsetX = 50; // Adjust offset values as needed
    int offsetY = 50;
    int cellSize = 30; // Assuming cell size is constant
    int wallThickness = 3; // wall thickness

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell& cell = grid[y][x];

            // Draw rectangles for walls based on cell.walls booleans
            float left = x * cellSize + offsetX;
            float top = y * cellSize + offsetY;
            float right = left + cellSize;
            float bottom = top + cellSize;

            sf::RectangleShape topWall(sf::Vector2f(cellSize, wallThickness));
            topWall.setPosition(left, top);
            topWall.setFillColor(sf::Color::White); // Adjust color as needed
            if (cell.walls[0]) {
                window.draw(topWall);
            }

            sf::RectangleShape rightWall(sf::Vector2f(wallThickness, cellSize));
            rightWall.setPosition(right, top);
            rightWall.setFillColor(sf::Color::White); // Adjust color as needed
            if (cell.walls[1]) {
                window.draw(rightWall);
            }

            sf::RectangleShape bottomWall(sf::Vector2f(cellSize, wallThickness));
            bottomWall.setPosition(left, bottom);
            bottomWall.setFillColor(sf::Color::White); // Adjust color as needed
            if (cell.walls[2]) {
                window.draw(bottomWall);
            }

            sf::RectangleShape leftWall(sf::Vector2f(wallThickness, cellSize));
            leftWall.setPosition(left, top);
            leftWall.setFillColor(sf::Color::White); // Adjust color as needed
            if (cell.walls[3]) {
                window.draw(leftWall);
            }
        }
    }
}

void Maze::removeWall(Cell& current, Cell& next) {
    int x = current.getX() - next.getX();
    if (x == 1) {
        current.walls[3] = false;
        next.walls[1] = false;
    }
    else if (x == -1) {
        current.walls[1] = false;
        next.walls[3] = false;
    }

    int y = current.getY() - next.getY();
    if (y == 1) {
        current.walls[0] = false;
        next.walls[2] = false;
    }
    else if (y == -1) {
        current.walls[2] = false;
        next.walls[0] = false;
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
