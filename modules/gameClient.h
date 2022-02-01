#pragma once

#include "nlohmann/json.hpp"
#include "client/client.h"
#include "game/game.h"

class GameClient {
public:
    GameClient(bool debug = true) : game(new Game()), client(new Client(debug)) {}

    // must be called once and first.
    bool initGame(const std::string& name, const std::string& password = "",
                  const std::string& game_name="", int num_turns = 0, int num_players = 1,
                  bool is_observer = false);


    [[nodiscard]] bool GameIsFinished() const { return game->IsFinished();}

    void UpdateGameState();

//    void CheckGameAction();  Do we really need this?

    ~GameClient();

    bool SendTurn() const;

    void SendAction() const;
    void InitPlayersId();

    Client *getClient() const { return client;}

    bool isOurTurn(){ return true;}

private:

    // entities
    Game* game;
    Client* client;
    tuple<int, int, int> MakePosTuple(const nlohmann::ordered_json& coordinate);

};


