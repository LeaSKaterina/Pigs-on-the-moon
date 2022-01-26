#include <iostream>
#include "modules/client/Client.h"
#include "modules/game.h"

int main() {

    Client client;
    std::cout << client.Login("test2") << '\n';
    std::cout << client.Map() << '\n';
    std::cout << client.Logout() << '\n';

    Game game;
    game.InitMap(11);

    return 0;
}