#ifndef PIGS_ON_THE_MOON_GAME_CLIENT_H
#define PIGS_ON_THE_MOON_GAME_CLIENT_H

#include "client/client.h"
#include "game/game.h"

class GameClient {
public:
    GameClient();

    bool initGame(const std::string& name, const std::string& password = "",
                  const std::string& game_name="", int num_turns = 45, int num_players = 3,
                  bool is_observer = false);

    [[nodiscard]] bool GameIsFinished() const;

    void CheckGameState();

//    void CheckGameAction();  Do we really need this?

    ~GameClient();

private:

    // entities
    Game* game;
    Client* client;

    // vars
    bool game_is_finished = false;
};




#endif //PIGS_ON_THE_MOON_GAME_CLIENT_H
