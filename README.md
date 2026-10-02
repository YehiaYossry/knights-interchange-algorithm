# 6-Knights Interchange Algorithm

An iterative improvement algorithm implemented in C++ to solve the **Knight Interchange Problem**.

The objective is to swap the positions of 3 White knights and 3 Black knights on a grid so that the White knights move to the bottom target positions and the Black knights move to the top target positions, following standard chess knight movements without any two knights sharing the same square.

---

## 📌 Problem Overview
* **Initial State:** 3 White knights positioned at the top and 3 Black knights at the bottom.
* **Target State:** 3 Black knights positioned at the top and 3 White knights at the bottom.
* **Constraints:**
  * Knights move using standard chess $L$-shaped jumps.
  * No two knights can occupy the same square at any point in time.
  * Solved using an **Iterative Improvement Algorithm** (Local Search / Heuristic Evaluation).

---

## 🛠️ Project Structure
* `handson4.cpp` — Main C++ source code containing board state representation, legal move generation, heuristic evaluation, and iterative search logic.

---

## 🚀 How to Run

### 1. Compile
Open your terminal inside the project directory and run:

```bash
g++ handson4.cpp -o knight_solver
```

### 2. Execute
Run the compiled executable:

#### On Windows (PowerShell / Command Prompt):
```powershell
.\knight_solver.exe
```

#### On Linux / macOS:
```bash
./knight_solver
```

---

## 🎯 Algorithm & Approach
1. **State Space Representation:** Tracks the 2D grid matrix and the precise locations of all 6 knights.
2. **Move Validation:** Evaluates legal $L$-shaped jumps into empty squares to strictly enforce the single-occupancy constraint.
3. **Iterative Search:** Evaluates intermediate board states using heuristic scoring to guide the knights toward their goal state.