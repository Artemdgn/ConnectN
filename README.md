# ConnectN

A Connect 4 style game where you can choose your own board size and how many pieces in a row to win.

## How to Play

Two versions available:
- **console/** - Terminal version, works anywhere
- **qt/** - GUI version with Qt

### Console Version

```bash
cd console
g++ -std=c++11 main.cpp -o connectN
./connectN
```

You'll be asked for:
- Number of rows and columns
- How many in a row to win
- Target score

Then just type the column number to drop your piece.

### Qt Version

Need Qt installed. Open `qt/ConnectN.pro` in Qt Creator and run it.

## Rules

- Players take turns dropping pieces
- First to get N in a row wins the round
- First to reach target score wins the game
