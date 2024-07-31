#include "AStarSolver.h"
#include "GUI.h"

GUI::GUI(int width, int height)
    : window(sf::VideoMode(width, height), "Maze Generator and Solver"),
    maze(15, 15), solver(maze), mazeSize(15) {
    if (!font.loadFromFile("E:/vs/Maze/Maze/arial.ttf")) {
        // Handle error
    }
    if (!wallTexture.loadFromFile("E:/vs/Maze/Maze/grass.png")) {
        // Handle error
    }
    initializeGUI();
}

void GUI::initializeGUI() {
    // Initialize buttons and labels
    generateMazeButton.setFont(font);
    generateMazeButton.setString("Generate Maze");
    generateMazeButton.setCharacterSize(24);
    generateMazeButton.setFillColor(sf::Color::White);
    generateMazeButton.setPosition(1020, 50);

    aStarButton.setFont(font);
    aStarButton.setString("Solve Maze");
    aStarButton.setCharacterSize(24);
    aStarButton.setFillColor(sf::Color::White);
    aStarButton.setPosition(1020, 100);

    mazeSizeLabel.setFont(font);
    mazeSizeLabel.setString("Maze Size:");
    mazeSizeLabel.setCharacterSize(24);
    mazeSizeLabel.setFillColor(sf::Color::White);
    mazeSizeLabel.setPosition(1020, 150);

    mazeSizeValue.setFont(font);
    mazeSizeValue.setString(std::to_string(mazeSize));
    mazeSizeValue.setCharacterSize(24);
    mazeSizeValue.setFillColor(sf::Color::White);
    mazeSizeValue.setPosition(1150, 150);

    increaseSizeButton.setSize(sf::Vector2f(30, 30));
    increaseSizeButton.setFillColor(sf::Color(21, 245, 5));
    increaseSizeButton.setPosition(1200, 150);

    decreaseSizeButton.setSize(sf::Vector2f(30, 30));
    decreaseSizeButton.setFillColor(sf::Color::Red);
    decreaseSizeButton.setPosition(1250, 150);

    resetButton.setFont(font);
    resetButton.setString("Reset Maze");
    resetButton.setCharacterSize(24);
    resetButton.setFillColor(sf::Color::White);
    resetButton.setPosition(1020, 200);

}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear();
        maze.draw(window, wallTexture);
        solver.drawSolution(window);//added lines of claude code
        window.draw(generateMazeButton);
        window.draw(aStarButton);
        window.draw(mazeSizeLabel);
        window.draw(mazeSizeValue);
        window.draw(increaseSizeButton);
        window.draw(decreaseSizeButton);
        window.draw(resetButton);
        window.display();
    }
}


void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed: {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (isGenerateMazeButtonClicked(mousePos)) {
                maze.generateAnimated(window, wallTexture);
            }
            else if (isAStarButtonClicked(mousePos)) {
                solver.solve(); // Implement this function for A* pathfinding
            }
            else if (isIncreaseSizeButtonClicked(mousePos)) {
                increaseMazeSize();
            }
            else if (isDecreaseSizeButtonClicked(mousePos)) {
                decreaseMazeSize();
            }
            else if (isResetButtonClicked(mousePos)) {
                resetMaze();
            }
            break;
        }
        case sf::Event::MouseMoved: {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (isGenerateMazeButtonClicked(mousePos)) {
                generateMazeButton.setFillColor(sf::Color::Yellow); // Hover color
            }
            else {
                generateMazeButton.setFillColor(sf::Color::White);  // Default color
            }
            if (isAStarButtonClicked(mousePos)) {
                aStarButton.setFillColor(sf::Color::Yellow); // Hover color
            }
            else {
                aStarButton.setFillColor(sf::Color::White);  // Default color
            }
            if (isResetButtonClicked(mousePos)) {
                resetButton.setFillColor(sf::Color::Yellow); // Hover color
            }
            else {
                resetButton.setFillColor(sf::Color::White);  // Default color
            }
            break;
        }
        default:
            break;
        }
    }
}


bool GUI::isGenerateMazeButtonClicked(sf::Vector2i mousePos) {
    return generateMazeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GUI::isAStarButtonClicked(sf::Vector2i mousePos) {
    return aStarButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GUI::isIncreaseSizeButtonClicked(sf::Vector2i mousePos) {
    return increaseSizeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GUI::isDecreaseSizeButtonClicked(sf::Vector2i mousePos) {
    return decreaseSizeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

bool GUI::isResetButtonClicked(sf::Vector2i mousePos) {
    return resetButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void GUI::resetMaze() {
    maze = Maze(mazeSize, mazeSize);  // Recreate maze with the same size
}

void GUI::increaseMazeSize() {
    if (mazeSize < 50) {  //upper limit
        mazeSize++;
        maze = Maze(mazeSize, mazeSize);  // Recreate maze with new size
        mazeSizeValue.setString(std::to_string(mazeSize));
    }
}

void GUI::decreaseMazeSize() {
    if (mazeSize > 5) {  //lower limit
        mazeSize--;
        maze = Maze(mazeSize, mazeSize);  // Recreate maze with new size
        mazeSizeValue.setString(std::to_string(mazeSize));
    }
}
