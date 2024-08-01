#ifndef CELL_H
#define CELL_H

class Cell {
private:
    int x, y;

public:
    Cell(int x, int y);
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left.. 0,1,2,3 ko order ma
    // array of 4 booleans representing the presence of walls on the top, right, bottom, and left sides of the cell.

    int getX() const;   //x ko value change garna pardeina so.
    int getY() const;
    void removeWall(int direction);  //Removes the wall in the specified direction (0 for top, 1 for right, 2 for bottom, 3 for left).
    bool hasAllWalls() const;

};

#endif
