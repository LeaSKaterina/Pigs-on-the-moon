
#include "game.h"
#include "action_controller.h"

using namespace std;

Vehicle *Game::Find(int adaptedPlayerId, const tuple<int, int, int> &spawn) const {
    for (auto *p: vehicles[adaptedPlayerId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}

Game::~Game() {
    // TODO!
    delete player;
    delete map;
    // vehicles?
}
// Init

void Game::InitMap(int size) {
    map = new Map(size);
}


void Game::InitPlayer(int id, string name, string password) {
    player = new Player(id, name, password);
}

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
}

void Game::InitPlayersId(const int realId[3]) { // magic const will be removed later
    for(int i = 0; i < numPlayers; i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

// Add

void Game::AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn) {
    Vehicle *t = new Vehicle(type, playerId);
    t->InitSpawn(map->Get(spawn));
    vehicles[playersIdAdapter.at(playerId)].push_back(t);
}

void Game::AddBase(vector <tuple<int, int, int>> &points) {
    map->AddBase(points);
}

// Update

// get state
void Game::UpdateState(int currTurn, int currPlayer) {
    currentTurn = currTurn;
    currentPlayer = currPlayer;
}

void Game::UpdateVehicleState(int parentId, tuple<int, int, int> spawn, tuple<int, int, int> pos, int health,
                              int capturePoints) {
    Vehicle *v = Find(playersIdAdapter.at(parentId), spawn);
    v->Update(health, map->Get(pos), capturePoints);
}

void Game::UpdateAttackMatrix(int playerId, vector<int> attacked) {
    attackMatrix[playersIdAdapter.at(playerId)] = move(attacked);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    int adaptedPlayerId = playersIdAdapter.at(playerId);
    captures[adaptedPlayerId] = capture;
    kills[adaptedPlayerId] = kill;
}

vector<tuple<Action, int, Hex *>> Game::Play() const {
    // TODO!
    return vector<tuple<Action, int, Hex *>>();
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
