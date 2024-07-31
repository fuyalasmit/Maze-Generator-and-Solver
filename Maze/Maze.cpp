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

void Maze::generateAnimated(sf::RenderWindow& window, const sf::Texture& wallTexture) {
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
            draw(window, wallTexture); // Pass the texture here
            window.display();

            // Optional: Add a delay to slow down animation
            sf::sleep(sf::milliseconds(1)); // Adjust delay as needed...
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

void Maze::draw(sf::RenderWindow& window, const sf::Texture& wallTexture) {
    int offsetX = 50; // Adjust offset values as needed
    int offsetY = 50;
    int cellSize = 30; // Assuming cell size is constant
    int wallThickness = 5; // wall thickness

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell& cell = grid[y][x];

            // Draw rectangles for walls based on cell.walls booleans
            float left = x * cellSize + offsetX;
            float top = y * cellSize + offsetY;
            float right = left + cellSize;
            float bottom = top + cellSize;

            if (cell.walls[0]) {
                sf::RectangleShape topWall(sf::Vector2f(cellSize, wallThickness));
                topWall.setPosition(left, top);
                topWall.setTexture(&wallTexture);
                window.draw(topWall);
            }

            if (cell.walls[1]) {
                sf::RectangleShape rightWall(sf::Vector2f(wallThickness, cellSize));
                rightWall.setPosition(right, top);
                rightWall.setTexture(&wallTexture);
                window.draw(rightWall);
            }

            if (cell.walls[2]) {
                sf::RectangleShape bottomWall(sf::Vector2f(cellSize, wallThickness));
                bottomWall.setPosition(left, bottom);
                bottomWall.setTexture(&wallTexture);
                window.draw(bottomWall);
            }

            if (cell.walls[3]) {
                sf::RectangleShape leftWall(sf::Vector2f(wallThickness, cellSize));
                leftWall.setPosition(left, top);
                leftWall.setTexture(&wallTexture);
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
