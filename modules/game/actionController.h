#pragma once

#include "map/hex.h"
#include "map/map.h"
#include <cstdlib>
#include <iostream>
#include <unordered_map>

class ActionController {
private:
    static void ModuleDecrement(int &n);

    static void ModuleIncrement(int &n);

    static void ReduceModule(int &n, int amount);

    static void IncreaseModule(int &n, int amount);


public:
    static Point GetTargetForMove(Point coordinates, Map *map);

    static Point GetNextOnAxis(Point coordinates, Map *map);

    static std::vector<bool>
    NeutralityRuleCheck(const std::vector<std::vector<int>> &attackMatrix, int playerId, int playersNum);

    static std::unordered_map<Vehicle *, std::vector<Vehicle *>>
    GetPointsForShoot(const std::vector<std::vector<int>> &attackMatrix,
                      const std::vector<std::vector<Vehicle *>> &vehicles,
                      int playerId, int playersNum = 3);
};
