#ifndef PIGS_ON_THE_MOON_GAME_GAME_H
#define PIGS_ON_THE_MOON_GAME_GAME_H

#include <tuple>
#include <map>
#include <vector>
#include <string>
#include "actionController.h"
#include "../actors/vehicle.h"
#include "../actors/player.h"
#include "../map/map.h"
#include "../enums/action.h"

using namespace std;

class Game {
private:
    vector<int> state;
    vector<vector<Vehicle *>> vehicles;

    // new: custom id start from 0 to numPlayers - 1
    map<int, int> playersIdAdapter; // [real id 1, ..]->[0, 1, 2]
    vector<int> tanksIdAdapter; // save real id for server

    // order??

    vector<int> captures;
    vector<int> kills;

    const int numRounds = 15;

    int numTurns;
    int currentTurn;

    int numPlayers;
    int currentPlayerId;

    bool isFinished = false;

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

    void InitPlayersId(const vector<int>& realId);

    void InitVehiclesIds(int playerId, const vector<int>& realId);

    // add methods
    void AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn);

    void AddBase(vector<tuple<int, int, int>> &points);

    // get state
    void UpdateState(int currTurn, int currPlayer, bool finished = false);

    void UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                            int capturePoints);

    void UpdateAttackMatrix(int playerId, vector<int> attacked);

    void UpdateWinPoints(int playerId, int capture, int kill);


    [[nodiscard]] vector<tuple<Action, int, Hex*>> Play() const;

    // get action
    // ...

    // Getters

    [[nodiscard]] int GetNumPlayers() const;

    [[nodiscard]] bool IsFinished() const;
};



#endif //PIGS_ON_THE_MOON_GAME_GAME_H