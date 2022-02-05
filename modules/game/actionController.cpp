#include "actionController.h"

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
    x = std::get<0>(coordinates);
    y = std::get<1>(coordinates);
    z = std::get<2>(coordinates);
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
    Point res = std::make_tuple(x, y, z);
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
    res = std::make_tuple(x, y, z);
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
    res = std::make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;


    return std::make_tuple(-1, -1, -1);// нам не нужно перемещаться
}

Point ActionController::GetTargetForMove(Point coordinates, Map *map) {
    auto [x, y, z] = coordinates;

    if (x == 0 || y == 0 || z == 0)
        return GetNextOnAxis(coordinates, map);

    auto *maxAbs = &x;
    if (abs(*maxAbs) < abs(y)) maxAbs = &y;
    if (abs(*maxAbs) < abs(z)) maxAbs = &z;

    if (*maxAbs == 0 || abs(*maxAbs) == 1)
        return std::make_tuple(-1, -1, -1);// нам не нужно перемещаться, мы на базе

    ModuleDecrement(x);
    ModuleDecrement(y);
    ModuleDecrement(z);
    ModuleDecrement(*maxAbs);

    Point res = std::make_tuple(x, y, z);
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

    res = std::make_tuple(x, y, z);

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

    res = std::make_tuple(x, y, z);
    if (map->Get(res)->IsEmpty()) return res;

    //    return res;
    return std::make_tuple(-1, -1, -1);// нам не нужно перемещаться
}

Point ActionController::GetTargetForShoot(Point coordinates, std::vector<std::vector<int>> attackMatrix,
                                          std::vector<std::vector<Vehicle *>> vehicles, int playerId) {
    return Point(-1, -1, -1);
}// какая-то логика выстрела. если не стрелять - возвращает (-1,-1,-1)


std::vector<int> ActionController::GetPotentialDamage(const std::vector<Vehicle*>& vehicles, const std::vector<Point>& enemyPoints){
    std::vector<int> potentialDamage(10);
    std::vector<bool> buffer;
    for (auto v : vehicles) {
        buffer = v->IsAvailableForShoot(enemyPoints);
        for (int i = 0; i < 10; i++) {
            potentialDamage[i] += buffer[i];
        }
    }
    return potentialDamage;
}

std::vector<Point> ActionController::GetPointsForShoot(const std::vector<std::vector<int>>& attackMatrix, std::vector<std::vector<Vehicle *>> vehicles, int playerId) {
    std::vector<Point> enemyPoints;
    std::vector<Vehicle *> playerVehicles = vehicles[playerId];

    for (auto vect : vehicles) {
        if (vect[0]->GetPlayerId() != playerId) {
            for (auto v : vect) {
                enemyPoints.push_back(v->GetCurrentPosition());
            }
        }
    }

    std::vector<int> potentialDamage = GetPotentialDamage(playerVehicles, enemyPoints);

    // TODO
    // check the rule of neutrality using attackMatrix
    // if we can destroy the enemy - shoot
    // if vehicle doesn't shoot res[id] = (-1,-1,-1)
    // else res[id] = current position of target vehicle

    std::vector<Point> res(5);
    return res;
}
