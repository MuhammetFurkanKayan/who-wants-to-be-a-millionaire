# Who Wants to Be a Millionaire? — Console Edition

A fully-featured, console-based implementation of the iconic **"Who Wants to Be a Millionaire?"** game show, written in **C**.

---

## About

This project brings the excitement of *Who Wants to Be a Millionaire?* directly to your terminal. Players answer 12 increasingly difficult multiple-choice questions to climb the prize ladder from **2,000 TL** all the way up to **1,000,000 TL** — just like the real show. The game features a database of **1,900+ questions** loaded from a CSV file, random question selection for each level, two classic lifelines, and a persistent leaderboard that records every player's result.

---

## Features

- **12-Level Prize Ladder** — Prizes escalate from 2,000 TL to 1,000,000 TL across 12 questions.
- **1,900+ Question Database** — Questions are stored in `question.csv`, categorized by difficulty level (1–12), and selected randomly each playthrough for high replayability.
- **Two Lifelines**
  - **50/50** — Eliminates two incorrect options, leaving the correct answer and one distractor.
  - **Double Dip** — Gives the player a second chance: if the first answer is wrong, the incorrect option is removed and the player can try again.
- **Lifeline Chaining** — Both lifelines can be used on the same question for maximum help.
- **Safety Net System** — Guaranteed prize thresholds at levels 2–6 (5,000 TL) and levels 7–11 (50,000 TL) to cushion a wrong answer.
- **Walk Away Option** — Type `leave` at any time to quit and keep your current winnings.
- **Persistent Leaderboard** — Player names and final prizes are saved to `players.txt`, displayed at the start of each new game.

---

## Project Structure

```
src/
├── main.c           # Source code (game logic, file I/O, lifelines)
├── question.csv     # Question database (~1,900 questions, CSV format)
└── players.txt      # Leaderboard file (auto-updated after each game)
```

### Question CSV Format

Each row in `question.csv` follows this structure:

```
ID, Level, Question, Choice A, Choice B, Choice C, Choice D, Correct Answer, Category
```

| Field            | Description                            |
|------------------|----------------------------------------|
| `ID`             | Unique question identifier             |
| `Level`          | Difficulty level (1–12)                |
| `Question`       | The question text                      |
| `Choice A–D`     | Four multiple-choice options           |
| `Correct Answer` | The correct option letter (A/B/C/D)    |
| `Category`       | Category identifier                    |

---

## Getting Started

### Prerequisites

- A **C compiler** (GCC, MinGW, Clang, MSVC, etc.)

### Compilation

```bash
gcc main.c -o main
```

### Running the Game

```bash
./main
```

> **Note:** Make sure `question.csv` and `players.txt` are in the same directory as the executable.

---

## How to Play

1. The game begins by displaying the **leaderboard** of previous players.
2. Enter your **name** when prompted.
3. The **prize ladder** and available **lifelines** are shown.
4. For each question, you can:
   - Answer by typing `A`, `B`, `C`, or `D`
   - Use a lifeline by typing `50/50` or `doubledip`
   - Walk away by typing `leave`
5. Answer all **12 questions** correctly to win **1,000,000 TL**!

### Prize Ladder

| Question | Prize (TL)  |
|----------|-------------|
| 1        | 2,000       |
| 2        | 5,000       |
| 3        | 7,500       |
| 4        | 10,000      |
| 5        | 20,000      |
| 6        | 30,000      |
| 7        | 50,000      |
| 8        | 100,000     |
| 9        | 200,000     |
| 10       | 300,000     |
| 11       | 500,000     |
| 12       | 1,000,000   |

### Safety Nets

- Wrong answer on questions **3–6** → You keep **5,000 TL**
- Wrong answer on questions **7–11** → You keep **50,000 TL**
- Wrong answer on questions **1–2** → You leave with **0 TL**

---

## Technical Details

- **Language:** C
- **Data Structures:** Custom `struct Infos` for questions, `struct User` for player state
- **File I/O:** CSV parsing with `strtok()`, player data persistence via text file
