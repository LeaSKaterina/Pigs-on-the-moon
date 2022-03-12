#include "game.h"

using namespace std;
using namespace VehiclesTypes;

Vehicle *Game::FindVehicle(int adaptedPlayerId, const Point3D &spawn) const {
    for (auto *p : vehicles[adaptedPlayerId]) {
        if (p->GetSpawn() == spawn)
            return p;
    }
    return nullptr;
}

Game::~Game() {
    delete player;
    delete map;
    for (auto &vehicle : vehicles) {
        for (auto v : vehicle) {
            delete v;
        }
    }
}

Game::Game(int playerId, std::string name, std::string password, int playersNum,
           const nlohmann::ordered_json &mapInfo,
           const nlohmann::ordered_json &gameState) {
    player = new Player(playerId, std::move(name), std::move(password));
    InitVariables(playersNum);
}

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
    for (auto &v : attackMatrix)
        v.resize(playersNum);
    captures.resize(playersNum);
    kills.resize(playersNum);
}

void Game::InitPlayersId(const vector<int> &realId) {
    for (int i = 0; i < realId.size(); i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

void Game::InitVehiclesIds(int playerId, const unordered_map<std::string, vector<int>> &realId) {
    std::vector<int> tanksIdAdapter(5);
    if (playerId != player->GetId())
        return;
    int next = 0;
    for (int i = 0; i < VehiclesTypes::typesNum; i++) {
        auto &tanks = realId.at(VehiclesTypes::sTypes[i]);
        for (const auto &id : tanks) {
            tanksIdAdapter[next++] = id;
        }
    }
    player->SetIdAdapter(std::move(tanksIdAdapter));
}

// Add

void Game::AddVehicle(int playerId, Type type, Point3D spawn) {
    // there choose type of tanks
    Vehicle *t;
    switch (type) {
        case MEDIUM_TANK:
            t = new MediumTank(playerId);
            break;
        case LIGHT_TANK:
            t = new LightTank(playerId);
            break;
        case HEAVY_TANK:
            t = new HeavyTank(playerId);
            break;
        case AT_SPG:
            t = new AtSpg(playerId);
            break;
        case SPG:
            t = new Spg(playerId);
    }
    t->InitSpawn(map->GetHexByPoint(spawn));
    vehicles[playerId].push_back(t);// there player id passed from 0 to 2 (GameClient)
}

// get state
void Game::UpdateState(int currTurn, int currPlayer, bool finished) {
    currentTurn = currTurn;
    currentPlayerId = currPlayer;
    isFinished = finished;
}

void Game::UpdateVehicleState(int parentId, Point3D spawn, Point3D pos, int health,
                              int capturePoints) {
    Vehicle *v = FindVehicle(playersIdAdapter.at(parentId), spawn);
    v->Update(health, map->GetHexByPoint(pos), capturePoints);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    int adaptedPlayerId = playersIdAdapter.at(playerId);
    captures[adaptedPlayerId] = capture;
    kills[adaptedPlayerId] = kill;
}

void Game::UpdateAttackMatrix(int playerId, const std::vector<int> &attacked) {
    int customId = playersIdAdapter.at(playerId);
    for (int i = 0; i < numPlayers; i++) {
        attackMatrix[customId][i] = false;
    }

    for (const int &i : attacked) {
        attackMatrix[customId][playersIdAdapter.at(i)] = true;
    }
}

Map *Game::GetMap() const {
    return map;
}
const std::vector<Vehicle *> &Game::GetVehicles(int playerId, bool adapted) const {
    return vehicles[(adapted ? playerId : playersIdAdapter.at(playerId))];
}