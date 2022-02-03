#include "modules/gameClient.h"
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

int main() {
//    bool debug = true;

    ///////////////////////////////////////////////////////////////////////////////variables for debugging
    const std::string game = "test4";// the name of the game we are connecting to
    const int numbersCount = 2;      // number of players. Values from [1, 2, 3]
    const int numbersTurn = 100;     // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1;                // our connection number. Values from [1, 2, 3] // may be mare than numberCount
                                     ///////////////////////////////////////////////////////////////////////////////

    if (ourOrder > numbersCount)// simple check max value
        ourOrder = numbersCount;

    Client *clients = new Client[numbersCount - 1];// bots for extras
    GameClient gc;                          // our overmind

    int clientIndex = 0;
    for (int i = 0; i < numbersCount; ++i) {// Login
        if (i == ourOrder - 1) {
            gc.InitGame("test14", "", game, numbersTurn, numbersCount);
            continue;
        }
        clients[clientIndex].Login("bot" + std::to_string(clientIndex), "", game, numbersTurn, numbersCount);
        ++clientIndex;
    }


    while (!gc.SendTurn()) {}
    gc.InitPlayersId();
    while (!gc.GameIsFinished()) {
        gc.UpdateGameState();
        if (gc.IsPlayTime())
            gc.SendAction();

        #ifdef _DEBUG
//            std::cout << gc.getClient()->GameState();
            std::cerr << "\n---------------------------------------\n";
        #endif

        gc.SendTurn();
    }
    std::cout << "Game is finished : " << std::boolalpha << gc.GameIsFinished() << '\n';
}
