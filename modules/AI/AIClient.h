#pragma once

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
