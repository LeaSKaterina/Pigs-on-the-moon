#pragma once

#include <tuple>
#include <map>
#include <vector>
#include <string>
#include "../actors/vehicle.h"
#include "../actors/player.h"
#include "../map/map.h"
<<<<<<< HEAD
#include "../enums/action.h"
=======
//#include "../enums/action.h"

>>>>>>> action_branch

using namespace std;

class Game {
private:
    vector<int> state;
    vector<vector<Vehicle *>> vehicles;
    vector<int> tanksIdAdapter;
    vector<int> playersIdAdapter;

    // new: custom id start from 0 to numPlayers - 1
    map<int, int> playersIdAdapter; // [real id 1, ..]->[0, 1, 2]

    // order??

    vector<int> captures;
    vector<int> kills;

    const int numRounds = 15;
    int numTurns;
    int currentTurn;

    int numPlayers;
    int currentPlayer;

    vector<vector<int>> attackMatrix; // {"id" : "whom attack"}
    Map *map;

    Player *player;

    [[nodiscard]] Vehicle *Find(int adaptedPlayerId, const tuple<int, int, int> &spawn) const;

public:
    Game() = default;

    ~Game();

    // init methods
    // all inits must be called firstly!
    void InitMap(int size);

    void InitPlayer(int id, string name, string password = "");

    void InitVariables(int playersNum = 3);

    void InitPlayersId(const int realId[3]);

    // add methods
    void AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn);

    void AddBase(vector<tuple<int, int, int>> &points);

    // get state
    void UpdateState(int currTurn, int currPlayer);

    void UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, vector<int> attacked);

    void UpdateWinPoints(int playerId, int capture, int kill);


    [[nodiscard]] vector<tuple<Action, int, Hex*>> Play() const;

    // get action
    // ...
};
