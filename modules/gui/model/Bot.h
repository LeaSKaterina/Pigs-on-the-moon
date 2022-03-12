#pragma once

#include "AI/AIClient.h"

class Controller;

class Bot {
public:
    Bot(Controller &controller, const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
        int numPlayers = 1, bool isObserver = false) : controller(controller) {
        gc = new AIClient(name, password, gameName, numTurns, numPlayers, isObserver);
    }

    void StartAI();

    AIClient *gc;

    ~Bot() { delete gc; }

private:
    Controller &controller;
};
