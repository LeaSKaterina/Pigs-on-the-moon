//
// Created by Alex on 27.01.2022.
//

#ifndef PIGS_ON_THE_MOON_GAME_CLIENT_H
#define PIGS_ON_THE_MOON_GAME_CLIENT_H

#include "client/Client.h"
#include "game.h"

class GameClient {
public:
    GameClient() {
        game = new Game();
        client = new Client();
    }
    bool initGame(const std::string& name, const std::string& password = "",
                  const std::string& game_name="", int num_turns = 45, int num_players = 3,
                  bool is_observer = false);
    ~GameClient() {
        client->Logout();
        delete game;
        delete client;
    }
private:
    Game* game;
    Client* client;
};




#endif //PIGS_ON_THE_MOON_GAME_CLIENT_H
