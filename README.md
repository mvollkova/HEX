# HEX GAME
The classic variant of the game Hex is played on an 11 x 11 hexagonal board.

![Hex board (11×11) placeholder](examples/board.png)

## Overview

This project implements **basic analytical functions** for the board game **Hex**. 

1. `BOARD_SIZE`
2. `PAWNS_NUMBER`
3. `IS_BOARD_CORRECT`
4. `IS_GAME_OVER`
5. `IS_BOARD_POSSIBLE`

## Game rules (short summary)

* Two players: **Red** and **Blue**.
* Red always moves first.
* Players alternately place a stone of their color (`r` or `b`) on empty hexes.
* **Red** aims to connect the **top** and **bottom** edges; **Blue** aims to connect the **left** and **right** edges.
* The first player to form a continuous connection between their sides wins.
* No draws are possible.


## Implemented Queries

### 1. `BOARD_SIZE`

Returns the integer size of the board (from 1 to 11). It is determined by counting the number of hexes per row or line in the ASCII representation.

Example:

```
<   >
```

Output:

```
1
```

---

### 2. `PAWNS_NUMBER`

Returns the total number of stones (`r` and `b`) currently on the board.

Example:

```
< r >-< b >
```

Output:

```
2
```

---

### 3. `IS_BOARD_CORRECT`

Checks whether the board state is consistent with the rules of alternating moves.

Rules:

* Red always moves first.
* Let `R` = number of red stones, `B` = number of blue stones.
* The position is **correct** if `R == B` (it's Red’s turn) or `R == B + 1` (it's Blue’s turn).

Outputs:

```
YES
```

or

```
NO
```

---

### 4. `IS_GAME_OVER`

Checks whether either player has already connected their two sides.

Outputs:

```
YES RED
YES BLUE
NO
```

Implementation tip:

* Use BFS/DFS (or Union-Find) to check path connectivity.
* For Red: top ↔ bottom.
* For Blue: left ↔ right.

---

### 5. `IS_BOARD_POSSIBLE`

Checks whether the board is a **possible** state of play, meaning:

1. The board is correct (`IS_BOARD_CORRECT = YES`).
2. If a player has already won, that win must have occurred **on the last move**.

Algorithm:

* If `IS_BOARD_CORRECT = NO`, output `NO`.
* If the board shows a win, temporarily remove each of the winner’s stones one by one and check if the win disappears. If removing **any** stone breaks the win, the board is possible (YES). If not, the win must have occurred earlier (NO).

Outputs:

```
YES
```

or

```
NO
```

More information about this game: https://en.wikipedia.org/wiki/Hex_(board_game)
