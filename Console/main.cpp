#include<iostream>
#include "Grid.cpp"     
#include "Player.cpp"   
#include "Game.cpp" 

using namespace std;

int main(){

    int rows;
    int columns;
    int connectN;
    int targetScore;

    cout << "--- CONNECT N GAME ---" << endl;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> columns;
    cout << "Enter the number of pieces in a row to win: ";
    cin >> connectN;
    cout << "Enter how many rounds to win to win the whole game: ";
    cin >> targetScore;
    cout << endl;
    cout << "Starting game! " << rows << "x" << columns << " board, Connect " << connectN << ", first to " << targetScore << " wins!" << endl;
    cout << endl;

    Grid* grid = new Grid(rows, columns);
    Game* game = new Game(grid, connectN , targetScore);
    game->play();
    return 0;
}
