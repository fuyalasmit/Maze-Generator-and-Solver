#include "GUI.h"

GUI::GUI(int width, int height)
    : window(sf::VideoMode(width, height), "Maze Generator and Solver"),
    maze(20, 20), solver(maze), mazeSize(20) {
    if (!font.loadFromFile("arial.ttf")) {
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
    generateMazeButton.setPosition(820, 50);

    aStarButton.setFont(font);
    aStarButton.setString("Solve Maze");
    aStarButton.setCharacterSize(24);
    aStarButton.setFillColor(sf::Color::White);
    aStarButton.setPosition(820, 100);

    mazeSizeLabel.setFont(font);
    mazeSizeLabel.setString("Maze Size:");
    mazeSizeLabel.setCharacterSize(24);
    mazeSizeLabel.setFillColor(sf::Color::White);
    mazeSizeLabel.setPosition(820, 150);

    mazeSizeValue.setFont(font);
    mazeSizeValue.setString(std::to_string(mazeSize));
    mazeSizeValue.setCharacterSize(24);
    mazeSizeValue.setFillColor(sf::Color::White);
    mazeSizeValue.setPosition(950, 150);

    increaseSizeButton.setSize(sf::Vector2f(30, 30));
    increaseSizeButton.setFillColor(sf::Color(21, 245, 5));
    increaseSizeButton.setPosition(1000, 150);

    decreaseSizeButton.setSize(sf::Vector2f(30, 30));
    decreaseSizeButton.setFillColor(sf::Color::Red);
    decreaseSizeButton.setPosition(1050, 150);

    resetButton.setFont(font);
    resetButton.setString("Reset Maze");
    resetButton.setCharacterSize(24);
    resetButton.setFillColor(sf::Color::White);
    resetButton.setPosition(820, 200);

}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear();
        maze.draw(window);
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
                maze.generateAnimated(window);
            }
            else if (isAStarButtonClicked(mousePos)) {
                solver.solve();
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
    if (mazeSize < 50) {  // Set a reasonable upper limit
        mazeSize++;
        maze = Maze(mazeSize, mazeSize);  // Recreate maze with new size
        mazeSizeValue.setString(std::to_string(mazeSize));
    }
}

void GUI::decreaseMazeSize() {
    if (mazeSize > 5) {  // Set a reasonable lower limit
        mazeSize--;
        maze = Maze(mazeSize, mazeSize);  // Recreate maze with new size
        mazeSizeValue.setString(std::to_string(mazeSize));
    }
}

