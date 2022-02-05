#include "actionController.h"

using namespace std;

void ActionController::ReduceModule(int &n, const int amount) {
    for (int i = 0; i < amount; i++) {
        ModuleDecrement(n);
    }
}

void ActionController::IncreaseModule(int &n, const int amount) {
    for (int i = 0; i < amount; i++) {
        ModuleIncrement(n);
    }
}

void ActionController::ModuleDecrement(int &n) {
    if (n == 0) return;
    if (n > 0) n--;
    else
        n++;
}

void ActionController::ModuleIncrement(int &n) {
    //    if (n == 0) return;
    if (n >= 0) n++;
    else
        n--;
}

void Restore(int &x, int &y, int &z, const Point coordinates) {
    x = get<0>(coordinates);
    y = get<1>(coordinates);
    z = get<2>(coordinates);
}

Point ActionController::GetNextOnAxis(Point coordinates, Map *map) {
    auto [x, y, z] = coordinates;
    if (x == 0) {
        ReduceModule(y, 2);
        ReduceModule(z, 2);
    }
    if (y == 0) {
        ReduceModule(x, 2);
        ReduceModule(z, 2);
    }
    if (z == 0) {
        ReduceModule(x, 2);
        ReduceModule(y, 2);
    }
    Point res = make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;

    Restore(x, y, z, coordinates);
    if (x == 0) {
        ReduceModule(y, 2);
        ModuleIncrement(z);
        x = 0 - y - z;
    }
    if (y == 0) {
        ReduceModule(z, 2);
        ModuleIncrement(x);
        y = 0 - x - z;
    }
    if (z == 0) {
        ReduceModule(x, 2);
        ModuleIncrement(y);
        z = 0 - x - y;
    }
    res = make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;

    Restore(x, y, z, coordinates);
    if (x == 0) {
        ReduceModule(z, 2);
        ModuleIncrement(y);
        x = 0 - y - z;
    }
    if (y == 0) {
        ReduceModule(x, 2);
        ModuleIncrement(z);
        y = 0 - x - z;
    }
    if (z == 0) {
        ReduceModule(y, 2);
        ModuleIncrement(x);
        z = 0 - x - y;
    }
    res = make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;


    return make_tuple(-1, -1, -1);// нам не нужно перемещаться
}

Point ActionController::GetTargetForMove(Point coordinates, Map *map) {
    auto [x, y, z] = coordinates;

    if (x == 0 || y == 0 || z == 0)
        return GetNextOnAxis(coordinates, map);

    auto *maxAbs = &x;
    if (abs(*maxAbs) < abs(y)) maxAbs = &y;
    if (abs(*maxAbs) < abs(z)) maxAbs = &z;

    if (*maxAbs == 0 || abs(*maxAbs) == 1)
        return make_tuple(-1, -1, -1);// нам не нужно перемещаться, мы на базе

    ModuleDecrement(x);
    ModuleDecrement(y);
    ModuleDecrement(z);
    ModuleDecrement(*maxAbs);

    Point res = make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;


    Restore(x, y, z, coordinates);


    if (maxAbs == &x) {
        ReduceModule(x, 2);
        y = 0 - x - z;
    }
    if (maxAbs == &y) {
        ReduceModule(y, 2);
        z = 0 - x - y;
    }
    if (maxAbs == &z) {
        ReduceModule(z, 2);
        x = 0 - y - z;
    }

    res = make_tuple(x, y, z);

    if (map->Get(res)->IsEmpty()) return res;

    Restore(x, y, z, coordinates);


    if (maxAbs == &x) {
        ReduceModule(x, 2);
        z = 0 - x - y;
    }
    if (maxAbs == &y) {
        ReduceModule(y, 2);
        x = 0 - y - z;
    }
    if (maxAbs == &z) {
        ReduceModule(z, 2);
        y = 0 - x - z;
    }

    res = make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;

    //    return res;
    return make_tuple(-1, -1, -1);// нам не нужно перемещаться
}

bool ActionController::NeutralityRuleCheck(const std::vector<std::vector<int>> &attackMatrix, int playerId, int enemyId) {
    for (int i = 0; i < attackMatrix.size(); i++) {
        if (i == enemyId) {
            continue;
        }
        for (int j = 0; j < attackMatrix[i].size(); j++) {
            if (attackMatrix[i][j] == enemyId) {// he was attacked
                for (auto id : attackMatrix[enemyId]) {
                    if (id == playerId) {// but he attack us
                        return true;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

std::unordered_map<Vehicle *, vector<Vehicle *>> ActionController::GetPointsForShoot(const std::vector<std::vector<int>> &attackMatrix,
                                                                                     const std::vector<std::vector<Vehicle *>> &vehicles,
                                                                                     int playerId, int playersNum, int playerVehiclesNum) {

    const vector<Vehicle *> &playerVehicles = vehicles[playerId];
    std::unordered_map<Vehicle *, vector<Vehicle *>> res(playerVehiclesNum * (playersNum - 1));
    for (auto &our : playerVehicles) {
        for (auto vect : vehicles) {
            if (vect[0]->GetPlayerId() != playerId)
                continue;
            for (auto enemy : vect) {
                if (our->IsAvailableForShoot(enemy) && NeutralityRuleCheck(attackMatrix, playerId, enemy->GetPlayerId()))
                    res[enemy].push_back(our);
            }
        }
    }

    return res;

    // TODO
    // if we can destroy the enemy - shoot
}
