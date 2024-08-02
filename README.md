# Maze Generator and Solver

This project is a maze generator and solver developed as part of a third-semester computer engineering course. It demonstrates object-oriented programming (OOP) concepts using C++ and SFML for graphics rendering.

## Features

- **Maze Generation**: Uses a recursive backtracking algorithm to create complex and solvable mazes.
- **Maze Solving**: Implements the A* algorithm to efficiently find the shortest path from the start to the end of the maze.
- **Graphical User Interface**: Interactive UI to generate and solve mazes, adjust maze size, and reset the maze.

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/fuyalasmit/Maze-Generator-and-Solver.git
    ```

2. **Install SFML**:
    Follow the instructions for your operating system from the [SFML website](https://www.sfml-dev.org/download.php).

3. **Build the project**:
    - Ensure SFML is correctly linked in your build system (e.g., Visual Studio, CMake, etc.).
    - Compile the source files (`AStarSolver.cpp`, `BackTrack.cpp`, `GUI.cpp`, `Cell.cpp`).
    - Make sure to edit constructor in maze.cpp file, since it contains path of font and image.

4. **Run the application**:
    - Execute the compiled binary to start the application.

## Usage

- **Generate Maze**: Click the "Generate Maze" button to create a new random maze.
- **Solve Maze**: Click the "Solve Maze" button to solve the current maze using the A* algorithm.
- **Adjust Maze Size**: Use the increase/decrease size buttons to change the maze dimensions.
- **Reset Maze**: Click "Reset Maze" to clear the current maze and reset the size.

## Project Structure

- **main.cpp**: Entry point of the application.
- **GUI.h / GUI.cpp**: Handles the graphical user interface and event processing.
- **Maze.h / Maze.cpp**: Contains the logic for maze generation and rendering.
- **Cell.h / Cell.cpp**: Defines the properties of each cell in the maze.
- **AStarSolver.h / AStarSolver.cpp**: Implements the A* algorithm to solve the maze.

## Customization

You can customize the appearance of the maze by modifying the `wallTexture` and adjusting the size of the cells in `Maze.cpp`. The colors and font used in the GUI can be changed in `GUI.cpp`.

## Algorithms

### Maze Generation

- **Recursive Backtracking (DFS)**: The maze is generated using a recursive backtracking algorithm, which follows a depth-first search approach. Starting from an initial cell, it recursively visits unvisited neighboring cells, carving paths and backtracking when no unvisited neighbors remain. This method ensures that all cells are visited and connected, resulting in a perfect maze with no loops.

### Maze Solving

- **A\* Algorithm**: The A* algorithm is used for solving the maze. It is a pathfinding algorithm that finds the shortest path from the start point to the end point. A* uses a heuristic to prioritize paths that seem most promising, making it efficient and effective for solving mazes.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Contact

For any questions or suggestions, please contact me [here](mailto:asmitphuyal4040@gmail.com).
