#pragma once

#include "gameClient.h"

class Controller;

class Bot {
public:
    Bot(Controller &controller, const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
        int numPlayers = 1, bool isObserver = false) : controller(controller) {
        gc.InitGame(name, password, gameName, numTurns, numPlayers, isObserver);
    }

    void StartAI();

    GameClient gc;

private:
    Controller &controller;
};
