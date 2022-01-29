#pragma once

#include <tuple>
#include <vector>
#include <string>
#include "../actors/vehicle.h"
#include "../actors/player.h"
#include "../map/map.h"

using namespace std;

class Game {
private:
    vector<int> state;
    vector<vector<Vehicle *>> vehicles;

    vector<int> captures;
    vector<int> kills;

    const int numRounds = 15;
    int numTurns{};
    int currentTurn{};

    int numPlayers{};
    int currentPlayer{};

    vector<vector<int>> attackMatrix; // {"id" : "whom attack"}
    Map *map{};

    Player *player{};

    [[nodiscard]] Vehicle *Find(int parentId, const tuple<int, int, int> &spawn) const;

public:
    Game();

    ~Game();

    void InitMap(int size);

    void AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn);

    void AddBase(vector<tuple<int, int, int>> &points);

    void InitPlayer(int id, string name, string password = "");

    void InitVariables(int playersNum = 3);

    // get state
    void UpdateState(int currTurn, int currPlayer);

    void UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, vector<int> attacked);

    void UpdateWinPoints(int playerId, int capture, int kill);
    // get action

};
