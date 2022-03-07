#include "actionController.h"

using namespace std;


//method analyze attackMatrix and return vector<bool>. If v[i] = true - we can attack i player
vector<bool> ActionController::NeutralityRuleCheck(const std::vector<std::vector<bool>> &attackMatrix, int playerId) {
    vector<bool> canAttack(attackMatrix.size(), true);// return vector. Default we can attack anyone.
    canAttack[playerId] = false;
    // check
    for (int i = 0; i < attackMatrix.size(); i++) {// consider who i is attacking
        if (i == playerId)
            continue;
        for (int j = 0; j < attackMatrix[i].size(); j++) {
            if (i == j || j == playerId)// we can skip j == playerId because canAttack[i] = true default
                continue;
            if (attackMatrix[i][j]) {                    // j is the last enemy (third player). If true - i attacks j player.
                canAttack[j] = attackMatrix[j][playerId];// And if j don't attack us - we can't attack him.
                break;
            }
        }
    }

    return canAttack;
}

std::unordered_map<Vehicle *, vector<Vehicle *>>
ActionController::GetPointsForShoot(const vector<vector<bool>> &attackMatrix,
                                    const vector<vector<Vehicle *>> &vehicles,
                                    const Map* map,
                                    int playerId) {
    const vector<Vehicle *> &playerVehicles = vehicles[playerId];

    vector<bool> canAttack = move(NeutralityRuleCheck(attackMatrix, playerId));
    std::unordered_map<Vehicle *, vector<Vehicle *>> res; // key - enemy tank, value - who can attack
    for (auto &our : playerVehicles) {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i][0]->GetPlayerId() == playerId || !canAttack[i])
                continue;
            for (auto enemy : vehicles[i]) {
                if (our->IsAvailableForShoot(enemy)) {
                    if (our->GetType() != VehiclesTypes::Type::AT_SPG
                        || !map->HasObstacleBetween(*(our->GetCurrentHex()), (*enemy->GetCurrentHex())))
                        res[enemy].push_back(our);
                }
            }
        }
    }

    return res;
}
