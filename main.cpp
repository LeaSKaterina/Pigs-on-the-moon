#include "gameClient.h"
#include <iostream>
#include <thread>

using namespace std;

// mystical process. I do not advise you to understand this. Just change value as you need.
// I use GameClient * because in this case destructor for GameClient don't run. It's important. If destructor runs then runtime error come.
// All because GameClient haven't deep copy for * tupe(
void ClientThreadFunction(GameClient *gc) {
    while (!gc->SendTurn()) {}
    gc->InitIds();
    while (!gc->GameIsFinished()) {
        gc->UpdateGameState();
        if (gc->IsPlayTime())// play only our turn
            gc->SendAction();

        gc->SendTurn();
    }
}


int main() {
    ///////////////////////////////////////////////////////////////////////////////variables for debugging
    std::string gameName = "Pigs-on-the-moon";// the name of the game we are connecting to
    const int playersCount = 3;               // number of players. Values from [1, 2, 3]
    const int numbersTurn = 100;               // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1;                         // our connection number. Values from [1, 2, 3] // may be more than numberCount
    ///////////////////////////////////////////////////////////////////////////////

    ourOrder = min(ourOrder, playersCount);// simple check for easy life


    gameName += "_" + std::to_string(playersCount) + "_" + std::to_string(ourOrder);

    GameClient gc;                                        // our overmind
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
    gc.InitIds();
    while (!gc.GameIsFinished()) {
        gc.UpdateGameState();
        if (gc.IsPlayTime())// play only our turn
            gc.SendAction();

#ifdef _DEBUG
        std::cerr << "\n---------------------------------------\n";
#endif

        gc.SendTurn();
    }

    for (int i = 0; i < playersCount - 1; ++i) {// wait all our children's to avoid run time exception
        threads[i].join();
    }

    std::cout << "Game is finished : " << std::boolalpha << gc.GameIsFinished() << '\n';

    return 0;
}
