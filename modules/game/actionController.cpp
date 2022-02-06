#include "actionController.h"

using namespace std;

// TODO
vector<bool> ActionController::NeutralityRuleCheck2(const std::vector<std::vector<bool>> &attackMatrix, int playerId, int playersNum) {
    vector<bool> canAttack;
    canAttack.reserve(playersNum);
    for (int i = 0; i < playersNum; i++) {
        canAttack.push_back(true);
    }
    canAttack[playerId] = false;

    for (int i = 0; i < attackMatrix.size(); i++) {
        for (int j = 0; j < attackMatrix[i].size(); j++) {
            if (i == j || i == playerId)
                continue;
            if (attackMatrix[i][j]) {
                if (j == playerId)
                    break;
                canAttack[j] = attackMatrix[j][playerId];
                break;
            }
        }
    }
    return canAttack;
}

vector<bool>
ActionController::NeutralityRuleCheck(const std::vector<std::vector<int>> &attackMatrix, int playerId, int playersNum) {
    vector<bool> canAttack(playersNum);
    for (int enemyId = 0; enemyId < playersNum; enemyId++) {
        if (enemyId == playerId) {
            continue;
        }

        canAttack[enemyId] = true;
        for (int i = 0; i < attackMatrix.size(); i++) {
            if (i == enemyId) {
                continue;
            }
            for (int j = 0; j < attackMatrix[i].size(); j++) {
                if (attackMatrix[i][j] == enemyId) {// he was attacked
                    for (auto id : attackMatrix[enemyId]) {
                        if (id == playerId) {// but he attack us
                            break;
                        }
                    }
                    canAttack[enemyId] = false;
                    break;
                }
            }
        }
    }
    return canAttack;
}

std::unordered_map<Vehicle *, vector<Vehicle *>>
ActionController::GetPointsForShoot(const vector<vector<int>> &attackMatrix,
                                    const vector<vector<Vehicle *>> &vehicles,
                                    int playerId, int playersNum) {

    const vector<Vehicle *> &playerVehicles = vehicles[playerId];
    vector<bool> canAttack(playersNum);
    canAttack = move(NeutralityRuleCheck(attackMatrix, playerId, playersNum));
    std::unordered_map<Vehicle *, vector<Vehicle *>> res;
    for (auto &our : playerVehicles) {
        for (int i = 0; i < vehicles.size(); i++) {
            if (vehicles[i][0]->GetPlayerId() == playerId || !canAttack[i])
                continue;
            for (auto enemy : vehicles[i]) {
                if (our->IsAvailableForShoot(enemy))
                    res[enemy].push_back(our);
            }
        }
    }

    return res;
}
