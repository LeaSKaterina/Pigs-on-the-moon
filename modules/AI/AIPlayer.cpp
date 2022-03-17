#include "AIPlayer.h"

using namespace std;

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
    const vector<unique_ptr<Vehicle>> &playerVehicles = v[playerId];

    vector<bool> canAttack = NeutralityRuleCheck(playerId);
    std::unordered_map<Vehicle *, vector<Vehicle *>> res;// key - enemy tank, value - who can attack
    for (auto &our : playerVehicles) {
        for (int i = 0; i < v.size(); i++) {
            if (v[i][0]->GetPlayerId() == playerId || !canAttack[i])
                continue;
            for (auto& enemy : v[i]) {
                if (our->IsAvailableToShoot(enemy->GetCurrentPosition())) {
                    if (our->GetType() != VehiclesTypes::Type::AT_SPG ||
                        !game->GetMap()->HasObstacleBetween(*(our->GetCurrentHex()), (*enemy->GetCurrentHex())))
                        res[enemy.get()].push_back(our.get());
                }
            }
        }
    }

    return res;
}

int AIPlayer::GetPossibleDamageForPoint(const Point3D &point3D) const {
    int res = 0;
    vector<bool> canAttack = NeutralityRuleCheck(game->GetAdaptedPlayerId());
    for (int i = 0; i < game->GetNumPlayers(); i++) {
        if (canAttack[i]) {
            for (auto& vehicle : game->GetVehicles(i, true)) {
                if (vehicle->IsAvailableToShoot(point3D)) {
                    if (vehicle->GetType() != VehiclesTypes::Type::AT_SPG ||
                        !game->GetMap()->HasObstacleBetween(*(vehicle->GetCurrentHex()),
                                                            *(game->GetMap()->GetHexByPoint(point3D))))
                        res++;
                }
            }
        }
    }
    return res;
}

bool AIPlayer::CanDieOnPoint(const Vehicle &vehicle, const Point3D &point3D) const {
    return vehicle.GetHp() <= GetPossibleDamageForPoint(point3D);
}
