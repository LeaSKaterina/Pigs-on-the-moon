#pragma once

#include "client/client.h"
#include "game/game.h"

#include "enums/vehicle_types.h"

#include "nlohmann/json.hpp"

class GameClient {
public:
    explicit GameClient() : game(new Game()), client(new Client()) {}
    ~GameClient();

    // Inits

    // must be called once and first.
    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 0, int numPlayers = 1,
                  bool isObserver = false);

    // must be called once and only when all players are connected
    void InitIds();

    // Game process

    [[nodiscard]] bool IsPlayTime() const { return game->IsPlayerTurn(); }
    [[nodiscard]] bool GameIsFinished() const { return game->IsFinished(); }

    void UpdateGameState();
    //    void UpdateGameAction();  Do we really need it?

    bool SendTurn() const;
    void SendAction() const;

private:
    // entities
    Game* game;
    Client* client;

    static tuple<int, int, int> MakePosTuple(const nlohmann::json&& coordinate);

    // init methods
    bool Login(const string &name, const string &password, const string &gameName, int numTurns,
                               int numPlayers, bool isObserver);
    void InitMap();
    void InitSpawns(const nlohmann::json&& spawnInfo);
    void InitPlayersIds(const nlohmann::json&& am);
    void InitVehiclesIds(const nlohmann::json&& vehicles);

    void UpdateVehicles(const nlohmann::json&& vehicles);
    void UpdateAttackMatrix(const nlohmann::json&& am);
    void UpdateWinPoints(const nlohmann::json&& winPoints);
};
