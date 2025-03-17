#include <iostream>

class GamePlayer {
public:
static const int NumTurns = 5;
int scores[NumTurns];

};

int main(){

    GamePlayer ref;
    ref.scores[4] = 5;
    std::cout << "success! "<< ref.scores[4] ;
    return 0;
}