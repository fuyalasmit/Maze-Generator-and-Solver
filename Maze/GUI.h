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
    sf::Text mazeSizeLabel;
    sf::Text mazeSizeValue;
    sf::RectangleShape increaseSizeButton;
    sf::RectangleShape decreaseSizeButton;
    sf::Text resetButton;
    int mazeSize;
    sf::Texture wallTexture;

    void handleEvents();
    //void draw();
    void initializeGUI();
    void resetMaze();
    bool isGenerateMazeButtonClicked(sf::Vector2i mousePos);
    bool isAStarButtonClicked(sf::Vector2i mousePos);
    bool isIncreaseSizeButtonClicked(sf::Vector2i mousePos);
    bool isDecreaseSizeButtonClicked(sf::Vector2i mousePos);
    bool isResetButtonClicked(sf::Vector2i mousePos);
    void increaseMazeSize();
    void decreaseMazeSize();
};

#endif