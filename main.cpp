#include "game.h"

int main() {
    Game game;
    game.InitMap(11);
    game.InitPlayer(0, "Katya", "****");
    game.InitVariables();
    return 0;
}