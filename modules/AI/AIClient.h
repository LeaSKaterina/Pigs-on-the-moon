#pragma once

#include "gameClient.h"
#include "AIPlayer.h"

class AIClient : public GameClient {
public:
    AIClient() : ai(nullptr) {}
    ~AIClient() { delete ai; }
    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 0, int numPlayers = 1,
                  bool isObserver = false) override;
    void SendAction() const override;


private:
    AIPlayer *ai;

};


