#pragma once

#include "AIBehaviorTree/aiBehaviorTree.h"
#include "AIPlayer.h"
#include "gameClient.h"

class AIClient : public GameClient {
public:
    explicit AIClient(const std::string &name, const std::string &password = "",
                      const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
                      bool isObserver = false)
        : GameClient(name, password, gameName, numTurns, numPlayers, isObserver),
          ai(new AIPlayer(GetGame())),
          onlyObserve(isObserver) {}

    ~AIClient() { delete ai; }

    AIPlayer *GetAIPlayer() { return ai; }

    void Start() {
        onlyObserve ? StartObserver() : StartAI();
    }

    void StartAI() {
        this->ConnectPlayer();
        tree.Init(this);

        while (!this->GameIsFinished()) {
            std::cout << "Bot\n";
            this->UpdateGameState();
            if (this->IsPlayTime())// play only our turn
                tree.ProcessAllTanks();
#ifdef _DEBUG
            std::cerr << "\n---------------------------------------\n";
#endif
            this->SendTurn();
        }
    }

    void StartObserver() {
        this->ConnectPlayer();
        while (!this->GameIsFinished()) {
            std::cout << "Observer\n";
            this->UpdateGameState();
#ifdef _DEBUG
            std::cerr << "\n---------------------------------------\n";
#endif
            this->SendTurn();
        }
    }

private:
    AIPlayer *ai;
    AIBehaviorTree tree;
    bool onlyObserve;
};
