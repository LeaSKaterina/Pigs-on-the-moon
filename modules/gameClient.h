#pragma once

#include "nlohmann/json.hpp"
#include "client/client.h"
#include "game/game.h"

class GameClient {
public:
    GameClient(bool debug = true) : game(new Game()), client(new Client(debug)) {}

    // must be called once and first.
    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 0, int numPlayers = 1,
                  bool isObserver = false);


    [[nodiscard]] bool GameIsFinished() const { return game->IsFinished(); }

    void UpdateGameState();

//    void CheckGameAction();  Do we really need this?

    ~GameClient();

    bool SendTurn() const;

    void SendAction() const;

    void InitPlayersId();

    Client *GetClient() const { return client; }

    [[nodiscard]] bool IsPlayTime() const { return game->IsPlayerTurn(); }
private:

    // entities
    Game *game;
    Client *client;

    tuple<int, int, int> MakePosTuple(const nlohmann::ordered_json &coordinate);

};


