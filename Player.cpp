#include "Player.h"

Player::Player(string name, GridPosition pieceColour) {
    this->name = name;
    this->pieceColour = pieceColour;
}

string Player::getName() {
    return this->name;
}

GridPosition Player::getPieceColour() {
    return this->pieceColour;
}
