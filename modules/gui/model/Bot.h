#pragma once

#include "gameClient.h"

class Bot {
public:
    Bot(const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
        int numPlayers = 1) {
        gc.InitGame(name, password, gameName, numTurns, numPlayers);
    }

    void StartAI(){gc.StartAI();}

private:
    GameClient gc;
};
