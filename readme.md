MatrixRun — DAA Based Console Game

Overview

**MatrixRun** is a console-based grid escape game built using **C/C++**, designed to demonstrate core concepts of **Design and Analysis of Algorithms (DAA)**.

The game models a 2D grid as a graph:

* Each cell represents a **node**
* Movements between cells represent **edges**

**Objective:**
Reach the destination while avoiding an intelligent enemy that chases you using shortest path algorithms.

---

Features

* Graph-based game logic (Grid → Graph)
* 🔎 **BFS (Breadth-First Search)** for:

  * Sound wave propagation
  * Enemy detection
* ⚡ **Dijkstra’s Algorithm** for:

  * Shortest path calculation
  * Enemy movement
* Player movement using **W A S D**
* Dynamic enemy AI
* Random map generation with obstacles
* Win/Lose conditions
* Continuous game loop

---

Game Mechanics

* Player (**P**) starts at a random position
* Destination (**D**) is randomly generated
* Enemy (**E**) spawns randomly
* Walls (**#**) block movement
* Empty cells (**.**) are traversable

 **Goal:** Reach **D** before the enemy catches you

---

Algorithms Used

Breadth-First Search (BFS)

* Used for **enemy detection**
* Checks reachability between player and enemy
* Time Complexity: **O(V + E)**

Dijkstra’s Algorithm

* Used for **enemy pathfinding**
* Computes shortest path from enemy to player
* Time Complexity:

  * **O(V²)** (current implementation)
  * **O(E log V)** (optimized version)

---

Graph Representation

* Grid → Graph
* Cell → Node
* Valid move → Edge
* Walls → Blocked edges

---

Project Structure

```
MatrixRun/
├── main.c
├── main.cpp
├── map.c
├── map.h
├── player_movement.c
├── player.h
├── DAA.c
├── DAA.h
```

---

How to Run

Compile

```bash
gcc main.c map.c player_movement.c DAA.c -o matrixrun
```

Run

```bash
./matrixrun
```

---

Controls

| Key | Action     |
| --- | ---------- |
| W   | Move Up    |
| S   | Move Down  |
| A   | Move Left  |
| D   | Move Right |

---

Game Conditions

Win

* Player reaches destination (**D**)

Lose

* Enemy catches the player (**P**)

---

DAA Concepts Demonstrated

* Graph modeling using matrices
* BFS traversal
* Shortest path algorithms
* State-based simulation
* Algorithm-driven AI behavior

---

Future Improvements

* Timer-based sound wave system
* Multiple enemies
* GUI/Web version
* Sound effects
* Advanced enemy AI

---

Author
ANKIT KUMAR SINGH,
SHREYASH RAWAT,
DISHAV KUMAR,
HARSH RAJ

---

Acknowledgement

This project demonstrates how theoretical algorithms like **BFS** and **Dijkstra** can be applied to real-world scenarios such as **game development and AI movement**.
