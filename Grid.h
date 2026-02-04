#ifndef GRID_H
#define GRID_H

#include <vector>
    using namespace std;

enum GridPosition { EMPTY, YELLOW, RED };

class Grid {
private:
    int rows;
    int columns;
    vector<vector<int>> grid;

public:
    Grid(int rows, int columns);
    void initializeGrid();
    vector<vector<int>> getGrid();
    int getColumnCount();
    int placePiece(int column, GridPosition pieceColour);
    bool checkWin(int connectN, int row, int column, GridPosition pieceColour);
};

#endif // GRID_H
