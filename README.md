# 🐉 Dragon Training System
### How to Train Your Dragon – Part I

## 📖 Project Overview

This project implements a **dragon–warrior simulation system** inspired by the assignment  
*How to Train Your Dragon*.

The program simulates a warrior traversing a **10×10 grid-based map**, engaging in battles with different types of dragons, managing special dragon effects, and computing the **total time required** to complete all objectives and defeat the dragons.

The simulation includes:
- Detection of special locations and entities on the map
- Battle time computation
- Handling of dragons with special behavioral effects
- Health point (HP) updates and elimination state tracking

---

## 🏗 Project Structure

```
Dragon-Assignment
├── dragon.h
├── dragon.cpp
├── main.h
├── main.cpp
├── run.sh
├── tnc_tc_01_input.txt
├── tnc_tc_02_input.txt
├── ...
├── tnc_tc_14_input.txt
├── main.exe
└── README.md
```

---

## ⚙ Core Functionalities

### 1️⃣ Map Processing

- Fixed-size **10×10 integer matrix**
- Identification of special positions, including:
  - Heritage location
  - Key location
  - Time Illusion Dragon
  - Chaos Reversing Dragon

These positions directly affect traversal logic and battle outcomes.

---

### 2️⃣ Battle Simulation

Core function:
```cpp
void totalTime(int map[10][10], int warriorDamage, int HP);
```

Responsibilities:
- Move warrior across map
- Calculate battle time
- Reduce HP after each encounter
- Track defeated dragons
- Apply special dragon effects

---

### 3️⃣ Special Dragon Effects

- 🌀 Time Illusion Dragon - Modify time calculation during battles.
- 🔄 Chaos Reversing Dragon - Alters movement direction or traversal logic.

Each special dragon introduces additional constraints that must be handled explicitly during simulation.
---

### 4️⃣ Supporting Functions

Examples:
- `findHeritageLocation(...)`
- `findKeyLocation(...)`
- `findTimeIllusionDragon(...)`
- `findChaosReversingDragon(...)`
- `CalculateTime(...)`
- `CalculateHP(...)`
- `ForwardorBackward(...)`

---

## 🚀 How to Compile & Run

### Compile (Unix environment)

```bash
g++ -o main main.cpp dragon.cpp -I . -std=c++11
```

### Run

```bash
./main tnc_tc_01_input.txt
```

⚠ The assignment is evaluated on Unix.

---

## 📊 Algorithm Design

- Map traversal: O(N²)
- Battle simulation: O(N²)
- State tracking with 2D boolean array
- Greedy traversal logic

Worst-case time complexity: O(N²), where N =  10.

---

## 🎯 Learning Outcomes

- 2D array manipulation
- Simulation-based problem solving
- Function decomposition
- Structured programming
- State management in C++

---

## 📌 Notes

- No additional headers allowed (follow assignment rules).
- Code must compile using C++11.
- All logic implemented inside `dragon.cpp`.

---
