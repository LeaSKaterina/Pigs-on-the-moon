#pragma once

#include "gameClient.h"

class Bot {
public:
    Bot(const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
        int numPlayers = 1, bool isObserver = false) {
        gc.InitGame(name, password, gameName, numTurns, numPlayers, isObserver);
    }

    void StartAI() { gc.StartAI(); }

    GameClient gc;
};
