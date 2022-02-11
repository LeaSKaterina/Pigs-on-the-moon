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
#include "enums/vehicleTypes.h"
#include "map/map.h"
#include <map>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>


class Game {
private:
    std::vector<int> state;
    std::vector<std::vector<Vehicle *>> vehicles;

    // new: custom id start from 0 to numPlayers - 1
    std::map<int, int> playersIdAdapter;// [real id 1, ..]->[0, 1, 2]
    std::vector<int> tanksIdAdapter;    // save real id for server

    std::vector<int> captures;
    std::vector<int> kills;

    const int numRounds = 15;
    static constexpr int numPlayerVehicles = 5;

    int numTurns;
    int currentTurn;

    int numPlayers;
    int currentPlayerId;

    bool isFinished = false;

    std::vector<std::vector<bool>> attackMatrix;// {"id" : "whom attack"}
    Map *map;

    Player *player;

    [[nodiscard]] Vehicle *Find(int adaptedPlayerId, const Point3D &spawn) const;

    void InitVariables(int playersNum = 3);

    // Strategy
    static void ProcessAttackPossibility(std::unordered_map<Vehicle *, std::vector<Vehicle *>> &priorityShootTargets);

public:
    Game(int playerId, std::string name, std::string password = "", int playersNum = 3);

    ~Game();

    // init methods
    // all inits must be called firstly!
    void InitMap(int size) { map = new Map(size); }

    void InitPlayersId(const std::vector<int> &realId);

    void InitVehiclesIds(int playerId, const std::unordered_map<std::string, std::vector<int>> &realId);

    // add methods

    void AddVehicle(int playerId, VehiclesTypes::Type type, Point3D spawn);

    void AddBase(std::vector<Point3D> &points) { map->AddBase(points); }

    // get state
    void UpdateState(int currTurn, int currPlayer, bool finished = false);

    void UpdateVehicleState(int parentId, Point3D spawn, Point3D pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, const std::vector<int>& attacked);

    void UpdateWinPoints(int playerId, int capture, int kill);

    [[nodiscard]] std::vector<std::tuple<Action, int, Point3D>> Play() const;

    // get action
    // ...

    // Getters

    [[nodiscard]] int GetNumPlayers() const { return numPlayers; }

    [[nodiscard]] bool IsPlayerTurn() const { return currentPlayerId == player->GetId(); }

    [[nodiscard]] bool IsFinished() const { return isFinished; }
};
