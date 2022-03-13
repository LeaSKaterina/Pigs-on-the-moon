#include "AIPlayer.h"

using namespace std;

vector<tuple<Action, int, Point3D>> AIPlayer::Play() const {
    Point3D targetPoint{0, 0, 0};
    vector<tuple<Action, int, Point3D>> res;
    const auto &playerVehicles = game->GetVehicles(game->GetAdaptedPlayerId());

    std::vector<std::vector<Hex *>> paths(game->GetPlayerVehiclesNum());

    const auto *map = game->GetMap();
    for (int i = 0; i < game->GetPlayerVehiclesNum(); i++) {
        // TODO: There will be another check for danger

        if (!map->IsBasePoint(playerVehicles[i]->GetCurrentPosition()))
            paths[i] = map->GetShortestWay(
                    *playerVehicles[i]->GetCurrentHex(),
                    *map->GetHexByPoint(targetPoint));
    }

    unordered_map<Vehicle *, vector<Vehicle *>> priorityShootTargets =
            move(GetPointsForShoot(game->GetAdaptedPlayerId()));

    ProcessAttackPossibility(priorityShootTargets);// Check if it's ok

    bool round = false;
    for (int i = 0; i < game->GetPlayerVehiclesNum();) {
        auto *currentVehicle = playerVehicles[i];
        bool satisfied = false;
        if (currentVehicle->PriorityAction() == Action::MOVE || round) {
            auto hex = currentVehicle->GetAvailableMovePoint(paths[i]);
            if (hex != nullptr) {
                res.emplace_back(Action::MOVE, game->GetVehicleServerId(i), hex->GetCoordinates());
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
                        res.emplace_back(Action::SHOOT, game->GetVehicleServerId(i), currentVehicle->Shoot(*vToAttack));
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


void AIPlayer::ProcessAttackPossibility(unordered_map<Vehicle *, vector<Vehicle *>> &priorityShootTargets) {
    for (auto &[attackedV, playerV] : priorityShootTargets) {
        if (attackedV->GetHp() > playerV.size())
            continue;
        for (auto *v : playerV) {
            priorityShootTargets[v].push_back(attackedV);
        }
    }
}

//method analyze attackMatrix and return vector<bool>. If v[i] = true - we can attack i player
vector<bool> AIPlayer::NeutralityRuleCheck(int playerId) const {
    auto &am = game->GetAttackMatrix();
    vector<bool> canAttack(am.size(), true);// return vector. Default we can attack anyone.
    canAttack[playerId] = false;
    // check
    for (int i = 0; i < am.size(); i++) {// consider who i is attacking
        if (i == playerId)
            continue;
        for (int j = 0; j < am[i].size(); j++) {
            if (i == j || j == playerId)// we can skip j == playerId because canAttack[i] = true default
                continue;
            if (am[i][j]) {                    // j is the last enemy (third player). If true - i attacks j player.
                canAttack[j] = am[j][playerId];// And if j don't attack us - we can't attack him.
                break;
            }
        }
    }
    return canAttack;
}

std::unordered_map<Vehicle *, vector<Vehicle *>>
AIPlayer::GetPointsForShoot(int playerId) const {
    auto &v = game->GetVehicles();
    const vector<Vehicle *> &playerVehicles = v[playerId];

    vector<bool> canAttack = NeutralityRuleCheck(playerId);
    std::unordered_map<Vehicle *, vector<Vehicle *>> res;// key - enemy tank, value - who can attack
    for (auto &our : playerVehicles) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i][0]->GetPlayerId() == playerId || !canAttack[i])
                continue;
            for (auto enemy : v[i]) {
                if (our->IsAvailableForShoot(enemy)) {
                    if (our->GetType() != VehiclesTypes::Type::AT_SPG ||
                        !game->GetMap()->HasObstacleBetween(*(our->GetCurrentHex()), (*enemy->GetCurrentHex())))
                        res[enemy].push_back(our);
                }
            }
        }
    }

    return res;
}

