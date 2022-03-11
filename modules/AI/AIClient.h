#ifndef PIGS_ON_THE_MOON_AICLIENT_H
#define PIGS_ON_THE_MOON_AICLIENT_H

#include "../gameClient.h"
#include "AIPlayer.h"

class AIClient : public GameClient {
private:
    AIPlayer *ai;

public:
    AIClient() : ai(nullptr) {}
    ~AIClient() { delete ai; }
    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 0, int numPlayers = 1,
                  bool isObserver = false) override;
    void SendAction() const override;
private:
};


#endif//PIGS_ON_THE_MOON_AICLIENT_H
