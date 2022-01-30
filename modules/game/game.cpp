
#include "game.h"
#include "action_controller.h"

using namespace std;

Vehicle *Game::Find(int parentId, const tuple<int, int, int> &spawn) const {
    for (auto *p: vehicles[parentId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}

Game::Game() {}

Game::~Game() {}

void Game::InitMap(int size) {
    map = new Map(size);
}

void Game::AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn) {
    Vehicle *t = new Vehicle(type, playerId);
    t->InitSpawn(map->Get(spawn));
    vehicles[playerId].push_back(t);
}

void Game::AddBase(vector<tuple<int, int, int>> &points) {
    map->AddBase(points);
}

void Game::InitPlayer(int id, string name, string password) {
    player = new Player(id, name, password);
}

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum + 1);
    attackMatrix.resize(playersNum + 1);
    captures.resize(playersNum + 1);
    kills.resize(playersNum + 1);
}

// get state
void Game::UpdateState(int currTurn, int currPlayer) {
    currentTurn = currTurn;
    currentPlayer = currPlayer;
}

void Game::UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                              int capturePoints) {
    Vehicle *v = Find(parentId, spawn);
    v->Update(health, map->Get(pos), capturePoints);
}

void Game::UpdateAttackMatrix(int playerId, vector<int> attacked) {
    attackMatrix[playerId] = move(attacked);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    captures[playerId] = capture;
    kills[playerId] = kill;
}

bool TargetIsAvailable(const tuple<int, int, int> *target) {
    auto[x, y, z] = *target;
    return x != -1 && y != -1 && z != -1;
}

vector<tuple<int, int, Hex *>> Game::Play() {
    vector<tuple<int, int, Hex *>> res;
    tuple<int, int, int> target;
    auto v = vehicles[playersIdAdapter[player->GetId()]];

    for (int i = 0; i < 5; i++) {
        target = ActionController::getTargetForMove(v[i]->GetCurrentPosition(), map);
        if (TargetIsAvailable(&target)) {
            res.emplace_back(101, tanksIdAdapter[i], map->Get(target));
        } else {
            target = ActionController::getTargetForShoot(v[i]->GetCurrentPosition(), &attackMatrix, vehicles,
                                                         playersIdAdapter[player->GetId()]);
            if (TargetIsAvailable(&target)) {
                res.emplace_back(102, tanksIdAdapter[i], map->Get(target));
            }
        }
    }

    return res;
}

// get action
