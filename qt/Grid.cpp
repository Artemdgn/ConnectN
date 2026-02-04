#include "Grid.h"

Grid::Grid(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    initializeGrid();
}

void Grid::initializeGrid() {
    grid.clear();
    grid.resize(rows);
    for(int i = 0; i < rows; i++) {
        grid[i].resize(columns, GridPosition::EMPTY);
    }
}

vector<vector<int>> Grid::getGrid() {
    return grid;
}

int Grid::getColumnCount() {
    return columns;
}

int Grid::placePiece(int column, GridPosition pieceColour) {
    if(column < 0 || column >= columns) {
        return -1;
    }
    if(pieceColour == GridPosition::EMPTY) {
        return -1;
    }
    for(int row = rows - 1; row >= 0; row--) {
        if(grid[row][column] == GridPosition::EMPTY) {
            grid[row][column] = pieceColour;
            return row;
        }
    }
    return -1;
}

bool Grid::checkWin(int connectN, int row, int column, GridPosition pieceColour) {
    // Check horizontal
    int count = 0;
    for(int c = 0; c < columns; c++) {
        if(grid[row][c] == pieceColour) count++;
        else count = 0;
        if(count == connectN) return true;
    }

    // Check vertical
    count = 0;
    for(int r = 0; r < rows; r++) {
        if(grid[r][column] == pieceColour) count++;
        else count = 0;
        if(count == connectN) return true;
    }

    // Check diagonal
    count = 0;
    for(int r = 0; r < rows; r++) {
        int c = column - row + r;
        if(c >= 0 && c < columns && grid[r][c] == pieceColour) count++;
        else count = 0;
        if(count == connectN) return true;
    }

    // Check anti-diagonal
    count = 0;
    for(int r = 0; r < rows; r++) {
        int c = column + row - r;
        if(c >= 0 && c < columns && grid[r][c] == pieceColour) count++;
        else count = 0;
        if(count == connectN) return true;
    }

    return false;
}
