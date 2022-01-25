#pragma once

#include <tuple>
#include <vector>
#include <string>
#include "actors\vehicle.h"
#include "map\map.h"
#include "actors\player.h"

using namespace std;

class Game {
private:
    vector<int> state;
    vector <vector<Vehicle *>> vehicles;

    vector<int> captures;
    vector<int> kills;

    const int numRounds = 15;
    int numTurns;
    int currentTurn;

    int numPlayers;
    int currentPlayer;

    vector <vector<int>> attackMatrix; // {"id" : "whom attack"}
    Map *map;

    Player *player;

    Vehicle *Find(int parentId, const tuple<int, int, int> &spawn) const {
        for (auto *p: vehicles[parentId]) {
            if (p->GetSpawn() == spawn)
                return p;
        }
        return nullptr;
    }

public:
    Game() {}

    ~Game() {}

    void InitMap(int size) {
        map = new Map(size);
    }

    void AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn) {
        Vehicle *t = new Vehicle(type, playerId);
        t->initSpawn(map->get(spawn));
        vehicles[playerId].push_back(t);
    }

    void AddBase(vector <tuple<int, int, int>> &points) {
        map->AddBase(points);
    }

    void InitPlayer(int id, string name, string password = "") {
        player = new Player(id, name, password);
    }

    void InitVariables(int playersNum = 3) {
        numPlayers = playersNum;
        numTurns = numRounds * numPlayers;
        currentTurn = 0;

        vehicles.resize(playersNum + 1);
        attackMatrix.resize(playersNum + 1);
        captures.resize(playersNum + 1);
        kills.resize(playersNum + 1);
    }

    // get state
    void UpdateState(int currTurn, int currPlayer) {
        currentTurn = currTurn;
        currentPlayer = currPlayer;
    }

    void UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                            int capturePoints) {
        Vehicle *v = Find(parentId, spawn);
        v->Update(health, map->Get(pos), capturePoints);
    }

    void UpdateAttackMatrix(int playerId, vector<int> attacked) {
        attackMatrix[playerId] = move(attacked);
    }

    void UpdateWinPoints(int playerId, int capture, int kill) {
        captures[playerId] = capture;
        kills[playerId] = kill;
    }
    // get action

};
