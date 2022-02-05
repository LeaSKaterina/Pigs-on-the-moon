#pragma once

#include "client/client.h"
#include "game/game.h"
#include "enums/vehicleTypes.h"

#include <unordered_map>
#include <nlohmann/json.hpp>

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
    Game *game;
    Client *client;

    static Point MakePosTuple(const nlohmann::json &&coordinate);

    // init methods
    bool Login(const std::string &name, const std::string &password, const std::string &gameName, int numTurns,
               int numPlayers, bool isObserver);

    // init methods

    void InitMap();

    void InitSpawns(const nlohmann::ordered_json &&spawnInfo);

    void InitPlayersIds(const nlohmann::ordered_json &&am);

    void InitVehiclesIds(const nlohmann::ordered_json &&vehicles);

    void UpdateVehicles(const nlohmann::ordered_json &&vehicles);

    void UpdateAttackMatrix(const nlohmann::ordered_json &&am);

    void UpdateWinPoints(const nlohmann::ordered_json &&winPoints);

};
