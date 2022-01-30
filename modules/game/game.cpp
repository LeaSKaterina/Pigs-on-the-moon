
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
// There
void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
}

void Game::InitPlayersId(const vector<int>& realId) {
    for(int i = 0; i < realId.size(); i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

void Game::InitVehiclesIds(int playerId, const vector<int> &realId) {
    if(playerId != player->GetId())
        return;
    // TODO _
    for (int i = 0; i < realId.size() && i < numPlayers; i++) {
        tanksIdAdapter[i] = realId[i];
    }
}

// Add

void Game::AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn) {
    Vehicle *t = new Vehicle(type, playerId);
    t->InitSpawn(map->Get(spawn));
    vehicles[playerId].push_back(t); // there player id passed from 0 to 2 (GameClient)
}

void Game::AddBase(vector <tuple<int, int, int>> &points) {
    map->AddBase(points);
}

// Update

// get state
void Game::UpdateState(int currTurn, int currPlayer, bool finished) {
    currentTurn = currTurn;
    currentPlayer = currPlayer;
    isFinished = finished;
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

bool TargetIsAvailable(const tuple<int, int, int> *target) {
    auto[x, y, z] = *target;
    return x != -1 && y != -1 && z != -1;
}

vector<tuple<Action, int, Hex *>> Game::Play() const {
    vector<tuple<Action, int, Hex *>> res;
    tuple<int, int, int> target;
    auto v = vehicles[playersIdAdapter.at(player->GetId())];

    for (int i = 0; i < 5; i++) {
        target = ActionController::getTargetForMove(v[i]->GetCurrentPosition(), map);
        if (TargetIsAvailable(&target)) {
            res.push_back(std::make_tuple(Action::MOVE, tanksIdAdapter[i], map->Get(target)));
//            res.emplace_back(std::make_tuple(Action::MOVE, tanksIdAdapter[i], map->Get(target)));
        } else {
            target = ActionController::getTargetForShoot(v[i]->GetCurrentPosition(), attackMatrix, vehicles,
                                                         playersIdAdapter.at(player->GetId()));
            if (TargetIsAvailable(&target)) {
                res.emplace_back(Action::SHOOT, tanksIdAdapter[i], map->Get(target));
            }
        }
    }

    return res;
//    return vector<tuple<Action, int, Hex *>>();
}

int Game::GetNumPlayers() const {
    return numPlayers;
}

bool Game::IsFinished() const {
    return isFinished;
}

// get action
