#include "game.h"

Vehicle *Game::Find(int parentId, const tuple<int, int, int> &spawn) const {
    for (auto *p: vehicles[parentId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}


int Game::GetCustomId(int realId) const { // for 3 players it can be more effective that with std::map
    for(int id = 0; id < numPlayers; id++)
        if(playersIdAdapter[id] == realId)
            return id;
    return -1;
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

//    playersNum++; // Think we can do this without += 1.
    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
    playersIdAdapter.resize(playersNum);
}

void Game::InitPlayersId(const int realId[3]) { // magic const will be fixed later
    // TODO! if in InitVariables resize without +=1 there i = 0.
    for(int i = 0; i < numPlayers; i++) {
        playersIdAdapter[i] = realId[i];
    }
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

vector<tuple<Action, int, Hex *>> Game::Play() const {
    // TODO!
    return vector<tuple<Action, int, Hex *>>();
}

// get action
