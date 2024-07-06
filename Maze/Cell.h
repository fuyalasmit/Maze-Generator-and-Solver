#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell(int x, int y);
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left

    int getX() const;
    int getY() const;
    void removeWall(int direction);
    bool hasAllWalls() const;

private:
    int x, y;
};

#endif
