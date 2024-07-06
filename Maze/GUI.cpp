#include "GUI.h"

GUI::GUI(int width, int height)
    : window(sf::VideoMode(width, height), "Maze Generator and Solver"),
    maze(20, 20), solver(maze), isSolving(false) {
    if (!font.loadFromFile("E:/vs/Maze/Maze/arial.ttf")) {
        // Handle error
    }
    initializeGUI();
}

void GUI::initializeGUI() {
    generateMazeButton.setFont(font);
    generateMazeButton.setString("Generate Maze");
    generateMazeButton.setCharacterSize(24);
    generateMazeButton.setFillColor(sf::Color::Green);
    generateMazeButton.setPosition(820, 50);

    aStarButton.setFont(font);
    aStarButton.setString("A* Solver");
    aStarButton.setCharacterSize(24);
    aStarButton.setFillColor(sf::Color::Green);
    aStarButton.setPosition(820, 100);
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear();
        maze.draw(window);
        if (isSolving) {
            solver.drawSolution(window);
        }
        window.draw(generateMazeButton);
        window.draw(aStarButton);
        window.display();
    }
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (generateMazeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                maze.generate();
                isSolving = false;
            }
            else if (aStarButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                solver.solve();
                isSolving = true;
            }
        }
    }
}

void GUI::draw() {
    maze.draw(window);
    if (isSolving) {
        solver.drawSolution(window);
    }
    window.draw(generateMazeButton);
    window.draw(aStarButton);
}
