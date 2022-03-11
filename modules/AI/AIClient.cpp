#include "AIClient.h"

AIClient::AIClient(const std::string &name, const std::string &password, const std::string &gameName,
                   int numTurns, int numPlayers, bool isObserver) {
    gc.InitGame(name, password, gameName, numTurns, numPlayers, isObserver);
    ai = new AIPlayer(gc.GetGame());
}
