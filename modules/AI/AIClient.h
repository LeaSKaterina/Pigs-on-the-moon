#pragma once

#include "gameClient.h"
#include "AIPlayer.h"

class AIClient : public GameClient {
public:
    explicit AIClient(const std::string &name, const std::string &password = "",
                      const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
                      bool isObserver = false)
        : GameClient(name, password, gameName, numTurns, numPlayers, isObserver),
          ai(new AIPlayer(GetGame())) {}

    ~AIClient() { delete ai; }

    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 0, int numPlayers = 1,
                  bool isObserver = false);
    void SendAction() const;

    AIPlayer* GetAIPlayer(){ return ai; }

private:
    AIPlayer *ai;

};

