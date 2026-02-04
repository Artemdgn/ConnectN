#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Grid.h"
    using namespace std;

class Player {
private:
    string name;
    GridPosition pieceColour;

public:
    Player(string name, GridPosition pieceColour);
    string getName();
    GridPosition getPieceColour();
};

#endif // PLAYER_H
