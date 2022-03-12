#pragma once

#include "client/client.h"
#include "enums/types.h"
#include "game/game.h"
#include "map/Point3D.h"

#include <nlohmann/json.hpp>
#include <unordered_map>

#include <chrono>
#include <thread>

class GameClient {
public:
    explicit GameClient(const std::string &name, const std::string &password = "",
                        const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
                        bool isObserver = false);

    ~GameClient();

    // Inits

    // must be called once and first.
    bool InitGame(const std::string &name, const std::string &password = "",
                  const std::string &gameName = "", int numTurns = 45, int numPlayers = 3,
                  bool isObserver = false);

    // must be called once and only when all players are connected
    void InitIds();

    // Game process

    [[nodiscard]] bool IsPlayTime() const { return game->IsPlayerTurn(); }

    [[nodiscard]] bool GameIsFinished() const { return game->IsFinished(); }

    void UpdateGameState();

    bool SendTurn() const;

    // starts magit in cycle
    // requires connection to the game
    void StartAI();

    [[nodiscard]] Game *GetGame() const { return game; } // TODO! const Game*


protected:
    // entities
    Game *game;
    Client *client;

    // init methods
    bool Login(const std::string &name, const std::string &password, const std::string &gameName, int numTurns,
               int numPlayers, bool isObserver);

    void InitMap();

    static Point3D MakePosTuple(const nlohmann::json &coordinate);

    void InitSpawns(const nlohmann::ordered_json &spawnInfo);

    void InitContent(const nlohmann::ordered_json &contentInfo);

    void InitPlayersIds(const nlohmann::ordered_json &am);

    void InitVehiclesIds(const nlohmann::ordered_json &vehicles);

    // update methods

    void UpdateVehicles(const nlohmann::ordered_json &vehicles);

    void UpdateAttackMatrix(const nlohmann::ordered_json &am);

    void UpdateWinPoints(const nlohmann::ordered_json &winPoints);

    void SendAction(const std::vector<std::tuple<Action, int, Point3D>> &actions) const;
};
