#pragma once


#include "AI/AIClient.h"
#include "AIBehaviorTree/aiBehaviorTree.h"
#include <memory>

class Controller;

class Bot {
public:
    explicit Bot(const std::string &name, const std::string &password = "", const std::string &gameName = "", int numTurns = 0,
                 int numPlayers = 1, bool isObserver = false) {
        gc = std::make_unique<AIClient>(name, password, gameName, numTurns, numPlayers, isObserver);
    }

    void StartAI() { gc->StartAI(); }

    [[nodiscard]] AIClient *GetClient() const { return gc; }

    ~Bot() = default;

private:
    std::unique_ptr<AIClient> gc;
};
