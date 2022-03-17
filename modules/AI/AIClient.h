#pragma once

#include "AIPlayer.h"
#include "gameClient.h"

class AIClient : public GameClient {
public:
    explicit AIClient(const std::string &name, const std::string &password = "",
                      const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
                      bool isObserver = false)
        : GameClient(name, password, gameName, numTurns, numPlayers, isObserver),
          onlyObserve(isObserver) {}

    ~AIClient() = default;

    AIPlayer *GetAIPlayer() { return ai.get(); }

    void StartAI() {
        this->ConnectPlayer();
        ai = std::make_unique<AIPlayer>(GetGame());

        while (!this->GameIsFinished()) {
            std::cout << "Bot\n";
            this->UpdateGameState();
            if (this->IsPlayTime() && !onlyObserve)// play only our turn
                GameClient::SendAction(ai->Play());
#ifdef _DEBUG
            std::cerr << "\n---------------------------------------\n";
#endif
            this->SendTurn();
        }
    }

private:
    std::unique_ptr<AIPlayer> ai;
    bool onlyObserve;
};
