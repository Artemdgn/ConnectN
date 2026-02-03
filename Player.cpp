
#include <string>

using namespace std;

class Player{
    
    private:
        string name;
        GridPosition pieceColour;
    
    public:
        Player(string name, GridPosition pieceColour){
            this->name = name;
            this->pieceColour = pieceColour;
        }
        string getName(){
            return this->name;
        }
        GridPosition getPieceColour(){
            return this->pieceColour;
        }
};