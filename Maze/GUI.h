#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Maze.h"
#include "AStarSolver.h"

class GUI {
public:
    GUI(int width, int height);
    void run();

private:
    sf::RenderWindow window;
    Maze maze;
    AStarSolver solver;
    sf::Font font;
    sf::Text generateMazeButton;
    sf::Text aStarButton;
    bool isSolving;

    void handleEvents();
    void draw();
    void initializeGUI();
};

#endif
