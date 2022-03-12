#ifndef PIGS_ON_THE_MOON_AICLIENT_H
#define PIGS_ON_THE_MOON_AICLIENT_H

#include "../gameClient.h"
#include "AIPlayer.h"

class AIClient : public GameClient {
public:
    explicit AIClient(const std::string &name, const std::string &password = "",
             const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
             bool isObserver = false)
        : GameClient(name, password, gameName, numTurns, numPlayers, isObserver),
          ai(new AIPlayer(GetGame())) {}

    ~AIClient() { delete ai; }

    void SendAction() const;

private:
    AIPlayer *ai;
};


#endif//PIGS_ON_THE_MOON_AICLIENT_H
