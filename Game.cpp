#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Game{

    private:
        Grid* grid;
        int connectedN;
        vector<Player*> players;
        // order does not matter for us
        unordered_map<string, int> score;
        int targetScore;

    public:
        Game(Grid* grid, int connectedN, int targetScore){
            this->grid = grid;
            this->connectedN = connectedN;
            this->targetScore = targetScore;

            this->players.push_back(new Player("Player 1", YELLOW));
            this->players.push_back(new Player("Player 2", RED));
            // to create empty map and assign it to score
            this->score = unordered_map<string, int>();
            for(Player* player: this->players){
                //equiv to score.put(player.getName(), 0); in java
                this->score[player->getName()] = 0;
            }
        }

        void printBoard(){
            cout << "Board:" << endl;
            vector<vector<int>> grid = this->grid->getGrid();
            for(int i = 0; i < grid.size(); i++){
                string row = "";
                for(int j = 0; j < grid[i].size(); j++){
                    if(grid[i][j] == GridPosition::EMPTY){
                        row+= "E ";
                    }
                    else if(grid[i][j] == GridPosition::YELLOW){
                        row+= "Y ";
                    }
                    else if(grid[i][j] == GridPosition::RED){
                        row+= "R ";
                    }
                }
                cout<< row << endl;
            }
            cout << endl;

        }

        vector<int>playMove(Player* player){
            printBoard();
            cout << player->getName() << " 's turn" << endl;
            int columnCount = this->grid->getColumnCount();

            cout << "Enter column between 0 and " << columnCount - 1 << " to add piece: ";
            int moveToColumn = 0;
            cin >> moveToColumn;

            int moveToRow = this->grid->placePiece(moveToColumn, player->getPieceColour()); 
            //DEFENSIVE PROGRAMMING
            while(moveToRow == -1){
                cout << "This column is full, please enter another column: ";
                cin >> moveToColumn;
                moveToRow = this->grid->placePiece(moveToColumn, player->getPieceColour());
            }
            return vector<int> {moveToRow, moveToColumn};
        }

        Player* playRound(){
            // to keep looping until some player wins
            while(true){
                for(int i = 0; i < this->players.size(); i++){
                    vector<int> currBoardState = playMove(players[i]);
                    int row = currBoardState[0];
                    int column = currBoardState[1];
                    GridPosition pieceColour = this->players[i]->getPieceColour();
                    if(this->grid->checkWin(this->connectedN, row, column, pieceColour)){
                        // equiv int newScore = currentScore + 1;
                        this->score[players[i]->getName()] = this->score[players[i]->getName()] + 1;
                        return this->players[i];
                    }
                }
            }
        }
        void play(){
            int currentMaxScore = 0;
            Player* winner = nullptr;
            while(currentMaxScore < this->targetScore){
                winner = playRound();
                cout << winner->getName() << " won the round " << endl;
                currentMaxScore = max(currentMaxScore, this->score[winner->getName()]);
                // maxScore reached, we reset to play more
                this->grid->initializeGrid();
            }
            cout << winner->getName() << " won the game " << endl;
        }
        
};