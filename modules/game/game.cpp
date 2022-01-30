#include "game.h"

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

// get action
