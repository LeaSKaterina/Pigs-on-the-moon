#pragma once

#include "../actors/player.h"
#include "../actors/vehicles/vehicle.h"
#include "../actors/vehicles/spg.h"
#include "../actors/vehicles/atSpg.h"
#include "../actors/vehicles/heavyTank.h"
#include "../actors/vehicles/lightTank.h"
#include "../actors/vehicles/mediumTank.h"
#include "../enums/action.h"
#include "../enums/vehicle_types.h"
#include "../map/map.h"
#include "actionController.h"
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

    // order??

    std::vector<int> captures;
    std::vector<int> kills;

    const int numRounds = 15;
    static constexpr int numPlayerVehicles = 5;

    int numTurns;
    int currentTurn;

    int numPlayers;
    int currentPlayerId;

    bool isFinished = false;

    std::vector<std::vector<int>> attackMatrix;// {"id" : "whom attack"}
    Map *map;

    Player *player;

    [[nodiscard]] Vehicle *Find(int adaptedPlayerId, const Point &spawn) const;

    // Strategy
    static void ProcessAttackPossibility(std::unordered_map<Vehicle*, std::vector<Vehicle*>>& priorityShootTargets) ;

public:
    Game() = default;

    ~Game();

    // init methods
    // all inits must be called firstly!
    void InitMap(int size) { map = new Map(size); }

    void InitPlayer(int id, std::string name, std::string password = "") { player = new Player(id, std::move(name), std::move(password)); }

    void InitVariables(int playersNum = 3);

    void InitPlayersId(const std::vector<int> &realId);

    void InitVehiclesIds(int playerId, const std::unordered_map<std::string, std::vector<int>> &realId);

    // add methods

    void AddVehicle(int playerId, VehiclesTypes::Type type, Point spawn);

    void AddBase(std::vector<Point> &points) { map->AddBase(points); }

    // get state
    void UpdateState(int currTurn, int currPlayer, bool finished = false);

    void UpdateVehicleState(int parentId, Point spawn, Point pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, std::vector<int> attacked) {
        attackMatrix[playersIdAdapter.at(playerId)] = std::move(attacked);
    }

    void UpdateWinPoints(int playerId, int capture, int kill);

    [[nodiscard]] std::vector<std::tuple<Action, int, Hex *>> Play() const;

    // get action
    // ...

    // Getters

    [[nodiscard]] int GetNumPlayers() const { return numPlayers; }

    [[nodiscard]] bool IsPlayerTurn() const { return currentPlayerId == player->GetId(); }

    [[nodiscard]] bool IsFinished() const { return isFinished; }
};
