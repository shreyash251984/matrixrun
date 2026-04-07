# MatrixRun — DAA Based Console Game

##  Overview

**MatrixRun** is a console-based grid escape shooter game built using **C/C++**, designed to demonstrate core concepts of **Design and Analysis of Algorithms (DAA)**.

The game represents a 2D grid as a **graph**, where:

* Each cell acts as a **node**
* Movements between cells act as **edges**

The objective is simple:

> Reach the destination while avoiding an intelligent enemy that chases you using shortest path algorithms.


##  Features

*  Graph-based game logic (2D grid → graph)
*  **BFS (Breadth-First Search)** for:

  * Sound wave propagation
  * Enemy detection
*  **Dijkstra’s Algorithm** for:

  * Shortest path calculation
  * Enemy movement
*  Player movement using `W A S D`
*  Enemy AI that chases player dynamically
*  Random map generation with obstacles
*  Win/Lose conditions
*  Continuous game loop



##  Game Mechanics

* Player (`P`) starts at a random location
* Destination (`D`) is randomly generated
* Enemy (`E`) spawns randomly
* Walls (`#`) block movement
* Empty cells (`.`) are traversable

###  Objective:

Reach `D` before the enemy catches you.



##  Algorithms Used

###  Breadth-First Search (BFS)

* Used for **sound wave detection**
* Checks if enemy is reachable from player
* Time Complexity: `O(V + E)`

###  Dijkstra’s Algorithm

* Used for **enemy pathfinding**
* Computes shortest path from enemy to player
* Time Complexity:

  * `O(V^2)` (array-based)
  * `O(E log V)` (priority queue version)



##  Graph Representation

* Grid → Graph
* Cell → Node
* Valid movement → Edge
* Walls → Removed edges



##  Project Structure

MatrixRun/

- main.c
- map.c
- map.h
- player_movement.c
- player.h
- DAA.c
- DAA.h
- main.cpp




## ⚙️ How to Run

### 🔧 Compile

command: 
gcc mainn.c map.c player_movement.c DAA.c -o matrixrun


### ▶ Run

command: 
./matrixrun




##  Controls

| W   | Move Up    |
| S   | Move Down  |
| A   | Move Left  |
| D   | Move Right |


## Game Conditions

###  Win

* Player reaches destination (`D`)

###  Lose

* Enemy reaches player (`P`)



##  DAA Concepts Demonstrated

* Graph modeling using matrices
* BFS traversal
* Shortest path algorithms
* State-based simulation
* Algorithm-driven AI behavior



##  Future Improvements

*  Timer-based sound wave trigger
*  Multiple enemies
*  GUI/Web version
*  Sound effects
*  Smarter enemy AI



##  Author

**MatrixRun Project**
Built as a **DAA Course Project**



##  Acknowledgement

This project demonstrates how theoretical algorithms like **BFS and Dijkstra** can be applied to real-world scenarios such as **game development and AI movement**.

