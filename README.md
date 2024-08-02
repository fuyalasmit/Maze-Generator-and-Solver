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

4. **Run the application**:
    - Execute the compiled binary to start the application.

## Usage

- Use the GUI buttons to generate a new maze or solve an existing one.
- Adjust the maze size using the provided options.
- Reset the maze to clear and start a new session.

## Technologies Used

- **C++**: Core programming language used for implementing OOP concepts and algorithms.
- **SFML**: Graphics library used for rendering the maze and UI components.

## Algorithms

### Maze Generation

- **Recursive Backtracking (DFS)**: The maze is generated using a recursive backtracking algorithm, which follows a depth-first search approach. Starting from an initial cell, it recursively visits unvisited neighboring cells, carving paths and backtracking when no unvisited neighbors remain. This method ensures that all cells are visited and connected, resulting in a perfect maze with no loops.

### Maze Solving

- **A* Algorithm**: The A* algorithm is used for solving the maze. It is a pathfinding algorithm that finds the shortest path from the start point to the end point. A* uses a heuristic to prioritize paths that seem most promising, making it efficient and effective for solving mazes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For any questions or suggestions, please contact me at [asmitphuyal4040@gmail.com].
