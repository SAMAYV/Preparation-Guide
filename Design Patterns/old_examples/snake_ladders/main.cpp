#include <iostream>
#include "game.cpp"
#include "board.cpp"
#include "player.cpp"
#include "dice.cpp"
using namespace std;

int main() {
    Game* game = new Game(10);
    game->startGame();
    return 0;
}