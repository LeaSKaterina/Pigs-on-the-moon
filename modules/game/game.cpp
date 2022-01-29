#include "game.h"

Vehicle *Game::Find(int parentId, const tuple<int, int, int> &spawn) const {
    for (auto *p: vehicles[parentId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}

Game::Game() = default;

Game::~Game() {
    // TODO!
    delete player;
    delete map;
    // vehicles?
}
// Init

// all inits must be called firstly!
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

    vehicles.resize(playersNum + 1);
    attackMatrix.resize(playersNum + 1);
    captures.resize(playersNum + 1);
    kills.resize(playersNum + 1);
}

// Add

void Game::AddVehicle(int playerId, Vehicle::Type type, tuple<int, int, int> spawn) {
    Vehicle *t = new Vehicle(type, playerId);
    t->InitSpawn(map->Get(spawn));
    vehicles[playerId].push_back(t);
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

// get action