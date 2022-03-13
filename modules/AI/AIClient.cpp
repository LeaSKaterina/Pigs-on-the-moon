#include "AIClient.h"

//bool AIClient::InitGame(const std::string &name, const std::string &password, const std::string &gameName, int numTurns, int numPlayers, bool isObserver) {
//    if (GameClient::InitGame(name, password, gameName, numTurns, numPlayers, isObserver))
//        ai = new AIPlayer(GetGame());
//    return ai;
//}

void AIClient::SendAction() const {
    GameClient::SendAction(ai->Play());
}
