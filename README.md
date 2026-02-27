# 🐉 DRAGON TRAINING SYSTEM – HỆ THỐNG LUYỆN RỒNG 

## 📖 Project Overview | Tổng quan dự án

This project implements a dragon–warrior simulation system inspired by *How to Train Your Dragon*.

The program processes a 10x10 map, calculates battle time, manages special dragon effects, and determines the final total time required to defeat dragons and complete objectives.

Dự án mô phỏng hệ thống chiến đấu giữa chiến binh và rồng trên bản đồ 10x10, bao gồm:
- Tìm vị trí vật phẩm đặc biệt
- Tính thời gian chiến đấu
- Xử lý rồng hiệu ứng đặc biệt
- Cập nhật HP và trạng thái tiêu diệt

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

## ⚙ Core Functionalities | Chức năng chính

### 1️⃣ Map Processing
- 10x10 integer matrix
- Special positions:
  - Heritage location
  - Key location
  - Time Illusion Dragon
  - Chaos Reversing Dragon

---

### 2️⃣ Battle Simulation

Function:
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

- 🌀 Time Illusion Dragon
- 🔄 Chaos Reversing Dragon

Each special dragon affects movement or battle calculation differently.

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

Worst-case time complexity: O(N²)

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
