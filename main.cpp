#include <iostream>
//#include "modules/client/Client.h"
//#include "modules/game.h"
#include "modules/gameClient.h"

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;


int main() {
    bool debug = true;

///////////////////////////////////////////////////////////////////////////////variables for debugging
    std::string game = "test3";// the name of the game we are connecting to
    int numbersCount = 2; // number of players. Values from [1, 2, 3]
    int numbersTurn = 100; // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1; // our connection number. Values from [1, 2, 3] // may be mare than numberCount
///////////////////////////////////////////////////////////////////////////////

    if(ourOrder > numbersCount) // simple check max value
        ourOrder = numbersCount;

    Client* clients = new Client[numbersCount - 1]; // bots for extras
    GameClient gc(debug); // our overmind

    int clientIndex = 0;
    for (int i = 0; i < numbersCount; ++i) {// Login
        if(i == ourOrder - 1) {
            gc.initGame("test14", "", game, numbersTurn, numbersCount);
            continue;
        }
        clients[clientIndex].Login("bot" + std::to_string(clientIndex), "", game, numbersTurn, numbersCount);
        ++clientIndex;
    }


    while(gc.SendTurn() != true);
    gc.InitPlayersId();
    while(gc.GameIsFinished() != true){
        gc.CheckGameState();
        if(gc.isPlayTime())
            gc.SendAction();
//        std::cout << gc.getClient()->GameState();
        if(debug)
            std::cerr << "\n---------------------------------------\n";
        gc.SendTurn();
    }
    std::cout << "Game is finished : " << std::boolalpha << gc.GameIsFinished() << '\n';
}

