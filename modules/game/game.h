#pragma once

#include "actionController.h"
#include "actors/player.h"
#include "actors/vehicles/atSpg.h"
#include "actors/vehicles/heavyTank.h"
#include "actors/vehicles/lightTank.h"
#include "actors/vehicles/mediumTank.h"
#include "actors/vehicles/spg.h"
#include "actors/vehicles/vehicle.h"
#include "enums/action.h"
#include "enums/types.h"
#include "map/map.h"

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

class Game {
public:
    Game(int playerId, std::string name, std::string password, int playersNum,
         const nlohmann::ordered_json &mapInfo,
         const nlohmann::ordered_json &gameState);

    ~Game();

    // update methods
    void UpdateGameState(const nlohmann::ordered_json &state);

    // init methods
    // all inits must be called firstly!
    void InitMap(int size) { map = new Map(size); }

    void InitPlayersId(const std::vector<int> &realId);

    void InitVehiclesIds(int playerId, const std::unordered_map<std::string, std::vector<int>> &realId);

    // add methods

    void AddVehicle(int playerId, VehiclesTypes::Type type, Point3D spawn);

    void AddConstruct(ConstructionsTypes::Type type, std::vector<Point3D> &points) {
        map->AddConstruction(type, points);
    }


    // game state
    void UpdateState(int currTurn, int currPlayer, bool finished = false);

    void UpdateVehicleState(int parentId, Point3D spawn, Point3D pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, const std::vector<int> &attacked);

    void UpdateWinPoints(int playerId, int capture, int kill);

    // game action
    // ...

    // Getters

    [[nodiscard]] int GetNumPlayers() const { return numPlayers; }

    [[nodiscard]] int GetPlayerVehiclesNum() const { return numPlayerVehicles; }

    [[nodiscard]] auto &GetVehicles() const { return vehicles; }

    [[nodiscard]] const std::vector<Vehicle *> &GetVehicles(int playerId, bool adapted = true) const;

    [[nodiscard]] Map *GetMap() const;// TODO! const Map*

    [[nodiscard]] const Player *GetPlayer() const { return player; }

    [[nodiscard]] int GetAdaptedPlayerId() const { return playersIdAdapter.at(player->GetId()); }

    [[nodiscard]] auto &GetAttackMatrix() const { return attackMatrix; }

    [[nodiscard]] bool IsPlayerTurn() const { return currentPlayerId == player->GetId(); }

    [[nodiscard]] bool IsFinished() const { return isFinished; }

    static Point3D MakePosTuple(const nlohmann::json &coordinate);

private:
    std::vector<std::vector<Vehicle *>> vehicles;

    // new: custom id start from 0 to numPlayers - 1
    std::map<int, int> playersIdAdapter;// [real id 1, ..]->[0, 1, 2]

    std::vector<int> captures;
    std::vector<int> kills;

    const int numRounds = 15;
    static constexpr int numPlayerVehicles = 5;

    int numTurns{};
    int currentTurn{};

    int numPlayers{};
    int currentPlayerId{};

    bool isFinished = false;

    std::vector<std::vector<bool>> attackMatrix;// {"id" : "whom attack"}
    Map *map{};

    Player *player;

    [[nodiscard]] Vehicle *FindVehicle(int adaptedPlayerId, const Point3D &spawn) const;

    void InitVariables(int playersNum);
    void UpdateWinPoints(const nlohmann::ordered_json &winPoints);
    void UpdateAttackMatrix(const nlohmann::ordered_json &am);
    void UpdateVehicles(const nlohmann::ordered_json &vehicles);
    void _InitMap(const nlohmann::json &mapInfo);
    void InitContent(const nlohmann::ordered_json &contentInfo);
    void InitSpawns(const nlohmann::ordered_json &spawnInfo);
};
