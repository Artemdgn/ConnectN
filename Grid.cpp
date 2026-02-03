
#include <vector>   // for std::vector
#include <iostream> // for cout inside Grid
#include <algorithm> // fro max/min

using namespace std;

enum GridPosition {
    EMPTY, YELLOW, RED
};

class Grid{

    private:
        int rows;
        int columns;
        //dynamic 2D array type of variable
        vector<vector<int>> grid;

    public: 
        Grid(int rows, int columns){
            this->rows = rows;
            this->columns = columns;
            //calling method to fill dynamic 2d array in fileds
            initializeGrid(); 
        }

        void initializeGrid(){
            // to initialize with empty dynamic 2D array
            this->grid = vector<vector<int>>();
            for(int i = 0; i < rows; i++){
                // .push_back() in cpp == .add() in java
                grid.push_back(vector<int>());
                    for(int j = 0; j < columns; j++){
                        //to get fields form static and enum classes we use
                        //GridPosition::EMPTY for emum ( is equivalent to GridPosition.empty for object class fields)
                        grid[i].push_back(GridPosition::EMPTY);
                    }
            }
        }
        

        // getter for grid
        vector<vector<int>>getGrid(){
            return this->grid;
        }

        // getter for columns
        int getColumnCount(){
            return this->columns;
        }

        int placePiece(int column, GridPosition pieceColour){
            if(column < 0 || column >= this->columns){
                throw "invalid column";
            }
            if(pieceColour == GridPosition::EMPTY){
                throw "Invalid pieceColour";
            }
            //start forl lowest white position
            //vectors in cpp = java arrayLists with direct access
            for(int row = this->rows-1; row >=0; row--){
                if(grid[row][column] == GridPosition::EMPTY){
                    grid[row][column] = pieceColour;
                    return row;
                }
            }
            return -1;
        }

        bool checkWin(int connectN, int row, int column, GridPosition pieceColour){

            int count = 0;
            for(int c = 0; c < this->columns; c++){
                if(this->grid[row][c] == pieceColour){
                    count++;
                }
                //reset if sequance is disconnected
                else{
                    count = 0;
                }
                if(count == connectN){
                    return true;
                }
            }
        
            count = 0;
            for(int r = 0; r < this->rows; r++){
                if(this->grid[r][column] == pieceColour){
                    count++;
                }
                //reset if sequance is disconnected
                else{
                    count = 0;
                }
                if(count == connectN){
                    return true;
                }
            }
        
            count = 0;
            for(int r = 0; r <this->rows; r++){
                int c = column - row + r;
                //scanning the entire diagonal, from the top of the board to the bottom
                if(c >=0 && c < columns && grid[r][c] == pieceColour){
                    count++;
                }
                else{
                    count = 0;
                }
                if(count == connectN){
                    return true;
                }
            }

            count = 0;
            for(int r = 0; r < this->rows; r++){
                int c = column + row - r;
                //scanning the entire anti diagonal, from the top of the board to the bottom
                if(c >=0 && c < columns && grid[r][c] == pieceColour){
                    count++;
                }
                else{
                    count = 0;
                }
                if(count == connectN){
                    return true;
                }
                
            }
            return false;
        }
};

