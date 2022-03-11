#ifndef PIGS_ON_THE_MOON_AICLIENT_H
#define PIGS_ON_THE_MOON_AICLIENT_H

#include "../gameClient.h"
#include "AIPlayer.h"

class AIClient {
private:
    GameClient gc;
    AIPlayer* ai;
public:
    AIClient(const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
        int numPlayers = 1, bool isObserver = false);
    ~AIClient() {delete ai;}
};


#endif//PIGS_ON_THE_MOON_AICLIENT_H
