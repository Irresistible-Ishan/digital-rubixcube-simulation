# digital-rubixcube-simulation

This project is a high-performance simulation of a digital Rubik's Cube. It serves as the foundational environment to be used for Reinforcement Learning (RL) model training (specifically aiming for a fully unsupervised solving agent in a separate repository).

This project isn't just about rendering a Rubik's cube; it's an exploration of the series of RL methods required to approach and solve complex, sparse-reward environments.

> **Note:** This is an educational and learning-based project, not a commercial product.

---

## Current Progress & Iterations
- **Initial Attempts:** 
  - The first attempt (`simulationinC.c`) used a complex "table cloth method" with 7x7 char arrays to track faces.
  - The second version (`engine.c`) used a simpler 6x9 character array but relied on string parsing ('r', 'l', 'u') which is slow for RL.
  - The latest C version (`cube_engine.c`) transitioned to a purely numerical `int cube[6][9]` system (0-5 representing colors) and integer-based moves, optimizing for maximum speed.
- **Python-C Integration:** The C engine was compiled into a Dynamic Link Library (`cube_engine.dll`), allowing interaction with Python via `ctypes` (as tested in `engineRemoteTest.py`).

---
(NOTE : the text is structured using AI but this is not by AI)
## Upcoming Engine Architecture (The Fresh Start)

While the legacy C engine was highly optimized for speed, its hardcoded update logic made scaling to advanced moves (like `M`, `E`, `S` slice moves) and full cube rotations overly verbose and mathematically inefficient. Continuing on that path risked severe architectural debt. 

Therefore, we are shifting to a **cleaner, completely fresh architecture** built from the ground up, designed specifically to balance simulation completeness with scalable RL state extraction:

### 1. Phased Development Strategy
To avoid architectural bottlenecks, development is strictly split into phases:
- **Phase 1 (The Core Simulation):** Achieve a 100% mathematically correct simulation supporting *all* moves (Normal: `L`, `R`, `U`, `D`, `F`, `B`; Slices: `M`, `E`, `S`; and Cube Rotations: `x`, `y`, `z`) and scramble generators.
- **Phase 2 (The RL Integration):** Only after the core movement system is fully validated will we attach the Python RL loop and HER buffer.

### 2. Separation of Concerns (State vs. Logic)
The new engine strictly separates the raw **cube state** from the **move relationship logic**. 
- **The State:** The cube is represented simply as six separate 3x3 2D matrices.
- **The Rationale:** Earlier ideas explored a full 3D coordinate tensor or a 7x7 hybrid "table cloth" array. However, a 3D structure complicates matrix rotations and RL training-state extraction unnecessarily. The 6x(3x3) 2D approach is cleaner, easier to debug, and avoids the maintenance nightmare of expanding hybrid arrays for slice moves.

### 3. Graph-Based Adjacency Matrix (The Core Innovation)
To eliminate hardcoded neighbor-updating functions for every possible move, we are implementing a **Node Connection Matrix** inspired by Graph Theory.
- Instead of manually writing logic like *"if Front rotates, update Top's bottom row, Right's left column..."*, we define a generalized 6x6 spatial relationship matrix:
  ```
       W   O   R   B   G   Y
    W  0  -1  ...
    O      0
    R          0
    B              0
    G                  0
  ```
- **Spatial Mapping Values:** `0` (Self/Unconnected), `-1` (Left), `+1` (Right), `+2` (Up), `-2` (Down), `3` (Direct Opposite).
- **How it works:** When a specific move type is triggered (e.g., a slice move where the middle block moves right), the engine queries this generalized adjacency matrix. It automatically identifies the `current`, `top opposite`, and `down` faces mathematically connected to the axis of rotation, running a generalized update function across them.

### 4. Modular Move Processing
Move execution logic is broken down into specific operational pipelines:
- `normal_rotate()`
- `slice_move()`
- `cube_rotate()`
Because the generalized adjacency matrix inherently knows the topology of the cube, these modular functions simply ask the graph *who* to update, massively reducing boilerplate code.

---

## 🧠 RL Strategy Defined
After evaluating DQN, Vanilla PPO, and DeepCubeA, the chosen path forward is using **Hindsight Experience Replay (HER)** combined with sparse rewards (-1 for every state except the solved state). This avoids the "local optimum" trap of dense rewards.

---

## 📁 File Explanations (Current Repository)

- **`cube_engine.c` / `cube_engine.dll`**: The legacy optimized C engine and its compiled library.
- **`simulationinC.c` & `engine.c` / `enginev2.c`**: Iterative versions of the C engine showcasing the evolution of the array logic.
- **`engineRemoteTest.py` & `engine_newApproach.py`**: Python scripts testing the `ctypes` bindings for the C DLL.
- **`docs.txt`**: Extensive planning documentation containing move mapping, matrix rotation logic, and the theoretical evaluation of different RL algorithms (DQN, PPO, HER, DeepCubeA).

---

## 🚀 Next Steps
- **Build the New Engine:** Implement the new graph-based 3x3 matrix architecture with full support for slice moves (M, E) and cube rotations.
- **RL Agent Implementation:** Build the Python RL loop that will interface with the new engine.
- **HER Replay Buffer:** Implement the Hindsight Experience Replay memory buffer to solve the sparse reward problem.
- **Neural Network Architecture:** Design the Policy/Value network to predict the best moves.
- **Training:** Run the training loop and monitor for convergence.