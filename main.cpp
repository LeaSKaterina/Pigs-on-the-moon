#include "gameClient.h"
#include <iostream>
#include <thread>

using namespace std;

//thread function. One thread - one bot.
void ClientThreadFunction(const string &name, const string &password, const string &gameName, int numTurns, int numPlayers) {
    GameClient gc;
    gc.StartAI(name, password, gameName, numTurns, numPlayers);
}


int main() {
    ///////////////////////////////////////////////////////////////////////////////variables for debugging
    std::string gameName = "Pigs-on-the-moon";// the name of the game we are connecting to
    const int playersCount = 3;               // number of players. Values from [1, 2, 3]
    const int numbersTurn = 100;              // numbers of turns. Values from [0 ... 100]
    int ourOrder = 1;                         // our connection number. Values from [1, 2, 3] // may be more than numberCount
    ///////////////////////////////////////////////////////////////////////////////

    ourOrder = min(ourOrder, playersCount);// simple check for easy life

    gameName += "_" + std::to_string(playersCount) + "_" + std::to_string(ourOrder);

    std::vector<std::thread> threads;

    int botCount = 0;
    for (int i = 0; i < playersCount; ++i) {// Login all
        if (i == ourOrder - 1) {
            threads.emplace_back(ClientThreadFunction, "overmind", "", gameName, numbersTurn, playersCount); // our overmind
            continue;
        }
        threads.emplace_back(ClientThreadFunction, "bot" + std::to_string(botCount), "", gameName, numbersTurn, playersCount);
        ++botCount;
    }

    for (int i = 0; i < threads.size(); ++i) {// wait all our children's to avoid run time exception
        threads[i].join();
    }

    return 0;
}
