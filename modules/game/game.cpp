#include "game.h"

using namespace std;
using namespace VehiclesTypes;

Vehicle *Game::Find(int adaptedPlayerId, const Point &spawn) const {
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

void Game::InitVariables(int playersNum) {
    numPlayers = playersNum;
    numTurns = numRounds * numPlayers;
    currentTurn = 0;

    vehicles.resize(playersNum);
    attackMatrix.resize(playersNum);
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
    for (int i = 0; i < VehiclesTypes::TypesNum; i++) {
        auto &tanks = realId.at(VehiclesTypes::s_types[i]);
        // q: is there more than one access?
        for (const auto &id : tanks) {
            tanksIdAdapter[next++] = id;
        }
    }
}

// Add

void Game::AddVehicle(int playerId, Type type, tuple<int, int, int> spawn) {
    // there choose type of tanks
    Vehicle* t;
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
    t->InitSpawn(map->Get(spawn));
    vehicles[playerId].push_back(t);// there player id passed from 0 to 2 (GameClient)
}

// get state
void Game::UpdateState(int currTurn, int currPlayer, bool finished) {
    currentTurn = currTurn;
    currentPlayerId = currPlayer;
    isFinished = finished;
}

void Game::UpdateVehicleState(int parentId, Point spawn, Point pos, int health,
                              int capturePoints) {
    Vehicle *v = Find(playersIdAdapter.at(parentId), spawn);
    v->Update(health, map->Get(pos), capturePoints);
}

void Game::UpdateWinPoints(int playerId, int capture, int kill) {
    int adaptedPlayerId = playersIdAdapter.at(playerId);
    captures[adaptedPlayerId] = capture;
    kills[adaptedPlayerId] = kill;
}

bool TargetIsAvailable(const Point *target) {
    auto [x, y, z] = *target;
    return !(x == -1 && y == -1 && z == -1);
}

vector<tuple<Action, int, Hex *>> Game::Play() const {
    Point targetPoint = make_tuple(0, 0, 0);
    vector<tuple<Action, int, Hex *>> res;
    Point target;
    const auto& playerVehicles = vehicles[playersIdAdapter.at(player->GetId())];

    vector<multimap<int, Point>> priorityMoveTargets(numPlayerVehicles);

    for(int i = 0; i < numPlayerVehicles; i++) {
        // TODO: There will be another check for danger
        if(!map->IsBasePoint(playerVehicles[i]->GetCurrentPosition()))
            priorityMoveTargets[i] = move(playerVehicles[i]->GetAvailableMovePoints(targetPoint));
    }

    unordered_map<Vehicle*, vector<Vehicle*>> priorityShootTargets =
            move(ActionController::GetPointsForShoot(attackMatrix, vehicles,
                                                     playersIdAdapter.at(player->GetId()),
                                                     numPlayers, numPlayerVehicles));

    ProcessAttackPossibility(priorityShootTargets); // Check if it's ok

    // TODO! Shoot -> Move
    bool round = false;
    for(int i = 0; i < numPlayerVehicles;) {
        auto* current = playerVehicles[i];
        bool satisfied = false;
        if (current->PriorityAction() == Action::MOVE) {
            for (auto& [_, p] : priorityMoveTargets[i]) {
                auto* point = map->Get(p);
                if (point->IsEmpty()) {
                    res.emplace_back(Action::MOVE, tanksIdAdapter[i], point);
                    satisfied = true;
                    point->Occupy();
                    break;
                }
            }
        }
        if (!satisfied && current->PriorityAction() == Action::SHOOT) {
            if (!priorityShootTargets.at(current).empty()) {
                // TODO: priority.
                for (auto* vToAttack : priorityShootTargets.at(current)) {
                    if (vToAttack->IsAlive()) {
                        vToAttack->GetHit();
                        satisfied = true;
                        break;
                    }
                }
            }
        }

        if (satisfied) {
            i++;
            round = false;
        }
        else {
            round = true;
        }
    }

    return res;
}

// TODO! priority
void Game::ProcessAttackPossibility(unordered_map<Vehicle *, vector<Vehicle *>> &priorityShootTargets) {
    for(auto& [attackedV, playerV] : priorityShootTargets) {
        if (attackedV->GetHp() > playerV.size())
            continue;
        for (auto* v : playerV) {
            priorityShootTargets[v].push_back(attackedV);
        }
    }
}

