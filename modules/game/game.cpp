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

Game::Game(int playerId, std::string name, std::string password, int playersNum) {
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
    tanksIdAdapter.resize(numPlayerVehicles);
}

void Game::InitPlayersId(const vector<int> &realId) {
    for (int i = 0; i < realId.size(); i++) {
        playersIdAdapter[realId[i]] = i;
    }
}

void Game::InitVehiclesIds(int playerId, const unordered_map<std::string, vector<int>> &realId) {
    if (playerId != player->GetId())
        return;
    int next = 0;
    for (int i = 0; i < VehiclesTypes::typesNum; i++) {
        auto &tanks = realId.at(VehiclesTypes::sTypes[i]);
        for (const auto &id : tanks) {
            tanksIdAdapter[next++] = id;
        }
    }
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

bool TargetIsAvailable(const Point3D *target) {
    auto [x, y, z] = *target;
    return !(x == -1 && y == -1 && z == -1);
}

vector<tuple<Action, int, Point3D>> Game::Play() const {
    Point3D targetPoint{-3, 10, -7};
    vector<tuple<Action, int, Point3D>> res;
    const auto &playerVehicles = vehicles[playersIdAdapter.at(player->GetId())];

    std::vector<std::vector<Hex *>> paths(numPlayerVehicles);

    for (int i = 0; i < numPlayerVehicles; i++) {
        // TODO: There will be another check for danger
        if (map->IsBasePoint(playerVehicles[i]->GetCurrentPosition()) == false)
        paths[i] = std::move(this->map->GetShortestWay(*playerVehicles[i]->GetCurrentHex(), *map->GetHexByPoint(targetPoint)));
    }

    unordered_map<Vehicle *, vector<Vehicle *>> priorityShootTargets =
            move(ActionController::GetPointsForShoot(attackMatrix, vehicles,
                                                     playersIdAdapter.at(player->GetId()),
                                                     numPlayers));

    ProcessAttackPossibility(priorityShootTargets);// Check if it's ok

    bool round = false;
    for (int i = 0; i < numPlayerVehicles;) {
        auto *currentVehicle = playerVehicles[i];
        bool satisfied = false;
        if (currentVehicle->PriorityAction() == Action::MOVE || round) {
            auto hex = currentVehicle->GetAvailableMovePoint(paths[i]);
            if(hex != nullptr) {
                res.emplace_back(Action::MOVE, tanksIdAdapter[i], hex->GetCoordinates());
                satisfied = true;
                hex->Occupy();
            }
        }
        if (!satisfied && !priorityShootTargets.empty() && currentVehicle->PriorityAction() == Action::SHOOT) {
            if (!priorityShootTargets[currentVehicle].empty()) {
                // TODO: priority.
                for (auto *vToAttack : priorityShootTargets.at(currentVehicle)) {
                    if (vToAttack->IsAlive()) {
                        vToAttack->GetHit();
                        satisfied = true;
                        res.emplace_back(Action::SHOOT, tanksIdAdapter[i], playerVehicles[i]->Shoot(vToAttack));

                        break;
                    }
                }
            }
        }

        if (satisfied || round) {
            i++;
            round = false;
        } else {
            round = true;
        }
    }
    return res;
}

// TODO! priority
void Game::ProcessAttackPossibility(unordered_map<Vehicle *, vector<Vehicle *>> &priorityShootTargets) {
    for (auto &[attackedV, playerV] : priorityShootTargets) {
        if (attackedV->GetHp() > playerV.size())
            continue;
        for (auto *v : playerV) {
            priorityShootTargets[v].push_back(attackedV);
        }
    }
}
Map *Game::GetMap() const {
    return map;
}
const vector<std::vector<Vehicle *>> &Game::GetVehicles() const {
    return vehicles;
}
