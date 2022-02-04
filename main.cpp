#include "modules/gameClient.h"
#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>

using json = nlohmann::ordered_json;
using namespace std;

void ClientThreadFunction(GameClient *bot) {// mystical process. I do not advise you to understand this. Just change value as you need.
    while (!bot->SendTurn()) {}             // I use GameClient * because in this case destructor for GameClient don't run. It's important. If destructor runs then runtime error come.
    bot->InitPlayersId();                   // All because GameClient haven't deep copy for * tupe(


    while (!bot->GameIsFinished()) {// just stay and wait finish game
        bot->UpdateGameState();
        bot->SendTurn();// we don't want to wait 10 seconds
    }
}


int main() {
    bool debug = true;

    ///////////////////////////////////////////////////////////////////////////////variables for debugging
    std::string gameName = "Pigs-on-the-moon";// the name of the game we are connecting to
    const int playersCount = 2;                // number of players. Values from [1, 2, 3]
    const int numbersTurn = 40;                // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1;                          // our connection number. Values from [1, 2, 3] // may be more than numberCount
    ///////////////////////////////////////////////////////////////////////////////

    // TODO I can't use std::min( why??????????/
    ourOrder = min(ourOrder, playersCount);// simple check for easy life

    gameName += "_" + std::to_string(playersCount) + "_" + std::to_string(ourOrder);

    GameClient gc(debug);                                 // our overmind
    std::vector<GameClient> gameClients(playersCount - 1);// bots
    std::vector<std::thread> threads;

    int botCount = 0;
    for (int i = 0; i < playersCount; ++i) {// Login all
        if (i == ourOrder - 1) {
            gc.InitGame("overmind", "", gameName, numbersTurn, playersCount);
            continue;
        }
        gameClients[botCount].InitGame("bot" + std::to_string(botCount), "", gameName, numbersTurn, playersCount);
        threads.emplace_back(ClientThreadFunction, &gameClients[botCount]);
        ++botCount;
    }

    while (!gc.SendTurn()) {}// wait all players
    gc.InitPlayersId();
    while (!gc.GameIsFinished()) {
        gc.UpdateGameState();
        if (gc.IsPlayTime())// play only our turn
            gc.SendAction();
        if (debug)
            std::cerr << "\n---------------------------------------\n";
        gc.SendTurn();
    }

    for (int i = 0; i < playersCount - 1; ++i) {// wait all our children's to avoid run time exception
        threads[i].join();
    }

    std::cout << "Game is finished : " << std::boolalpha << gc.GameIsFinished() << '\n';
    return 0;
}
