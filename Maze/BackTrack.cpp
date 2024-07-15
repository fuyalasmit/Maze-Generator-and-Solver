#include "BackTrack.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <algorithm>

BackTrack::BackTrack(int width, int height) : width(width), height(height), current(nullptr) {
    for (int y = 0; y < height; ++y) {
        std::vector<Cell> row;
        for (int x = 0; x < width; ++x) {
            row.push_back(Cell(x, y));
        }
        grid.push_back(row);
    }
    current = &grid[0][0];
    current->visited = true;
}

Cell* BackTrack::checkNeighbors(Cell& cell) {
    std::vector<Cell*> neighbors;

    if (cell.y > 0 && !grid[cell.y - 1][cell.x].visited) {
        neighbors.push_back(&grid[cell.y - 1][cell.x]);
    }
    if (cell.y < height - 1 && !grid[cell.y + 1][cell.x].visited) {
        neighbors.push_back(&grid[cell.y + 1][cell.x]);
    }
    if (cell.x > 0 && !grid[cell.y][cell.x - 1].visited) {
        neighbors.push_back(&grid[cell.y][cell.x - 1]);
    }
    if (cell.x < width - 1 && !grid[cell.y][cell.x + 1].visited) {
        neighbors.push_back(&grid[cell.y][cell.x + 1]);
    }

    if (!neighbors.empty()) {
        std::shuffle(neighbors.begin(), neighbors.end(), std::mt19937(std::random_device()()));
        return neighbors.front();
    }
    return nullptr;
}

void BackTrack::removeWalls(Cell& a, Cell& b) {
    int dx = a.x - b.x;
    if (dx == 1) {
        a.leftWall = false;
        b.rightWall = false;
    }
    else if (dx == -1) {
        a.rightWall = false;
        b.leftWall = false;
    }

    int dy = a.y - b.y;
    if (dy == 1) {
        a.topWall = false;
        b.bottomWall = false;
    }
    else if (dy == -1) {
        a.bottomWall = false;
        b.topWall = false;
    }
}

void BackTrack::generateMaze() {
    while (true) {
        Cell* next = checkNeighbors(*current);
        if (next) {
            next->visited = true;
            stack.push_back(current);
            removeWalls(*current, *next);
            current = next;
        }
        else if (!stack.empty()) {
            current = stack.back();
            stack.pop_back();
        }
        else {
            break;
        }
    }
}

void BackTrack::draw(sf::RenderWindow& window, float cellSize) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].draw(window, cellSize);
        }
    }
}

const std::vector<std::vector<Cell>>& BackTrack::getGrid() const {
    return grid;
}
