#pragma once

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
    Game(int playerId, const std::string &name, const std::string &password, bool isObserver, int playersNum,
         const nlohmann::ordered_json &mapInfo);

    ~Game();

    // update methods
    void UpdateGameState(const nlohmann::ordered_json &state);

    // init methods
    // all inits must be called firstly!

    void InitIds(const nlohmann::ordered_json &state);

    // Getters

    [[nodiscard]] int GetNumPlayers() const { return numPlayers; }

    [[nodiscard]] int GetPlayerVehiclesNum() const { return numPlayerVehicles; }

    [[nodiscard]] auto &GetVehicles() const { return vehicles; }

    [[nodiscard]] const std::vector<Vehicle *> &GetVehicles(int playerId, bool adapted = true) const;

    [[nodiscard]] const Map *GetMap() const { return map; }

    [[nodiscard]] int GetAdaptedPlayerId() const { return playersIdAdapter.at(player->GetId()); }

    [[nodiscard]] int GetVehicleServerId(int index) const { return tanksIdAdapter[index]; }

    [[nodiscard]] auto &GetAttackMatrix() const { return attackMatrix; }

    [[nodiscard]] bool IsPlayerTurn() const { return currentPlayerId == player->GetId(); }

    [[nodiscard]] bool IsFinished() const { return isFinished; }

    static Point3D MakePosTuple(const nlohmann::json &coordinate);

private:
    Map *map;
    Player *player;

    std::vector<std::vector<Vehicle *>> vehicles;

    // new: custom id start from 0 to numPlayers - 1
    std::map<int, int> playersIdAdapter;// [real id 1, ..]->[0, 1, 2]

    // save real ids of tanks to interact with the server
    std::vector<int> tanksIdAdapter;// custom id -> server id

    // dynamic info

    std::vector<std::vector<bool>> attackMatrix;// {"id" : "whom attack"}
    std::vector<int> captures;
    std::vector<int> kills;

    // consts

    const int numPlayerVehicles = 5;
    int numPlayers;
    int currentPlayerId = 0;

    bool isFinished = false;

    [[nodiscard]] Vehicle *FindVehicle(int adaptedPlayerId, const Point3D &spawn) const;

    // Update methods

    void UpdateWinPoints(const nlohmann::ordered_json &winPoints);

    void UpdateAttackMatrix(const nlohmann::ordered_json &am);

    void UpdateVehicles(const nlohmann::ordered_json &veh);

    // Init methods

    void InitVariables(int playersNum);

    void InitMap(const nlohmann::json &mapInfo);

    void InitContent(const nlohmann::ordered_json &contentInfo);

    void InitSpawns(const nlohmann::ordered_json &spawnInfo);

    void InitPlayersIds(const nlohmann::ordered_json &am);

    void InitVehiclesIds(const nlohmann::ordered_json &veh);

    void InitVehiclesIds(const std::unordered_map<std::string, std::vector<int>> &realId);

    // add methods

    void AddVehicle(int playerId, VehiclesTypes::Type type, Point3D spawn);

    // update methods
    // game state

    void UpdateVehicleState(int parentId, const Point3D &spawn, const Point3D &pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, const std::vector<int> &attacked);

    // game action
    // ...
};
